#include "imagewidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QtDebug> //DBG only
/*!
 * \class ImageWidget
 * \brief Widget for showing Pixmaps
 */
ImageWidget::ImageWidget(QWidget *parent) :
    QWidget(parent),
    mPixmapOffset(0,0)
{
    setAttribute( Qt::WA_NoSystemBackground);
}

void ImageWidget:: setPixmap( const QPixmap& pixmap)
{
    mPixmap = pixmap;
    setMinimumSize( pixmap.size());
    updatePixmapOffset();
    updateGeometry();
    update();
}
QSize ImageWidget:: sizeHint()
{
    return mPixmap.size();
}

void ImageWidget:: paintEvent( QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.drawPixmap( mPixmapOffset, mPixmap);
}

void ImageWidget:: resizeEvent( QResizeEvent *event)
{
    Q_UNUSED(event)
    updatePixmapOffset();
}

void ImageWidget:: updatePixmapOffset()
{
    mPixmapOffset.setX( (width()  - mPixmap.width())  / 2 );
    mPixmapOffset.setY( (height() - mPixmap.height()) / 2 );
}
