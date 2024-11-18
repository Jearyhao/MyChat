#include "friendlistdialog.h"
#include "ui_friendlistdialog.h"

FriendListDialog::FriendListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendListDialog)
{
    ui->setupUi(this);
}

FriendListDialog::~FriendListDialog()
{
    delete ui;
}
