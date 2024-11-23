#include "chatingrecorddialog.h"
#include "ui_chatingrecorddialog.h"

ChatingRecordDialog::ChatingRecordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatingRecordDialog)
{
    ui->setupUi(this);
}

ChatingRecordDialog::~ChatingRecordDialog()
{
    delete ui;
}
