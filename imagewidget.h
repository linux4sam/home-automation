#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = 0);
    void setPixmap( const QPixmap& pixmap);
    QSize sizeHint();

protected:
    void paintEvent( QPaintEvent *event);
    void resizeEvent( QResizeEvent *event);

private:
    void updatePixmapOffset();
    QPixmap mPixmap;
    QPoint mPixmapOffset;
};

#endif // IMAGEWIDGET_H
