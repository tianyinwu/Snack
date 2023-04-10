#ifndef QMYVIDEOWIDGET_H
#define QMYVIDEOWIDGET_H

#include <QVideoWidget>
#include <QMediaPlayer>

class QMyVideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    explicit QMyVideoWidget(QWidget *parent = nullptr);
    void setMediaPlayer(QMediaPlayer *player);

signals:

public slots:

private:
    QMediaPlayer *thePlayer;

protected:

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);


};

#endif // QMYVIDEOWIDGET_H
