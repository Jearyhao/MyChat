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
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}
void ServerDialog::onReadyRead()
{
    QTcpSocket* tcpClient = qobject_cast<QTcpSocket*>(sender());
    if (tcpClient) {
        QByteArray data = tcpClient->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject json = doc.object();

        if (json.contains("sender_id") && json.contains("message")) {
            // 处理消息
            QString senderId = json["sender_id"].toString();
            QString message = json["message"].toString();

            // 存储到数据库
            QSqlQuery query;
            query.prepare("INSERT INTO chatingrecords (sender_id, receiver_id, message) VALUES (:sender_id, :receiver_id, :message)");
            query.bindValue(":sender_id", senderId);
            query.bindValue(":receiver_id", senderId); // 假设 receiver_id 与 sender_id 相同
            query.bindValue(":message", message);
            if (!query.exec()) {
                qDebug() << "Failed to insert message into database:" << query.lastError().text();
                return;
            }

            // 检查是否存在与 friend_id 的连接
            if (socketHash.contains(senderId)) {
                QTcpSocket* receiverSocket = socketHash.value(senderId);
                receiverSocket->write(data);
            }
        } else {
            // 处理用户 ID
            QString userId = QString::fromUtf8(data);
            if (!socketHash.contains(userId)) {
                socketHash.insert(userId, tcpClient);
                qDebug() << "User" << userId << "connected";
            }
        }
    }
}
//定时器到时后将执行的槽函数
void ServerDialog::onTimeout(void){
    //遍历检查容器中保存的和客户端通信套接字是否已经断开连接，如果是则删除

}
