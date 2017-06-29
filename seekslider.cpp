#include "seekslider.h"

#include <QMouseEvent>
#include <QApplication>

SeekSlider::SeekSlider(QWidget *parent)
    : QSlider(parent),
      m_mp(NULL)
{
    setOrientation(Qt::Horizontal);
    setMinimum(0);
    setMaximum(100);
    setEnabled(false);
    m_maxVal = 1;
    connect(this, SIGNAL(sliderPressed()), this, SLOT(aboutToMoveSlider()));
    connect(this, SIGNAL(sliderReleased()), this, SLOT(sliderReleasedSlot()));
}

void SeekSlider::setMaxVal(const qint64 i) {
    if (m_maxVal != i) {
        m_maxVal = i;
        setValue(currentValue());
    }
}

void SeekSlider::setMediaObject(QMediaPlayer *mp) {
    m_mp = mp;
    setMaxVal(mp->duration());
    connect(mp, SIGNAL(positionChanged(qint64)), this, SLOT(seek(qint64)));
    connect(mp, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));
    connect(mp, SIGNAL(audioAvailableChanged(bool)), this, SLOT(audioAvailableChanged(bool)));
    connect(mp, SIGNAL(seekableChanged(bool)), this, SLOT(seekableChanged(bool)));
    connect(mp, SIGNAL(durationChanged(qint64)), this, SLOT(mediaDurationChanged(qint64)));
    connect(mp, SIGNAL(mediaChanged(QMediaContent)), this, SLOT(mediaChanged(QMediaContent)));
}

qint64 SeekSlider::currentValue() {
    return qint64( (value()*m_maxVal) / 100 );
}

SeekSlider::~SeekSlider() {
}

void SeekSlider::aboutToMoveSlider() {
    Q_ASSERT(m_mp!=NULL);
    if (m_mp->state()==QMediaPlayer::PlayingState) {
        m_mp->pause();
    }
}

void SeekSlider::sliderReleasedSlot() {
    Q_ASSERT(m_mp!=NULL);
    if (m_mp->state()==QMediaPlayer::PausedState) {
        m_mp->setPosition(currentValue());
        m_mp->play();
    }
}

void SeekSlider::mediaChanged(QMediaContent) {
    Q_ASSERT(m_mp!=NULL);
    mediaDurationChanged(m_mp->duration());
}

void SeekSlider::mediaDurationChanged(const qint64 d) {
    if (m_maxVal != d)
        m_maxVal = d;

    setMaxVal(d);
    setValue(currentValue());
}

void SeekSlider::seek(const qint64 v) {
    if (v != currentValue()) {
        int localVal = (int)(100*v)/m_maxVal;
        setSliderPosition(localVal);
    }
}

void SeekSlider::setValue(const qint64 v) {
    if (v != currentValue()) {
        int localVal = (int)(100*v)/m_maxVal;
        QSlider::setValue(localVal);
    }
}

void SeekSlider::stateChanged(QMediaPlayer::State s) {
    switch (s) {
    case QMediaPlayer::StoppedState: setEnabled(false); break;
    case QMediaPlayer::PlayingState:
    case QMediaPlayer::PausedState: setEnabled(true); break;
    }
}

void SeekSlider::audioAvailableChanged(const bool available) {
    setEnabled(available);
}

void SeekSlider::seekableChanged(const bool canSeek) {
    setEnabled(canSeek);
}

void SeekSlider::currentMediaChanged(QMediaContent) {
    QMouseEvent event(QEvent::MouseButtonRelease, QPoint(), Qt::LeftButton, 0, 0);
    QApplication::sendEvent(this, &event);
}
