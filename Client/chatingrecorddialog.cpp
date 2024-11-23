#include "chatingrecorddialog.h"
#include "ui_chatingrecorddialog.h"

ChatingRecordDialog::ChatingRecordDialog(const QString &userId, const QString &friendId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatingRecordDialog),
    userId(userId),
    friendId(friendId)
{
    ui->setupUi(this);
    // 创建套接字并连接到服务器
    tcpSocket = new QTcpSocket(this);
    // 请替换为你的服务器 IP 和端口
    tcpSocket->connectToHost("127.0.0.1", 10086);

    // 连接信号和槽，处理服务器返回的数据
    connect(tcpSocket, &QTcpSocket::readyRead, this, &ChatingRecordDialog::onReadyRead);

    // 构造请求 JSON 数据
    QJsonObject json;
    json["kind"] = "chatingrecord";
    json["id"] = userId;
    json["friend_id"] = friendId;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    // 发送数据到服务器
    tcpSocket->write(data);
}

ChatingRecordDialog::~ChatingRecordDialog()
{
    if (tcpSocket) {
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
    }
    delete ui;
}
void ChatingRecordDialog::onReadyRead()
{
    QByteArray data = tcpSocket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isNull()) {
        QJsonObject json = doc.object();
        if (json.contains("kind") && json["kind"].toString() == "chatingrecord_response") {
            QJsonArray records = json["records"].toArray();

            // 清空列表
            ui->listWidget->clear();

            // 显示聊天记录
            for (const QJsonValue &value : records) {
                QJsonObject record = value.toObject();
                QString sender = record["sender_id"].toString();
                QString receiver = record["receiver_id"].toString();
                QString message = record["message"].toString();
                QString time = record["time"].toString();

                QString displayText = QString("[%1] %2: %3").arg(time).arg(sender).arg(message);
                ui->listWidget->addItem(displayText);
            }
        }
    }
}