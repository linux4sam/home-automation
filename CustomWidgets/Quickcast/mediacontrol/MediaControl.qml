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

    property int elapsedTime: 0
    property bool isPlaying: false

    signal stopClicked

    width: childrenRect.width; height: childrenRect.height

    Row {
        id: panel

        spacing: 8

        StopButton {
            id: stopButton

            enabled: isPlaying // TODO: `enable` in 1.5 
            onClicked: wrapper.stopClicked()
        }

        VolumeSlider {
            id: volumeSlider

            volume: streaming.volumeControl.volume
            anchors.verticalCenter: stopButton.verticalCenter
            onVolumeChanged: streaming.volumeControl.volume = volume
        }

        Text {
            id: elapsed

            function formatTime(time) {
                var sec = Math.floor(time/1000)
                var min = Math.floor(sec/60)
                sec = sec % 60
                if (sec <= 9)
                    sec = "0" + sec
                return "" + min + ":" + sec
            }

            height: stopButton.height
            width: 50
            text: formatTime(wrapper.elapsedTime)
            color: "#5f5f5f"
            font.pixelSize: 16
            verticalAlignment: Text.AlignVCenter
        }
    }
}
