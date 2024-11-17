#ifndef CHATINGDIALOG_H
#define CHATINGDIALOG_H

#include <QDialog>

namespace Ui {
class ChatingDialog;
}

class ChatingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatingDialog(QWidget *parent = nullptr);
    ~ChatingDialog();

private:
    Ui::ChatingDialog *ui;
};

#endif // CHATINGDIALOG_H
