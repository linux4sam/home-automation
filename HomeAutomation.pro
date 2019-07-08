#-------------------------------------------------
#
# Project created by QtCreator 2012-11-12T09:54:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += multimediawidgets multimedia

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
include(CustomWidgets/Weather/weather.pri)
include(CustomWidgets/Camera/camera.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    SlidingStackedWidget.cpp \
    maincontrols.cpp \
    hvacscreen.cpp \
    HVAC/hvacset.cpp \
    homescreen.cpp \
    HVAC/weatherforcast.cpp \
    HVAC/weatherdetail.cpp \
    customtoolbutton.cpp \
    securityscreen.cpp \
    lightingscreen.cpp \
    imagebutton.cpp \
    imagewidget.cpp \
    zoneselector.cpp \
    HVAC/hvacselector.cpp

HEADERS  += mainwindow.h \
    SlidingStackedWidget.h \
    maincontrols.h \
    hvacscreen.h \
    HVAC/hvacset.h \
    homescreen.h \
    HVAC/weatherforcast.h \
    HVAC/weatherdetail.h \
    customtoolbutton.h \
    securityscreen.h \
    lightingscreen.h \
    imagebutton.h \
    imagewidget.h \
    zoneselector.h \
    HVAC/hvacselector.h

FORMS    += mainwindow.ui \
    maincontrols.ui \
    hvacscreen.ui \
    HVAC/hvacset.ui \
    homescreen.ui \
    HVAC/weatherforcast.ui \
    HVAC/weatherdetail.ui \
    securityscreen.ui \
    lightingscreen.ui \

RESOURCES += \
    HA-resources.qrc \
    playerResources.qrc \
    homeScreen.qrc \
    HVACResources.qrc

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
