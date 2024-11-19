#ifndef FRIENDLISTDIALOG_H
#define FRIENDLISTDIALOG_H

#include <QDialog>
#include "ui_friendlistdialog.h"
#include "chatingdialog.h"
namespace Ui {
class FriendListDialog;
}

class FriendListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FriendListDialog(const QString &friendId, QWidget *parent = nullptr);
    ~FriendListDialog();
    Ui::FriendListDialog *ui; // 将 ui 设为 public 以便在 UserDialog 中访问
private slots:
    void on_pushButton_clicked();

private:
    QString friendId;
};

#endif // FRIENDLISTDIALOG_H
