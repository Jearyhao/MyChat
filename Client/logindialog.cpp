#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    enrollDialog(new EnrollDialog(this)), // 初始化
    reviseDialog(nullptr),
    userDialog(nullptr)
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

void LoginDialog::on_loginButton_clicked()
{
    QString id = ui->idEdit->text();
    QString password = ui->passwordEdit->text();

    // 检查数据库中是否存在相同的id
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "查询数据库失败: " + query.lastError().text());
        return;
    }

    if (!query.next()) {
        QMessageBox::warning(this, "错误", "该账号不存在,请检查输入的ID");
        return;
    }

    QString storedPassword = query.value(0).toString();
    if (storedPassword != password) {
        QMessageBox::warning(this, "错误", "密码错误,请重新输入");
        return;
    }

    // 密码正确，跳转到 UserDialog 界面
    if (!userDialog) {
        userDialog = new UserDialog(id, this);
    }
    userDialog->show();
    this->hide();
}
