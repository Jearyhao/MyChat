#ifndef REVISEDIALOG_H
#define REVISEDIALOG_H

#include <QDialog>

namespace Ui {
class ReviseDialog;
}

class ReviseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReviseDialog(QWidget *parent = nullptr);
    ~ReviseDialog();

private slots:
    void on_returnLoginButton_clicked();

private:
    Ui::ReviseDialog *ui;
};

#endif // REVISEDIALOG_H
