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

#ifndef PHONONMEDIAPLAYER_H
#define PHONONMEDIAPLAYER_H

#include <phonon/Global>
#include "mediaplayer.h"

namespace Phonon {
class MediaObject;
}

namespace media {

class VolumeControl;

class PhononMediaPlayer : public MediaPlayer
{
    Q_OBJECT

public:
    explicit PhononMediaPlayer(QObject *parent = 0);

    Phonon::MediaObject *player() const { return m_mediaObject; }

    bool isPlaying() const;

    qint64 elapsed() const;

    VolumeControl *volumeControl() const;

    QString errorMessage() const;

    bool hasError() const;

    const QMap<QString, QString> &metaData() const;

    void play(const QUrl &url);

    void stop();

private slots:
    void updateMetaData();
    void mediaObjectStateChanged(Phonon::State newState, Phonon::State oldState);

private:
    VolumeControl *m_volumeCtrl;
    Phonon::MediaObject *m_mediaObject;
};

} // namespace media

#endif // PHONONMEDIAPLAYER_H
