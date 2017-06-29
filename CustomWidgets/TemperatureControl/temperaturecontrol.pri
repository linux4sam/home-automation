INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
SOURCES += \
    CustomWidgets/TemperatureControl/temperaturecontrol.cpp
HEADERS += \
    CustomWidgets/TemperatureControl/temperaturecontrol.h
OTHER_FILES += \
    $$PWD/resources/temp-dial-top.svg \
    $$PWD/resources/temp-dial-stylesheet.qss \
    CustomWidgets/TemperatureControl/resources/temp-dial-FINAL.svg

QT += svg

FORMS += \
    CustomWidgets/TemperatureControl/temperaturecontrol.ui

RESOURCES += \
    CustomWidgets/TemperatureControl/tempresources.qrc
