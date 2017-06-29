#include <QHBoxLayout>
#include <QMediaPlayer>
#include <QSlider>
#include <QToolButton>
#include <QWidget>

#include "volumeslider.h"

VolumeSlider::VolumeSlider(QWidget *parent) :
    QWidget(parent),
    m_inMute(false),
    // TODO: Need to check if next images is good to general app design
    m_icnMute (new QIcon(QString(":/resources/sliders/mute.png"))),
    m_icnUnMute (new QIcon(QString(":/resources/sliders/volume.png"))),
    m_mp(NULL)
{
    m_layout = new QHBoxLayout(this);
    this->setLayout(m_layout);

    m_btnMute = new QToolButton(this);
    m_btnMute->setToolButtonStyle(Qt::ToolButtonIconOnly);
    m_btnMute->setAutoRaise(true);
    m_btnMute->setIcon(*m_icnUnMute);
    connect(m_btnMute, SIGNAL(clicked()), this, SLOT(toggleMute()));
    m_layout->addWidget(m_btnMute);

    m_slider = new QSlider(this);
    m_slider->setOrientation(Qt::Horizontal);
    m_slider->setMinimum(0);
    m_slider->setMaximum(100);
    m_slider->setSliderPosition(100);

    m_layout->addWidget(m_slider);
}

void VolumeSlider::setStyleSheetForSlider(const QString &ss) {
    m_slider->setStyleSheet(ss);
}

void VolumeSlider::mute(const bool m)  {
    Q_ASSERT(m_mp!=NULL);
    if (m != m_inMute) {
        m_inMute = m;
        if (m) {
            // Need to mute
            changeMuteIcon(true);
            m_mp->setMuted(true);
        } else {
            // Need to un-mute
            changeMuteIcon(false);
            m_mp->setMuted(false);
        }
    }
}

void VolumeSlider::changeMuteIcon(const bool muted) {
    m_btnMute->setIcon( muted ? *m_icnMute : *m_icnUnMute );
}

void VolumeSlider::volumeChanged(const int v) {
    if (v != m_slider->value())
        m_slider->setSliderPosition(v);
}

void VolumeSlider::setMediaObject(QMediaPlayer *mp) {
    m_mp = mp;
    connect(mp, SIGNAL(mutedChanged(bool)), this, SLOT(changeMuteIcon(bool)));
    connect(mp, SIGNAL(volumeChanged(int)), this, SLOT(volumeChanged(int)));
    connect(m_slider, SIGNAL(valueChanged(int)), mp, SLOT(setVolume(int)));
}

void VolumeSlider::toggleMute() {
    mute(!m_inMute);
}
