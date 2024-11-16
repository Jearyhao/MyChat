#include "loginserver.h"
#include "ui_loginserver.h"

LoginServer::LoginServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginServer),
    serverDialog(nullptr), // 初始化指针
    enrollDialog(nullptr), // 初始化指针
    reviseDialog(nullptr) // 初始化指针
{
    ui->setupUi(this);
    ui->idEdit->setPlaceholderText("请输入管理员账号:");
    ui->passwordEdit->setPlaceholderText("请输入密码:");
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginServer::on_loginButton_clicked); // 连接信号和槽
    connect(ui->enrollButton, &QPushButton::clicked, this, &LoginServer::on_enrollButton_clicked);
    connect(ui->revisePasswordButton, &QPushButton::clicked, this, &LoginServer::on_revisePasswordButton_clicked);
}

LoginServer::~LoginServer()
{
    delete ui;
    if (serverDialog) {
        delete serverDialog; // 确保删除ServerDialog对象
    }
    if (enrollDialog) {
        delete enrollDialog; // 确保删除EnrollDialog对象
    }
    if (reviseDialog) {
        delete reviseDialog; // 确保删除ReviseDialog对象
    }
}
void LoginServer::on_loginButton_clicked()
{
    if (!serverDialog) {
        serverDialog = new ServerDialog(this); // 创建ServerDialog窗口
    }
    serverDialog->show(); // 显示ServerDialog窗口
    this->hide(); // 关闭当前LoginServer窗口
}
void LoginServer::on_enrollButton_clicked()
{
    ui->idEdit->clear();
    ui->passwordEdit->clear();
    if (!enrollDialog) {
        enrollDialog = new EnrollDialog(this); // 创建EnrollDialog窗口
    }
    enrollDialog->show(); // 显示EnrollDialog窗口
    this->hide(); // 隐藏当前LoginServer窗口
}

void LoginServer::on_revisePasswordButton_clicked()
{
    ui->idEdit->clear();
    ui->passwordEdit->clear();
    if (!reviseDialog) {
        reviseDialog = new ReviseDialog(this); // 创建ReviseDialog窗口
    }
    reviseDialog->show(); // 显示ReviseDialog窗口
    this->hide(); // 隐藏当前LoginServer窗口
}
