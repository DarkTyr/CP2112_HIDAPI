#-------------------------------------------------
#
# Project created by QtCreator 2014-09-09T20:58:35
#
#-------------------------------------------------

QT      += core
QT      -= gui

TARGET  = CP2112_Testing_Console
CONFIG  += console
CONFIG  -= app_bundle

TEMPLATE = app

HEADERS += \
    ../../../include/cp2112_hidapi.h \
    ../../../include/hidapi.h

SOURCES += main.cpp \
    ../../../src/cp2112_hidapi.cpp

# -------------------------------------------------
# Add appropriate source file depending on OS
# -------------------------------------------------
macx:  SOURCES += ../../../src/mac/hid.c
unix: !macx:  SOURCES += ../../../src/linux/hid.c
win32: SOURCES += ../../../src/windows/hid.c

#-------------------------------------------------
# HID API Requirements to compile in Qt
# Make sure to add the required libraries or
# frameoworks for the hidapi to work depending on
# what OS is being used
#-------------------------------------------------
macx: LIBS += -framework CoreFoundation -framework IOkit
win32: LIBS += -lSetupAPI
#link to the libudev library for hidraw HIDAPI
unix: !macx: LIBS += -ludev
#link to usb-1.0 for libusb HIDAPI
#unix: !macx: LIBS += -lusb-1.0

# -------------------------------------------------
# Make sure output directory for object file and
# library is in the correct subdirectory
# -------------------------------------------------
macx {
    DESTDIR = mac
    OBJECTS_DIR = mac
    MOC_DIR = mac
    UI_DIR = mac
    RCC_DIR = mac
}
unix: !macx {
    DESTDIR = linux
    OBJECTS_DIR = linux
    MOC_DIR = linux
    UI_DIR = linux
    RCC_DIR = linux
}
win32 {
    DESTDIR = windows
    OBJECTS_DIR = windows
    MOC_DIR = windows
    UI_DIR = windows
    RCC_DIR = windows
}

DISTFILES += \
    ../../../udev/hid-cp2112.rules
