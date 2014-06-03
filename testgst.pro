#-------------------------------------------------
#
# Project created by QtCreator 2014-01-23T01:27:33
#
#-------------------------------------------------
QT       += core
QT       += gui
QT       += widgets

TARGET = GstQtWindow
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    streaming_window.cpp \
    mainwindow.cpp
unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += gstreamer-0.10
}

HEADERS += \
    streaming_window.h \
    mainwindow.h

unix:!macx:!symbian: LIBS += -L$$PWD/GstSupport/build/ -lGstSupport -lgstinterfaces-0.10

INCLUDEPATH += $$PWD/GstSupport/include
DEPENDPATH += $$PWD/GstSupport/include

FORMS += \
    mainwindow.ui
