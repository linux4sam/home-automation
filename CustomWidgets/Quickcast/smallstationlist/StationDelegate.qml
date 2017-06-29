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

    width: itemWidth
    height: itemHeight
    property double scaleW: 480/800
    property double scaleH: 272 / 480;

    signal clicked

    MouseArea {
        anchors.fill: parent
        onClicked: wrapper.clicked(index)
    }

    BorderImage {
        source: "../toolbutton.sci"
        anchors.fill: parent
        smooth: true
        opacity: 0.7
    }

    Column {
        id: cols

        spacing: 4*scaleH
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left; leftMargin: 8*scaleW
            right: parent.right; rightMargin: 8*scaleW
        }

        Text {
            text: name
            width: cols.width
            elide: Text.ElideRight
            color: "#afafaf"
            font.pixelSize: 16*scaleH
            font.bold: true
        }

        Text {
            text: genre
            color: "#9f9f9f"
            width: cols.width
            elide: Text.ElideRight
            font.pixelSize: 14*scaleH
            font.capitalization: Font.Capitalize
        }
    }
}
