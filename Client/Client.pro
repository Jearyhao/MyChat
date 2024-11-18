QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addfrienddialog.cpp \
    chatingdialog.cpp \
    enrolldialog.cpp \
    frienditem.cpp \
    friendlistdialog.cpp \
    logindialog.cpp \
    main.cpp \
    clientdialog.cpp \
    profiledialog.cpp \
    revisedialog.cpp \
    searchdialog.cpp \
    userdialog.cpp

HEADERS += \
    addfrienddialog.h \
    chatingdialog.h \
    clientdialog.h \
    enrolldialog.h \
    frienditem.h \
    friendlistdialog.h \
    logindialog.h \
    profiledialog.h \
    revisedialog.h \
    searchdialog.h \
    userdialog.h

FORMS += \
    addfrienddialog.ui \
    chatingdialog.ui \
    clientdialog.ui \
    enrolldialog.ui \
    frienditem.ui \
    friendlistdialog.ui \
    logindialog.ui \
    profiledialog.ui \
    revisedialog.ui \
    searchdialog.ui \
    userdialog.ui

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

RESOURCES += \
    headPhoto.qrc
