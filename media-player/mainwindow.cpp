#include "mainwindow.h"
#include <QFileDialog>
#include <QPainter>
#include <QRectF>
#include <QStyleFactory>
#include <QAction>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    sound_state = true;
    m_unit = 1000;
    open_file_name = "";

    m_player->setRenderer(renderer);

    connect(play_button, SIGNAL(clicked(bool)), this, SLOT(play_button_clicked()));
    connect(stop_button, SIGNAL(clicked(bool)), this, SLOT(stop_button_clicked()));
    connect(sound_button, SIGNAL(clicked(bool)), this, SLOT(sound_button_clicked()));

    connect(left_button, &DButton::clicked, this, [=]{
        m_player->seekBackward();
    });
    connect(right_button, &DButton::clicked, this, [=]{
        m_player->seekForward();
    });

    connect(play_slider, SIGNAL(sliderMoved(int)), SLOT(seek_by_slider(int)));
    connect(play_slider, SIGNAL(sliderPressed()), SLOT(seek_by_slider()));
    connect(m_player, SIGNAL(positionChanged(qint64)), SLOT(update_slider(qint64)));
    connect(m_player, SIGNAL(started()), SLOT(update_slider()));
    connect(m_player, SIGNAL(notifyIntervalChanged()), SLOT(update_slider_unit()));
    connect(m_player, SIGNAL(started()), SLOT(player_started()));

    connect(sound_slider, SIGNAL(sliderMoved(int)), this, SLOT(move_sound_slider()));
    connect(sound_slider, SIGNAL(sliderPressed()), this, SLOT(move_sound_slider()));

    initUI();
}

void MainWindow::initUI()
{
    m_menu = new QMenu(this);
    QAction *openAction = m_menu->addAction("Open");
    QAction *fullAction = m_menu->addAction("Full screen");
    QAction *aboutAction = m_menu->addAction("About");
    QAction *exitAction = m_menu->addAction("Exit");

    connect(openAction, &QAction::triggered, this, [=]{
            play_button_open_file();
    });

    connect(exitAction, &QAction::triggered, this, [=]{
            qApp->quit();
    });

    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAboutDialog);

    tb->setFileName("");
    // titlebar()->setCustomWidget(tb, Qt::AlignVCenter, false);
    // titlebar()->setMenu(m_menu);
    setCentralWidget(widget);
    
    time->setStyleSheet("QLabel { color: white; }");

    sound_slider->setFixedWidth(100);

    bottom_layout->addSpacing(10);
    bottom_layout->addWidget(time);
    bottom_layout->addStretch();
    bottom_layout->addWidget(stop_button);
    bottom_layout->addSpacing(15);
    bottom_layout->addWidget(left_button);
    bottom_layout->addSpacing(15);
    bottom_layout->addWidget(play_button);
    bottom_layout->addSpacing(15);
    bottom_layout->addWidget(right_button);
    bottom_layout->addSpacing(15);
    bottom_layout->addWidget(sound_button);
    bottom_layout->addWidget(sound_slider);
    bottom_layout->addStretch();
    bottom_layout->addWidget(full_button);

    slider_layout->addWidget(play_slider);

    main_layout->addWidget(renderer->widget());
    main_layout->addLayout(slider_layout);
    main_layout->addLayout(bottom_layout);

    main_layout->setMargin(1);
    main_layout->setSpacing(1);
    bottom_layout->setMargin(10);
    bottom_layout->setSpacing(5);

    play_button->setIcon(QIcon(":/resources/disabled_play.svg"));
    stop_button->setIcon(QIcon(":/resources/stop_normal.svg"));
    left_button->setIcon(QIcon(":/resources/disabled_previous.svg"));
    right_button->setIcon(QIcon(":/resources/disabled_next.svg"));
    full_button->setIcon(QIcon(":/resources/fullscreen_normal.svg"));
    sound_button->setIcon(QIcon(":/resources/default_unmute.svg"));

    play_button->setIconSize(QSize(32, 32));
    sound_button->setIconSize(QSize(20, 20));

    time->hide();
    sound_slider->setValue(100);

    widget->setLayout(main_layout);
}

