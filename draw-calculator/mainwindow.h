#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "titlebar.h"
#include "expressionlist.h"
#include "buttonlist.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget *mainWidget;
    QVBoxLayout *mainLayout;
    TitleBar *titleBar;
    ExpressionList *expList;
    ButtonList *btnList;

private slots:
    void handleInput(const QString &text);
};

#endif // MAINWINDOW_H
