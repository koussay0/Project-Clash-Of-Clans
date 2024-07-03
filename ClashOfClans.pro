QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Imageelemnt.cpp \
    bullet.cpp \
    castle.cpp \
    citizens.cpp \
    defense.cpp \
    empty.cpp \
    enemy.cpp \
    fence.cpp \
    game.cpp \
    healthmarker.cpp \
    lostwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    node.cpp \
    optionswindow.cpp \
    wongame.cpp \
    wonlevel.cpp

HEADERS += \
    Imageelemnt.h \
    bullet.h \
    castle.h \
    citizens.h \
    defense.h \
    empty.h \
    enemy.h \
    fence.h \
    game.h \
    healthmarker.h \
    lostwindow.h \
    mainwindow.h \
    node.h \
    optionswindow.h \
    wongame.h \
    wonlevel.h

FORMS += \
    lostwindow.ui \
    mainwindow.ui \
    optionswindow.ui \
    wongame.ui \
    wonlevel.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
