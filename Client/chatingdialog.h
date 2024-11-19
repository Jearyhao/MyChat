#ifndef CHATINGDIALOG_H
#define CHATINGDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
namespace Ui {
class ChatingDialog;
}

class ChatingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatingDialog(const QString &friendId, QWidget *parent = nullptr);
    ~ChatingDialog();

private slots:

    void on_sendButton_clicked();

private:
    Ui::ChatingDialog *ui;
    QString friendId;

    void loadFriendNickname();
};

#endif // CHATINGDIALOG_H
