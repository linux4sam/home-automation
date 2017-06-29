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

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFileInfo>
#include <QFile>
#include <QDir>

#include "urldownloader.h"

UrlDownloader::UrlDownloader(QObject *parent) :
    QObject(parent), m_nam(0), reply(0)
{
}

void UrlDownloader::setUrl(const QUrl &url)
{
    m_url = url;
}

void UrlDownloader::setDestination(const QString &file)
{
    m_destination.setFileName(file);
}

void UrlDownloader::setNetworkAccessManager(QNetworkAccessManager *nam)
{
    if (m_nam && m_nam->parent() == this) {
        delete m_nam;
    }
    m_nam = nam;
}

void UrlDownloader::download()
{
    if (reply) {
        return;
    }

    qDebug("Starting download");

    if (!m_url.isValid()) {
        // Set error and emit
        qDebug("Url not valid: %s", qPrintable(m_url.toString()));
        return;
    }

    // Check if dest dir exists, else create it
    QFileInfo fileInfo(m_destination);
    QDir destDir = fileInfo.absoluteDir();

    if (!destDir.exists() && !destDir.mkpath(".")) {
        // Set error and emit
        qDebug("Error creating directory");
        return;
    }

    if (!m_destination.open(QFile::WriteOnly)) {
        // Set error and emit
        qDebug("Can't open file for writing");
        return;
    }

    if (!m_nam) {
        m_nam = new QNetworkAccessManager(this);
        qDebug("Creating network manager");
    }

    reply = m_nam->get(QNetworkRequest(m_url));
    connect(reply, SIGNAL(readyRead()), SLOT(readyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), SIGNAL(progress(qint64,qint64)));
    connect(reply, SIGNAL(finished()), SLOT(replyFinished()));
}

bool UrlDownloader::isActive()
{
    return reply;
}

void UrlDownloader::replyFinished()
{
    if (reply->error() != QNetworkReply::NoError) {
        emit finished();
        return;
    }

    qDebug("Reply finished");
    if (!reply->atEnd()) {
        readyRead();
    }

    m_destination.close();
    reply->deleteLater();
    reply = 0;
    emit finished();
}

void UrlDownloader::readyRead()
{
    char buff[4096];
    int len;

    qDebug("Reading data...");
    while ( (len = reply->read(buff, sizeof(buff))) > 0 ) {
        if (m_destination.write(buff, len) < len) {
            // set and emit error
        }
    }
}
