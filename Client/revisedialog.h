#ifndef REVISEDIALOG_H
#define REVISEDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlError>

#include <QMessageBox>

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
    void on_inputFieldsChanged(); // 添加槽函数声明
    void on_reviseButton_clicked();

private:
    Ui::ReviseDialog *ui;
};

#endif // REVISEDIALOG_H
