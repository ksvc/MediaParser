#-------------------------------------------------
#
# Project created by QtCreator 2017-09-25T20:29:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MediaParser
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
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
    BaseBox.cpp \
    FileReader.cpp \
    Mp4Display.cpp \
    Mp4Parser.cpp \
    DefaultContainerBox.cpp \
    MovieHeaderBox.cpp \
    TrackBox.cpp \
    TrackHeaderBox.cpp \
    MediaHeaderBox.cpp \
    HandlerRefBox.cpp \
    SampleDescBox.cpp \
    VisualSampleEntry.cpp \
    AudioSampleEntry.cpp \
    TimeToSampleBox.cpp

HEADERS += \
        mainwindow.h \
    BaseBox.h \
    FileReader.h \
    Mp4Display.h \
    Mp4Parser.h \
    DefaultContainerBox.h \
    FourCC.h \
    MovieHeaderBox.h \
    TrackBox.h \
    TrackHeaderBox.h \
    MediaHeaderBox.h \
    HandlerRefBox.h \
    SampleDescBox.h \
    VisualSampleEntry.h \
    AudioSampleEntry.h \
    TimeToSampleBox.h \
    Mp4Define.h

FORMS += \
    MainWindow.ui
