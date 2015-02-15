#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T18:39:33
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = LoggingUtil
TEMPLATE = app
DESTDIR  = $$PWD/test

SOURCES += main.cpp\
           mainWindow.cpp \
           spamer.cpp \
    LoggingField.cpp

HEADERS  += mainWindow.h \
            spamer.h \
    LoggingField.h

FORMS    += mainWindow.ui
