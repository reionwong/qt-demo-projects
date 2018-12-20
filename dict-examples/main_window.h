#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "dict.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget *widget;
    QVBoxLayout *layout;
    QHBoxLayout *searchLayout;
    QHBoxLayout *pronLayout;
    QLineEdit *edit;
    QPushButton *button;
    QLabel *nameLabel;
    QLabel *ukPron;
    QLabel *usPron;
    QLabel *infoLabel;

    Dict *dict;

    void initUI();

private slots:
    void receiveQueryWord(QString name, QString ukPron, QString usPron, QString chinese, QString ukAudio, QString usAudio, QString message);
    void on_button_clicked();
};

#endif // MAIN_WINDOW_H
