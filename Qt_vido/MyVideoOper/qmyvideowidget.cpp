#include "qmyvideowidget.h"
#include <QKeyEvent>
#include <QMouseEvent>

QMyVideoWidget::QMyVideoWidget(QWidget *parent) : QVideoWidget(parent)
{

}

void QMyVideoWidget::setMediaPlayer(QMediaPlayer *player)
{
    thePlayer = player;


}

void QMyVideoWidget::keyPressEvent(QKeyEvent *event)
{
    //ESC退出全屏
    if(event->key()==Qt::Key_Escape && isFullScreen())
    {
        setFullScreen(false);
        event->accept();

    }
    QVideoWidget::keyPressEvent(event);
}

void QMyVideoWidget::mousePressEvent(QMouseEvent *event)
{

    //鼠标单击控制播放和暂停
    if(event->button()==Qt::LeftButton)
    {
        thePlayer->state()==QMediaPlayer::PlayingState?
                    thePlayer->pause():
                    thePlayer->play();

    }
    QVideoWidget::mousePressEvent(event);
}
