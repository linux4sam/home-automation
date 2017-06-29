#ifndef QUICKCASTWIDGET_H
#define QUICKCASTWIDGET_H

#include <QWidget>

namespace media { class MediaPlayer; }
namespace icecast {
    class StationRepository;
    class StationTableModel;
}
namespace streaming { class Streaming; }

class QDeclarativeView;

namespace Ui {
class QuickCastWidget;
}

class QuickCastWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit QuickCastWidget(bool isSmallResolution, QWidget *parent = 0);
    ~QuickCastWidget();

    void createModel();
    void createDeclarativeView();
    void updateStations();

    QDeclarativeView *qDeclView;
    media::MediaPlayer *mediaPlayer;
    icecast::StationRepository *stationRepo;
    icecast::StationTableModel *stationModel;
    streaming::Streaming *streaming;
    
private:
    Ui::QuickCastWidget *ui;
    bool smallRes;
};

#endif // QUICKCASTWIDGET_H
