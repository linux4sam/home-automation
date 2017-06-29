#include "hvacselector.h"
#include "imagewidget.h"
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPainter>

HVACSelector:: HVACSelector(View viewMode, QWidget *parent) :
    QWidget(parent)
{
    switch (viewMode) {
    case RadioList:
        mComboList = 0;
        setupRadioList();
        break;
    case ComboBox:
        mComboList = new HVACSelector( RadioList, parent);
        connect( mComboList, SIGNAL(systemSelected(int)), this, SLOT(onComboChecked(int)));
        setupComboBox();
        mComboList->hide();
        mComboList->setGeometry( QRect( x(), y(),
                                        mActiveSystem->width(),
                                        3 * mActiveSystem->height() + 30));
        break;
    }
}

void HVACSelector:: paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.fillRect( event->rect(), QColor("#19262E")); //should be setable
}

void HVACSelector:: onHeatChecked()
{
    emit systemSelected( HeatSystem);
}

void HVACSelector:: onCoolChecked()
{
    emit systemSelected( CoolSystem);
}

void HVACSelector:: onHumidifyChecked()
{
    emit systemSelected( HumidifySystem);
}

void HVACSelector:: onComboChecked(int system)
{
    mComboList->hide();
    mShowButton->setChecked(false);

    switch (static_cast<System>(system)) {
    case HeatSystem:
        mActiveSystem->setPixmap( QPixmap(":/resources/small-HeatCoolHumidify/button-heat-on.png"));
        break;
    case CoolSystem:
        mActiveSystem->setPixmap( QPixmap(":/resources/small-HeatCoolHumidify/button-cool-on.png"));
        break;
    case HumidifySystem:
        mActiveSystem->setPixmap( QPixmap(":/resources/small-HeatCoolHumidify/button-humidiify-on.png"));
        break;
    }

    emit systemSelected( system);
}

void HVACSelector:: setupRadioList()
{
    QSize iconSize(144, 64);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    mHeatButton = new QToolButton(this);
    mHeatButton->setSizePolicy(sizePolicy);
    mHeatButton->setFocusPolicy(Qt::NoFocus);
    QIcon iconHeat;
    iconHeat.addFile(QString::fromUtf8(":/resources/HeatCoolHumidify/button-heat-off.png"), QSize(), QIcon::Normal, QIcon::Off);
    iconHeat.addFile(QString::fromUtf8(":/resources/HeatCoolHumidify/button-heat-on.png"), QSize(), QIcon::Normal, QIcon::On);
    mHeatButton->setIcon(iconHeat);
    mHeatButton->setIconSize( iconSize);
    mHeatButton->setCheckable(true);
    mHeatButton->setAutoExclusive(true);
    mHeatButton->setChecked( true);
    connect( mHeatButton, SIGNAL(clicked()), this, SLOT(onHeatChecked()));

    mCoolButton = new QToolButton(this);
    mCoolButton->setSizePolicy(sizePolicy);
    mCoolButton->setFocusPolicy(Qt::NoFocus);
    QIcon iconCool;
    iconCool.addFile(QString::fromUtf8(":/resources/HeatCoolHumidify/button-cool-off.png"), QSize(), QIcon::Normal, QIcon::Off);
    iconCool.addFile(QString::fromUtf8(":/resources/HeatCoolHumidify/button-cool-on.png"), QSize(), QIcon::Normal, QIcon::On);
    mCoolButton->setIcon(iconCool);
    mCoolButton->setIconSize( iconSize);
    mCoolButton->setCheckable(true);
    mCoolButton->setAutoExclusive(true);
    connect( mCoolButton, SIGNAL(clicked()), this, SLOT(onCoolChecked()));

    mHumidifyButton = new QToolButton(this);
    mHumidifyButton->setSizePolicy(sizePolicy);
    mHumidifyButton->setFocusPolicy(Qt::NoFocus);
    QIcon iconHumidify;
    iconHumidify.addFile(QString::fromUtf8(":/resources/HeatCoolHumidify/button-humidiify-off.png"), QSize(), QIcon::Normal, QIcon::Off);
    iconHumidify.addFile(QString::fromUtf8(":/resources/HeatCoolHumidify/button-humidiify-on.png"), QSize(), QIcon::Normal, QIcon::On);
    mHumidifyButton->setIcon(iconHumidify);
    mHumidifyButton->setIconSize( iconSize);
    mHumidifyButton->setCheckable(true);
    mHumidifyButton->setAutoExclusive(true);
    connect(mHumidifyButton, SIGNAL(clicked()), this, SLOT(onHumidifyChecked()));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,10,0,0);
    layout->setSpacing(10);
    layout->addWidget( mHeatButton);
    layout->addWidget( mCoolButton);
    layout->addWidget( mHumidifyButton);
}

void HVACSelector:: setupComboBox()
{
    mActiveSystem = new ImageWidget(this);
    mActiveSystem->setPixmap( QPixmap(":/resources/small-HeatCoolHumidify/button-heat-on.png"));

    mShowButton = new QToolButton(this);
    QIcon icon;
    icon.addFile( ":/resources/smallcamera/up.png", QSize(), QIcon::Normal, QIcon::On);
    icon.addFile( ":/resources/smallcamera/down.png", QSize(), QIcon::Normal, QIcon::Off);
    mShowButton->setIcon( icon);
    mShowButton->setCheckable( true);
    connect( mShowButton, SIGNAL(clicked(bool)), mComboList, SLOT(setVisible(bool)));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,10,0,0);
    layout->setSpacing(10);
    layout->addWidget( mActiveSystem);
    layout->addWidget( mShowButton);
}

