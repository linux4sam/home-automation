#include "customvolumecontrol.h"

#include <QMediaPlayer>

using namespace media;

CustomVolumeControl::CustomVolumeControl(QMediaPlayer *output,
                                         QObject *parent)
    : VolumeControl(parent), m_audioOutput(output)
{
    Q_ASSERT(m_audioOutput);
    connect(output, SIGNAL(volumeChanged(int)), SIGNAL(volumeChanged(int)));
    connect(output, SIGNAL(mutedChanged(bool)), SIGNAL(mutedChanged(bool)));
}

int CustomVolumeControl::volume() const
{
    return m_audioOutput->volume();
}

bool CustomVolumeControl::isMuted() const
{
    return m_audioOutput->isMuted();
}

void CustomVolumeControl::setVolume(int vol)
{
    m_audioOutput->setVolume(vol);
}

void CustomVolumeControl::setMuted(bool mute)
{
    m_audioOutput->setMuted(mute);
}
