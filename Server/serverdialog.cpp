#include "serverdialog.h"
#include "ui_serverdialog.h"

ServerDialog::ServerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ServerDialog)
{
    ui->setupUi(this);
    //当客户端向服务器发送连接请求，发送信号:newConnection(Qt里面封装好的信号)
    connect(&tcpServer, SIGNAL(newConnection()),
            this, SLOT(onNewConnection()));
    connect(&timer, SIGNAL(timeout()), SLOT(onTimeout()));
    ui->portEdit->setPlaceholderText("请输入端口号：");
}

ServerDialog::~ServerDialog()
{
    delete ui;
}

//创建服务器按钮对应的槽函数
void ServerDialog::on_createButton_clicked()
{
    //设置服务器IP和端口
    if(tcpServer.listen(QHostAddress::Any, port) == true){
        qDebug() << "创建服务器成功！";
        //开启定时器
        timer.start(3000);
    } else{
        qDebug() << "创建服务器失败!";
    }
}

//响应客户段连接请求的槽函数
void ServerDialog::onNewConnection(){
    //获取和客户端通信的套接字
    QTcpSocket* tcpClient = tcpServer.nextPendingConnection();
    //保存套接字到容器

    //当客户端向服务器发送消息时，通信套接字发送信号：readyRead
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}
//接收客户端消息的槽函数
void ServerDialog::onReadyRead(){

}
//定时器到时后将执行的槽函数
void ServerDialog::onTimeout(void){
    //遍历检查容器中保存的和客户端通信套接字是否已经断开连接，如果是则删除

}
