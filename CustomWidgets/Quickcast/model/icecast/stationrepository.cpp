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

#include <QtGlobal>
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    #include <QtConcurrent/QtConcurrent>
#endif // (QT_VERSION >= 0x050000)

#include <QDir>
#include <QFile>
#include <QtCore>

#include "icecastdirectoryparser.h"
#include "icecastdirectorydownloader.h"
#include "station.h"
#include "stationrepository.h"

using namespace icecast;

StationRepository::StationRepository(QObject *parent) : QObject(parent)
{
    downloader = new IcecastDirectoryDownloader(this);
    downloader->setUrl(QUrl("http://dir.xiph.org/yp.xml"));
    downloader->setCacheFile("./stations/yp.xml");
    connect(downloader, SIGNAL(directoryUpdated(QString)), SLOT(directoryUpdated(QString)));
}

void StationRepository::refresh(bool force)
{
//	QtConcurrent::run(downloader, &IcecastDirectoryDownloader::download, force);
    downloader->download(force);
}

Station *StationRepository::byIndex(int index) const
{
    if (index >= 0 && index < m_stations.count()) {
        return m_stations.at(index);
    } else {
        return 0;
    }
}

int StationRepository::count() const
{
    return m_stations.count();
}

void StationRepository::directoryUpdated(const QString &filename)
{
	QtConcurrent::run(this, &StationRepository::threadedDirectoryUpdated, filename);
}

void StationRepository::threadedDirectoryUpdated(const QString &filename)
{
    QFile xmlFile(filename);

    if (!xmlFile.open(QFile::ReadOnly)) {
        qDebug("Failed to open file [%s]: %s", qPrintable(xmlFile.fileName()), qPrintable(xmlFile.errorString()));
        return;
    }

    QList<Station*> stations;
    IcecastDirectoryParser parser(stations);
    if (parser.read(&xmlFile)) {
        emit beginDirectoryUpdate();
        qDeleteAll(m_stations);
        m_stations.clear();
        m_stations = stations;
        emit endDirectoryUpdate();
    } else {
        qDebug("Error: %s", qPrintable(parser.errorString()));
    }
}
