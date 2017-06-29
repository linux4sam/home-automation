// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item {
    id: applicationItem; width: GridView.view.cellWidth; height: GridView.view.cellHeight

    function applicationClicked() {

////        console.log("clicked  "+ applicationName)
////        if(applicationName == "climate"){
////            overlay.onClimateButtonPressed()
////        }else if(applicationName == "lighting"){
////            overlay.onLightingButtonPressed()
////        }else if(applicationName == "media"){
////            overlay.onMediaButtonPressed()
////        }else if (applicationName == "security"){
////            overlay.onSecurityButtonPressed()
////        }

        switch(applicationType){
        case 1:
            console.log("clicked  climate")
            overlay.onClimateButtonPressed()
            break;
        case 2:
            console.log("clicked  lighting")
            overlay.onLightingButtonPressed()
            break;
        case 3:
            console.log("clicked  media")
            overlay.onMediaButtonPressed()
            break;
        case 4:
            console.log("clicked  security")
            overlay.onSecurityButtonPressed()
            break;
        case 5:
            console.log("clicked  home")
            overlay.onHomeButtonPressed()
            break;
        }

        loadingTimer.restart()
    }

    Item {
        anchors.centerIn: parent
        id: app

        scale: 0.0
        Behavior on scale { NumberAnimation { duration: 900; easing.type: Easing.InOutQuad} }

        Item {


            width: 34; height: 34; anchors.centerIn: parent

            Column {
                spacing: 15
                Rectangle {
                    id: appRect; width: 34; height: 34; color: "#00000000"; smooth: true
                    Image { id: thumb; source: applicationImage; x: 1; y: 1; width: 34; height: 34; smooth: true }
    //                Image { source: "images/gloss.png" }

                }
            }



            Timer {
                id: stateTimer
                interval: 200;
                repeat: false
                onTriggered: app.state = 'State1'
            }

        }

        states: [
           State {
                name: "Show"; when: thumb.status == Image.Ready
                PropertyChanges { target: app; scale: 1 }
            },

            State {
                name: "Pressed"
                PropertyChanges { target: app; scale: 1.5 }
            },
            State {
                name: "State1"
                PropertyChanges {target: app; scale: 1.0 }

            }

        ]
        transitions: [
            Transition {
                from: "Show"; to: "Start"
                ParentAnimation {
                    via: foreground
                    NumberAnimation { properties: "x,y"; duration: 500; easing.type: Easing.InOutQuad }
                }
            },
            Transition {
                NumberAnimation { properties: "scale"; duration: 200; easing.type: Easing.InOutQuart }
            }
        ]
    }
    MouseArea { anchors.fill: applicationItem; onClicked: { app.state = "Pressed"
                                                            stateTimer.start()
                                                            applicationClicked()

        }
    }
}
