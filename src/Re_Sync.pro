#-------------------------------------------------
#
# Project created by QtCreator 2013-04-04T14:17:22
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Re_Sync
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           script.cpp \
           logic.cpp

HEADERS  += mainwindow.h \
            script.h \
            logic.h

FORMS    += mainwindow.ui

RESOURCES += Re_Sync.qrc

RC_FILE = Re_Sync.rc
