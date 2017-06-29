#if HAVE_QT5
    #include <QtWidgets>
#endif

#include <QtGui>

#define SLIDER_RANGE 8

#include "custommediaplayer.h"
#include "mainwindow.h"

CustomMediaPlayer::CustomMediaPlayer(QWidget *parent) :
        playButton(0), nextEffect(0),
//            m_AudioOutput(Phonon::VideoCategory),
            m_videoWidget(new Phonon::VideoWidget(this))
{

    QSize buttonSize(34, 28);


    rewindButton = new QPushButton(this);
    rewindButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));

    playButton = new QPushButton(this);
    playIcon = style()->standardIcon(QStyle::SP_MediaPlay);
    pauseIcon = style()->standardIcon(QStyle::SP_MediaPause);
    playButton->setIcon(playIcon);

    slider = new Phonon::SeekSlider(this);
    slider->setMediaObject(&m_MediaObject);
    setStyleSheet(" QSlider::handle { image: url(:/resources/images/slider-dot.png)}"
                " QSlider::groove { min-height: 80px; };");
//    volume = new Phonon::VolumeSlider(&m_AudioOutput);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->setContentsMargins(8, 8, 8, 8);

    QHBoxLayout *layout = new QHBoxLayout();

    info = new QLabel(this);
    info->setMinimumHeight(70);
    info->setAcceptDrops(false);
    info->setMargin(2);
    info->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    info->setLineWidth(2);
    info->setAutoFillBackground(true);

    QPalette palette;
    palette.setBrush(QPalette::WindowText, Qt::white);

    rewindButton->setMinimumSize(buttonSize);
    playButton->setMinimumSize(buttonSize);

    info->setStyleSheet("border-image:url(:/images/screen.png) ; border-width:3px");
    info->setPalette(palette);
    info->setText(tr("<center>No media</center>"));

//    volume->setFixedWidth(120);

    layout->addWidget(rewindButton);
    layout->addWidget(playButton);

    layout->addStretch();
//    layout->addWidget(volume);

    vLayout->addWidget(info);
    initVideoWindow();
    vLayout->addWidget(&m_videoWindow);

    m_videoWindow.setMaximumSize(0.6* this->size().width(), 0.9* this->size().height());

    QVBoxLayout *buttonPanelLayout = new QVBoxLayout();
    m_videoWindow.hide();
    buttonPanelLayout->addLayout(layout);

    timeLabel = new QLabel(this);
    progressLabel = new QLabel(this);
    timeLabel->setPalette(palette);
    QWidget *sliderPanel = new QWidget(this);
    QHBoxLayout *sliderLayout = new QHBoxLayout();
    sliderLayout->addWidget(slider);
    sliderLayout->addWidget(timeLabel);
    sliderLayout->addWidget(progressLabel);
    sliderLayout->setContentsMargins(0, 0, 0, 0);
    sliderPanel->setLayout(sliderLayout);

    buttonPanelLayout->addWidget(sliderPanel);
    buttonPanelLayout->setContentsMargins(0, 0, 0, 0);

    QWidget *buttonPanelWidget = new QWidget(this);
    buttonPanelWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    buttonPanelWidget->setLayout(buttonPanelLayout);
    vLayout->addWidget(buttonPanelWidget);

    QHBoxLayout *labelLayout = new QHBoxLayout();

    vLayout->addLayout(labelLayout);
    setLayout(vLayout);

    // Setup signal connections:
    connect(rewindButton, SIGNAL(clicked()), this, SLOT(rewind()));
    //connect(openButton, SIGNAL(clicked()), this, SLOT(openFile()));
//    openButton->setMenu(fileMenu);

    connect(playButton, SIGNAL(clicked()), this, SLOT(playPause()));
    //connect(openButton, SIGNAL(clicked()), this, SLOT(openFile()));

//    connect(m_videoWidget, SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(showContextMenu(const QPoint &)));
//    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(showContextMenu(const QPoint &)));
//    connect(&m_MediaObject, SIGNAL(metaDataChanged()), this, SLOT(updateInfo()));
    connect(&m_MediaObject, SIGNAL(totalTimeChanged(qint64)), this, SLOT(updateTime()));
    connect(&m_MediaObject, SIGNAL(tick(qint64)), this, SLOT(updateTime()));
    connect(&m_MediaObject, SIGNAL(finished()), this, SLOT(finished()));
    connect(&m_MediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(stateChanged(Phonon::State,Phonon::State)));
    connect(&m_MediaObject, SIGNAL(bufferStatus(int)), this, SLOT(bufferStatus(int)));
    connect(&m_MediaObject, SIGNAL(hasVideoChanged(bool)), this, SLOT(hasVideoChanged(bool)));

    rewindButton->setEnabled(false);
    playButton->setEnabled(false);
    setAcceptDrops(true);

    setFile("big_buck_bunny_480x272_stereo.ogg");

//    m_audioOutputPath = Phonon::createPath(&m_MediaObject, &m_AudioOutput);
    Phonon::createPath(&m_MediaObject, m_videoWidget);
    resize(minimumSizeHint());
}

