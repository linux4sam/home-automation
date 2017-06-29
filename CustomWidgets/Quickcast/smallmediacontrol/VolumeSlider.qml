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

Image {
    id: container
    signal volumeChanged;   
    property real volume : 0
    source: "bar.png" //120x16
    property int maxX: 108*(480/800);

    MouseArea {
        anchors.fill: parent
        anchors.leftMargin: 4; anchors.rightMargin: 4 //half of slider
        onClicked: slider.x = mouse.x //set center on click
    }

    Image {
        id: slider
        source: "slider.png" //12x12
        anchors.verticalCenter: parent.verticalCenter
        Behavior on x {
            NumberAnimation {
                    easing.type: "OutBack"
                    duration: 300
            }
        }
        x: volume * maxX //container.width-slider.width
        onXChanged: {
            volume = slider.x / maxX
            container.volumeChanged(volume)
        }
        MouseArea {
            anchors.fill: parent
            drag.target: parent; drag.axis: "XAxis"; drag.minimumX: 0; drag.maximumX: maxX
        }
    }
}
