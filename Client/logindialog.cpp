#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    enrollDialog(new EnrollDialog(this)), // 初始化
    reviseDialog(nullptr)
{
    ui->setupUi(this);
    ui->idEdit->setPlaceholderText("请输入账号:");
    ui->passwordEdit->setPlaceholderText("请输入密码:");
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->loginButton->setEnabled(false);

    connect(ui->idEdit, &QLineEdit::textChanged, this, &LoginDialog::updateLoginButtonState);
    connect(ui->passwordEdit, &QLineEdit::textChanged, this, &LoginDialog::updateLoginButtonState);
    connect(ui->checkBox, &QCheckBox::stateChanged, this, &LoginDialog::updateLoginButtonState);
    connect(ui->enrollButton, &QPushButton::clicked, this, &LoginDialog::on_enrollButton_clicked);
    connect(ui->revisePasswordButton, &QPushButton::clicked, this, &LoginDialog::on_revisePasswordButton_clicked);
}
void LoginDialog::updateLoginButtonState()
{
    bool isIdFilled = !ui->idEdit->text().isEmpty();
    bool isPasswordFilled = !ui->passwordEdit->text().isEmpty();
    bool isCheckBoxChecked = ui->checkBox->isChecked();
    ui->loginButton->setEnabled(isIdFilled && isPasswordFilled && isCheckBoxChecked);
}
LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_enrollButton_clicked()
{
    ui->checkBox->setChecked(false); // 取消勾选
    ui->idEdit->clear();
    ui->passwordEdit->clear();
    if (!enrollDialog) {
        enrollDialog = new EnrollDialog(this); // 创建EnrollDialog窗口
    }
    enrollDialog->show(); // 显示EnrollDialog窗口
    this->hide(); // 隐藏当前LoginServer窗口
}

void LoginDialog::on_revisePasswordButton_clicked()
{
    ui->checkBox->setChecked(false); // 取消勾选
    ui->idEdit->clear();
    ui->passwordEdit->clear();
    if (!reviseDialog) {
        reviseDialog = new ReviseDialog(this); // 创建ReviseDialog窗口
    }
    reviseDialog->show(); // 显示ReviseDialog窗口
    this->hide(); // 隐藏当前LoginServer窗口
}
