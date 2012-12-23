#-------------------------------------------------
#
# Project created by QtCreator 2012-12-21T23:08:33
#
#-------------------------------------------------

QT       += core gui

TARGET = QtSAPIDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Speech/SREengine.cpp

HEADERS  += mainwindow.h \
    Speech/SREngine.h

FORMS    += mainwindow.ui

## Microsoft Speech API
INCLUDEPATH += L"D:/Program Files/Microsoft Speech SDK 5.1/Include/"
##LIBS += L"D:/Program Files/Microsoft Speech SDK 5.1/Lib/i386/"
