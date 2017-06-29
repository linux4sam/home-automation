/*
 * Copyright (c) 2010 Mario Boikov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

import QtQuick 1.1
import "smallmediacontrol"
import "smallstationlist"

Image {
    id: main

    property double scaleW: 480/800
    property double scaleH: 272 / 480;

    property int itemWidth: 200*scaleW
    property int itemHeight: 60*scaleH

    width: 600*scaleW
    height: 400*scaleH
    source: "welcome_bg.png"
    focus: true

    Item {
        id: header

        height: childrenRect.height
        anchors { top: parent.top; left: parent.left; right: stationView.left }

        Column {
            spacing: 10*scaleH
            anchors { top: parent.top; topMargin: 10*scaleH; left: parent.left; right: parent.right }

            Text {
                text: "Internet Radio"
                width: parent.width
                color: "#0F93DD"
                font { pixelSize: 20*scaleH; bold: true }
                textFormat: Text.PlainText
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                text: "LIVE radios from around the world.\n\nPlease select a station"
                width: parent.width
                color: "#cfcfcf"
                font.pixelSize: 14*scaleH
                textFormat: Text.PlainText
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    Text {
        id: footer

        text: "Volume"
        color: "#afafaf"
        font.pixelSize: 10*scaleH
        horizontalAlignment: Text.AlignHCenter
        anchors { left: parent.left; right: stationView.left; bottom: parent.bottom; bottomMargin: 5 }
    }

    NowPlaying {
        id: currentStream

        station: streaming.metaData.name
        artist: streaming.metaData.artist
        title: streaming.metaData.title
        genre: streaming.metaData.genre
        homepage: streaming.metaData.homepage
        bitrate: streaming.metaData.bitrate
        opacity: streaming.isStreaming ?  1 : 0

        anchors {
            top: header.bottom
            bottom: control.top
            left: header.left
            right: stationView.left
            margins: 40*scaleH;
        }

        Behavior on opacity {
            NumberAnimation { duration: 500 }
        }
    }

    Text {
        id: errorMessage

        width: 400*scaleW; height: 200*scaleH
        opacity: streaming.hasError ? 1 : 0
        text: qsTr("Not connected to Internet?:\n") + streaming.errorMessage
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "red"
        scale : streaming.hasError ? 1 : 0.4

        font { bold: true; pixelSize: 14*scaleH }
        anchors {
            margins: 40*scaleH; top: header.bottom;
            horizontalCenter: header.horizontalCenter;
            verticalCenter: parent.verticalCenter
        }

        Behavior on scale {
            NumberAnimation { duration: 600; easing.type: Easing.OutBounce }
        }

        Behavior on opacity {
            NumberAnimation { duration: 300 }
        }
    }

    MediaControl {
        id: control

        isPlaying: streaming.isStreaming
        elapsedTime: streaming.elapsedTime
        anchors.bottom: footer.top; anchors.bottomMargin: 0
        anchors.horizontalCenter: header.horizontalCenter
        onStopClicked: streaming.stop()
    }

    PathView {
        id: stationView

        width: itemWidth; height: parent.height
        model: stationModel
        pathItemCount: height/itemHeight
        delegate: StationDelegate { width: itemWidth; height: itemHeight; onClicked: streaming.start(index) }
        anchors.right: parent.right
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        clip: true
        path: Path {
            startX: stationView.width+(itemHeight/2); startY: -(itemHeight/2)
            PathQuad { x: stationView.width+(itemHeight/2); y: stationView.height+(itemHeight/2); controlX: -(itemHeight/2); controlY: stationView.height/2 }
        }
    }

    Keys.onDownPressed: stationView.incrementCurrentIndex()
    Keys.onUpPressed: stationView.decrementCurrentIndex()
}
