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

#ifndef METADATA_H
#define METADATA_H

#include <QObject>
#include <QPointer>
#include <QMultiMap>
#include <QUrl>

namespace streaming {

class Streaming;

/**
 * Stream meta data.
 *
 * All meta data isn't available until playback has started. When playback is
 * started additional meta data may be present.
 *
 * The following meta data may be available before playback:
 * name - station name
 * url - stream url
 * bitrate - playback bitrate for the station
 * genre - genres
 *
 * In addition to the meta data above, following meta data may
 * be available after starting playback.
 * homepage - url to station's homepage
 * artist - current artist
 * title - current song title
 *
 * Any meta data may change during playback, for example, some stations might
 * change the bitrate between tracks. The stream's meta data always has
 * priority over the 'static' meta data passed to the constructor, if the data
 * is valid.
 */
class MetaData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name NOTIFY metaDataChanged)
    Q_PROPERTY(QUrl url READ url NOTIFY metaDataChanged)
    Q_PROPERTY(int bitrate READ bitrate NOTIFY metaDataChanged)
    Q_PROPERTY(QString genre READ genre NOTIFY metaDataChanged)
    Q_PROPERTY(QString artist READ artist NOTIFY metaDataChanged)
    Q_PROPERTY(QString title READ title NOTIFY metaDataChanged)
    Q_PROPERTY(QUrl homepage READ homepage NOTIFY metaDataChanged)

    friend class Streaming;

public:
    explicit MetaData(QObject *parent = 0);

    inline QUrl url() const { return m_url; }

    QString name() const;

    int bitrate() const;

    QString genre() const;

    QString artist() const;

    QString title() const;

    QUrl homepage() const;

signals:
    void metaDataChanged();

private:
    void updateMetaData(const QMap<QString, QString> &metaData);

private:
    QUrl m_url;
    QString m_name;
    QString m_genre;
    int m_bitrate;
    QMap<QString, QString> m_metaData;
};

} // namespace streaming

#endif // METADATA_H
