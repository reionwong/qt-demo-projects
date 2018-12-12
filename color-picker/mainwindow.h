#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "colorview.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "pickerwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);

private:
    QWidget *mainWidget;
    QHBoxLayout *layout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QHBoxLayout *redLayout;
    QHBoxLayout *greenLayout;
    QHBoxLayout *blueLayout;
    QHBoxLayout *hexLayout;

    ColorView *colorView;
    QPushButton *pickerButton;
    QPushButton *copyButton;

    QLabel *redTips;
    QLabel *greenTips;
    QLabel *blueTips;
    QLabel *hexTips;

    QLineEdit *redEdit;
    QLineEdit *greenEdit;
    QLineEdit *blueEdit;
    QLineEdit *hexEdit;

    PickerWindow *pickerWindow;

    void initUI();

private slots:
    void pickerButtonClicked();
    void copyButtonClicked();
    void pickerFinished(QColor color);
};

#endif // MAINWINDOW_H
