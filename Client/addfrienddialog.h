#ifndef ADDFRIENDDIALOG_H
#define ADDFRIENDDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTcpSocket>
namespace Ui {
class AddFriendDialog;
}

class AddFriendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFriendDialog(const QString &id, QTcpSocket *socket, QWidget *parent = nullptr);
    ~AddFriendDialog();

private slots:

    void on_addFriendButton_clicked();

private:
    Ui::AddFriendDialog *ui;
    QString userId; // 保存用户 ID
    QTcpSocket *tcpSocket;
signals:
    void friendAdded();
};

#endif // ADDFRIENDDIALOG_H
