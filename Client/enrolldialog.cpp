#include "enrolldialog.h"
#include "ui_enrolldialog.h"

EnrollDialog::EnrollDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnrollDialog)
{
    ui->setupUi(this);
    ui->nickNameEdit->setPlaceholderText("请输入你的昵称:");
    ui->idEdit->setPlaceholderText("请输入id:");
    ui->passwordEdit->setPlaceholderText("请输入密码:");
    ui->confirmPasswordEdit->setPlaceholderText("请确认密码:");
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    ui->enrollButton->setEnabled(false); // 初始时禁用注册按钮
    connect(ui->idEdit, &QLineEdit::textChanged, this, &EnrollDialog::on_inputFieldsChanged);
    connect(ui->passwordEdit, &QLineEdit::textChanged, this, &EnrollDialog::on_inputFieldsChanged);
    connect(ui->confirmPasswordEdit, &QLineEdit::textChanged, this, &EnrollDialog::on_inputFieldsChanged);
    connect(ui->checkBox, &QCheckBox::stateChanged, this, &EnrollDialog::on_inputFieldsChanged);
}

EnrollDialog::~EnrollDialog()
{
    delete ui;
}

void EnrollDialog::on_returnLoginButton_clicked()
{
    ui->checkBox->setChecked(false); // 取消勾选
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

void EnrollDialog::on_inputFieldsChanged()
{
    // 检查所有输入字段是否已填写
    bool allFieldsFilled = !ui->idEdit->text().isEmpty() &&
                           !ui->passwordEdit->text().isEmpty() &&
                           !ui->confirmPasswordEdit->text().isEmpty() &&
                           ui->checkBox->isChecked();

    // 根据输入字段的状态启用或禁用注册按钮
    ui->enrollButton->setEnabled(allFieldsFilled);
}
void EnrollDialog::on_enrollButton_clicked() {
    QString nickName = ui->nickNameEdit->text();
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

    if (query.next() && query.value(0).toInt() > 0) {
        QMessageBox::warning(this, "错误", "该ID已被注册，请使用其他ID");
        return;
    }

    // 检查密码是否一致
    if (password != confirmPassword) {
        QMessageBox::warning(this, "错误", "两次输入的密码不一致，请重新输入");
        ui->confirmPasswordEdit->clear();
        return;
    }

    // 插入新用户数据
    query.prepare("INSERT INTO users (nickname, id, password) VALUES (:nickname, :id, :password)");
    query.bindValue(":nickname", nickName);
    query.bindValue(":id", id);
    query.bindValue(":password", password);
    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "插入数据失败: " + query.lastError().text());
        return;
    }

    QMessageBox::information(this, "成功", "注册成功！");
    this->close();
}
