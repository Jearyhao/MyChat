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
    //获取服务器端口
    port = ui->portEdit->text().toShort();
    //设置服务器IP和端口
    if(tcpServer.listen(QHostAddress::Any, port) == true){
        qDebug() << "创建服务器成功！";
        //禁用“创建服务器”按钮和“端口输入”
        ui->createButton->setEnabled(false);
        ui->portEdit->setEnabled(false);
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
    tcpClientList.append(tcpClient);
    //当客户端向服务器发送消息时，通信套接字发送信号：readyRead
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}
//接收客户端消息的槽函数
void ServerDialog::onReadyRead(){
    //遍历容器哪个客户端给服务器发送了消息
    for(int i = 0; i < tcpClientList.size(); i++){
        //bytesAvailable:获取当前套接字等待读取消息字节数
        //返回0表示没有消息
        //返回>0，说明当前套接字有消息到来
        if(tcpClientList.at(i)->bytesAvailable()){
            //读取消息并保存
            QByteArray buf = tcpClientList.at(i)->readAll();
            //显示聊天消息
            ui->listWidget->addItem(buf);
            ui->listWidget->scrollToBottom();
            //转发消息给所有在线客户端
            sendMessage(buf);
        }
    }
}
//转发聊天消息给其他客户端
void ServerDialog::sendMessage(const QByteArray& buf){
    for(int i = 0; i < tcpClientList.size(); i++){
        tcpClientList.at(i)->write(buf);
    }
}
//定时器到时后将执行的槽函数
void ServerDialog::onTimeout(void){
    //遍历检查容器中保存的和客户端通信套接字是否已经断开连接，如果是则删除
    for(int i = 0; i < tcpClientList.size(); i++){
        if(tcpClientList.at(i)->state() == QAbstractSocket::UnconnectedState){
            tcpClientList.removeAt(i);
            //删去一个套接字后，后面的套接字下标会往前移
            //为了避免失效的后一个也是实效的被跳过，i要减1
            i--;
        }
    }
}
