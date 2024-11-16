#include "loginserver.h"
#include "ui_loginserver.h"

LoginServer::LoginServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginServer),
    serverDialog(nullptr) // 初始化指针
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginServer::on_loginButton_clicked); // 连接信号和槽
}

LoginServer::~LoginServer()
{
    delete ui;
}
void LoginServer::on_loginButton_clicked()
{
    if (!serverDialog) {
        serverDialog = new ServerDialog(this); // 创建ServerDialog窗口
    }
    ServerDialog *serverDialog = new ServerDialog(this); // 创建ServerDialog窗口
    serverDialog->show(); // 显示ServerDialog窗口
    this->hide(); // 关闭当前LoginServer窗口
}