void CustomMediaPlayer::stateChanged(Phonon::State newstate, Phonon::State oldstate)
{
    Q_UNUSED(oldstate);

    if (oldstate == Phonon::LoadingState) {
        QRect videoHintRect = QRect(QPoint(0, 0), m_videoWindow.sizeHint());
        QRect newVideoRect = QApplication::desktop()->screenGeometry().intersected(videoHintRect);
        if (!m_smallScreen) {
            if (m_MediaObject.hasVideo()) {
                // Flush event que so that sizeHint takes the
                // recently shown/hidden m_videoWindow into account:
                qApp->processEvents();
                resize(sizeHint());
            } else
                resize(minimumSize());
        }
    }

    switch (newstate) {
        case Phonon::ErrorState:
            if (m_MediaObject.errorType() == Phonon::FatalError) {
                playButton->setEnabled(false);
                rewindButton->setEnabled(false);
            } else {
                m_MediaObject.pause();
            }
            QMessageBox::warning(this, "Phonon Mediaplayer", m_MediaObject.errorString(), QMessageBox::Close);
            break;

        case Phonon::StoppedState:
            m_videoWidget->setFullScreen(false);
            // Fall through
        case Phonon::PausedState:
            playButton->setIcon(playIcon);
            if (m_MediaObject.currentSource().type() != Phonon::MediaSource::Invalid){
                playButton->setEnabled(true);
                rewindButton->setEnabled(true);
            } else {
                playButton->setEnabled(false);
                rewindButton->setEnabled(false);
            }
            break;
        case Phonon::PlayingState:
            playButton->setEnabled(true);
            playButton->setIcon(pauseIcon);
            if (m_MediaObject.hasVideo())
                m_videoWindow.show();
            // Fall through
        case Phonon::BufferingState:
            rewindButton->setEnabled(true);
            break;
        case Phonon::LoadingState:
            rewindButton->setEnabled(false);
            break;
    }

}



void CustomMediaPlayer::setVolume(qreal volume)
{
//    m_AudioOutput.setVolume(volume);
}


void CustomMediaPlayer::initVideoWindow()
{
    QVBoxLayout *videoLayout = new QVBoxLayout();
    videoLayout->addWidget(m_videoWidget);
    videoLayout->setContentsMargins(0, 0, 0, 0);
    m_videoWindow.setLayout(videoLayout);
    m_videoWindow.setMinimumSize(100, 100);


}



void CustomMediaPlayer::playPause()
{
    if (m_MediaObject.state() == Phonon::PlayingState)
        m_MediaObject.pause();
    else {
        if (m_MediaObject.currentTime() == m_MediaObject.totalTime())
            m_MediaObject.seek(0);
        m_MediaObject.play();
    }
}

void CustomMediaPlayer::setFile(const QString &fileName)
{
    m_MediaObject.setCurrentSource(Phonon::MediaSource(fileName));
    m_MediaObject.play();
}

bool CustomMediaPlayer::playPauseForDialog()
{
    // If we're running on a small screen, we want to pause the video when
    // popping up dialogs. We neither want to tamper with the state if the
    // user has paused.
    if (m_smallScreen && m_MediaObject.hasVideo()) {
        if (Phonon::PlayingState == m_MediaObject.state()) {
            m_MediaObject.pause();
            return true;
        }
    }
    return false;
}

void CustomMediaPlayer::bufferStatus(int percent)
{
    if (percent == 100)
        progressLabel->setText(QString());
    else {
        QString str = QString::fromLatin1("(%1%)").arg(percent);
        progressLabel->setText(str);
    }
}


void CustomMediaPlayer::updateTime()
{
    long len = m_MediaObject.totalTime();
    long pos = m_MediaObject.currentTime();
    QString timeString;
    if (pos || len)
    {
        int sec = pos/1000;
        int min = sec/60;
        int hour = min/60;
        int msec = pos;

        QTime playTime(hour%60, min%60, sec%60, msec%1000);
        sec = len / 1000;
        min = sec / 60;
        hour = min / 60;
        msec = len;

        QTime stopTime(hour%60, min%60, sec%60, msec%1000);
        QString timeFormat = "m:ss";
        if (hour > 0)
            timeFormat = "h:mm:ss";
        timeString = playTime.toString(timeFormat);
        if (len)
            timeString += " / " + stopTime.toString(timeFormat);
    }
    timeLabel->setText(timeString);
}

void CustomMediaPlayer::rewind()
{
    m_MediaObject.seek(0);
}

void CustomMediaPlayer::finished()
{
}

void CustomMediaPlayer::scaleChanged(QAction *act)
{
    if (act->text() == tr("Scale and crop"))
        m_videoWidget->setScaleMode(Phonon::VideoWidget::ScaleAndCrop);
    else
        m_videoWidget->setScaleMode(Phonon::VideoWidget::FitInView);
}

void CustomMediaPlayer::aspectChanged(QAction *act)
{
    if (act->text() == tr("16/9"))
        m_videoWidget->setAspectRatio(Phonon::VideoWidget::AspectRatio16_9);
    else if (act->text() == tr("Scale"))
        m_videoWidget->setAspectRatio(Phonon::VideoWidget::AspectRatioWidget);
    else if (act->text() == tr("4/3"))
        m_videoWidget->setAspectRatio(Phonon::VideoWidget::AspectRatio4_3);
    else
        m_videoWidget->setAspectRatio(Phonon::VideoWidget::AspectRatioAuto);
}

void CustomMediaPlayer::hasVideoChanged(bool bHasVideo)
{
    info->setVisible(!bHasVideo);
    m_videoWindow.setVisible(bHasVideo);


//    m_fullScreenAction->setEnabled(bHasVideo);
}
