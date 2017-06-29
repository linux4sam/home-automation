
import QtQuick 1.1
import "qrc:/qml/smallkeyboard/assets"

Item {
    id: top_canvas
    width: 480
    height: 130
    signal sigEnterButtonPressed (string key)
    function presetText(text)
    {
        text_input.text=text;
    }

    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: 39
        color: "white"

    TextInput {
        id: text_input
        anchors.centerIn: parent
        text: qsTr("text")
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 12
    }
    }

    KeyboardLogic {
        id: kbd
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
    }
}







