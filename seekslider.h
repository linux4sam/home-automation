#ifndef SEEKSLIDER_H
#define SEEKSLIDER_H

#include <QSlider>
#include <QMediaPlayer>

class SeekSlider : public QSlider {

    Q_OBJECT

public:
    SeekSlider(QWidget *parent = 0);
    void setMaxVal(const qint64 i);
    void setMediaObject(QMediaPlayer *mp);
    qint64 currentValue();
    ~SeekSlider();

public slots:
    void mediaChanged(QMediaContent);
    void mediaDurationChanged(const qint64 d);
    void seek(const qint64 v);
    void setValue(const qint64 v);
    void stateChanged(QMediaPlayer::State s);
    void audioAvailableChanged(const bool available);
    void seekableChanged(const bool canSeek);
    void currentMediaChanged(QMediaContent /*media*/);

private:
    qint64 m_maxVal;
    QMediaPlayer *m_mp;

private slots:
    void aboutToMoveSlider();
    void sliderReleasedSlot();
};


#endif // SEEKSLIDER_H
