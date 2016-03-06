# -------------------------------------------------
# Project created by QtCreator 2010-10-29T15:54:07
# -------------------------------------------------
QT -= gui
TARGET = CP2112_HIDAPI
TEMPLATE = lib
CONFIG += staticlib
HEADERS += ../include/hidapi.h
SOURCES += cp2112_hidapi.cpp
# -------------------------------------------------
# Add appropriate source file depending on OS
# -------------------------------------------------
macx:  SOURCES += mac/hid.c
unix: !macx:  SOURCES += linux/hid.c
win32: SOURCES += windows/hid.c

#-------------------------------------------------
# HID API Requirements to compile in Qt
# Make sure to add the required libraries or
# frameoworks for the hidapi to work depending on
# what OS is being used
#-------------------------------------------------
macx: LIBS += -framework CoreFoundation -framework IOkit
win32: LIBS += -lSetupAPI
#link to the libudev library for hidraw HIDAPI
#unix: !macx: LIBS += -ludev
#link to usb-1.0 for libusb HIDAPI
unix: !macx: LIBS += -lusb-1.0

# -------------------------------------------------
# Make sure output directory for object file and
# library is in the correct subdirectory
# -------------------------------------------------

DESTDIR = ../lib

