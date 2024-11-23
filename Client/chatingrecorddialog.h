#ifndef CHATINGRECORDDIALOG_H
#define CHATINGRECORDDIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
namespace Ui {
class ChatingRecordDialog;
}

class ChatingRecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatingRecordDialog(const QString &userId, const QString &friendId, QWidget *parent = nullptr);
    ~ChatingRecordDialog();

private:
    Ui::ChatingRecordDialog *ui;
    QString userId;
    QString friendId;
    QTcpSocket *tcpSocket;

private slots:
    void onReadyRead();
};

#endif // CHATINGRECORDDIALOG_H
