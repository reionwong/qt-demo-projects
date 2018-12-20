#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenu>

#include <QSlider>
#include "titlebar.h"
#include "dbutton.h"

#include <QtAV>
#include <QtAVWidgets>
#include <QtAV/AVPlayer.h>

using namespace QtAV;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    void initUI();

private:
    QString open_file_name;
    int m_unit;
    bool sound_state;

public slots:
    void showAboutDialog();

private slots:
    void play_button_clicked();
    void play_button_open_file();
    void play_button_state();
    void stop_button_clicked();
    void sound_button_clicked();

    void seek_by_slider(int value);
    void seek_by_slider();

    void update_slider(qint64 value);
    void update_slider();
    void update_slider_unit();
    void move_sound_slider();
    void player_started();

private:
    QWidget *widget = new QWidget();
    TitleBar *tb = new TitleBar();
    QVBoxLayout *main_layout = new QVBoxLayout();
    QHBoxLayout *slider_layout = new QHBoxLayout();
    QHBoxLayout *bottom_layout = new QHBoxLayout();

    AVPlayer *m_player = new AVPlayer;
    VideoRendererId v = VideoRendererId_Widget;
    VideoRenderer* renderer = VideoRenderer::create(v);

    QSlider *play_slider = new QSlider(Qt::Horizontal);
    QLabel *time = new QLabel("00:00:00/00:00:00");
    DButton *stop_button = new DButton();
    DButton *left_button = new DButton();
    DButton *right_button = new DButton();
    DButton *play_button = new DButton();
    DButton *sound_button = new DButton();
    QSlider *sound_slider = new QSlider(Qt::Horizontal);
    DButton *full_button = new DButton();

    QMenu *m_menu;

protected:
    void paintEvent(QPaintEvent *);
};

#endif
