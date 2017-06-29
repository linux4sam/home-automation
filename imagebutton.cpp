#include "imagebutton.h"

ImageButton::ImageButton(QWidget *parent) :
    QLabel(parent)
{
}

void ImageButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->geometry().contains(mapToParent(e->pos())))
        emit clicked();
}
