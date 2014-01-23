#-------------------------------------------------
#
# Project created by QtCreator 2014-01-23T01:27:33
#
#-------------------------------------------------
QT       += core
QT       += gui

TARGET = untitled
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    streaming_window.cpp
unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += gstreamer-0.10
}

HEADERS += \
    streaming_window.h

unix:!macx:!symbian: LIBS += -L$$PWD/GstSupport/build/ -lGstSupport

INCLUDEPATH += $$PWD/GstSupport/include
DEPENDPATH += $$PWD/GstSupport/include
