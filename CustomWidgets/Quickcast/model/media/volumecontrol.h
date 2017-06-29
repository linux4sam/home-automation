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

#ifndef VOLUMECONTROL_H
#define VOLUMECONTROL_H

#include <QObject>
namespace media {

/**
     * Volume control interface.
     */
class VolumeControl : public QObject
{
    Q_OBJECT
#if (QT_VERSION >= 0x050000)
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
#else
    Q_PROPERTY(qreal volume READ volume WRITE setVolume NOTIFY volumeChanged)
#endif // (QT_VERSION >= 0x050000)
    Q_PROPERTY(bool muted READ isMuted WRITE setMuted NOTIFY mutedChanged)

public:
    explicit VolumeControl(QObject *parent = 0) : QObject(parent) {}

#if (QT_VERSION >= 0x050000)
    virtual int volume() const = 0;
#else
    virtual qreal volume() const = 0;
#endif // (QT_VERSION >= 0x050000)

    virtual bool isMuted() const = 0;

signals:
#if (QT_VERSION >= 0x050000)
    void volumeChanged(int volume);
#else
    void volumeChanged(qreal volume);
#endif // (QT_VERSION >= 0x050000)

    void mutedChanged(bool isMuted);

public slots:
#if (QT_VERSION >= 0x050000)
    virtual void setVolume(int vol) = 0;
#else
    virtual void setVolume(qreal vol) = 0;
#endif // (QT_VERSION >= 0x050000)

    virtual void setMuted(bool mute) = 0;
};

} // namespace media

#endif // VOLUMECONTROL_H
