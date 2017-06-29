INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
SOURCES += \
    CustomWidgets/Camera/videowidget.cpp \
    CustomWidgets/Camera/capturethread.cpp \
    CustomWidgets/Camera/cameracapture.cpp

HEADERS += \
    CustomWidgets/Camera/videowidget.h \
    CustomWidgets/Camera/capturethread.h \
    CustomWidgets/Camera/cameracapture.h

OTHER_FILES += \

LIBS += -lv4l2 -lv4lconvert

DEFINES += __STDC_CONSTANT_MACROS

FORMS += \
    CustomWidgets/Camera/cameracapture.ui

RESOURCES += \
    CustomWidgets/Camera/cameraResources.qrc
