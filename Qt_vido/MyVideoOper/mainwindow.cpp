#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("Qt 视频播放器");
    player = new QMediaPlayer(this); //创建播放器
    player->setNotifyInterval(2000); //信息更新周期2000ms
    player->setVideoOutput(ui->videoWidget); //视频显示组件
    ui->videoWidget->setMediaPlayer(player); //视频显示组件关联插放器


    //播放器状态变化
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),
            this,SLOT(on_stateChanged(QMediaPlayer::State)));
    //播放位置变化
    connect(player,SIGNAL(positionChanged(qint64 )),
            this,SLOT(on_positionChanged(qint64)));
    //视频文件时长变化
    connect(player,SIGNAL(durationChanged(qint64 )),
            this,SLOT(on_durationChanged(qint64)));

    //默认音量
    player->setVolume(ui->hsVolume->value());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_stateChanged(QMediaPlayer::State state)
{
    //播放器状态变化
    ui->btnPlay->setEnabled(!(state==QMediaPlayer::PlayingState));
    ui->btnPause->setEnabled(state==QMediaPlayer::PlayingState);
    ui->btnStop->setEnabled(state==QMediaPlayer::PlayingState);
}

void MainWindow::on_durationChanged(qint64 duration)
{
    //视频文件时长变化 （参数duration为毫秒)
    ui->hsPos->setMaximum(int(duration));
    int secs=int(duration/1000); //秒
    int mins = secs/60; //分
    secs = secs % 60; //余数秒
    durationTime=QString("%1:%2").arg(mins).arg(secs);
    ui->lbTimes->setText(positionTime+"/"+durationTime);


}

void MainWindow::on_positionChanged(qint64 position)
{
    //播放位置变化
    if(ui->hsPos->isSliderDown()) return;  //如果正在拖动进度条，则返回

    ui->hsPos->setSliderPosition(int(position));
    int secs = int(position/1000); //秒
    int mins = secs/60;
    secs = secs % 60;
    positionTime = QString("%1:%2").arg(mins).arg(secs);
    ui->lbTimes->setText(positionTime+"/"+durationTime);

}

void MainWindow::on_btnOpen_clicked()
{
    //打开文件
    QString curPath = QDir::homePath();
    QString filter = "mp4 文件(*.mp4);;avi 文件(*.avi);;所有文件(*.*)";
    QString aFile = QFileDialog::getOpenFileName(this,"选择视频文件",curPath,filter);
    if(aFile.isEmpty()) return;
    QFileInfo fileInfo(aFile);
    ui->lbFileName->setText(fileInfo.fileName());
    player->setMedia(QUrl::fromLocalFile(aFile));

    player->play();
}

void MainWindow::on_btnPlay_clicked()
{
    player->play();
}

void MainWindow::on_btnPause_clicked()
{
    player->pause();
}

void MainWindow::on_btnStop_clicked()
{
    player->stop();
}

void MainWindow::on_hsVolume_valueChanged(int value)
{
    player->setVolume(value);
}

void MainWindow::on_btnMute_clicked()
{
    player->setMuted(!player->isMuted());
    if(player->isMuted())
    {
        ui->btnMute->setText("音量");
        ui->hsVolume->setValue(0);
        ui->hsVolume->setEnabled(false);
    }
    else
    {
        ui->btnMute->setText("静音");
        ui->hsVolume->setEnabled(true);
    }


}

void MainWindow::on_hsPos_valueChanged(int value)
{
    player->setPosition(value);
}

void MainWindow::on_btnFullScreen_clicked()
{
    ui->videoWidget->setFullScreen(true);
}
