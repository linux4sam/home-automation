/****************************************************************************
**
** This class has been based on the code originally written by jurgenm
**
****************************************************************************/

#include "SlidingStackedWidget.h"
#include "imagewidget.h"
#include <QtDebug> //DBG ONLY

/***
 ** Default constructor
 **/
SlidingStackedWidget::SlidingStackedWidget(QWidget *parent)
    : QStackedWidget(parent),
    mBeginWidget(new ImageWidget(this)),
    mEndWidget(new ImageWidget(this))
{
    if (parent!=0) {
            m_mainwindow=parent;
        }
        else {
            m_mainwindow=this;
            qDebug()<<"ATTENTION: untested mainwindow case !";
        }
        //parent should not be 0; not tested for any other case yet !!

        //Now, initialize some private variables with default values
        m_vertical=false;
        //setVerticalMode(true);
        m_speed=700;
        m_animationtype = QEasingCurve::InOutQuad;  //check out the QEasingCurve documentation for different styles
        m_now=0;
        m_next=0;
        m_wrap=false;
        m_pnow=QPoint(0,0);
        m_active=false;

        //Findind background color (try stylesheet first)
        int ss_pos = qApp->styleSheet().indexOf( "QMainWindow");
        if (ss_pos != -1) { //has the stylesheet setting
            ss_pos = qApp->styleSheet().indexOf( "background", ss_pos);
            ss_pos = qApp->styleSheet().indexOf( ":", ss_pos);
            QString color = qApp->styleSheet().mid( ss_pos+1,
                                                    qApp->styleSheet().indexOf(";", ss_pos) - ss_pos - 1)
                                              .trimmed();
            mBackgroundColor = QColor( color);
        } else { //read from pallete
            mBackgroundColor = palette().background().color();
        }
}

/***
 ** Default destructor
 **/
SlidingStackedWidget::~SlidingStackedWidget(){
}

/***
 ** Set the Vertical or Horizontal mode for animation
 **/
void SlidingStackedWidget::setVerticalMode(bool vertical) {
        m_vertical=vertical;
}

/***
 ** Set the animation speed
 **/
void SlidingStackedWidget::setSpeed(int speed) {
        m_speed = speed;
}

/***
 ** Change the animation type - consult QEasingCurve for available options
 **/
void SlidingStackedWidget::setAnimation(enum QEasingCurve::Type animationtype) {
        m_animationtype = animationtype;
}

/***
 ** Set wrapping
 **/
void SlidingStackedWidget::setWrap(bool wrap) {
        m_wrap=wrap;
}

/***
 ** Slide the next page in the stacked Widget - based on index
 **/
void SlidingStackedWidget::slideInNext() {
        int now=currentIndex();
        if (m_wrap||(now<count()-1))
                // count is inherit from QStackedWidget
                slideInIdx(now+1);
}

/***
 ** Slide in the previous page in the stacked Widget
 **/
void SlidingStackedWidget::slideInPrev() {
        int now=currentIndex();
        if (m_wrap||(now>0))
                slideInIdx(now-1);
}

/***
 ** Slide to the page with index
 **/
void SlidingStackedWidget::slideInIdx(int idx, bool withanimation, enum t_direction direction) {
        //int idx, t_direction direction=AUTOMATIC
        if (idx>count()-1) {
            direction=m_vertical ? TOP2BOTTOM : RIGHT2LEFT;
            idx -= count();
        }
        else if (idx<0) {
            direction= m_vertical ? BOTTOM2TOP: LEFT2RIGHT;
            idx += count();
        }

        if (!withanimation)
            setCurrentIndex(idx);
        else
            slideInWgt( widget( idx), direction);
        //widget() is a function inherited from QStackedWidget
}

/***
 ** Main function that provides logic for moving pages in stackedWidget
 **/
