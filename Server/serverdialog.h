#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlError>
#include <QHash>
#include <QJsonObject>
#include <QJsonDocument>
QT_BEGIN_NAMESPACE
namespace Ui { class ServerDialog; }
QT_END_NAMESPACE

class ServerDialog : public QDialog
{
    Q_OBJECT

public:
    ServerDialog(QWidget *parent = nullptr);
    ~ServerDialog();
 
private slots:
    //创建服务器按钮对应的槽函数
    //void on_createButton_clicked();
    //响应客户端连接请求的槽函数
    void onNewConnection();
    //接收客户端消息的槽函数
    void onReadyRead();
    //定时器到时后将执行的槽函数
    void onTimeout(void);
    void onClientDisconnected();
private:
    Ui::ServerDialog *ui;
    QTcpServer tcpServer;
    quint16 port = 10086;//服务器端口

    QTimer timer;//定时器，用来判断tcpClientList中是否有套接字已经断开连接,有的话就关掉
    QHash<QString, QTcpSocket*> socketHash;
};
#endif // SERVERDIALOG_H
