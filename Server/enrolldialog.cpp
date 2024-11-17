#include "enrolldialog.h"
#include "ui_enrolldialog.h"
#include <QDebug>

EnrollDialog::EnrollDialog(QWidget *parent) :
    QDialog(parent), // 确保继承自 QDialog
    ui(new Ui::EnrollDialog)
{
    ui->setupUi(this);
    ui->idEdit->setPlaceholderText("请输入id:");
    ui->passwordEdit->setPlaceholderText("请输入密码:");
    ui->confirmPasswordEdit->setPlaceholderText("请确认密码:");
    ui->enrollButton->setEnabled(false); // 初始时禁用注册按钮
    //connect(ui->returnLoginButton, &QPushButton::clicked, this, &EnrollDialog::on_returnLoginButton_clicked);
    //connect(ui->enrollButton, &QPushButton::clicked, this, &EnrollDialog::on_enrollButton_clicked);
    connect(ui->idEdit, &QLineEdit::textChanged, this, &EnrollDialog::on_inputFieldsChanged);
    connect(ui->passwordEdit, &QLineEdit::textChanged, this, &EnrollDialog::on_inputFieldsChanged);
    connect(ui->confirmPasswordEdit, &QLineEdit::textChanged, this, &EnrollDialog::on_inputFieldsChanged);
    connect(ui->checkBox, &QCheckBox::stateChanged, this, &EnrollDialog::on_inputFieldsChanged);
}

EnrollDialog::~EnrollDialog()
{
    delete ui;
}
void EnrollDialog::on_returnLoginButton_clicked()
{
    ui->checkBox->setChecked(false); // 取消勾选
    ui->idEdit->clear();
    ui->passwordEdit->clear();
    ui->confirmPasswordEdit->clear();
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    QWidget *parent = this->parentWidget(); // 获取父窗口
    if (parent)
    {
        parent->show(); // 显示父窗口
    }
    this->close(); // 关闭当前窗口
}

void EnrollDialog::on_enrollButton_clicked()
{
    QString id = ui->idEdit->text();
    QString password = ui->passwordEdit->text();
    QString confirmPassword = ui->confirmPasswordEdit->text();

    QSqlQuery query;
    query.prepare("select * from adminusers where id = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        qDebug() << "账号已存在";
        ui->idEdit->clear();
        ui->passwordEdit->clear();
        ui->confirmPasswordEdit->clear();
        QMessageBox::information(this, "失败", "账号已存在");
        return;
    }
    // 检查密码是否一致
    if (password != confirmPassword) {
        QMessageBox::warning(this, "错误", "两次输入的密码不一致，请重新输入");
        ui->confirmPasswordEdit->clear();
        return;
    }
    query.prepare("INSERT INTO adminusers (id, password) VALUES (:id, :password)");
    query.bindValue(":id", id);
    query.bindValue(":password", password);

    if (query.exec()) {
        qDebug() << "账号创建成功";
        QMessageBox::information(this, "成功", "账号创建成功");
    } else {
        qDebug() << "账号创建失败: " << query.lastError().text();
    }
}
void EnrollDialog::on_inputFieldsChanged()
{
    bool enableButton = !ui->idEdit->text().isEmpty() &&
                        !ui->passwordEdit->text().isEmpty() &&
                        !ui->confirmPasswordEdit->text().isEmpty() &&
                        ui->checkBox->isChecked();
    ui->enrollButton->setEnabled(enableButton);
}
