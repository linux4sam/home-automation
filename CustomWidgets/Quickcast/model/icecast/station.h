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

#ifndef STATION_H
#define STATION_H

#include <QUrl>

namespace icecast {

/**
 * Data container for a station in the Icecast directory.
 */
class Station
{
public:
    explicit Station() {}

    // Url property
    inline void setUrl(const QString &url) { setUrl(QUrl(url)); }
    inline void setUrl(const QUrl &url) { m_url = url; }
    inline QUrl url() const { return m_url; }

    // Name property
    inline void setName(const QString &name) { m_name = name; }
    inline QString name() const { return m_name; }

    // Genre property
    inline void setGenre(const QString &genre) { m_genre = genre; }
    inline QString genre() const { return m_genre; }

    // Bitrate property
    inline void setBitrate(int bitrate) { m_bitrate = bitrate; }
    inline int bitrate() const { return m_bitrate; }

private:
    QUrl m_url;
    QString m_name;
    QString m_genre;
    int m_bitrate;
};

} // namespace icecast

#endif // STATION_H
