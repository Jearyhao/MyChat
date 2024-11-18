#include "userdialog.h"
#include "ui_userdialog.h"

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
    ui->tabWidget->setCurrentWidget(ui->chatingtab);
    //创建好友列表
    FriendItem *friendItem = new FriendItem();
    friendItem->setHeadPhoto(":/headPhoto/11.jpg");
    QListWidgetItem * m_Item = new QListWidgetItem(ui->chatinglistWidget);
    //设置管理项，m_Item的宽高
    m_Item->setSizeHint(QSize(281, 64));
    //将自定义的Qwidget---friendItem，设置为m_Item的小部件
    ui->chatinglistWidget->setItemWidget(m_Item, friendItem);
}

UserDialog::~UserDialog()
{
    delete ui;

}
void UserDialog::onModifyProfile()
{
    qDebug() << "onModifyProfile called";
    ProfileDialog *profileDialog = new ProfileDialog(userId, this);
    profileDialog->setAttribute(Qt::WA_DeleteOnClose); // 确保对话框关闭时自动删除
    profileDialog->show();
}

void UserDialog::onAddFriend()
{
    qDebug() << "onAddFriend called";
    AddFriendDialog *addFriendDialog = new AddFriendDialog(this);
    addFriendDialog->setAttribute(Qt::WA_DeleteOnClose); // 确保对话框关闭时自动删除
    addFriendDialog->show();
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


