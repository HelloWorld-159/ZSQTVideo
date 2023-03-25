#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
private:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
    
    QString m_durationTime;
    QString m_positionTime;
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void OnDurationChanged(qint64 duration);
    void OnPositionChanged(qint64 position);
    void OnStateChanged(QMediaPlayer::PlaybackState state);
    
    void on_btnAdd_clicked();
    
    void on_btnPlay_clicked();
    
    void on_btnPause_clicked();
    
    void on_btnStop_clicked();
    
    void on_btnSound_clicked();
    
    void on_sliderVolumn_valueChanged(int value);
    
    void on_btnFullScreen_clicked();
    
    void on_sliderPosition_valueChanged(int value);
    
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
