#-------------------------------------------------
#
# Project created by QtCreator 2020-04-05T00:15:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += charts

RC_ICONS = images/sigma.ico
RC_FILE = aproxim.rc
ICON = images/sigma.icns
win32::LIBS += -lQt5Axbase -lQt5AxContainer

TARGET = aproxim
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    approximator.cpp \
    approximator_2.cpp \
    dataanalysis.cpp \
    functions.cpp \
    options.cpp \
    util.cpp \
    xls_table.cpp

HEADERS += \
        mainwindow.h \
    approximator.h \
    approximator_2.h \
    dataanalysis.h \
    functions.h \
    options.h \
    util.h \
    xls_table.h

FORMS += \
        mainwindow.ui \
    options.ui

RESOURCES += \
    aproxim.qrc
