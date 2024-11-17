#include "revisedialog.h"
#include "ui_revisedialog.h"

ReviseDialog::ReviseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReviseDialog)
{
    ui->setupUi(this);
    ui->idEdit->setPlaceholderText("请输入id:");
    ui->passwordEdit->setPlaceholderText("请输入密码:");
    ui->confirmPasswordEdit->setPlaceholderText("请确认密码:");
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

}
