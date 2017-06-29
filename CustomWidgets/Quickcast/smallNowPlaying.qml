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

Item {
    id: wrapper

    property string station
    property string artist
    property string title
    property string genre
    property string homepage
    property int bitrate

    property double scaleW: 480/800
    property double scaleH: 272 / 480;

    BorderImage {
        source: "smalltoolbutton.sci"
        anchors.fill: parent
        smooth: true
        opacity: 0.7
    }

    Column {
        id: cols

        spacing: 4
        anchors { fill: parent; margins: 10 *scaleH}

        Text {
            text: station
            width: cols.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            color: "#dfdfdf"
            font.bold: true
            font.pixelSize: 14*scaleH
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            function createOnAir(artist, title) {
                if (!artist && !title) {
                    return qsTr("N/A")
                } else if (artist && title) {
                    return artist + " - " + title
                } else if (artist) {
                    return artist
                } else {
                    return title
                }
            }

            text: qsTr("<b>On Air:</b> %1").arg(createOnAir(artist, title))
            color: "#bfbfbf"
            width: cols.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            font.pixelSize: 12*scaleH
        }
        Text {
            text: qsTr("<b>Tags:</b> %1").arg(genre ? genre : qsTr("N/A"))
            color: "#bfbfbf"
            width: cols.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            font.pixelSize: 12*scaleH
            font.capitalization: Font.Capitalize
        }
        Text {
            text: qsTr("<b>Bitrate:</b> %1").arg(bitrate ? bitrate : qsTr("N/A"))
            color: "#bfbfbf"
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            width: cols.width
            font.pixelSize: 12*scaleH
        }
        Text {
            text: qsTr("<b>Url:</b> <a style='color: #bfbfbf' href='%1'>%1</a>").arg(homepage ? homepage : qsTr("N/A"))
            color: "#bfbfbf"
            width: cols.width
            wrapMode: Text.WrapAnywhere
            font.pixelSize: 12*scaleH
            onLinkActivated: Qt.openUrlExternally(streamMetaData.homepage)
        }
    }
}
