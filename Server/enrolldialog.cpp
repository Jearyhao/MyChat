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

    if (id.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        qDebug() << "请填写所有字段";
        return;
    }

    if (password != confirmPassword) {
        qDebug() << "两次输入的密码不一致";
        return;
    }
    if (!ui->checkBox->isChecked()) {
        qDebug() << "请勾选同意条款";
        return;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO users (id, password) VALUES (:id, :password)");
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
