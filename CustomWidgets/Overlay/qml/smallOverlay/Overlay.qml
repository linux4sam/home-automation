// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: overlay

    signal onClimateButtonPressed()
    signal onLightingButtonPressed()
    signal onMediaButtonPressed()
    signal onSecurityButtonPressed()
    signal onHomeButtonPressed()

    width: 34
    height: 272
////    x: 0
////    y: 0
    state: "OffScreen"


    //color: "blue"
    //opacity: 0.75
    //border.color: "black"
    //border.width: 1
    //radius: 5

  //  PropertyAnimation on x { to: 0; duration: 1000; easing.type: Easing.OutBounce }
  //  PropertyAnimation on y { to: 50; duration: 1000; easing.type: Easing.OutBounce }

   // gradient: Gradient {
   //     GradientStop {position: 0.0; color: "grey"}
   //     GradientStop {position: 1.0; color: "black"}
   // }

    Image {
        id: image1
////        x: 0
////        y: 0
        width: 46
        height: 272
        fillMode: Image.TileHorizontally
        source: "../../smallresources/button-slider-on.png"
    }

    ListModel {
        id: buttonsModel

        ListElement {
////            applicationName: "climate"
            applicationType: 1
            applicationImage: "../../smallresources/button-climate-off.png"
        }
        ListElement {
////            applicationName: "lighting"
            applicationType: 2
            applicationImage: "../../smallresources/button-lighting-off.png"
        }
        ListElement {
////            applicationName: "media"
            applicationType: 3
            applicationImage: "../../smallresources/button-media-off.png"
        }
        ListElement {
////            applicationName: "security"
            applicationType: 4
            applicationImage: "../../smallresources/button-security-off.png"
        }
        ListElement {
////            applicationName: "home"
            applicationType: 5
            applicationImage: "../../smallresources/button-home-off.png"
        }
    }

    GridView {
        id: grid_view_front
////        x: 0
////        y: 0
        width: 34
        height: 272
        interactive: false
        highlightMoveDuration: -1
        highlightFollowsCurrentItem: false
        highlightRangeMode: GridView.NoHighlightRange


//      anchors.verticalCenter: parent.verticalCenter
////      anchors.verticalCenterOffset: -100
//        anchors { verticalCenterOffset: -60; verticalCenter: parent.verticalCenter}

        contentHeight: 34
        contentWidth: 34
        cellHeight: 55
        cellWidth: 34

        delegate: ApplicationDelegate {}
        model: buttonsModel

        MouseArea {
            id: overlayButton
            x: 31
            y: 118
            width: 24
            height: 35

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

            PropertyChanges {
                target: grid_view_front
                cellWidth: 33
                contentWidth: 34
            }
        },
        State {
            name: "OffScreen"
            PropertyChanges {target: overlay; x: -34 }

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
                NumberAnimation { properties: "x"; to: -40; duration: 500; easing.type: Easing.InOutQuad }
        }
    ]
}
