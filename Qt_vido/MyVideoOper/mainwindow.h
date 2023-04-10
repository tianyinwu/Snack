#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_stateChanged(QMediaPlayer::State state);
    void on_durationChanged(qint64 duration);
    void on_positionChanged(qint64 position);


    void on_btnOpen_clicked();

    void on_btnPlay_clicked();

    void on_btnPause_clicked();

    void on_btnStop_clicked();

    void on_hsVolume_valueChanged(int value);

    void on_btnMute_clicked();

    void on_hsPos_valueChanged(int value);

    void on_btnFullScreen_clicked();

private:
    Ui::MainWindow *ui;

    QMediaPlayer *player;  //视频播放器
    QString durationTime;
    QString positionTime;

};

#endif // MAINWINDOW_H
