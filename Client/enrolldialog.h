#ifndef ENROLLDIALOG_H
#define ENROLLDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlError>

#include <QMessageBox>

namespace Ui {
class EnrollDialog;
}

class EnrollDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EnrollDialog(QWidget *parent = nullptr);
    ~EnrollDialog();

private slots:
    void on_returnLoginButton_clicked();
    void on_enrollButton_clicked();
    void on_inputFieldsChanged(); // 添加槽函数声明

private:
    Ui::EnrollDialog *ui;
};

#endif // ENROLLDIALOG_H
