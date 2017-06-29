INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += core network

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += webkitwidgets multimedia
    LIBS += -lQt5Concurrent

    HEADERS += \
        CustomWidgets/Quickcast/model/media/customvolumecontrol.h \
        CustomWidgets/Quickcast/model/media/custommediaplayer.h
    SOURCES += \
        CustomWidgets/Quickcast/model/media/customvolumecontrol.cpp \
        CustomWidgets/Quickcast/model/media/custommediaplayer.cpp
} else {
    QT += phonon
    HEADERS += \
        CustomWidgets/Quickcast/model/media/phononmediaplayer.h \
        CustomWidgets/Quickcast/model/media/nullvolumecontrol.h \
        CustomWidgets/Quickcast/model/media/phononvolumecontrol.h
    SOURCES += \
        CustomWidgets/Quickcast/model/media/phononmediaplayer.cpp \
        CustomWidgets/Quickcast/model/media/nullvolumecontrol.cpp \
        CustomWidgets/Quickcast/model/media/phononvolumecontrol.cpp
}

# Input
HEADERS += \
    CustomWidgets/Quickcast/model/util/urldownloader.h \
    CustomWidgets/Quickcast/model/media/mediaplayer.h \
    CustomWidgets/Quickcast/model/icecast/stationtablemodel.h \
    CustomWidgets/Quickcast/model/icecast/station.h \
    CustomWidgets/Quickcast/model/icecast/stationrepository.h \
    CustomWidgets/Quickcast/model/icecast/icecastdirectoryparser.h \
    CustomWidgets/Quickcast/model/streaming/streaming.h \
    CustomWidgets/Quickcast/model/streaming/metadata.h \
    CustomWidgets/Quickcast/model/media/volumecontrol.h \
    CustomWidgets/Quickcast/model/icecast/icecastdirectorydownloader.h \


SOURCES += \
    CustomWidgets/Quickcast/model/util/urldownloader.cpp \
    CustomWidgets/Quickcast/model/icecast/stationtablemodel.cpp \
    CustomWidgets/Quickcast/model/icecast/stationrepository.cpp \
    CustomWidgets/Quickcast/model/icecast/icecastdirectoryparser.cpp \
    CustomWidgets/Quickcast/model/streaming/streaming.cpp \
    CustomWidgets/Quickcast/model/streaming/metadata.cpp \
    CustomWidgets/Quickcast/model/icecast/icecastdirectorydownloader.cpp \

