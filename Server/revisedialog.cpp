#include "revisedialog.h"
#include "ui_revisedialog.h"

ReviseDialog::ReviseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReviseDialog)
{
    ui->setupUi(this);
    ui->idEdit_2->setPlaceholderText("请输入id:");
    ui->passwordEdit_2->setPlaceholderText("请输入新的密码:");
    ui->confirmPasswordEdit_2->setPlaceholderText("请确认新的密码:");
    connect(ui->returnLoginButton_2, &QPushButton::clicked, this, &ReviseDialog::on_returnLoginButton_clicked);
}

ReviseDialog::~ReviseDialog()
{
    delete ui;
}

void ReviseDialog::on_returnLoginButton_clicked()
{
    ui->idEdit_2->clear();
    ui->passwordEdit_2->clear();
    ui->confirmPasswordEdit_2->clear();
    QWidget *parent = this->parentWidget(); // 获取父窗口
    if (parent)
    {
        parent->show(); // 显示父窗口
    }
    this->close(); // 关闭当前窗口

}
