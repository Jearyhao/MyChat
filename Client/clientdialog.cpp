#include "clientdialog.h"
#include "ui_clientdialog.h"

ClientDialog::ClientDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ClientDialog)
{
    ui->setupUi(this);
    status = false;//离线
    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(&tcpSocket, SIGNAL(error(QAbstractSocker::SocketError)),
            this, SLOT(onError()));
    ui->serverIpEdit->setPlaceholderText("请输入服务器IP:");
    ui->serverPortEdit->setPlaceholderText("请输入服务器端口号:");
    ui->usernameEdit->setPlaceholderText("请输入你的昵称:");
    ui->messagelineEdit->setPlaceholderText("请输入消息:");
}

ClientDialog::~ClientDialog()
{
    delete ui;
}

//连接服务器按钮对应的槽函数
void ClientDialog::on_connectButton_clicked()
{
    //如果当前是离线状态，则建立和服务器的连接
    //如果当前是在线状态，则断开和服务器的连接
    if(status == false){
        //获取服务器IP
        serverIP.setAddress(ui->serverIpEdit->text());
        //获取服务器端口
        serverPort = ui->serverPortEdit->text().toUShort();
        //获取聊天室昵称
        username = ui->usernameEdit->text();
        //向服务器发送连接请求
        //成功发送信号:connnected
        //失败发送信号:error
        tcpSocket.connectToHost(serverIP, serverPort);

    } else{
        //向服务器发送离开聊天室的提示消息
        QString msg = username + ":离开了聊天室！";
        tcpSocket.write(msg.toUtf8());
        //关闭和服务器连接，发送信号:disconnected
        tcpSocket.disconnectFromHost();
    }
}

//发送按钮对应的槽函数
void ClientDialog::on_sendButton_clicked()
{
    //获取用户输入聊天消息
    QString msg = ui->messagelineEdit->text();
    if(msg == ""){
        return;
    }
    msg = username + ":" + msg;
    //发送聊天消息
    tcpSocket.write(msg.toUtf8());
    //清空消息输入框
    ui->messagelineEdit->clear();
}


//和服务器连接成功时执行的槽函数
void ClientDialog::onConnected(){
    status = true;//在线
    ui->sendButton->setEnabled(true);//恢复按钮状态
    ui->serverIpEdit->setEnabled(false);//禁用IP
    ui->serverPortEdit->setEnabled(false);//禁用Port
    ui->usernameEdit->setEnabled(false);//禁用昵称输入
    ui->connectButton->setText("离开聊天室");

    //向服务器发送进入聊天室提示消息
    QString msg = username + ":进入了聊天室";
    //toUtf8:QString转换QByteArray
    tcpSocket.write(msg.toUtf8());

}
//和服务器断开连接时执行的槽函数
void ClientDialog::onDisconnected(){
    status = false;//离线
    ui->sendButton->setEnabled(false);//禁用按钮状态
    ui->serverIpEdit->setEnabled(true);//恢复IP
    ui->serverPortEdit->setEnabled(true);//恢复Port
    ui->usernameEdit->setEnabled(true);//恢复昵称输入
    ui->connectButton->setText("连接服务器");
}
//接收聊天消息的槽函数
void ClientDialog::onReadyRead(){
    //接收消息
    if(tcpSocket.bytesAvailable()){
        QByteArray buf = tcpSocket.readAll();
        //显示消息
        ui->listWidget->addItem(buf);
        ui->listWidget->scrollToBottom();
    }
}
//网络异常执行的槽函数
void ClientDialog::onError(){
    //errorString():获取网络异常的原因(父指针，窗口标题，网络异常的原因)
    QMessageBox::critical(this, "ERROR", tcpSocket.errorString());
}
