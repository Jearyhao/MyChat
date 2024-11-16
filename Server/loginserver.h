#ifndef LOGINSERVER_H
#define LOGINSERVER_H

#include <QWidget>
#include "serverdialog.h" // 包含ServerDialog的头文件
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

private:
    Ui::LoginServer *ui;
    ServerDialog *serverDialog; // 声明ServerDialog对象
};

#endif // LOGINSERVER_H
