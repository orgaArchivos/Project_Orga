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
    metadata.cpp \
    campo.cpp \
    metacampos.cpp \
    datas.cpp \
    indiceshash.cpp \
    indice1.cpp

HEADERS  += mainwindow.h \
    masterbloque.h \
    mdtbloque.h \
    databloque.h \
    migestor.h \
    metadata.h \
    campo.h \
    metacampos.h \
    datas.h \
    indiceshash.h \
    indice1.h

FORMS    += mainwindow.ui

RESOURCES += \
    iconos.qrc

OTHER_FILES += \
    Descripción-InformaciónGeneral.txt
