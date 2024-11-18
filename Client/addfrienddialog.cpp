#include "addfrienddialog.h"
#include "ui_addfrienddialog.h"
#include <QDebug>
AddFriendDialog::AddFriendDialog(const QString &id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFriendDialog),
    userId(id) // 正确初始化 userId
{
    ui->setupUi(this);
}

AddFriendDialog::~AddFriendDialog()
{
    delete ui;
}

void AddFriendDialog::on_addFriendButton_clicked()
{
    QString friendId = ui->searchIdEdit->text().trimmed();
    if (friendId.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("请输入好友ID"));
        return;
    }
    qDebug() << friendId;
    if (friendId == userId) {
        QMessageBox::warning(this, tr("警告"), tr("不能添加自己为好友"));
        return;
    }
    QSqlQuery query;

    // 检查用户是否存在
    query.prepare("SELECT id FROM users WHERE id = :id");
    query.bindValue(":id", friendId);
    if (!query.exec()) {
        QMessageBox::critical(this, tr("错误"), tr("查询数据库失败: ") + query.lastError().text());
        return;
    }

    if (!query.next()) {
        QMessageBox::warning(this, tr("警告"), tr("没有找到该ID的用户"));
        return;
    }
    // 检查是否已经是好友关系
    query.prepare("SELECT relationship_id FROM relationship WHERE user_id = :user_id AND friend_id = :friend_id");
    query.bindValue(":user_id", userId);
    query.bindValue(":friend_id", friendId);
    if (!query.exec()) {
        QMessageBox::critical(this, tr("错误"), tr("查询数据库失败: ") + query.lastError().text());
        return;
    }

    if (query.next()) {
        QMessageBox::information(this, tr("提示"), tr("你们已经是好友关系"));
        return;
    }

    // 插入两条数据，表示添加好友
    query.prepare("INSERT INTO relationship (user_id, friend_id) VALUES (:user_id, :friend_id)");
    query.bindValue(":user_id", userId);
    query.bindValue(":friend_id", friendId);
    if (!query.exec()) {
        QMessageBox::critical(this, tr("错误"), tr("添加好友失败: ") + query.lastError().text());
        return;
    }

    query.prepare("INSERT INTO relationship (user_id, friend_id) VALUES (:user_id, :friend_id)");
    query.bindValue(":user_id", friendId);
    query.bindValue(":friend_id", userId);
    if (!query.exec()) {
        QMessageBox::critical(this, tr("错误"), tr("添加好友失败: ") + query.lastError().text());
        return;
    }

    QMessageBox::information(this, tr("成功"), tr("添加好友成功"));
}
