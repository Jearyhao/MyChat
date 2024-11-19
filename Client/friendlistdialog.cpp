#include "friendlistdialog.h"
#include "ui_friendlistdialog.h"

FriendListDialog::FriendListDialog(const QString &friendId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendListDialog),
    friendId(friendId)
{
    ui->setupUi(this);
}

FriendListDialog::~FriendListDialog()
{
    delete ui;
}


void FriendListDialog::on_pushButton_clicked()
{
    ChatingDialog *chatingDialog = new ChatingDialog(friendId, this);
    chatingDialog->setAttribute(Qt::WA_DeleteOnClose); // 确保对话框关闭时自动删除
    chatingDialog->show();
}
