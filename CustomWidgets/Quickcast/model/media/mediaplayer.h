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

#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QObject>
#include <QMap>

class QUrl;

namespace media {

class VolumeControl;

/**
 * Media player interface.
 */
class MediaPlayer : public QObject
{
    Q_OBJECT

    /**
     * Constant Volume control property.
     */
    Q_PROPERTY(media::VolumeControl *volumeControl READ volumeControl() CONSTANT)

    /**
     * Playing state property.
     */
    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY playingChanged)

    /**
     * Elapsed playback time property.
     */
    Q_PROPERTY(qint64 elapsed READ elapsed NOTIFY elapsedChanged)

    /**
     * Property telling if the player is in error state.
     */
    Q_PROPERTY(bool hasError READ hasError NOTIFY errorChanged)

    /**
     * Property holding error message.
     */
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorChanged)

public:
    explicit MediaPlayer(QObject *parent = 0) : QObject(parent) {}

    virtual VolumeControl *volumeControl() const = 0;

    virtual bool isPlaying() const = 0;

    virtual qint64 elapsed() const = 0;

    virtual const QMap<QString, QString> &metaData() const = 0;

    virtual QString errorMessage() const = 0;

    virtual bool hasError() const = 0;

signals:
    void playingChanged(bool isPlaying);

    void elapsedChanged(qint64 time);

    void metaDataChanged(const QMap<QString, QString> &metaData);

    void errorChanged(QString message);

public slots:
    virtual void play(const QUrl &url) = 0;

    virtual void stop() = 0;
};

} // namespace media

#endif // MEDIAPLAYER_H
