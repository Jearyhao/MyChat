#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QPixmap>
#include <QSqlQuery>
#include <QSqlError>
#include <QBitmap>
#include <QPainter>
namespace Ui {
class ProfileDialog;
}

class ProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileDialog(const QString &id, QWidget *parent = nullptr);
    ~ProfileDialog();

signals:
    void profileUpdated(); // 添加信号声明

private slots:
    void on_uploadButton_clicked(); // 添加槽函数声明

    void on_saveButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ProfileDialog *ui;
    QString userId; // 保存用户 ID
    void saveImage(const QString &sourcePath, const QString &destPath);
    void updateAvatarPathInDatabase(const QString &avatarPath);
    void updateUserInfoInDatabase(const QString &nickname, const QString &signature, const QString &country, const QString &birthday, const QString &region, const QString &sex); // 添加更新用户信息的函数声明
    void loadUserInfo(); // 添加加载用户信息的函数声明
    void setProfileButtonStyle(const QString &avatarPath); // 添加设置 profileButton 样式的函数声明

};

#endif // PROFILEDIALOG_H
