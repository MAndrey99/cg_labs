QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KG4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawer.cpp

HEADERS  += mainwindow.h \
    drawer.h

FORMS    += mainwindow.ui
