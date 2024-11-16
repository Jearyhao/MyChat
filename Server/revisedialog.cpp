#include "revisedialog.h"
#include "ui_revisedialog.h"

ReviseDialog::ReviseDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReviseDialog)
{
    ui->setupUi(this);
}

ReviseDialog::~ReviseDialog()
{
    delete ui;
}
