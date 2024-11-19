#include "chatingdialog.h"
#include "ui_chatingdialog.h"

ChatingDialog::ChatingDialog(const QString &friendId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatingDialog),
    friendId(friendId)
{
    ui->setupUi(this);
    loadFriendNickname();
}

ChatingDialog::~ChatingDialog()
{
    delete ui;
}


void ChatingDialog::loadFriendNickname()
{
    // 查询数据库以获取好友的昵称
    QSqlQuery query;
    query.prepare("SELECT nickname FROM users WHERE id = :id");
    query.bindValue(":id", friendId);
    if (query.exec() && query.next()) {
        QString nickname = query.value(0).toString();
        ui->friendNameLabel->setText(nickname); // 将昵称设置到 friendNameLabel
    } else {
        QMessageBox::critical(this, "错误", "无法获取好友昵称: " + query.lastError().text());
    }
}


void ChatingDialog::on_sendButton_clicked()
{

}
