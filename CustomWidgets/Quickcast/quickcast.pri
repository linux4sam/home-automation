#TARGET = quickcast
QT += core declarative network

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += webkitwidgets
    LIBS += -lQt5Concurrent
} else {
    QT += phonon
}

SUBDIRS = model

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

#LIBS += -L./model -licecastmodel

#PRE_TARGETDEPS += ./libicecastmodel.a

SOURCES += CustomWidgets/Quickcast/quickcastwidget.cpp

HEADERS += CustomWidgets/Quickcast/quickcastwidget.h

FORMS += \
    CustomWidgets/Quickcast/quickcastwidget.ui

RESOURCES += \
    CustomWidgets/Quickcast/resources.qrc

OTHER_FILES += \
    CustomWidgets/Quickcast/QuickCastRadio.qml \
    CustomWidgets/Quickcast/NowPlaying.qml \
    CustomWidgets/Quickcast/mediacontrol/StopButton.qml \
    CustomWidgets/Quickcast/mediacontrol/MediaControl.qml \
    CustomWidgets/Quickcast/mediacontrol/VolumeSlider.qml \
    CustomWidgets/Quickcast/stationlist/StationDelegate.qml \
    CustomWidgets/Quickcast/smallNowPlaying.qml \
    CustomWidgets/Quickcast/smallQuickCastRadio.qml \
    CustomWidgets/Quickcast/smallmediacontrol/MediaControl.qml \
    CustomWidgets/Quickcast/smallmediacontrol/StopButton.qml \
    CustomWidgets/Quickcast/smallmediacontrol/VolumeSlider.qml \
    CustomWidgets/Quickcast/smallmediacontrol/bar.png \
    CustomWidgets/Quickcast/smallmediacontrol/slider.png \
    CustomWidgets/Quickcast/smallstationlist/StationDelegate.qml
