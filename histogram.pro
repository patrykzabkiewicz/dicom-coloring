#-------------------------------------------------
#
# Project created by QtCreator 2011-03-09T20:41:49
#
#-------------------------------------------------

QT       += core gui

TARGET = histogram
TEMPLATE = app


LIBS += -L/usr/lib \
        -lvtkCommon \
        -lvtksys \
        -lQVTK \
        -lvtkViews \
        -lvtkWidgets \
        -lvtkInfovis \
        -lvtkRendering \
        -lvtkVolumeRendering \
        -lvtkGraphics \
        -lvtkImaging \
        -lvtkIO \
        -lvtkFiltering \
        -lvtkDICOMParser \
        -lvtkverdict \
        -lvtkmetaio \
        -lvtkNetCDF \
        -lvtksqlite \
        -lvtkexoIIc \
        -lvtkftgl \
        -lvtkHybrid

INCLUDEPATH += /usr/include/vtk-5.4

SOURCES += main.cpp \
    window.cpp \
    renderarea.cpp \
    points.cpp \
    preset.cpp

HEADERS  += \
    window.h \
    renderarea.h \
    points.h \
    preset.h

FORMS    +=
