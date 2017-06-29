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

#include "station.h"
#include "stationrepository.h"
#include "stationtablemodel.h"

using namespace icecast;

StationTableModel::StationTableModel(StationRepository *repo, QObject *parent) :
    QAbstractTableModel(parent), m_stationRepo(repo)
{
    m_roles.insert(Qt::UserRole + StreamUrl, "streamUrl");
    m_roles.insert(Qt::UserRole + Name, "name");
    m_roles.insert(Qt::UserRole + Genre, "genre");
    m_roles.insert(Qt::UserRole + Bitrate, "bitrate");

#if !(QT_VERSION >= 0x050000)
    setRoleNames(m_roles);
#endif // !(QT_VERSION >= 0x050000)
    m_stationRepo = repo;
    connect(repo, SIGNAL(beginDirectoryUpdate()), SLOT(directoryUpdateBegin()));
    connect(repo, SIGNAL(endDirectoryUpdate()), SLOT(directoryUpdateEnd()));
}

int StationTableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : MaxColumns;
}

int StationTableModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : stationCount();
}

QVariant StationTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (!index.isValid() ||
        row < 0 || row >= stationCount() ||
        col < 0 || col >= MaxColumns) {
        return QVariant();
    }

    // Support roles
    if (role >= Qt::UserRole) {
        col = role - Qt::UserRole;
        role = Qt::DisplayRole;
    }

    if (role == Qt::DisplayRole) {
        Station *station = stationAt(row);
        switch (col) {
            case Name: return station->name();
            case Genre: return station->genre();
            case Bitrate: return station->bitrate();
            case StreamUrl: return station->url();
            default: return QVariant();
        }
    }

    if (role == Qt::TextAlignmentRole && col == Bitrate) {
        return Qt::AlignRight;
    }

    return QVariant();
}

QVariant StationTableModel::headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    } else if (orientation == Qt::Horizontal) {
        switch (section) {
            case Name: return tr("Name");
            case Genre: return tr("Genre");
            case Bitrate: return tr("Bitrate");
            case StreamUrl: return tr("Stream");
            default: return QVariant();
        }
    } else {
        return section + 1;
    }
}

int StationTableModel::stationCount() const
{
    return m_stationRepo ? m_stationRepo->count() : 0;
}

Station *StationTableModel::stationAt(int index) const {
    return m_stationRepo ? m_stationRepo->byIndex(index) : 0;
}

void StationTableModel::directoryUpdateBegin()
{
    beginResetModel();
}

void StationTableModel::directoryUpdateEnd()
{
    endResetModel();
}

#if (QT_VERSION >= 0x050000)
    QHash <int, QByteArray> StationTableModel::roleNames() const
    {
        return m_roles;
    }
#endif // (QT_VERSION >= 0x050000)
