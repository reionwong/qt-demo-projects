#include "mainwindow.h"
#include <QPainter>
#include <QPalette>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget = new QWidget();
    layout = new QHBoxLayout();
    leftLayout = new QVBoxLayout();
    rightLayout = new QVBoxLayout();
    redLayout = new QHBoxLayout();
    greenLayout = new QHBoxLayout();
    blueLayout = new QHBoxLayout();
    hexLayout = new QHBoxLayout();
    colorView = new ColorView();
    pickerButton = new QPushButton("取色");
    copyButton = new QPushButton("复制");
    redTips = new QLabel("红：");
    greenTips = new QLabel("绿：");
    blueTips = new QLabel("蓝：");
    hexTips = new QLabel("值：");
    redEdit = new QLineEdit();
    greenEdit = new QLineEdit();
    blueEdit = new QLineEdit();
    hexEdit = new QLineEdit();
    pickerWindow = new PickerWindow(this);

    leftLayout->addStretch();
    leftLayout->addWidget(colorView);
    leftLayout->addSpacing(8);
    leftLayout->addWidget(pickerButton);
    leftLayout->addWidget(copyButton);
    leftLayout->addStretch();

    rightLayout->addStretch();
    rightLayout->addLayout(redLayout);
    rightLayout->addSpacing(5);
    rightLayout->addLayout(greenLayout);
    rightLayout->addSpacing(5);
    rightLayout->addLayout(blueLayout);
    rightLayout->addSpacing(5);
    rightLayout->addLayout(hexLayout);
    rightLayout->addStretch();

    redLayout->addWidget(redTips);
    redLayout->addWidget(redEdit);

    greenLayout->addWidget(greenTips);
    greenLayout->addWidget(greenEdit);

    blueLayout->addWidget(blueTips);
    blueLayout->addWidget(blueEdit);

    hexLayout->addWidget(hexTips);
    hexLayout->addWidget(hexEdit);

    layout->addStretch();
    layout->addLayout(leftLayout);
    layout->addStretch();
    layout->addLayout(rightLayout);
    layout->addStretch();

    mainWidget->setLayout(layout);

    setCentralWidget(mainWidget);

    colorView->setBackgroundColor("#FFFFFF");

    initUI();

    connect(pickerButton, &QPushButton::clicked, this, &MainWindow::pickerButtonClicked);
    connect(colorView, &ColorView::clicked, this, &MainWindow::pickerButtonClicked);
    connect(copyButton, &QPushButton::clicked, this, &MainWindow::copyButtonClicked);
    connect(pickerWindow, &PickerWindow::finished, this, &MainWindow::pickerFinished);
}

MainWindow::~MainWindow()
{

}

void MainWindow::initUI()
{
    QPalette palette;
    palette.setColor(QPalette::WindowText, QColor("#FFFFFF"));

    QFont font;
    font.setPointSize(12);

    redTips->setPalette(palette);
    greenTips->setPalette(palette);
    blueTips->setPalette(palette);
    hexTips->setPalette(palette);

    redTips->setFont(font);
    greenTips->setFont(font);
    blueTips->setFont(font);
    hexTips->setFont(font);

    layout->setMargin(0);

    redEdit->setFixedWidth(70);
    greenEdit->setFixedWidth(70);
    blueEdit->setFixedWidth(70);
    hexEdit->setFixedWidth(70);

    redEdit->setFixedHeight(30);
    greenEdit->setFixedHeight(30);
    blueEdit->setFixedHeight(30);
    hexEdit->setFixedHeight(30);

    redEdit->setText("255");
    greenEdit->setText("255");
    blueEdit->setText("255");
    hexEdit->setText("#FFFFFF");

    pickerButton->setFixedWidth(92);
    copyButton->setFixedWidth(92);

    colorView->setBackgroundColor("#FFFFFF");
}

void MainWindow::pickerButtonClicked()
{
    pickerWindow->setVisible(true);
    pickerWindow->start();
}

void MainWindow::copyButtonClicked()
{

}

void MainWindow::pickerFinished(QColor color)
{
    QString hex = QString("#%1%2%3").arg(color.red(), 2, 16, QLatin1Char('0')).arg(color.green(), 2, 16, QLatin1Char('0')).arg(color.blue(), 2, 16, QLatin1Char('0')).toUpper();

    redEdit->setText(QString::number(color.red()));
    greenEdit->setText(QString::number(color.green()));
    blueEdit->setText(QString::number(color.blue()));
    hexEdit->setText(hex);

    colorView->setBackgroundColor(hex);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(QColor("#373F47"));
    painter.drawRect(rect());
}
