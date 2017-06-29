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

Rectangle {
    id: container

    signal volumeChanged;

    width: slider.width * 10
    height: slider.height + 4

    property int sliderMaxWidth : container.width - slider.width
    property int volume : 50
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#424242" }
        GradientStop { position: 1.0; color: "#717171" }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: container.moveSlider(mouse.x)
    }

    function moveSlider(x) {
        console.log("x: ", x)

        var swidth = slider.width ///2

        if (x <= swidth) {
            slider.x = 0
        } else if (x >= container.width - swidth) {
            slider.x = sliderMaxWidth
        } else {
            slider.x = x - swidth
        }
    }

    radius: 8; opacity: 0.7; smooth: true
    Rectangle {
        id: slider

        anchors.verticalCenter: parent.verticalCenter
        Behavior on x {
            SequentialAnimation {
                NumberAnimation {
                    easing.type: "OutBack"
                    duration: 300
                }
            }
        }

        x: Math.round((volume*sliderMaxWidth)/100) //volume*(container.width-slider.width)/100
        y: 0; width: 12; height: 12
        radius: 6; smooth: true
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#ffffff" }
            GradientStop { position: 1.0; color: "#fefefe" }
        }
        MouseArea {
            anchors.fill: parent
            drag.target: parent; drag.axis: "XAxis"; drag.minimumX: 0; drag.maximumX: sliderMaxWidth
        }

        onXChanged: {
            if (x < 0) {
                volume = 0;
            } else {
                volume = Math.round(100*slider.x/sliderMaxWidth) //(container.width-slider.width);
                console.log("onXChanged, volume=", volume)
                container.volumeChanged(volume)
            }
        }
    }
}
