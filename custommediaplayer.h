#ifndef CUSTOMMEDIAPLAYER_H
#define CUSTOMMEDIAPLAYER_H

#if HAVE_QT5
    #include <QtWidgets>
#endif

#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <Phonon>

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QSlider;
class QTextEdit;
class QMenu;
class Ui_settings;
QT_END_NAMESPACE


class CustomMediaPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit CustomMediaPlayer(QWidget *parent = 0);
    
    void setFile(const QString &text);
    void initVideoWindow();
    void setVolume(qreal volume);

public slots:
    void rewind();
    void updateTime();
    void finished();
    void playPause();
    void scaleChanged(QAction *);
    void aspectChanged(QAction *);

private slots:
    void stateChanged(Phonon::State newstate, Phonon::State oldstate);
    void bufferStatus(int percent);

    void hasVideoChanged(bool);

private:
    bool playPauseForDialog();


    QIcon playIcon;
    QIcon pauseIcon;
    QMenu *fileMenu;
    QPushButton *playButton;
    QPushButton *rewindButton;
    Phonon::SeekSlider *slider;
    QLabel *timeLabel;
    QLabel *progressLabel;
    Phonon::VolumeSlider *volume;

    QLabel *info;
    Phonon::Effect *nextEffect;

    QAction *m_fullScreenAction;

    QWidget m_videoWindow;
    Phonon::MediaObject m_MediaObject;
    Phonon::AudioOutput m_AudioOutput;
    Phonon::VideoWidget *m_videoWidget;
    Phonon::Path m_audioOutputPath;
    bool m_smallScreen;
    QRect widgetGeometry;

};


#endif // CUSTOMMEDIAPLAYER_H
