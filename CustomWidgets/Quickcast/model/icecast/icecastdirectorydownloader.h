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

#ifndef ICECASTDIRECTORYDOWNLOADER_H
#define ICECASTDIRECTORYDOWNLOADER_H

#include <QObject>

#include "util/urldownloader.h"

class QUrl;
class QFile;

namespace icecast {

/**
 * Downloads and caches the Icecast directory xml file.
 *
 * When a download is triggered the expire time is checked, if the time has
 * not expired the cached file is read else a new directory file is downloaded
 * from the Icecast directory.
 *
 * This behavior can be overriden by passing 'force=true' when calling
 * download().
 *
 * The default expire time is 24h.
 */
class IcecastDirectoryDownloader : public QObject
{
    Q_OBJECT
public:
    explicit IcecastDirectoryDownloader(QObject *parent = 0);

    void setUrl(const QUrl &url);

    void setCacheFile(const QString file);

    void setCacheExpires(qint64 secs);

signals:
    void directoryUpdated(const QString &filename);

public slots:
    void download(bool force = false);

private slots:
    void finished();

private:
    UrlDownloader downloader;

    qint64 m_expires;
};

} // namespace icecast

#endif // ICECASTDIRECTORYDOWNLOADER_H
