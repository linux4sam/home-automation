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

//#include <phonon/MediaObject> //??

#include "media/mediaplayer.h"
#include "icecast/station.h"
#include "icecast/stationrepository.h"
#include "metadata.h"
#include "streaming.h"

using namespace streaming;

Streaming::Streaming(icecast::StationRepository *repo, media::MediaPlayer *player,
                     QObject *parent) :
    QObject(parent), m_player(player), m_repository(repo)
{
    m_metaData = new MetaData(this);

    connect(player, SIGNAL(playingChanged(bool)), SIGNAL(streamingChanged(bool)));
    connect(player, SIGNAL(elapsedChanged(qint64)), SIGNAL(elapsedTimeChanged(qint64)));
    connect(player, SIGNAL(errorChanged(QString)), SIGNAL(error(QString)));
    connect(player, SIGNAL(metaDataChanged(QMap<QString,QString>)),
            SLOT(updateMetaData(QMap<QString,QString>)));
}

bool Streaming::isStreaming() const
{
    return m_player ? m_player->isPlaying() : false;
}

void Streaming::start(int index)
{
    stop();

    icecast::Station *station = m_repository->byIndex(index);
    if (station) {
        m_metaData->m_url = station->url();
        m_metaData->m_name = station->name();
        m_metaData->m_genre = station->genre();
        m_metaData->m_bitrate = station->bitrate();
        m_player->play(station->url());
    }
}

void Streaming::stop()
{
    m_player->stop();
    emit metaDataChanged(0);
    emit elapsedTimeChanged(0);
}

media::VolumeControl *Streaming::volumeControl() const
{
    return m_player ? m_player->volumeControl() : 0;
}

qint64 Streaming::elapsedTime() const
{
    return isStreaming() ? m_player->elapsed() : 0;
}

streaming::MetaData *Streaming::metaData() const
{
    return m_metaData;
}

void Streaming::updateMetaData(const QMap<QString,QString> &md)
{
    m_metaData->updateMetaData(md);
    emit metaDataChanged(m_metaData);
}

bool Streaming::hasError() const
{
    return m_player ? m_player->hasError() : true;
}

QString Streaming::errorMessage() const
{
    return m_player ? m_player->errorMessage() : tr("No MediaPlayer instance");
}
