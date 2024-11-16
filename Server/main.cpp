#include "serverdialog.h"
#include "loginserver.h"
#include "revisedialog.h"
#include "enrolldialog.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlError>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginServer w;
    w.show();
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
        db.setHostName("127.0.0.1");//你的IP地址
        db.setDatabaseName("openGauss");
        db.setUserName("jrh"); //用户名
        db.setPassword("741QAZabc");//密码
        db.setPort(26000); //opengauss端口号为26000
        bool flag = db.open();
        if (flag){
            qDebug() << "success";
        } else{
            qDebug() << "failed";
        }

    return a.exec();
}
