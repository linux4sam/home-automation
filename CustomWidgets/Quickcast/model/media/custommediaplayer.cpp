#include "custommediaplayer.h"
#include "customvolumecontrol.h"
#include <QMediaPlayer>

using namespace media;


CustomMediaPlayer::CustomMediaPlayer(QObject *parent) :
    MediaPlayer(parent)
{

    m_mediaObject = new QMediaPlayer(this);
    m_mediaObject->setNotifyInterval(1000);

    connect(m_mediaObject, SIGNAL(positionChanged(qint64)),this, SIGNAL(elapsedChanged(qint64)));
    connect(m_mediaObject, SIGNAL(stateChanged(QMediaPlayer::State)),
            SLOT(mediaObjectStateChanged(QMediaPlayer::State)));
    connect(m_mediaObject, SIGNAL(metaDataChanged()), SLOT(updateMetaData()));
    connect(m_mediaObject, SIGNAL(error(QMediaPlayer::Error)), SLOT(errorOccured()));
    connect(m_mediaObject, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), SLOT(updateMediaStatus(QMediaPlayer::MediaStatus)));

    m_volumeCtrl = new CustomVolumeControl(m_mediaObject, this);
    m_volumeCtrl->setVolume(100);
    m_error = m_mediaObject->error() != QMediaPlayer::NoError;
    m_playing = m_mediaObject->state() == QMediaPlayer::PlayingState;
}

void CustomMediaPlayer::play(const QUrl &url)
{
    if(!url.isEmpty())
        qDebug() << url.toString();
    m_mediaObject->setMedia(url);
    m_mediaObject->play();
}

void CustomMediaPlayer::stop()
{
    m_mediaObject->stop();
}

bool CustomMediaPlayer::isPlaying() const
{
    return m_mediaObject->state() == QMediaPlayer::PlayingState;
}

qint64 CustomMediaPlayer::elapsed() const
{
    return m_mediaObject->position();
}

bool CustomMediaPlayer::hasError() const
{
    return m_error;
}

QString CustomMediaPlayer::errorMessage() const
{
    return m_mediaObject->errorString();
}

VolumeControl *CustomMediaPlayer::volumeControl() const
{
    return m_volumeCtrl;
}

const QMap<QString, QString> &CustomMediaPlayer::metaData() const
{
    QMap<QString, QString> *metaData = new QMap<QString, QString>();
    QStringList keys = m_mediaObject->availableMetaData();
    QString key;
    foreach (key, keys) {
        *metaData->insert(key,m_mediaObject->metaData(key).toString());
    }
    return *metaData;
}

void CustomMediaPlayer::updateMetaData()
{
    emit metaDataChanged(metaData());
}

void CustomMediaPlayer::mediaObjectStateChanged(QMediaPlayer::State state)
{
    if (m_error && m_mediaObject->error() == QMediaPlayer::NoError) {
        errorChanged(QString());
    }
    switch (state) {
        case QMediaPlayer::PausedState:
            qDebug("In Paused state");
            break;
        case QMediaPlayer::StoppedState:
            qDebug("In Stopped state");
            if (m_playing) {
                emit playingChanged(false);
                m_playing = false;
            }
            break;
        case QMediaPlayer::PlayingState:
            qDebug("In Playing state");
            emit playingChanged(true);
            m_playing = true;
            break;
    }
    m_error = m_mediaObject->error() != QMediaPlayer::NoError;
}

void CustomMediaPlayer::errorOccured()
{
    emit errorChanged(errorMessage());
    qDebug("In Error state: %s", qPrintable(m_mediaObject->errorString()));
    m_error = m_mediaObject->error() != QMediaPlayer::NoError;
}

void CustomMediaPlayer::updateMediaStatus(QMediaPlayer::MediaStatus status)
{
    switch(status) {
        case QMediaPlayer::UnknownMediaStatus:
            qDebug("Unknown Media Status");
            break;
        case QMediaPlayer::NoMedia:
            qDebug("No Media");
            break;
        case QMediaPlayer::LoadingMedia:
            qDebug("In Loading state");
            break;
        case QMediaPlayer::LoadedMedia:
            qDebug("Media has been Loaded");
            break;
        case QMediaPlayer::StalledMedia:
            qDebug("Media is stalled");
            break;
        case QMediaPlayer::BufferingMedia:
            qDebug("In Buffering state");
            break;
        case QMediaPlayer::BufferedMedia:
            qDebug("Media has been buffered");
            break;
        case QMediaPlayer::EndOfMedia:
            qDebug("End of Media");
            break;
        case QMediaPlayer::InvalidMedia:
            qDebug("Invalid Media");
            break;
   }
}
