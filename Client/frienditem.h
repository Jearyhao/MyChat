#ifndef FRIENDITEM_H
#define FRIENDITEM_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
namespace Ui {
class FriendItem;
}

class FriendItem : public QDialog
{
    Q_OBJECT

public:
    explicit FriendItem(QWidget *parent = nullptr);
    ~FriendItem();

    void setHeadPhoto(const QString &photoPath);

private:
    Ui::FriendItem *ui;
    
protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
};

#endif // FRIENDITEM_H
