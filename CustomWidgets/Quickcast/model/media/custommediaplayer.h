#ifndef CUSTOMMEDIAPLAYER_H
#define CUSTOMMEDIAPLAYER_H

#include <QMediaPlayer>
#include "mediaplayer.h"

namespace media {

class VolumeControl;

class CustomMediaPlayer : public MediaPlayer
{
    Q_OBJECT

public:
    explicit CustomMediaPlayer(QObject *parent = 0);

    QMediaPlayer *player() const { return m_mediaObject; }

    bool isPlaying() const;

    qint64 elapsed() const;

    VolumeControl *volumeControl() const;

    QString errorMessage() const;

    bool hasError() const;

    const QMap<QString, QString> &metaData() const;

    void play(const QUrl &url);

    void stop();

private slots:
    void updateMetaData();
    void mediaObjectStateChanged(QMediaPlayer::State state);
    void errorOccured();
    void updateMediaStatus(QMediaPlayer::MediaStatus status);

private:
    VolumeControl *m_volumeCtrl;
    QMediaPlayer *m_mediaObject;
    bool m_error, m_playing;
};

} // namespace media

#endif // CUSTOMMEDIAPLAYER_H
