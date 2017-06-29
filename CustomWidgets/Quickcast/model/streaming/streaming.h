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

#ifndef STREAMING_H
#define STREAMING_H

#include <QObject>
#include <QPointer>
#include <QMap>

class QUrl;

namespace media {
    class MediaPlayer;
    class VolumeControl;
}

namespace icecast {
    class StationRepository;
}

namespace streaming {

class MetaData;

/**
 * Service which handles stream playback.
 */
class Streaming : public QObject
{
    Q_OBJECT

    Q_PROPERTY(streaming::MetaData *metaData READ metaData NOTIFY metaDataChanged)
    Q_PROPERTY(bool isStreaming READ isStreaming NOTIFY streamingChanged())
    Q_PROPERTY(qint64 elapsedTime READ elapsedTime NOTIFY elapsedTimeChanged())
    Q_PROPERTY(media::VolumeControl *volumeControl READ volumeControl() CONSTANT)
    Q_PROPERTY(bool hasError READ hasError NOTIFY error)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY error)

public:
    Streaming(icecast::StationRepository *repo, media::MediaPlayer *player, QObject *parent=0);

    /**
     * Returns true if streaming is active else false.
     */
    bool isStreaming() const;

    /**
     * Return the stream's current meta data or null if not streaming.
     */
    MetaData *metaData() const;

    /**
     * Return the elapsed time in seconds playing this stream.
     */
    qint64 elapsedTime() const;

    /**
     * Return the volume control.
     */
    media::VolumeControl *volumeControl() const;

    /**
     * Returns true if there is an error preventing playback.
     */
    bool hasError() const;

    /**
     * Returns the error message.
     */
    QString errorMessage() const;

public slots:
    /**
     * Start streaming station at the specified index in the repository.
     */
    void start(int index);

    /**
     * Stop streaming.
     */
    void stop();

signals:
    /**
     * Signal emitted on 'isStreaming' changes.
     */
    void streamingChanged(bool isStreaming);

    /**
     * Signal emitted on meta data changes.
     * This signal will also be emitted when the stream is stopped and
     * the metaData will be a null pointer.
     */
    void metaDataChanged(const streaming::MetaData *metaData);

    /**
     * Signal emitted on elapsed time changes.
     * This signal will also be emitted when the stream is stopped nad
     * the elapsed time will be zero.
     */
    void elapsedTimeChanged(qint64 time);

    /**
     * Signal emitted when an error has occured.
     */
    void error(const QString &msg);

private slots:
    void updateMetaData(const QMap<QString,QString> &md);

private:
    QPointer<media::MediaPlayer> m_player;
    QPointer<icecast::StationRepository> m_repository;
    MetaData *m_metaData;
};

} // namespace streaming

#endif // STREAMING_H
