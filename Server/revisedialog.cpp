#include "revisedialog.h"
#include "ui_revisedialog.h"

ReviseDialog::ReviseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReviseDialog)
{
    ui->setupUi(this);
    connect(ui->returnLoginButton_2, &QPushButton::clicked, this, &ReviseDialog::on_returnLoginButton_clicked);
}

ReviseDialog::~ReviseDialog()
{
    delete ui;
}

void ReviseDialog::on_returnLoginButton_clicked()
{
    QWidget *parent = this->parentWidget(); // 获取父窗口
    if (parent)
    {
        parent->show(); // 显示父窗口
    }
    this->close(); // 关闭当前窗口

}
