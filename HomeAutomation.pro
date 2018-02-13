#-------------------------------------------------
#
# Project created by QtCreator 2012-11-12T09:54:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += webkitwidgets multimediawidgets multimedia

    LIBS += -lQt5Concurrent

    SOURCES += volumeslider.cpp\
        seekslider.cpp
    HEADERS  += volumeslider.h \
        seekslider.h
} else {
    QT += phonon webkit
}

TARGET = HomeAutomation
TEMPLATE = app

OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build

include(CustomWidgets/TemperatureControl/temperaturecontrol.pri)
include(CustomWidgets/LightControl/lightingcontrol.pri)
include(CustomWidgets/Keyboard/keyboard.pri)
include(CustomWidgets/Weather/weather.pri)
include(CustomWidgets/Overlay/overlay.pri)
include(CustomWidgets/Camera/camera.pri)
include(CustomWidgets/Quickcast/quickcast.pri)
include(CustomWidgets/Quickcast/model/model.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    SlidingStackedWidget.cpp \
    atmelmediaplayer.cpp \
    helpscreen.cpp \
    maincontrols.cpp \
    settingsscreen.cpp \
    Settings/climatesettings.cpp \
    Settings/prefssettings.cpp \
    Settings/lightingsettings.cpp \
    hvacscreen.cpp \
    HVAC/hvacset.cpp \
    homescreen.cpp \
    HVAC/weatherforcast.cpp \
    HVAC/weatherdetail.cpp \
    HVAC/radarinfo.cpp \
    customtoolbutton.cpp \
    securityscreen.cpp \
    lightingscreen.cpp \
    mediascreen.cpp \
    Settings/mediasettings.cpp \
    Settings/securitysettings.cpp \
    imagebutton.cpp \
    imagewidget.cpp \
    zoneselector.cpp \
    HVAC/hvacselector.cpp

HEADERS  += mainwindow.h \
    SlidingStackedWidget.h \
    atmelmediaplayer.h \
    helpscreen.h \
    maincontrols.h \
    settingsscreen.h \
    Settings/climatesettings.h \
    Settings/prefssettings.h \
    Settings/lightingsettings.h \
    hvacscreen.h \
    HVAC/hvacset.h \
    homescreen.h \
    HVAC/weatherforcast.h \
    HVAC/weatherdetail.h \
    HVAC/radarinfo.h \
    customtoolbutton.h \
    securityscreen.h \
    lightingscreen.h \
    mediascreen.h \
    Settings/mediasettings.h \
    Settings/securitysettings.h \
    imagebutton.h \
    imagewidget.h \
    zoneselector.h \
    HVAC/hvacselector.h

FORMS    += mainwindow.ui \
    atmelmediaplayer.ui \
    helpscreen.ui \
    maincontrols.ui \
    settingsscreen.ui \
    Settings/climatesettings.ui \
    Settings/prefssettings.ui \
    Settings/lightingsettings.ui \
    hvacscreen.ui \
    HVAC/hvacset.ui \
    homescreen.ui \
    HVAC/weatherforcast.ui \
    HVAC/weatherdetail.ui \
    HVAC/radarinfo.ui \
    securityscreen.ui \
    lightingscreen.ui \
    mediascreen.ui \
    Settings/mediasettings.ui \
    Settings/securitysettings.ui

RESOURCES += \
    HA-resources.qrc \
    playerResources.qrc \
    homeScreen.qrc \
    HVACResources.qrc \
    mediaSelection.qrc

OTHER_FILES += \
    microchip-stylesheet.qss

target.path = /opt/HomeAutomation
target.files = HomeAutomation HomeAutomation.sh microchip-stylesheet.qss stations/ resources/ CustomWidgets/ media/ images/
configfile.path = /opt/ApplicationLauncher/applications/xml
configfile.files = configs/01-home-automation.xml
imagefile.path = /opt/ApplicationLauncher/applications/resources
imagefile.files = configs/home-automation.png
INSTALLS += target configfile imagefile

QMAKE_CXXFLAGS = -O3
QMAKE_CXXFLAGS_RELEASE =
