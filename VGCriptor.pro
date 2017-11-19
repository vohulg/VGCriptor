#-------------------------------------------------
#
# Project created by QtCreator 2017-11-19T12:29:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VGCriptor
TEMPLATE = app


SOURCES += main.cpp\
        VGCriptor.cpp \
    aes.cpp

HEADERS  += VGCriptor.h \
    aes.h

FORMS    += VGCriptor.ui
