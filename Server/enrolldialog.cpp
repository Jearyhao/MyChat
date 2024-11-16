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
    connect(ui->returnLoginButton, &QPushButton::clicked, this, &EnrollDialog::on_returnLoginButton_clicked);
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
    QWidget *parent = this->parentWidget(); // 获取父窗口
    if (parent)
    {
        parent->show(); // 显示父窗口
    }
    this->close(); // 关闭当前窗口
}