void SlidingStackedWidget::slideInWgt(QWidget * nextWidget, enum t_direction  direction)
{
    qDebug() << "animBegin" << mBeginWidget->geometry() << "animEnd" << mEndWidget->geometry();
    // at the moment, do not allow re-entrance before an animation is completed.
    //other possibility may be to finish the previous animation abrupt, or
    //to revert the previous animation with a counter animation, before going ahead
    //or to revert the previous animation abrupt
    //and all those only, if the newwidget is not the same as that of the previous running animation.
    if (m_active)
        return;

    m_active=true;
    int now = currentIndex();		//currentIndex() is a function inherited from QStackedWidget
    int next = indexOf( nextWidget);
    if (now == next) {
        m_active = false;
        return;
    }
    if (direction == AUTOMATIC) {
        if ( now < next)
            direction = m_vertical ? TOP2BOTTOM : RIGHT2LEFT;
        else
            direction = m_vertical ? BOTTOM2TOP : LEFT2RIGHT;
    }

    //NOW....
    //calculate the shifts

    int offsetx = frameRect().width(); //inherited from mother
    int offsety = frameRect().height();//inherited from mother

    //the following is important, to ensure that the new widget
    //has correct geometry information when sliding in first time
    //nextWidget->setGeometry( 0,  0, offsetx, offsety);
    //setting pixmaps
    mBeginPixmap.fill( mBackgroundColor);
    currentWidget()->render( &mBeginPixmap, QPoint(), QRegion(), QWidget::DrawChildren);
    mBeginWidget->setPixmap( mBeginPixmap);
    mEndPixmap.fill( mBackgroundColor);
    nextWidget->setGeometry( geometry()); //this was not set cause widget is hidden
    nextWidget->render( &mEndPixmap, QPoint(), QRegion(), QWidget::DrawChildren);
    mEndWidget->setPixmap( mEndPixmap);

    switch (direction) {
    case BOTTOM2TOP:
        offsetx=0;
        offsety=-offsety;
        break;
    case TOP2BOTTOM:
        offsetx=0;
        break;
    case RIGHT2LEFT:
        offsetx=-offsetx;
        offsety=0;
        break;
    case LEFT2RIGHT:
        offsety=0;
    // TODO: add AUTOMATIC
    }

    //re-position the next widget outside/aside of the display area
    QPoint origin( 0, 0);
    QPoint pnext( -offsetx, -offsety);
    QPoint pnow( offsetx, offsety);
    m_pnow = origin;

    //animate both, the now and next widget to the side, using animation framework
    QPropertyAnimation *animnow = new QPropertyAnimation( mBeginWidget, "pos");
    animnow->setDuration(m_speed);
    animnow->setEasingCurve(m_animationtype);
    animnow->setStartValue( origin);
    animnow->setEndValue( pnow);

    QPropertyAnimation *animnext = new QPropertyAnimation( mEndWidget, "pos");
    animnext->setDuration(m_speed);
    animnext->setEasingCurve(m_animationtype);
    animnext->setStartValue( pnext);
    animnext->setEndValue( origin);

    QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;
    animgroup->addAnimation(animnow);
    animgroup->addAnimation(animnext);
    connect(animgroup, SIGNAL(finished()), this, SLOT(animationDoneSlot()));
    m_next=next;
    m_now=now;
    //make it visible/show
    currentWidget()->hide();
    mBeginWidget->show();
    mEndWidget->show();
    animgroup->start();

    //note; the rest is done via a connect from the animation ready;
    //animation->finished() provides a signal when animation is done;
    //so we connect this to some post processing slot,
    //that we implement here below in animationDoneSlot.
}

/***
 ** Signal handler for when the slide animation is done
 **/
void SlidingStackedWidget::animationDoneSlot(void) {
    //when ready, call the QStackedWidget slot setCurrentIndex(int)
    mBeginWidget->hide();
    mEndWidget->hide();
    setCurrentIndex(m_next);  //this function is inherit from QStackedWidget
    //widget(m_now)->hide();
    //then hide the outshifted widget now, and  (may be done already implicitely by QStackedWidget)
    //widget(m_now)->hide();
    //then set the position of the outshifted widget now back to its original
    //widget(m_now)->move(m_pnow);
    //so that the application could also still call the QStackedWidget original functions/slots for changings
    //widget(m_now)->update();
    //setCurrentIndex(m_next);  //this function is inherit from QStackedWidget
    m_active=false;
    emit animationFinished();
}

void SlidingStackedWidget::resizeEvent( QResizeEvent *event)
{
    Q_UNUSED(event)
    mBeginWidget->setGeometry( geometry());
    mBeginPixmap = QPixmap( mBeginWidget->size());
    mEndWidget->setGeometry( geometry());
    mEndPixmap = QPixmap( mEndWidget->size());
}
