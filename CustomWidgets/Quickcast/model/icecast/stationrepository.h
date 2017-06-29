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

#ifndef STATIONREPOSITORY_H
#define STATIONREPOSITORY_H

#include <QObject>
#include <QList>

class QUrl;

namespace icecast {

class Station;
class IcecastDirectoryDownloader;

/**
 * The station repository communicates with the Icecast directory service and
 * manages the collection with stations.
 */
class StationRepository : public QObject
{
    Q_OBJECT

public:
    explicit StationRepository(QObject *parent = 0);

    Station *byIndex(int index) const;

    int count() const;
    void threadedDirectoryUpdated(const QString &filename);

signals:
    void beginDirectoryUpdate();
    void endDirectoryUpdate();

public slots:
    void refresh(bool force=false);

private slots:
    void directoryUpdated(const QString &filename);

private:
    QList<Station*> m_stations;
    IcecastDirectoryDownloader *downloader;
};

} // namespace icecast

#endif // STATIONREPOSITORY_H
