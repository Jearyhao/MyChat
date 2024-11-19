#include "chatingdialog.h"
#include "ui_chatingdialog.h"

ChatingDialog::ChatingDialog(const QString &userId, const QString &friendId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatingDialog),
    userId(userId),
    friendId(friendId),
    socket(new QTcpSocket(this))
{
    ui->setupUi(this);
    loadFriendNickname();
    connectToServer();
    connect(socket, &QTcpSocket::readyRead, this, &ChatingDialog::onReadyRead);
}

ChatingDialog::~ChatingDialog()
{
    delete ui;
}

void ChatingDialog::connectToServer()
{
    socket->connectToHost("127.0.0.1", 10086);
    if (socket->waitForConnected(3000)) {
        qDebug() << "Connected to server";
        // 发送一条空数据
        QJsonObject json;
        json["sender_id"] = userId;
        json["receiver_id"] = "";
        json["message"] = "";
        json["time"] = QDateTime::currentDateTime().toString(Qt::ISODate);

        QJsonDocument doc(json);
        QByteArray data = doc.toJson();
        socket->write(data);
    } else {
        qDebug() << "Connection failed" << socket->errorString();
    }
}
void ChatingDialog::loadFriendNickname()
{
    // 查询数据库以获取好友的昵称
    QSqlQuery query;
    query.prepare("SELECT nickname FROM users WHERE id = :id");
    query.bindValue(":id", friendId);
    if (query.exec() && query.next()) {
        QString nickname = query.value(0).toString();
        ui->friendNameLabel->setText(nickname); // 将昵称设置到 friendNameLabel
    } else {
        QMessageBox::critical(this, "错误", "无法获取好友昵称: " + query.lastError().text());
    }
}

void ChatingDialog::on_sendButton_clicked()
{
    QString message = ui->textEdit->toPlainText();
    if (message.isEmpty()) {
        QMessageBox::warning(this, "警告", "消息不能为空");
        return;
    }

    QJsonObject json;
    json["sender_id"] = userId;
    json["receiver_id"] = friendId; // 假设 receiver_id 与 sender_id 相同
    json["message"] = message;
    json["time"] = QDateTime::currentDateTime().toString(Qt::ISODate);

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    socket->write(data);
    ui->textEdit->clear();
}
void ChatingDialog::onReadyRead()
{
    QByteArray data = socket->readAll();
    qDebug() << "Received data:" << data;
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject json = doc.object();
    qDebug() << "Received JSON data:" << doc.toJson(QJsonDocument::Indented);
    if (json.contains("sender_id") && json.contains("message")) {
        QString senderId = json["sender_id"].toString();
        QString message = json["message"].toString();
        QString time = json["time"].toString();
        qDebug() << senderId << " " << message << " " << time << " ";
        QString displayMessage = QString("[%1] %2: %3").arg(time, senderId, message);
        ui->listWidget->addItem(displayMessage); // 将消息添加到 listWidget
        ui->listWidget->scrollToBottom();
    }
}
