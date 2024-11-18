#include "profiledialog.h"
#include "ui_profiledialog.h"

ProfileDialog::ProfileDialog(const QString &id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileDialog),
    userId(id)
{
    ui->setupUi(this);
    connect(ui->headphotoButton, &QPushButton::clicked, this, &ProfileDialog::on_uploadButton_clicked); // 连接信号到槽函数
    //connect(ui->saveButton, &QPushButton::clicked, this, &ProfileDialog::on_saveButton_clicked);
    // 加载用户信息
    loadUserInfo();
}

ProfileDialog::~ProfileDialog()
{
    delete ui;
}
void ProfileDialog::loadUserInfo()
{
    QSqlQuery query;
    query.prepare("SELECT nickname, signature, country, birthday, region, sex, headphoto FROM users WHERE id = :id");
    query.bindValue(":id", userId);
    if (query.exec()) {
        if (query.next()) {
            ui->nicknameEdit->setText(query.value("nickname").toString());
            ui->signatureEdit->setText(query.value("signature").toString());
            ui->countryEdit->setText(query.value("country").toString());
            ui->birthdayEdit->setText(query.value("birthday").toString());
            ui->regionEdit->setText(query.value("region").toString());
            ui->comboBox->setCurrentText(query.value("sex").toString());
            QString avatarPath = query.value("headphoto").toString();
            setProfileButtonStyle(avatarPath); // 设置头像
        } else {
            QMessageBox::warning(this, tr("错误"), tr("未找到用户信息"));
        }
    } else {
        QMessageBox::warning(this, tr("错误"), tr("无法查询数据库: ") + query.lastError().text());
    }
}
void ProfileDialog::on_uploadButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择图片"), "", tr("Images (*.png *.xpm *.jpg)"));
    if (!filePath.isEmpty()) {
        QString destDir = QDir::currentPath() + "/temp";
        QDir().mkpath(destDir);

        QString fileName = QFileInfo(filePath).fileName();
        QString destPath = destDir + "/" + fileName;

        saveImage(filePath, destPath);
        updateAvatarPathInDatabase(destPath);
        setProfileButtonStyle(destPath); // 更新头像后设置 profileButton 样式
    }
}

void ProfileDialog::saveImage(const QString &sourcePath, const QString &destPath)
{
    QFile sourceFile(sourcePath);
    if (!sourceFile.copy(destPath)) {
        QMessageBox::warning(this, tr("错误"), tr("无法保存图片: ") + sourceFile.errorString());
    }
}

void ProfileDialog::updateAvatarPathInDatabase(const QString &avatarPath)
{
    QSqlQuery query;
    query.prepare("UPDATE users SET headphoto = :headphoto WHERE id = :id");
    query.bindValue(":headphoto", avatarPath);
    query.bindValue(":id", userId);
    if (!query.exec()) {
        QMessageBox::warning(this, tr("错误"), tr("无法更新数据库: ") + query.lastError().text());
    }
}

void ProfileDialog::updateUserInfoInDatabase(const QString &nickname, const QString &signature, const QString &country, const QString &birthday, const QString &region, const QString &sex)
{
    QSqlQuery query;
    query.prepare("UPDATE users SET nickname = :nickname, signature = :signature, country = :country, birthday = :birthday, region = :region, sex = :gender WHERE id = :id");
    query.bindValue(":nickname", nickname);
    query.bindValue(":signature", signature);
    query.bindValue(":country", country);
    query.bindValue(":birthday", birthday);
    query.bindValue(":region", region);
    query.bindValue(":sex", sex);
    query.bindValue(":id", userId);
    if (!query.exec()) {
        QMessageBox::warning(this, tr("错误"), tr("无法更新数据库: ") + query.lastError().text());
    } else {
        QMessageBox::information(this, tr("成功"), tr("用户信息已更新"));
    }
}

void ProfileDialog::on_saveButton_clicked()
{
    QString nickname = ui->nicknameEdit->text();
    QString signature = ui->signatureEdit->text();
    QString country = ui->countryEdit->text();
    QString birthday = ui->birthdayEdit->text();
    QString region = ui->regionEdit->text();
    QString sex = ui->comboBox->currentText();

    updateUserInfoInDatabase(nickname, signature, country, birthday, region, sex);
    loadUserInfo();
}
void ProfileDialog::setProfileButtonStyle(const QString &avatarPath)
{
    QPixmap pixmap(avatarPath);
    if (!pixmap.isNull()) {
        int buttonWidth = ui->headphotoButton->width();
        int buttonHeight = ui->headphotoButton->height();

        // 缩放图片以适应按钮的大小
        QPixmap scaledPixmap = pixmap.scaled(buttonWidth, buttonHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // 将图片保存到临时文件
        QString tempPath = QDir::tempPath() + "/temp_avatar.png";
        scaledPixmap.save(tempPath);

        // 设置按钮样式表
        QString styleSheet = QString("QPushButton {"
                                     "border: none;"
                                     "background-image: url(%1);"
                                     "background-position: center;"
                                     "background-repeat: no-repeat;"
                                     "background-clip: padding-box;"
                                     "background-origin: content-box;"
                                     "}")
                                     .arg(tempPath);

        ui->headphotoButton->setStyleSheet(styleSheet);
        ui->headphotoButton->setText(""); // 移除按钮上的文字
    }
}
void ProfileDialog::on_cancelButton_clicked()
{
    loadUserInfo();
}
