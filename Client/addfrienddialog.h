#ifndef ADDFRIENDDIALOG_H
#define ADDFRIENDDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
namespace Ui {
class AddFriendDialog;
}

class AddFriendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFriendDialog(const QString &userId, QWidget *parent = nullptr);
    ~AddFriendDialog();

private slots:

    void on_addFriendButton_clicked();

private:
    Ui::AddFriendDialog *ui;
    QString userId; // 保存用户 ID
};

#endif // ADDFRIENDDIALOG_H
