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
        src/main.cpp \
        src/mainwindow.cpp \
    src/mov/BaseBox.cpp \
    src/FileReader.cpp \
    src/Mp4Display.cpp \
    src/mov/Mp4Parser.cpp \
    src/mov/DefaultContainerBox.cpp \
    src/mov/MovieHeaderBox.cpp \
    src/mov/TrackBox.cpp \
    src/mov/TrackHeaderBox.cpp \
    src/mov/MediaHeaderBox.cpp \
    src/mov/HandlerRefBox.cpp \
    src/mov/SampleDescBox.cpp \
    src/mov/VisualSampleEntry.cpp \
    src/mov/AudioSampleEntry.cpp \
    src/mov/TimeToSampleBox.cpp \
    src/mov/SyncSampleBox.cpp \
    src/mov/CompositionOffsetBox.cpp \
    src/mov/ChunkOffsetBox.cpp \
    src/mov/SampleToChunkBox.cpp \
    src/mov/SampleSizeBox.cpp \
    src/mov/MetaBox.cpp \
    src/mov/PrimaryItemBox.cpp \
    src/mov/ItemInfoBox.cpp \
    src/mov/ItemReferenceBox.cpp \
    src/mov/ItemLocationBox.cpp \
    src/mov/ItemPropertyContainerBox.cpp \
    src/mov/ItemPropertyAssociationBox.cpp \
    src/mov/SingleItemTypeReferenceBox.cpp

HEADERS += \
        src/mainwindow.h \
    src/mov/BaseBox.h \
    src/FileReader.h \
    src/Mp4Display.h \
    src/mov/Mp4Parser.h \
    src/mov/DefaultContainerBox.h \
    src/FourCC.h \
    src/mov/MovieHeaderBox.h \
    src/mov/TrackBox.h \
    src/mov/TrackHeaderBox.h \
    src/mov/MediaHeaderBox.h \
    src/mov/HandlerRefBox.h \
    src/mov/SampleDescBox.h \
    src/mov/VisualSampleEntry.h \
    src/mov/AudioSampleEntry.h \
    src/mov/TimeToSampleBox.h \
    src/mov/Mp4Define.h \
    src/mov/SyncSampleBox.h \
    src/mov/CompositionOffsetBox.h \
    src/mov/ChunkOffsetBox.h \
    src/mov/SampleToChunkBox.h \
    src/mov/SampleSizeBox.h \
    src/mov/MetaBox.h \
    src/mov/PrimaryItemBox.h \
    src/mov/ItemInfoBox.h \
    src/mov/ItemReferenceBox.h \
    src/mov/ItemLocationBox.h \
    src/mov/ItemPropertyContainerBox.h \
    src/mov/ItemPropertyAssociationBox.h \
    src/mov/SingleItemTypeReferenceBox.h

FORMS += \
    src/MainWindow.ui
