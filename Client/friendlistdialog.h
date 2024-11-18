#ifndef FRIENDLISTDIALOG_H
#define FRIENDLISTDIALOG_H

#include <QDialog>

namespace Ui {
class FriendListDialog;
}

class FriendListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FriendListDialog(QWidget *parent = nullptr);
    ~FriendListDialog();

private:
    Ui::FriendListDialog *ui;
};

#endif // FRIENDLISTDIALOG_H
