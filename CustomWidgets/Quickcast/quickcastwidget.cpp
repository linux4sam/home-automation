#include "quickcastwidget.h"
#include "ui_quickcastwidget.h"

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

QuickCastWidget::QuickCastWidget(bool isSmallResolution, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuickCastWidget)
{
    ui->setupUi(this);
    smallRes = isSmallResolution;

    if (isSmallResolution) {
        // expand widget to take up all space
        ui->verticalLayout->setMargin(0);
    }

    createModel();
    stationRepo->refresh();
    createDeclarativeView();

    ui->verticalLayout->addWidget(qDeclView);
}

void QuickCastWidget::updateStations()
{
	stationRepo->refresh();
}

void QuickCastWidget::createModel()
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

void QuickCastWidget::createDeclarativeView()
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

    if(smallRes)
        qDeclView->setSource(QUrl("qrc:/smallQuickCastRadio.qml"));
    else
        qDeclView->setSource(QUrl("qrc:/QuickCastRadio.qml"));
}


QuickCastWidget::~QuickCastWidget()
{
    delete ui;
}
