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

#include <QApplication>
#include <QtDeclarative>
#include <QTimer>

#if (QT_VERSION >= 0x050000)
#include "model/media/custommediaplayer.h"
#else
#include "model/media/phononmediaplayer.h"
#endif // (QT_VERSION >= 0x050000)

#include "model/media/volumecontrol.h"
#include "model/streaming/streaming.h"
#include "model/streaming/metadata.h"
#include "model/icecast/stationrepository.h"
#include "model/icecast/stationtablemodel.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QApplication::applicationName());

    createModel();
    stationRepo->refresh();
    createDeclarativeView();

    setCentralWidget(qDeclView);
    // Due to a bug in PathView (QML) we have to load the stations
    // before creating the view.
    //QTimer::singleShot(0, this, SLOT(loadStations()));
}

void MainWindow::createModel()
{
#if (QT_VERSION >= 0x050000)
    mediaPlayer = new media::CustomMediaPlayer(this);
#else
    mediaPlayer = new media::PhononMediaPlayer(this);
#endif // (QT_VERSION >= 0x050000)
    stationRepo = new icecast::StationRepository(this);
    stationModel = new icecast::StationTableModel(stationRepo, this);
    streaming = new streaming::Streaming(stationRepo, mediaPlayer, this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::createDeclarativeView()
{
    qmlRegisterUncreatableType<streaming::MetaData>("Model.Streaming", 1, 0, "MetaData", tr("Instances only allowed from C++"));
    qmlRegisterUncreatableType<media::VolumeControl>("Model.Media", 1, 0, "VolumeControl", tr("Instances only allowed from C++"));

    qDeclView = new QDeclarativeView(this);

    QDeclarativeContext *context = qDeclView->rootContext();
    context->setContextProperty("stationModel", stationModel);
    context->setContextProperty("streaming", streaming);

    qDeclView->setAttribute(Qt::WA_OpaquePaintEvent);
    qDeclView->setAttribute(Qt::WA_NoSystemBackground);
    qDeclView->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    qDeclView->setFocus();

    qDeclView->setSource(QUrl("qrc:/QuickCastRadio.qml"));
}
