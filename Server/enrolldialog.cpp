#include "enrolldialog.h"
#include "ui_enrolldialog.h"

EnrollDialog::EnrollDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnrollDialog)
{
    ui->setupUi(this);
}

EnrollDialog::~EnrollDialog()
{
    delete ui;
}
