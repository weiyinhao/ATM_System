#-------------------------------------------------
#
# Project created by QtCreator 2019-12-09T15:53:14
#
#-------------------------------------------------

QT       += core gui sql
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ATMBackgroundManagementSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    login.cpp \
    Config/helper.cpp \
    Config/connectionpool.cpp

HEADERS += \
        widget.h \
    login.h \
    Config/helper.h \
    Config/connectionsql.h \
    Config/sqlserver.h \
    Config/connectionpool.h

FORMS += \
        widget.ui \
    login.ui

DISTFILES += \
    Config/11.txt

RESOURCES += \
    img.qrc
