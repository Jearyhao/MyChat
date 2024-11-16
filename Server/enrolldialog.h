#ifndef ENROLLDIALOG_H
#define ENROLLDIALOG_H

#include <QWidget>

namespace Ui {
class EnrollDialog;
}

class EnrollDialog : public QWidget
{
    Q_OBJECT

public:
    explicit EnrollDialog(QWidget *parent = nullptr);
    ~EnrollDialog();

private:
    Ui::EnrollDialog *ui;
};

#endif // ENROLLDIALOG_H
