/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2017 Rekols (Felix Bill)
 *
 * Author:     Rekols <rekols@foxmail.com>
 * Maintainer: Rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "widget.h"
#include <QDebug>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QMediaPlayer>
#include <QStringList>
#include "qqmusic_api.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QQMusicAPI *api = new QQMusicAPI(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    QListWidget *list = new QListWidget();
    QPushButton *btn = new QPushButton("搜索歌曲");
    QLineEdit *edit = new QLineEdit();
    QMediaPlayer *mediaplay = new QMediaPlayer();
    QLabel *label = new QLabel();

    layout->addWidget(edit);
    layout->addWidget(btn);
    layout->addWidget(list);
    layout->addWidget(label);

    QObject::connect(api, &QQMusicAPI::searchList, this, [=](QString text, QString url, QString image_url){ 
        names << text;
        urls << url;
        imageUrls << image_url;

        new QListWidgetItem(text, list);
    });

    QObject::connect(btn, &QPushButton::clicked, this, [=]{
        api->search(edit->text(), 1);
    });

    QObject::connect(list, &QListWidget::currentRowChanged, this, [=](int current){
        mediaplay->setMedia(QUrl(urls.at(current)));
        mediaplay->play();

        qDebug() << urls.at(current);
    });
}
