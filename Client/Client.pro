QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatingdialog.cpp \
    enrolldialog.cpp \
    logindialog.cpp \
    main.cpp \
    clientdialog.cpp \
    revisedialog.cpp \
    searchdialog.cpp

HEADERS += \
    chatingdialog.h \
    clientdialog.h \
    enrolldialog.h \
    logindialog.h \
    revisedialog.h \
    searchdialog.h

FORMS += \
    chatingdialog.ui \
    clientdialog.ui \
    enrolldialog.ui \
    logindialog.ui \
    revisedialog.ui \
    searchdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .qmake.stash \
    Client \
    Client.pro.user \
    Client.pro.user.4.8-pre1 \
    Client.pro.user.95c3b4a.22 \
    Makefile \
    clientdialog.o \
    main.o \
    moc_clientdialog.o
