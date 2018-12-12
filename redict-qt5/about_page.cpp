#include "about_page.h"
#include <QLabel>
#include <QSvgWidget>

AboutPage::AboutPage(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);

    QSvgWidget *icon = new QSvgWidget(":/resources/logo.svg");
    icon->setFixedSize(120, 120);

    QLabel *title = new QLabel("ReDict");
    title->setStyleSheet("font-size: 20px");

    QLabel *version = new QLabel("版本： v0.1");
    QLabel *tips = new QLabel("使用了有道API");
    QLabel *tips1 = new QLabel("项目地址：https://github.com/rekols/dictionary-reborn");
    QLabel *tips2 = new QLabel("本项目以GPLv3协议发布，禁止违反GPLv3协议非法闭源");

    layout->addStretch();
    layout->addWidget(icon, 0, Qt::AlignCenter);
    layout->addSpacing(5);
    layout->addWidget(title, 0, Qt::AlignCenter);
    layout->addWidget(version, 0, Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(tips, 0, Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(tips2, 0, Qt::AlignCenter);
    layout->addWidget(tips1, 0, Qt::AlignCenter);
    layout->addStretch();
}
