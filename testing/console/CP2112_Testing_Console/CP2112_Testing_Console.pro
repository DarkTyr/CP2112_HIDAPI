#-------------------------------------------------
#
# Project created by QtCreator 2014-09-09T20:58:35
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = CP2112_Testing_Console
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../../../src/cp2112_hidapi.cpp \
    ../../../src/windows/hid.c

HEADERS += \
    ../../../include/hidapi.h \
    ../../../include/cp2112_hidapi.h

#-------------------------------------------------
# HID API Requirements to compile in Qt
# Make sure to add the required libraries or
# frameoworks for the hidapi to work depending on
# what OS is being used
#-------------------------------------------------
macx: LIBS += -framework CoreFoundation -framework IOkit
win32: LIBS += -lSetupAPI
unix: !macx: LIBS += -lusb-1.0
