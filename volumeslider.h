#ifndef VOLUMESLIDER_H
#define VOLUMESLIDER_H

#include <QWidget>

class QHBoxLayout;
class QMediaPlayer;
class QSlider;
class QToolButton;

class VolumeSlider : public QWidget {

    Q_OBJECT

public:
    VolumeSlider(QWidget *parent = 0);
    void setStyleSheetForSlider(const QString &ss);

public slots:
    void mute(const bool m);
    void changeMuteIcon(const bool muted);
    void volumeChanged(const int v);
    void setMediaObject(QMediaPlayer *mp);
    void toggleMute();

private:
    QHBoxLayout *m_layout;
    QToolButton *m_btnMute;
    QSlider *m_slider;
    bool m_inMute;
    QIcon *m_icnMute;
    QIcon *m_icnUnMute;
    QMediaPlayer *m_mp;
};

#endif // VOLUMESLIDER_H
