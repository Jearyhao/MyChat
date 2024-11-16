#ifndef REVISEDIALOG_H
#define REVISEDIALOG_H

#include <QWidget>

namespace Ui {
class ReviseDialog;
}

class ReviseDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ReviseDialog(QWidget *parent = nullptr);
    ~ReviseDialog();

private:
    Ui::ReviseDialog *ui;
};

#endif // REVISEDIALOG_H
