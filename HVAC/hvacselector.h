#ifndef HVACSELECTOR_H
#define HVACSELECTOR_H

#include <QWidget>

class QToolButton;
class ImageWidget;

class HVACSelector : public QWidget
{
    Q_OBJECT
public:
    enum System {HeatSystem, CoolSystem, HumidifySystem};
    enum View {RadioList, ComboBox};
    explicit HVACSelector(View viewMode, QWidget *parent);

signals:
    void systemSelected( int );

protected:
    void paintEvent(QPaintEvent * event);

private slots:
    void onHeatChecked();
    void onCoolChecked();
    void onHumidifyChecked();
    void onComboChecked(int);

private:
    void setupRadioList();
    void setupComboBox();
    QToolButton *mHeatButton;
    QToolButton *mCoolButton;
    QToolButton *mHumidifyButton;
    QToolButton *mShowButton;
    ImageWidget *mActiveSystem;
    HVACSelector *mComboList;
};

#endif // HVACSELECTOR_H
