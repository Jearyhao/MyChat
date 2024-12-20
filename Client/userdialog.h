#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlError>
#include <QPixmap>
#include <QMessageBox>
#include <QPainterPath>
#include <QPainter>
#include "frienditem.h"
#include "friendlistdialog.h"
#include <QMenu>
#include <QAction>
#include "profiledialog.h"
#include "addfrienddialog.h"
#include <QTimer>
#include <QTcpSocket>
namespace Ui {
class UserDialog;
}

class UserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDialog(const QString &id, QWidget *parent = nullptr);
    ~UserDialog();
    void setAvatar(const QString &avatarPath); // 添加接收头像路径的方法
    void setNickName(const QString &nickName); // 添加接收昵称的方法
    void setPersonalizedSignature(const QString &signature); // 添加接收个性签名的方法
    void loadFriendList();

private slots:
    void onModifyProfile();
    void onAddFriend();
    void updateProfile(); // 添加槽函数声明
    void onReadyRead();
    void onRefresh();

private:
    Ui::UserDialog *ui;
    QString userId; // 保存用户 ID
    QString avatarPath; // 保存头像路径
    QTcpSocket *tcpSocket;
};

#endif // USERDIALOG_H
