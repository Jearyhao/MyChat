#include "userdialog.h"
#include "ui_userdialog.h"
#include "friendlistdialog.h"
UserDialog::UserDialog(const QString &id, QWidget *parent) :
    QDialog(parent, Qt::Window),
    ui(new Ui::UserDialog),
    userId(id)
{
    ui->setupUi(this);
    // 创建一个 QMenu 对象
    QMenu *menu = new QMenu(this);

    // 向 QMenu 对象中添加 QAction
    QAction *option1 = new QAction("修改资料", this);
    QAction *option2 = new QAction("添加好友", this);

    menu->addAction(option1);
    menu->addAction(option2);

    // 将 QMenu 设置为 QToolButton 的菜单
    ui->settingButton->setMenu(menu);
    ui->settingButton->setPopupMode(QToolButton::InstantPopup);
    // 连接 QAction 的 triggered 信号到槽函数
    connect(option1, &QAction::triggered, this, &UserDialog::onModifyProfile);
    connect(option2, &QAction::triggered, this, &UserDialog::onAddFriend);
    // 查询数据库，获取用户的头像路径
    QSqlQuery query;
    query.prepare("SELECT headphoto FROM users WHERE id = :id");
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
    }
    // 查询数据库，获取用户的个性签名
    query.prepare("SELECT signature FROM users WHERE id = :id");
    query.bindValue(":id", userId);
    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "查询数据库失败: " + query.lastError().text());
        return;
    }
    if (query.next()) {
        QString signature = query.value(0).toString();
        setPersonalizedSignature(signature); // 设置个性签名
    }
    loadFriendList();
    ui->nikenameLabel->setFocus();

}

UserDialog::~UserDialog()
{
    // 更新用户的在线状态为离线
    QSqlQuery query;
    query.prepare("UPDATE users SET online = 0 WHERE id = :id");
    query.bindValue(":id", userId);
    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "更新在线状态失败: " + query.lastError().text());
    }
    delete ui;

}
void UserDialog::onModifyProfile()
{
    qDebug() << "onModifyProfile called";
    ProfileDialog *profileDialog = new ProfileDialog(userId, this);
    profileDialog->setAttribute(Qt::WA_DeleteOnClose); // 确保对话框关闭时自动删除
    connect(profileDialog, &ProfileDialog::profileUpdated, this, &UserDialog::updateProfile); // 连接信号到槽函数
    profileDialog->show();
}

void UserDialog::onAddFriend()
{
    qDebug() << "onAddFriend called";
    AddFriendDialog *addFriendDialog = new AddFriendDialog(userId, this);
    addFriendDialog->setAttribute(Qt::WA_DeleteOnClose); // 确保对话框关闭时自动删除
    addFriendDialog->show();
}
void UserDialog::updateProfile()
{
    // 重新加载用户信息
    QSqlQuery query;
    query.prepare("SELECT headphoto, nickname, signature FROM users WHERE id = :id");
    query.bindValue(":id", userId);
    if (query.exec()) {
        if (query.next()) {
            QString avatarPath = query.value("headphoto").toString();
            QString nickName = query.value("nickname").toString();
            QString signature = query.value("signature").toString();
            setAvatar(avatarPath);
            setNickName(nickName);
            setPersonalizedSignature(signature);
        } else {
            QMessageBox::warning(this, tr("错误"), tr("未找到用户信息"));
        }
    } else {
        QMessageBox::warning(this, tr("错误"), tr("无法查询数据库: ") + query.lastError().text());
    }
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
void UserDialog::loadFriendList()
{
    ui->friendlistWidget->clear(); // 清空好友列表

    QSqlQuery query;
    query.prepare("SELECT friend_id FROM relationship WHERE user_id = :user_id");
    query.bindValue(":user_id", userId);
    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "查询好友列表失败: " + query.lastError().text());
        return;
    }

    while (query.next()) {
        QString friendId = query.value(0).toString();
        qDebug() << "Friend ID:" << friendId;
        QSqlQuery friendQuery;
        friendQuery.prepare("SELECT nickname, headphoto, signature, online FROM users WHERE id = :id");
        friendQuery.bindValue(":id", friendId);
        if (!friendQuery.exec()) {
            QMessageBox::critical(this, "错误", "查询好友信息失败: " + friendQuery.lastError().text());
            continue;
        }

        if (friendQuery.next()) {
            QString nickname = friendQuery.value("nickname").toString();
            QString headphoto = friendQuery.value("headphoto").toString();
            QString signature = friendQuery.value("signature").toString();
            int online = friendQuery.value("online").toInt();
            qDebug() << "Friend nickname:" << nickname;
            qDebug() << "Friend headphoto:" << headphoto;
            qDebug() << "Friend signature:" << signature;
            qDebug() << "Friend online:" << online;

            QListWidgetItem *item = new QListWidgetItem(ui->friendlistWidget);
            FriendListDialog *friendListItem = new FriendListDialog(userId, friendId);
            friendListItem->ui->nickNameLabel->setText(nickname);
            friendListItem->ui->signatureLabel->setText(signature);
            friendListItem->ui->onlineLabel->setText(online ? "在线" : "离线");

            QPixmap pixmap(headphoto);
            if (!pixmap.isNull()) {
                // 将头像缩放到指定大小
                pixmap = pixmap.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                // 创建一个透明的圆形 QPixmap
                QPixmap circularPixmap(pixmap.size());
                circularPixmap.fill(Qt::transparent);
                QPainter painter(&circularPixmap);
                painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿
                // 创建一个圆形路径
                QPainterPath path;
                path.addEllipse(0, 0, pixmap.width(), pixmap.height());
                // 裁剪为圆形
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, pixmap);
                // 设置圆形头像到标签
                friendListItem->ui->headPhotoLabel->setPixmap(circularPixmap);
            }
            item->setSizeHint(QSize(604, 100));
            //item->setSizeHint(friendItem->sizeHint());
            ui->friendlistWidget->setItemWidget(item, friendListItem);
        }
    }
}

