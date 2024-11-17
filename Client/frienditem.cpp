#include "frienditem.h"
#include "ui_frienditem.h"

FriendItem::FriendItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendItem)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint); // 设置无边框
    setAttribute(Qt::WA_TranslucentBackground); // 设置透明背景
}

FriendItem::~FriendItem()
{
    delete ui;
}
void FriendItem::setHeadPhoto(const QString &photoPath)
{
    QPixmap pixmap(photoPath);
    if (!pixmap.isNull()) {
        // 调整图片大小以适应 headphotoLabel
        QSize labelSize = ui->headphotolabel->size();
        int side = qMin(labelSize.width(), labelSize.height());
        QPixmap scaledPixmap = pixmap.scaled(side, side, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        // 创建圆形头像
        QPixmap circularPixmap(side, side);
        circularPixmap.fill(Qt::transparent);

        QPainter painter(&circularPixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        QPainterPath path;
        path.addEllipse(0, 0, side, side);
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, scaledPixmap);

        ui->headphotolabel->setPixmap(circularPixmap);
    } else {
        ui->headphotolabel->setText("无法加载图片");
    }
}
void FriendItem::enterEvent(QEvent *event)
{
    this->setStyleSheet("FriendItem { border: 1px solid black; }"); // 鼠标进入时设置边框
    QDialog::enterEvent(event);
}

void FriendItem::leaveEvent(QEvent *event)
{
    setStyleSheet(""); // 鼠标离开时移除边框
    //this->setStyleSheet("FriendItem { border: none; }"); // 鼠标离开时移除边框
    QDialog::leaveEvent(event);
}