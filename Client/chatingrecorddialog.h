#ifndef CHATINGRECORDDIALOG_H
#define CHATINGRECORDDIALOG_H

#include <QDialog>

namespace Ui {
class ChatingRecordDialog;
}

class ChatingRecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatingRecordDialog(QWidget *parent = nullptr);
    ~ChatingRecordDialog();

private:
    Ui::ChatingRecordDialog *ui;
};

#endif // CHATINGRECORDDIALOG_H
