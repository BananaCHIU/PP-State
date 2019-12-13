QT       += core gui
QT += multimedia multimediawidgets
QT += opengl
win32:RC_ICONS += res/icon.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Block.cpp \
    Bullet.cpp \
    Character.cpp \
    Dog.cpp \
    Game.cpp \
    House.cpp \
    Player.cpp \
    Raptor.cpp \
    Trigger.cpp \
    instruction.cpp \
    main.cpp \
    menu.cpp

HEADERS += \
    Block.h \
    Bullet.h \
    Character.h \
    Dog.h \
    Game.h \
    House.h \
    Node.h \
    Node.tpp \
    Player.h \
    Queue.h \
    Queue.tpp \
    Raptor.h \
    Trigger.h \
    instruction.h \
    menu.h

FORMS += \
    instruction.ui \
    mainwindow.ui \
    menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    res.qrc
