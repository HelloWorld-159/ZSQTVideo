#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAudioOutput>
#include <QDir>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_player = new QMediaPlayer(this);
    m_player->setVideoOutput(ui->videoWidget);
    m_audioOutput = new QAudioOutput();
    m_player->setAudioOutput(m_audioOutput);
    
    ui->videoWidget->setMediaPlayer(m_player);
    
    connect(m_player, SIGNAL(positionChanged(qint64)), this, SLOT(OnPositionChanged(qint64)));
    connect(m_player, SIGNAL(durationChanged(qint64)), this, SLOT(OnDurationChanged(qint64)));
    connect(m_player, SIGNAL(playbackStateChanged(QMediaPlayer::PlaybackState)), this, SLOT(OnStateChanged(QMediaPlayer::PlaybackState)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnDurationChanged(qint64 duration)
{ 
    ui->sliderPosition->setMaximum(duration);
    
    int secs = duration / 1000;
    int mins = secs / 60;
    secs = secs % 60;
    m_durationTime = QString::asprintf("%d:%d", mins, secs);
    ui->labRatio->setText(m_positionTime + "/" + m_durationTime);
}

void MainWindow::OnPositionChanged(qint64 position)
{ 
    if (ui->sliderPosition->isSliderDown())
        return;
    
    ui->sliderPosition->setSliderPosition(position);
    
    int secs = position / 1000;
    int mins = secs / 60;
    secs = secs % 60;
    
    m_positionTime = QString::asprintf("%d分:%d秒", mins, secs);
    ui->labRatio->setText(m_positionTime + "/" + m_durationTime);
}

void MainWindow::OnStateChanged(QMediaPlayer::PlaybackState state)
{
    ui->btnPlay->setEnabled(!(state == QMediaPlayer::PlayingState));
    ui->btnPause->setEnabled(state == QMediaPlayer::PlayingState);
    ui->btnStop->setEnabled(state == QMediaPlayer::PlayingState);
}

void MainWindow::on_btnAdd_clicked()
{
    QString curPath = QDir::homePath();
    QString dlgTitle = "xxxxx";
    QString filter = "mp4文件(*.mp4);;wmv文件(*.wmv);;所有文件(*.*)";
    QString aFile = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    if (aFile.isEmpty())
        return;
    
    QFileInfo fileInfo(aFile);
    ui->labCurMedia->setText(fileInfo.fileName());
    
    m_player->setSource(QUrl::fromLocalFile(aFile));
    
    m_player->setAudioOutput(m_audioOutput);
    m_player->play();
}

void MainWindow::on_btnPlay_clicked()
{
    m_player->play();
}

void MainWindow::on_btnPause_clicked()
{
    m_player->pause();
}

void MainWindow::on_btnStop_clicked()
{
    m_player->stop();
}

void MainWindow::on_btnSound_clicked()
{
    bool mute = m_audioOutput->isMuted();
    m_audioOutput->setMuted(!mute);
    if (mute)
        ui->btnSound->setIcon(QIcon(":/images/images/volumn.bmp"));
    else
        ui->btnSound->setIcon(QIcon(":/images/images/mute.bmp"));
}

void MainWindow::on_sliderVolumn_valueChanged(int value)
{
    m_audioOutput->setVolume(value / 100.0f);
}

void MainWindow::on_btnFullScreen_clicked()
{
    ui->videoWidget->setFullScreen(true);
}

void MainWindow::on_sliderPosition_valueChanged(int value)
{
    m_player->setPosition(value);
}
