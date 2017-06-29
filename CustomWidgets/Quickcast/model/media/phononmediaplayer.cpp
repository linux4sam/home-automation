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

#include <QUrl>


#include "phononvolumecontrol.h"
#include "phononmediaplayer.h"

using namespace media;

#include <phonon/MediaObject>
#include <phonon/MediaSource>
#include <phonon/AudioOutput>

PhononMediaPlayer::PhononMediaPlayer(QObject *parent) :
    MediaPlayer(parent)
{
    m_mediaObject = new Phonon::MediaObject(this);
    m_mediaObject->setTickInterval(1000);

    Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(m_mediaObject, audioOutput);

    connect(m_mediaObject, SIGNAL(tick(qint64)),this, SIGNAL(elapsedChanged(qint64)));
    connect(m_mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            SLOT(mediaObjectStateChanged(Phonon::State,Phonon::State)));
    connect(m_mediaObject, SIGNAL(metaDataChanged()), SLOT(updateMetaData()));

    m_volumeCtrl = new PhononVolumeControl(audioOutput, this);
}

void PhononMediaPlayer::play(const QUrl &url)
{
    if(!url.isEmpty())
        qDebug() << url.toString();
    m_mediaObject->clearQueue();
    m_mediaObject->setCurrentSource(Phonon::MediaSource(url));
    m_mediaObject->play();
}

void PhononMediaPlayer::stop()
{
    m_mediaObject->stop();
    m_mediaObject->clearQueue();
}

bool PhononMediaPlayer::isPlaying() const
{
    return m_mediaObject->state() == Phonon::PlayingState;
}

qint64 PhononMediaPlayer::elapsed() const
{
    return m_mediaObject->currentTime();
}

VolumeControl *PhononMediaPlayer::volumeControl() const
{
    return m_volumeCtrl;
}

bool PhononMediaPlayer::hasError() const
{
    return m_mediaObject->state() == Phonon::ErrorState;
}

QString PhononMediaPlayer::errorMessage() const
{
    return m_mediaObject->errorString();
}

const QMap<QString, QString> &PhononMediaPlayer::metaData() const
{
    return m_mediaObject->metaData();
}

void PhononMediaPlayer::updateMetaData()
{
    emit metaDataChanged(m_mediaObject->metaData());
}

void PhononMediaPlayer::mediaObjectStateChanged(Phonon::State newState, Phonon::State oldState)
{
    if (oldState == Phonon::ErrorState && newState != Phonon::ErrorState) {
        emit errorChanged(QString());
    }

    switch (newState) {
    case Phonon::LoadingState:
        qDebug("In Loading state");
        break;
    case Phonon::PausedState:
        qDebug("In Paused state");
        break;
    case Phonon::StoppedState:
        qDebug("In Stop state");
        if (oldState == Phonon::PlayingState) {
            emit playingChanged(false);
        }
        break;
    case Phonon::PlayingState:
        qDebug("In Playing state");
        emit playingChanged(true);
        break;
    case Phonon::BufferingState:
        qDebug("In Buffering state");
        break;
    case Phonon::ErrorState:
        emit errorChanged(errorMessage());
        qDebug("In Error state: %s", qPrintable(m_mediaObject->errorString()));
        break;
    }
}
