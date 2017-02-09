#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T14:29:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZorkUL
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Character.cpp \
    Command.cpp \
    CommandWords.cpp \
    item.cpp \
    Parser.cpp \
    Room.cpp \
    tracer.cpp


HEADERS  += mainwindow.h \
    Character.h \
    Command.h \
    CommandWords.h \
    item.h \
    Parser.h \
    Room.h \
    tracer.h \
    redefinenewkeyword.h


FORMS    += mainwindow.ui

RESOURCES += \
    img.qrc
win32:RC_FILE = myapp.rc
