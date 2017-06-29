INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
SOURCES += \
    CustomWidgets/Overlay/overlaycontrols.cpp

HEADERS += \
    CustomWidgets/Overlay/overlaycontrols.h

OTHER_FILES += \
    CustomWidgets/Overlay/qml/Overlay/*.qml \
    CustomWidgets/Overlay/qml/smallOverlay/*.qml

FORMS += \
    CustomWidgets/Overlay/overlaycontrols.ui


RESOURCES += \
    CustomWidgets/Overlay/overlayResources.qrc
