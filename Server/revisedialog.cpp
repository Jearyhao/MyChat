#include "revisedialog.h"
#include "ui_revisedialog.h"

ReviseDialog::ReviseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReviseDialog)
{
    ui->setupUi(this);
    ui->idEdit_2->setPlaceholderText("请输入id:");
    ui->passwordEdit_2->setPlaceholderText("请输入新的密码:");
    ui->confirmPasswordEdit_2->setPlaceholderText("请确认新的密码:");
    ui->passwordEdit_2->setEchoMode(QLineEdit::Password);
    ui->confirmPasswordEdit_2->setEchoMode(QLineEdit::Password);
    ui->reviseButton->setEnabled(false); // 初始时禁用修改按钮

    connect(ui->returnLoginButton_2, &QPushButton::clicked, this, &ReviseDialog::on_returnLoginButton_clicked);
    connect(ui->idEdit_2, &QLineEdit::textChanged, this, &ReviseDialog::on_inputFieldsChanged);
    connect(ui->passwordEdit_2, &QLineEdit::textChanged, this, &ReviseDialog::on_inputFieldsChanged);
    connect(ui->confirmPasswordEdit_2, &QLineEdit::textChanged, this, &ReviseDialog::on_inputFieldsChanged);
}
void ReviseDialog::on_inputFieldsChanged() //恢复修改密码按钮
{
    bool enableButton = !ui->idEdit_2->text().isEmpty() &&
                        !ui->passwordEdit_2->text().isEmpty() &&
                        !ui->confirmPasswordEdit_2->text().isEmpty();
    ui->reviseButton->setEnabled(enableButton);
}
ReviseDialog::~ReviseDialog()
{
    delete ui;
}

void ReviseDialog::on_returnLoginButton_clicked()
{
    ui->idEdit_2->clear();
    ui->passwordEdit_2->clear();
    ui->confirmPasswordEdit_2->clear();
    QWidget *parent = this->parentWidget(); // 获取父窗口
    if (parent)
    {
        parent->show(); // 显示父窗口
    }
    this->close(); // 关闭当前窗口

}

void ReviseDialog::on_reviseButton_clicked()
{
    QString id = ui->idEdit_2->text();
    QString newPassword = ui->passwordEdit_2->text();
    QString confirmPassword = ui->confirmPasswordEdit_2->text();

    if (newPassword != confirmPassword) {
        qDebug() << "两次输入的密码不一致";
        QMessageBox::information(this, "失败", "两次输入的密码不一致");
        return;
    }
    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "查询失败: " << query.lastError().text();
        return;
    }
    if (!query.next()) {
        qDebug() << "账号不存在";
        return;
    }
    query.prepare("UPDATE users SET password = :password WHERE id = :id");
    query.bindValue(":password", newPassword);
    query.bindValue(":id", id);
    if (query.exec()) {
        qDebug() << "密码修改成功";
        QMessageBox::information(this, "成功", "密码修改成功");
    } else {
        qDebug() << "密码修改失败: " << query.lastError().text();
    }
}
