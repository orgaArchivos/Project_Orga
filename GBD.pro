#-------------------------------------------------
#
# Project created by QtCreator 2014-04-27T14:40:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GBD
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    masterbloque.cpp \
    mdtbloque.cpp \
    databloque.cpp \
    migestor.cpp \
    metadata.cpp

HEADERS  += mainwindow.h \
    masterbloque.h \
    mdtbloque.h \
    databloque.h \
    migestor.h \
    metadata.h

FORMS    += mainwindow.ui

RESOURCES += \
    iconos.qrc
