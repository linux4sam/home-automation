#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QLabel>
#include <QMouseEvent>

class ImageButton : public QLabel
{
    Q_OBJECT
public:
    explicit ImageButton(QWidget *parent = 0);

protected:
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void clicked();

public slots:

};

#endif // IMAGEBUTTON_H
