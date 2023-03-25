#include "qmyvideowidget.h"
#include <QKeyEvent>
#include <QMouseEvent>

QmyVideoWidget::QmyVideoWidget(QWidget *parent) 
    : QVideoWidget(parent)
{
}

void QmyVideoWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && isFullScreen())
    {
        this->setFullScreen(false);
        event->accept();
    }

    QVideoWidget::keyPressEvent(event);
}

void QmyVideoWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (m_thePlayer->playbackState() == QMediaPlayer::PlayingState)
            m_thePlayer->pause();
        else
            m_thePlayer->play();
    }

    QVideoWidget::mousePressEvent(event);
}


void QmyVideoWidget::setMediaPlayer(QMediaPlayer *player) 
{
    m_thePlayer = player;
}
