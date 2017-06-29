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

#include <QXmlStreamReader>

#include "icecastdirectoryparser.h"
#include "station.h"

using namespace icecast;

IcecastDirectoryParser::IcecastDirectoryParser(QList<Station*> &stations) : items(stations)
{
}

bool IcecastDirectoryParser::read(QIODevice *device)
{
    xmlReader.setDevice(device);

    if (xmlReader.readNextStartElement() && xmlReader.name() == "directory") {
        readDirectory();
    } else {
        xmlReader.raiseError(QObject::tr("The file is not an icecast directory file"));
    }

    return !xmlReader.error();
}

QString IcecastDirectoryParser::errorString() const
{
    return xmlReader.errorString();
}

void IcecastDirectoryParser::readDirectory()
{
    while (xmlReader.readNextStartElement()) {
        if (xmlReader.name() == "entry") {
            readEntry();
        } else {
            xmlReader.skipCurrentElement();
        }
    }
    readOfflineEntry();
}

void IcecastDirectoryParser::readEntry()
{
    Station *item = new Station;

    while (xmlReader.readNextStartElement()) {

        if (xmlReader.name() == "server_name") {
            item->setName(xmlReader.readElementText());
        } else if (xmlReader.name() == "listen_url") {
            item->setUrl(xmlReader.readElementText());
        } else if (xmlReader.name() == "bitrate") {
            item->setBitrate(xmlReader.readElementText().toInt());
        } else if (xmlReader.name() == "genre") {
            item->setGenre(xmlReader.readElementText());
        } else if(xmlReader.name() == "server_type")
        {
            QString temp = xmlReader.readElementText();
            if(temp.compare(QString("application/ogg")) != 0){
                item->setName(QString(""));
                item->setUrl(QString(""));
                //break;
            }
        }else {
            xmlReader.skipCurrentElement();
        }
    }

    if (!item->url().isEmpty() && !item->name().isEmpty()) {
        items.append(item);
    }
}

void IcecastDirectoryParser::readOfflineEntry()
{
    Station *item = new Station;

    QUrl localSt = QUrl::fromLocalFile(QString("/opt/HomeAutomation/media/The_Sims_Theme_Sample.ogg"));
    item->setName(QString("Sample Offline Music"));
    item->setUrl(localSt);
    item->setBitrate(44000);
    item->setGenre(QString("Rock"));

    if (!item->url().isEmpty() && !item->name().isEmpty()) {
        items.append(item);
    }
}

