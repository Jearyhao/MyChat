#include "enrolldialog.h"
#include "ui_enrolldialog.h"
#include <QDebug>

EnrollDialog::EnrollDialog(QWidget *parent) :
    QDialog(parent), // 确保继承自 QDialog
    ui(new Ui::EnrollDialog)
{
    qDebug() << "EnrollDialog constructor called";
    ui->setupUi(this);
    connect(ui->returnLoginButton, &QPushButton::clicked, this, &EnrollDialog::on_returnLoginButton_clicked);
}

EnrollDialog::~EnrollDialog()
{
    delete ui;
}
void EnrollDialog::on_returnLoginButton_clicked()
{
    QWidget *parent = this->parentWidget(); // 获取父窗口
    if (parent)
    {
        parent->show(); // 显示父窗口
    }
    this->close(); // 关闭当前窗口
}