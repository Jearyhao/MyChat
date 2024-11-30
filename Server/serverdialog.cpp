#include "serverdialog.h"
#include "ui_serverdialog.h"

ServerDialog::ServerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ServerDialog)
{
    if (tcpServer.listen(QHostAddress::Any, port)) {
        qDebug() << "Server started on port" << port;
        timer.start(3000);
    } else {
        qDebug() << "Server failed to start: " << tcpServer.errorString();
    }
    ui->setupUi(this);
    //当客户端向服务器发送连接请求，发送信号:newConnection(Qt里面封装好的信号)
    connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    timer.start(3000);
    connect(&timer, SIGNAL(timeout()), SLOT(onTimeout()));
    //ui->portEdit->setPlaceholderText("请输入端口号：");
}

ServerDialog::~ServerDialog()
{
    delete ui;
}


void ServerDialog::onNewConnection()
{
    QTcpSocket* tcpClient = tcpServer.nextPendingConnection();
    //connect(tcpClient, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(tcpClient, &QTcpSocket::readyRead, this, &ServerDialog::onReadyRead);
    connect(tcpClient, &QTcpSocket::disconnected, this, &ServerDialog::onClientDisconnected);
}
void ServerDialog::onReadyRead()
{
    QTcpSocket* tcpClient = qobject_cast<QTcpSocket*>(sender());
    if (tcpClient) {
        QByteArray data = tcpClient->readAll();
        qDebug() << "Received data from client:" << data;
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject json = doc.object();
        if (json.contains("kind")) {
            QString kind = json["kind"].toString();

            // 处理用户登录，记录用户ID和套接字的映射
            if (kind == "login") {
                QString userId = json["id"].toString();
                socketHash[userId] = tcpClient;

                // 在 listWidget 上显示登录信息
                //ui->listWidget->addItem(QString("用户 %1 已登录").arg(userId));

                return;
            }

            // 处理添加好友请求
            if (kind == "addfriend") {
                QString userId = json["user_id"].toString();
                QString friendId = json["friend_id"].toString();

                // 执行添加好友的逻辑，更新数据库
                QSqlQuery query;
                // 检查用户是否已经存在好友关系
                query.prepare("SELECT relationship_id FROM relationship WHERE user_id = :user_id AND friend_id = :friend_id");
                query.bindValue(":user_id", userId);
                query.bindValue(":friend_id", friendId);
                if (!query.exec()) {
                    qDebug() << "查询好友关系失败：" << query.lastError().text();
                    // 向请求方发送失败消息
                    QJsonObject response;
                    response["kind"] = "addfriend_response";
                    response["status"] = "failed";
                    response["message"] = "查询好友关系失败";
                    QJsonDocument responseDoc(response);
                    tcpClient->write(responseDoc.toJson());
                    return;
                }

                if (query.next()) {
                    // 已经是好友关系
                    QJsonObject response;
                    response["kind"] = "addfriend_response";
                    response["status"] = "failed";
                    response["message"] = "你们已经是好友关系";
                    QJsonDocument responseDoc(response);
                    tcpClient->write(responseDoc.toJson());
                    return;
                }

                // 插入好友关系
                query.prepare("INSERT INTO relationship (user_id, friend_id) VALUES (:user_id, :friend_id)");
                query.bindValue(":user_id", userId);
                query.bindValue(":friend_id", friendId);
                if (!query.exec()) {
                    qDebug() << "添加好友失败：" << query.lastError().text();
                    // 向请求方发送失败消息
                    QJsonObject response;
                    response["kind"] = "addfriend_response";
                    response["status"] = "failed";
                    response["message"] = "添加好友失败";
                    QJsonDocument responseDoc(response);
                    tcpClient->write(responseDoc.toJson());
                } else {
                    // 添加好友的逆向关系
                    query.prepare("INSERT INTO relationship (user_id, friend_id) VALUES (:user_id, :friend_id)");
                    query.bindValue(":user_id", friendId);
                    query.bindValue(":friend_id", userId);
                    if (!query.exec()) {
                        qDebug() << "添加好友失败：" << query.lastError().text();
                    } else {
                        // 向请求方发送成功消息
                        QJsonObject response;
                        response["kind"] = "addfriend_response";
                        response["status"] = "success";
                        QJsonDocument responseDoc(response);
                        tcpClient->write(responseDoc.toJson());

                        // 通知双方刷新好友列表
                        QJsonObject notify;
                        notify["kind"] = "friendlist_updated";
                        QJsonDocument notifyDoc(notify);
                        QByteArray notifyData = notifyDoc.toJson();

                        // 通知请求方
                        if (socketHash.contains(userId)) {
                            socketHash[userId]->write(notifyData);
                        }

                        // 通知被添加的好友（如果在线）
                        if (socketHash.contains(friendId)) {
                            socketHash[friendId]->write(notifyData);
                        } else {
                            qDebug() << "好友" << friendId << "未在线，无法发送好友列表更新通知";
                        }
                    }
                }

                return;
            }

            if (kind == "chatingrecord") {
                // 获取请求者的 id 和 friend_id
                QString userId = json["id"].toString();
                QString friendId = json["friend_id"].toString();

                // 查询聊天记录
                QSqlQuery query;
                query.prepare("SELECT sender_id, receiver_id, message, time FROM chatingrecords WHERE \
                              (sender_id = :userId AND receiver_id = :friendId) OR \
                              (sender_id = :friendId AND receiver_id = :userId) \
                              ORDER BY time ASC");
                query.bindValue(":userId", userId);
                query.bindValue(":friendId", friendId);

                QJsonArray recordsArray;

                if (query.exec()) {
                    while (query.next()) {
                        QJsonObject record;
                        record["sender_id"] = query.value("sender_id").toString();
                        record["receiver_id"] = query.value("receiver_id").toString();
                        record["message"] = query.value("message").toString();
                        record["time"] = query.value("time").toString();

                        recordsArray.append(record);
                    }
                } else {
                    qDebug() << "Failed to query chat records:" << query.lastError().text();
                }

                // 构造返回给客户端的 JSON 数据
                QJsonObject responseJson;
                responseJson["kind"] = "chatingrecord_response";
                responseJson["records"] = recordsArray;

                QJsonDocument responseDoc(responseJson);
                QByteArray responseData = responseDoc.toJson();

                // 发送数据给客户端
                tcpClient->write(responseData);
            }
            // 其他 kind 的处理...
        }
        if (json.contains("sender_id") && json.contains("message")) {
            // 处理消息
            QString senderId = json["sender_id"].toString();
            QString receiverId = json["receiver_id"].toString();
            QString message = json["message"].toString();
            QString time = json["time"].toString();

            //qDebug() << "Received JSON data:" << doc.toJson(QJsonDocument::Indented);
            // 如果接收到的是空数据，则将客户端的 socket 存储到 Hash 表中
            if (message.isEmpty() && receiverId.isEmpty()) {
                if (!socketHash.contains(senderId)) {
                    socketHash.insert(senderId, tcpClient);
                    qDebug() << "User" << senderId << "connected";
                    // 在 listWidget 上显示登录信息
                    //ui->listWidget->addItem(QString("用户 %1 已登录").arg(senderId));
                }
                return;
            }
            qDebug() << senderId << " " << receiverId << " " << message << " " << time << " ";
            // 存储到数据库
            QSqlQuery query;
            query.prepare("INSERT INTO chatingrecords (sender_id, receiver_id, message, time) VALUES (:sender_id, :receiver_id, :message, :time)");
            query.bindValue(":sender_id", senderId);
            query.bindValue(":receiver_id", receiverId);
            query.bindValue(":message", message);
            query.bindValue(":time", time);
            if (!query.exec()) {
                qDebug() << "Failed to insert message into database:" << query.lastError().text();
                return;
            }
            // 查询 sender_id 对应的 nickname
            QString senderNickname;
            query.prepare("SELECT nickname FROM users WHERE id = :id");
            query.bindValue(":id", senderId);
            if (query.exec() && query.next()) {
                senderNickname = query.value(0).toString();
            } else {
                qDebug() << "Failed to get nickname for sender_id:" << senderId;
                senderNickname = senderId; // 如果查询失败，使用 senderId 作为昵称
            }
            // 查询 receiver_id 对应的 nickname
            QString receiverNickname;
            query.prepare("SELECT nickname FROM users WHERE id = :id");
            query.bindValue(":id", receiverId);
            if (query.exec() && query.next()) {
                receiverNickname = query.value(0).toString();
            } else {
                qDebug() << "Failed to get nickname for receiver_id:" << receiverId;
                receiverNickname = receiverId; // 如果查询失败，使用 receiverId 作为昵称
            }
            // 替换 JSON 数据中的 id 为 nickname
            json["sender_id"] = senderNickname;
            json["receiver_id"] = receiverNickname;
            QJsonDocument newDoc(json);
            QByteArray newData = newDoc.toJson();
            // 检查是否存在与 friend_id 的连接
            if (socketHash.contains(receiverId)) {
                QTcpSocket* receiverSocket = socketHash.value(receiverId);
                qDebug() << "Forwarding message to receiver:" << receiverId;
                receiverSocket->write(newData);
                // 同时将消息发送回发送者
                QTcpSocket* senderSocket = socketHash.value(senderId);
                senderSocket->write(newData);
                // 在 listWidget 上显示消息转发信息
                ui->listWidget->addItem(QString("%1 发送给 %2: %3").arg(senderNickname).arg(receiverNickname).arg(message));
            }
        }
    }
}
//定时器到时后将执行的槽函数
void ServerDialog::onTimeout()
{
    // 遍历 socketHash 容器
    QHash<QString, QTcpSocket*>::iterator it = socketHash.begin();
    while (it != socketHash.end()) {
        QTcpSocket* socket = it.value();
        // 检查套接字是否已经断开连接
        if (socket->state() == QAbstractSocket::UnconnectedState) {
            qDebug() << "Removing disconnected socket for user" << it.key();
            // 删除套接字
            it = socketHash.erase(it);
            socket->deleteLater();
        } else {
            ++it;
        }
    }
}
void ServerDialog::onClientDisconnected()
{
    QTcpSocket* tcpClient = qobject_cast<QTcpSocket*>(sender());
    if (tcpClient) {
        QString userId;
        // 查找对应的用户 ID
        foreach (const QString &key, socketHash.keys()) {
            if (socketHash.value(key) == tcpClient) {
                userId = key;
                break;
            }
        }
        if (!userId.isEmpty()) {
            socketHash.remove(userId);
            qDebug() << "用户" << userId << "已断开连接";
        }
        tcpClient->deleteLater();
    }
}
