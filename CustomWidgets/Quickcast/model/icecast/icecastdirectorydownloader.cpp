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

#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>

#include "icecastdirectorydownloader.h"

using namespace icecast;

IcecastDirectoryDownloader::IcecastDirectoryDownloader(QObject *parent) :
    QObject(parent), m_expires(60*60*24)
{
    connect(&downloader, SIGNAL(finished()), SLOT(finished()));
}

void IcecastDirectoryDownloader::setUrl(const QUrl &url)
{
    downloader.setUrl(url);
}

void IcecastDirectoryDownloader::setCacheFile(const QString file)
{
    downloader.setDestination(file);
}

void IcecastDirectoryDownloader::download(bool force)
{
    if (downloader.isActive())
        return;

    if (!force) {
        QFileInfo info(downloader.destination());
        QDateTime expireDate = info.lastModified().addSecs(m_expires);
        if (expireDate >= QDateTime::currentDateTime()) {
            qDebug("Cached file not expired, skipping update...");
            finished();
            return;
        }
    }
    qDebug("Updating icecast directory cache file");
    downloader.download();
}

void IcecastDirectoryDownloader::finished()
{
    emit directoryUpdated(downloader.destination());
}
