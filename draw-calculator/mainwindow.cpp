#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget = new QWidget;
    mainLayout = new QVBoxLayout(mainWidget);
    titleBar = new TitleBar;
    expList = new ExpressionList;
    btnList = new ButtonList;

    mainLayout->addWidget(expList);
    mainLayout->addWidget(btnList);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    setCentralWidget(mainWidget);

    connect(btnList, &ButtonList::clicked, this, &MainWindow::handleInput);
}

MainWindow::~MainWindow()
{

}

void MainWindow::handleInput(const QString &text)
{
    if (text == "0" || text == "1" || text == "2" || text == "3" || text == "4" || text == "5" ||
        text == "6" || text == "7" || text == "8" || text == "9") {
        expList->enterNumberEvent(text);
    } else if (text == "＋" || text == "－" || text == "×" || text == "÷" || text == "%") {
        expList->enterSymbolEvent(QString(text).replace("＋", "+").replace("－", "-"));
    } else if (text == ".") {
        expList->enterPointEvent();
    } else if (text == "←") {
        expList->enterBackspaceEvent();
    } else if (text == "C") {
        expList->enterClearEvent();
    } else if (text == "( )") {
        expList->enterBracketsEvent();
    } else if (text == "＝") {
        expList->enterEqualEvent();
    }
}
