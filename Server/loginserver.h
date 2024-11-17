#ifndef LOGINSERVER_H
#define LOGINSERVER_H

#include <QWidget>
#include "serverdialog.h" // 包含ServerDialog的头文件
#include "enrolldialog.h" // 包含EnrollDialog的头文件
#include "revisedialog.h" // 包含ReviseDialog的头文件
#include <QDebug>
#include <QMessageBox>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlError>
namespace Ui {
class LoginServer;
}

class LoginServer : public QWidget
{
    Q_OBJECT

public:
    explicit LoginServer(QWidget *parent = nullptr);
    ~LoginServer();

private slots:
    void on_loginButton_clicked();
    void on_enrollButton_clicked(); // 声明槽函数
    void on_revisePasswordButton_clicked();
    void updateLoginButtonState();

private:
    Ui::LoginServer *ui;
    ServerDialog *serverDialog; // 声明ServerDialog对象
    EnrollDialog *enrollDialog; // 声明EnrollDialog对象
    ReviseDialog *reviseDialog; // 声明ReviseDialog对象
};

#endif // LOGINSERVER_H
