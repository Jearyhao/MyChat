#include "serverdialog.h"
#include "loginserver.h"
#include "revisedialog.h"
#include "enrolldialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginServer w;
    w.show();
    return a.exec();
}
