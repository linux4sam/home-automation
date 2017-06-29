// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: overlay

    signal onClimateButtonPressed()
    signal onLightingButtonPressed()
    signal onMediaButtonPressed()
    signal onSecurityButtonPressed()

    width: 58
    height: 480
    state: "OffScreen"

   // gradient: Gradient {
   //     GradientStop {position: 0.0; color: "grey"}
   //     GradientStop {position: 1.0; color: "black"}
   // }

    Image {
        id: image1
////        x: 0
////        y: 0
        width: 78
        height: 480
        source: "../../resources/button-slider-on.png"
    }

    ListModel {
        id: buttonsModel

        ListElement {
////            applicationName: "climate"
            applicationType: 1
            applicationImage: "../../resources/button-climate-off.png"
        }
        ListElement {
////            applicationName: "lighting"
            applicationType: 2
            applicationImage: "../../resources/button-lighting-off.png"
        }
        ListElement {
////            applicationName: "media"
            applicationType: 3
            applicationImage: "../../resources/button-media-off.png"
        }
        ListElement {
////            applicationName: "security"
            applicationType: 4
            applicationImage: "../../resources/button-security-off.png"
        }
    }

    GridView {
        id: grid_view_front
        width: 60
        height: 280
        interactive: false
        highlightMoveDuration: -1
        highlightFollowsCurrentItem: false
        highlightRangeMode: GridView.NoHighlightRange

////      anchors.verticalCenterOffset: -100
        anchors { verticalCenterOffset: -100; verticalCenter: parent.verticalCenter}

        contentHeight: 60
        contentWidth: 60
        cellHeight: 70
        cellWidth: 60

        delegate: ApplicationDelegate {}
        model: buttonsModel

        MouseArea {
            id: overlayButton
            x: 50
            y: 193
            width: 41
            height: 100

            onClicked: {
                if (overlay.state == "OffScreen")
                {
                    overlay.state = "OnScreen"
                    loadingTimer.start()
                }else{
                    overlay.state = "OffScreen"
                }
            }
        }
    }

    Timer {
        id: loadingTimer
        interval: 4000;
        repeat: false
        onTriggered: overlay.state = "OffScreen"
    }

    states: [
        State {
            name: "OnScreen"
            PropertyChanges { target: overlay; x: 0 }
        },
        State {
            name: "OffScreen"
            PropertyChanges {target: overlay; x: -55 }

        }

    ]

    transitions: [
        Transition {
            from: "OffScreen"; to: "OnScreen"
 //           ParentAnimation {
 //               via: foreground
                NumberAnimation { properties: "x"; to: 0; duration: 500; easing.type: Easing.InOutQuad }
               // PropertyAnimation on x { to: 0; duration: 1000; easing.type: Easing.OutBounce }
 //           }
        },
        Transition {
            from: "OnScreen"; to: "OffScreen"
                NumberAnimation { properties: "x"; to: -55; duration: 500; easing.type: Easing.InOutQuad }
        }
    ]
}
