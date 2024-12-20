#ifndef CHATINGDIALOG_H
#define CHATINGDIALOG_H
#include "chatingrecorddialog.h"
#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
namespace Ui {
class ChatingDialog;
}

class ChatingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatingDialog(const QString &userId, const QString &friendId, QWidget *parent = nullptr);
    ~ChatingDialog();

private slots:

    void on_sendButton_clicked();
    void onReadyRead();
    void on_pushButton_clicked();

private:
    Ui::ChatingDialog *ui;
    QString userId;
    QString friendId;
    QTcpSocket *socket;
    void loadFriendNickname();
    void connectToServer();
};

#endif // CHATINGDIALOG_H
