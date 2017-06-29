#ifndef CUSTOMVOLUMECONTROL_H
#define CUSTOMVOLUMECONTROL_H

#include <QObject>
#include "volumecontrol.h"

class QMediaPlayer;

namespace media {

/**
     * Volume control implementation using Phonon AudioOutput.
     */
class CustomVolumeControl : public VolumeControl
{
    Q_OBJECT
public:
    explicit CustomVolumeControl(QMediaPlayer *output,
                                 QObject *parent = 0);

    int volume() const;

    bool isMuted() const;

    void setVolume(int vol);

    void setMuted(bool mute);

private:
    QMediaPlayer *m_audioOutput;
};

} // namespace media


#endif // CUSTOMVOLUMECONTROL_H
