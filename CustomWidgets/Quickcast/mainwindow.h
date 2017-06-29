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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif // (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))

namespace media { class MediaPlayer; }
namespace icecast {
    class StationRepository;
    class StationTableModel;
}
namespace streaming { class Streaming; }

class QDeclarativeView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createModel();
    void createDeclarativeView();

    QDeclarativeView *qDeclView;
#if (QT_VERSION >= 0x050000)
    media::CustomMediaPlayer *mediaPlayer;
#else
    media::MediaPlayer *mediaPlayer;
#endif // (QT_VERSION >= 0x050000)
    icecast::StationRepository *stationRepo;
    icecast::StationTableModel *stationModel;
    streaming::Streaming *streaming;
};

#endif // MAINWINDOW_H
