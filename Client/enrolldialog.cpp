#include "enrolldialog.h"
#include "ui_enrolldialog.h"

EnrollDialog::EnrollDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnrollDialog)
{
    ui->setupUi(this);
    ui->idEdit->setPlaceholderText("请输入id:");
    ui->passwordEdit->setPlaceholderText("请输入密码:");
    ui->confirmPasswordEdit->setPlaceholderText("请确认密码:");
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

void EnrollDialog::on_enrollButton_clicked()
{

}
