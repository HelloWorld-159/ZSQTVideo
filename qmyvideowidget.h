#ifndef QMYVIDEOWIDGET_H
#define QMYVIDEOWIDGET_H

#include <QtMultimediaWidgets/QVideoWidget>
#include <QtMultimedia/qmediaplayer.h>

class QmyVideoWidget : public QVideoWidget
{
private:
    QMediaPlayer *m_thePlayer;

public:
    QmyVideoWidget(QWidget *parent = Q_NULLPTR);
    
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    
public:
    void setMediaPlayer(QMediaPlayer *player);
};

#endif // QMYVIDEOWIDGET_H
