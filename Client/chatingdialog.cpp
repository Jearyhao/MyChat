#include "chatingdialog.h"
#include "ui_chatingdialog.h"

ChatingDialog::ChatingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatingDialog)
{
    ui->setupUi(this);
}

ChatingDialog::~ChatingDialog()
{
    delete ui;
}
