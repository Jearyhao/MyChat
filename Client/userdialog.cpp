#include "userdialog.h"
#include "ui_userdialog.h"

UserDialog::UserDialog(const QString &id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDialog),
    userId(id)
{
    ui->setupUi(this);
    // 查询数据库，获取用户的头像路径
    QSqlQuery query;
    query.prepare("SELECT headphoto FROM user_headphoto WHERE id = :id");
    query.bindValue(":id", userId);
    query.exec();
    if (query.next()) {
        qDebug() << "sussess";
        avatarPath = query.value(0).toString();
        setAvatar(avatarPath);// 设置头像
    }
    // 查询数据库，获取用户的昵称
    query.prepare("SELECT nickname FROM users WHERE id = :id");
    query.bindValue(":id", userId);
    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "查询数据库失败: " + query.lastError().text());
        return;
    }

    if (query.next()) {
        QString nickName = query.value(0).toString();
        setNickName(nickName); // 设置昵称
    }// 查询数据库，获取用户的个性签名

    /*query.prepare("SELECT signature FROM users WHERE id = :id");
    query.bindValue(":id", userId);
    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "查询数据库失败: " + query.lastError().text());
        return;
    }

    if (query.next()) {
        QString signature = query.value(0).toString();
        if (signature.isEmpty()) {
            signature = "该用户很懒，还没有设置个性签名";
        }
        setPersonalizedSignature(signature); // 设置个性签名
    } else {
        setPersonalizedSignature("该用户很懒，还没有设置个性签名"); // 设置默认个性签名
    }*/
    setPersonalizedSignature("该用户很懒，还没有设置个性签名");
}

UserDialog::~UserDialog()
{
    delete ui;

}
void UserDialog::setAvatar(const QString &avatarPath)
{
    this->avatarPath = avatarPath;
    QPixmap avatar(avatarPath);
    if (avatar.isNull()) {
        QMessageBox::warning(this, "错误", "加载头像失败");
    } else {
        // 调整头像大小以适应 headPhotoLabel
        QSize labelSize = ui->headPhotolabel->size();
        int side = qMin(labelSize.width(), labelSize.height());
        QPixmap scaledAvatar = avatar.scaled(side, side, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

        // 创建圆形头像
        QPixmap circularAvatar(side, side);
        circularAvatar.fill(Qt::transparent);

        QPainter painter(&circularAvatar);
        painter.setRenderHint(QPainter::Antialiasing);
        QPainterPath path;
        path.addEllipse(0, 0, side, side);
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, scaledAvatar);

        ui->headPhotolabel->setPixmap(circularAvatar);
    }
}
void UserDialog::setNickName(const QString &nickName)
{
    ui->nikenameLabel->setText(nickName);
}
void UserDialog::setPersonalizedSignature(const QString &signature)
{
    ui->personalizedSignatureEdit->setText(signature);
}
