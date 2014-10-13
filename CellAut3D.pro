#-------------------------------------------------
#
# Project created by QtCreator 2014-09-03T18:15:46
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CellAut3D
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    cube.cpp \
    jogodavida.cpp \
    flocosneve.cpp \
    neighbors.cpp \
    testneighbors.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    cube.h \
    jogodavida.h \
    flocosneve.h \
    neighbors.h \
    testneighbors.h

FORMS    += mainwindow.ui

LIBS += -lglut -lGLU
