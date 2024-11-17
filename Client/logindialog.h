#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "enrolldialog.h"
#include "revisedialog.h"
#include "clientdialog.h"
#include "userdialog.h"
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlError>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
private slots:
    void on_enrollButton_clicked();
    void on_revisePasswordButton_clicked();
    void updateLoginButtonState();

    void on_loginButton_clicked();

private:
    Ui::LoginDialog *ui;
    EnrollDialog *enrollDialog; // 成员变量
    ClientDialog *clentDialog;
    ReviseDialog *reviseDialog;
    UserDialog *userDialog;
};

#endif // LOGINDIALOG_H
