#include "revisedialog.h"
#include "ui_revisedialog.h"

ReviseDialog::ReviseDialog(QWidget *parent) :
    QDialog(parent, Qt::Window),
    ui(new Ui::ReviseDialog)
{
    ui->setupUi(this);
    ui->idEdit->setPlaceholderText("请输入id:");
    ui->passwordEdit->setPlaceholderText("请输入密码:");
    ui->confirmPasswordEdit->setPlaceholderText("请确认密码:");
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    ui->reviseButton->setEnabled(false); // 初始时修改密码按钮
    connect(ui->idEdit, &QLineEdit::textChanged, this, &ReviseDialog::on_inputFieldsChanged);
    connect(ui->passwordEdit, &QLineEdit::textChanged, this, &ReviseDialog::on_inputFieldsChanged);
    connect(ui->confirmPasswordEdit, &QLineEdit::textChanged, this, &ReviseDialog::on_inputFieldsChanged);
}

ReviseDialog::~ReviseDialog()
{
    delete ui;
}


void ReviseDialog::on_returnLoginButton_clicked()
{
    ui->idEdit->clear();
    ui->passwordEdit->clear();
    ui->confirmPasswordEdit->clear();
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    QWidget *parent = this->parentWidget(); // 获取父窗口
    if (parent)
    {
        parent->show(); // 显示父窗口
    }
    this->close(); // 关闭当前窗口
}

void ReviseDialog::on_inputFieldsChanged()
{
    bool allFieldsFilled = !ui->idEdit->text().isEmpty() &&
                           !ui->passwordEdit->text().isEmpty() &&
                           !ui->confirmPasswordEdit->text().isEmpty();

        // 根据输入字段的状态启用或禁用修改密码按钮
    ui->reviseButton->setEnabled(allFieldsFilled);
}
void ReviseDialog::on_reviseButton_clicked()
{
    QString id = ui->idEdit->text();
    QString password = ui->passwordEdit->text();
    QString confirmPassword = ui->confirmPasswordEdit->text();

    // 检查数据库中是否存在相同的id
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "查询数据库失败: " + query.lastError().text());
        return;
    }

    if (query.next() && query.value(0).toInt() == 0) {
        QMessageBox::warning(this, "错误", "该ID不存在，请检查输入的ID");
        ui->idEdit->clear();
        ui->passwordEdit->clear();
        ui->confirmPasswordEdit->clear();
        return;
    }

    // 检查密码是否一致
    if (password != confirmPassword) {
        QMessageBox::warning(this, "错误", "两次输入的密码不一致，请重新输入");
        ui->confirmPasswordEdit->clear();
        return;
    }

    // 更新用户密码
    query.prepare("UPDATE users SET password = :password WHERE id = :id");
    query.bindValue(":password", password);
    query.bindValue(":id", id);
    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "更新数据失败: " + query.lastError().text());
        return;
    }
    QMessageBox::information(this, "成功", "修改密码成功！");
}
