INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
SOURCES += \
    CustomWidgets/Weather/weatherxmlcontenthandler.cpp \
    CustomWidgets/Weather/weatherwidget.cpp \
    CustomWidgets/Weather/dayweatherdetail.cpp \
    CustomWidgets/Weather/dayweather.cpp
HEADERS += \
    CustomWidgets/Weather/weatherxmlcontenthandler.h \
    CustomWidgets/Weather/weatherwidget.h \
    CustomWidgets/Weather/dayweatherdetail.h \
    CustomWidgets/Weather/dayweather.h
OTHER_FILES += \
    CustomWidgets/Weather/resources/weather-stylesheet.qss

QT += network xml

FORMS += \
    CustomWidgets/Weather/weatherwidget.ui \
    CustomWidgets/Weather/dayweatherdetail.ui \
    CustomWidgets/Weather/dayweather.ui

RESOURCES += \
    CustomWidgets/Weather/weatherIcons.qrc \
    CustomWidgets/Weather/weatherXmlFeed.qrc
