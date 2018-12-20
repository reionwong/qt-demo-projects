
#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    widget = new QWidget();
    layout = new QVBoxLayout();
    searchLayout = new QHBoxLayout();
    pronLayout = new QHBoxLayout();
    edit = new QLineEdit();
    button = new QPushButton("查询");
    nameLabel = new QLabel("");
    ukPron = new QLabel("");
    usPron = new QLabel("");
    infoLabel = new QLabel("");
    dict = new Dict(this);

    searchLayout->addWidget(edit);
    searchLayout->addWidget(button);

    pronLayout->addStretch();
    pronLayout->addWidget(ukPron);
    pronLayout->addWidget(usPron);
    pronLayout->addStretch();

    layout->addSpacing(10);
    layout->addLayout(searchLayout);
    layout->addSpacing(35);
    layout->addWidget(nameLabel, 0, Qt::AlignCenter);
    layout->addLayout(pronLayout);
    layout->addSpacing(10);
    layout->addWidget(infoLabel, 0, Qt::AlignCenter);
    layout->addStretch();

    widget->setLayout(layout);
    setCentralWidget(widget);

    connect(dict, SIGNAL(signalQueryFinished(QString, QString, QString, QString, QString, QString, QString)), this, SLOT(receiveQueryWord(QString, QString, QString, QString, QString, QString, QString)));
    connect(button, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
    connect(edit, SIGNAL(returnPressed()), this, SLOT(on_button_clicked()));

    initUI();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initUI()
{
    edit->setFixedSize(350, 40);
    button->setFixedSize(80, 40);

    edit->setStyleSheet("font-size: 22px");
    nameLabel->setStyleSheet("font-size: 23px");
    ukPron->setStyleSheet("font-size: 15px");
    usPron->setStyleSheet("font-size: 15px");
    infoLabel->setStyleSheet("font-size: 15px");
}

void MainWindow::receiveQueryWord(QString name, QString uk, QString us, QString chinese, QString ukAudio, QString usAudio, QString message)
{
    if (message != "SUCCESS")
    {
        nameLabel->setText(message);
        ukPron->setText("");
        usPron->setText("");
        infoLabel->setText("");

        return;
    }

    nameLabel->setText(name);
    ukPron->setText(QString("英[%1]").arg(uk));
    usPron->setText(QString("美[%1]").arg(us));
    infoLabel->setText(chinese);
}

void MainWindow::on_button_clicked()
{
    if (edit->text().isEmpty())
        return;

    dict->queryWord(edit->text());
}
