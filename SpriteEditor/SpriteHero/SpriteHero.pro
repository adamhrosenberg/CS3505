#-------------------------------------------------
#
# Project created by QtCreator 2016-03-30T21:37:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpriteHero
TEMPLATE = app
CONFIG += c++11

#unix: CONFIG += link_pkgconfig
#unix: PKGCONFIG += Magick++

SOURCES += main.cpp\
        mainwindow.cpp \
    spriteview.cpp \
    colorchooser.cpp \
    model.cpp \
    introdialog.cpp \
    recentcolorlabel.cpp

HEADERS  += mainwindow.h \
    spriteview.h \
    colorchooser.h \
    model.h \
    introdialog.h \
    recentcolorlabel.h

FORMS    += mainwindow.ui \
    colorchooser.ui \
    introdialog.ui
