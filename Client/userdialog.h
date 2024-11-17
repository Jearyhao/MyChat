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


private:
    Ui::UserDialog *ui;
    QString userId; // 保存用户 ID
    QString avatarPath; // 保存头像路径
};

#endif // USERDIALOG_H
