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

#ifndef STATIONTABLEMODEL_H
#define STATIONTABLEMODEL_H

#include <QPointer>
#include <QAbstractTableModel>

namespace icecast {

class Station;
class StationRepository;

/**
 * Implements a Qt table model.
 *
 * The class has two pure virtual function that needs to be implmented:
 * - stationAt(int index) which returns a station at the specifed index
 * - stationCount() which returns the number of stations available.
 */
class StationTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    static const int MaxColumns = 4;

    enum Column {StreamUrl, Name, Genre, Bitrate};

    explicit StationTableModel(StationRepository *repo, QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

#if (QT_VERSION >= 0x050000)
    QHash <int, QByteArray> roleNames() const;
#endif // (QT_VERSION >= 0x050000)

private slots:
    void directoryUpdateBegin();
    void directoryUpdateEnd();

private:
    int stationCount() const;

    Station *stationAt(int index) const;

    QPointer<StationRepository> m_stationRepo;

    QHash <int, QByteArray> m_roles;
};

} // namespace icecast

#endif // STATIONTABLEMODEL_H
