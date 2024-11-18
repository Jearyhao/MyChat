#ifndef FRIENDLISTDIALOG_H
#define FRIENDLISTDIALOG_H

#include <QDialog>
#include "ui_friendlistdialog.h"
namespace Ui {
class FriendListDialog;
}

class FriendListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FriendListDialog(QWidget *parent = nullptr);
    ~FriendListDialog();
    Ui::FriendListDialog *ui; // 将 ui 设为 public 以便在 UserDialog 中访问
private:

};

#endif // FRIENDLISTDIALOG_H
