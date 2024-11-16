#ifndef ENROLLDIALOG_H
#define ENROLLDIALOG_H

#include <QDialog>

namespace Ui {
class EnrollDialog;
}

class EnrollDialog : public QDialog // 确保继承自 QDialog
{
    Q_OBJECT

public:
    explicit EnrollDialog(QWidget *parent = nullptr);
    ~EnrollDialog();

private slots:
    void on_returnLoginButton_clicked();

private:
    Ui::EnrollDialog *ui;
};

#endif // ENROLLDIALOG_H