void MainWindow::play_button_clicked()
{
    if (open_file_name.isEmpty())
    {
        play_button_open_file();
    }
    else
    {
        play_button_state();
    }
}

void MainWindow::play_button_open_file()
{
    QString new_file_name = QFileDialog::getOpenFileName(0, tr("Open a video"));

    if (new_file_name.isEmpty())
        return;

    open_file_name = new_file_name;

    if (open_file_name.isEmpty())
        return;

    m_player->play(open_file_name);
    play_button->setIcon(QIcon(":/resources/disabled_pause.svg"));
    time->show();

    tb->setFileName(QFileInfo(open_file_name).fileName());
}

void MainWindow::play_button_state()
{
    if (m_player->state() == m_player->PlayingState)
    {
        m_player->pause(true);
        play_button->setIcon(QIcon(":/resources/disabled_play.svg"));
    }
    else if (m_player->state() == m_player->PausedState)
    {
        m_player->pause(false);
        play_button->setIcon(QIcon(":/resources/disabled_pause.svg"));
    }
    else if (m_player->state() == m_player->StoppedState)
    {
        m_player->play();
        play_button->setIcon(QIcon(":/resources/disabled_pause.svg"));
    }

}

void MainWindow::sound_button_clicked()
{
    if (sound_state)
    {
        sound_button->setIcon(QIcon(":/resources/default_mute.svg"));
        sound_slider->setValue(0);
        m_player->audio()->setVolume(0);
        sound_state = false;
    }
    else
    {
        sound_button->setIcon(QIcon(":/resources/default_unmute.svg"));
        sound_slider->setValue(100);
        m_player->audio()->setVolume(sound_slider->value() / 100.0);
        sound_state = true;
    }
}

void MainWindow::stop_button_clicked()
{
    open_file_name = "";
    time->hide();

    m_player->stop();
    play_button->setIcon(QIcon(":/resources/disabled_play.svg"));
    tb->setFileName("");
    play_slider->setValue(0);
}

void MainWindow::seek_by_slider(int value)
{
    if (!m_player->isPlaying())
        return;

    m_player->seek(qint64(value * m_unit));
}

void MainWindow::seek_by_slider()
{
    seek_by_slider(play_slider->value());
}

void MainWindow::update_slider(qint64 value)
{
    play_slider->setRange(0, int(m_player->duration() / m_unit));
    play_slider->setValue(int(value / m_unit));
}

void MainWindow::update_slider()
{
    update_slider(m_player->position());
}

void MainWindow::update_slider_unit()
{
    m_unit = m_player->notifyInterval();
    update_slider();
}

void MainWindow::move_sound_slider()
{
    if (sound_slider->value() == 0)
    {
        sound_button->setIcon(QIcon(":/resources/default_mute.svg"));
        sound_state = false;
    }
    else
    {
        sound_button->setIcon(QIcon(":/resources/default_unmute.svg"));
        sound_state = true;
    }

    m_player->audio()->setVolume(sound_slider->value() / 100.0);
}

void MainWindow::player_started()
{

}

void MainWindow::showAboutDialog()
{
    QString descriptionText = tr("Simple, easy to use, nice player.");

//    auto *aboutDlg = new Dtk::Widget::DAboutDialog();
//    aboutDlg->setWindowModality(Qt::WindowModal);
//    aboutDlg->setWindowIcon(QPixmap::fromImage(QImage(":/resources/icon.svg")));
//    aboutDlg->setProductIcon(QPixmap::fromImage(QImage(":/resources/icon.svg")));
//    aboutDlg->setProductName(tr("Engine Player"));
//    aboutDlg->setVersion(QString("%1: 1.0").arg(tr("Version")));
//    aboutDlg->setDescription(descriptionText + "\n");
//    aboutDlg->show();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#333333"));
    painter.drawRect(rect());
}
