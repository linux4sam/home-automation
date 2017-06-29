
import QtQuick 1.1
import "qrc:/qml/keyboard/assets"

Item {
    id: top_canvas
    width: 800
    height: 300
    signal sigEnterButtonPressed (string key)
    function presetText(text)
    {
        text_input.text=text;
    }

    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: 70
        color: "white"

    TextInput {
        id: text_input
        anchors.centerIn: parent
        text: qsTr("text")
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 22
    }
    }

    KeyboardLogic {
        id: kbd
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
    }
}







