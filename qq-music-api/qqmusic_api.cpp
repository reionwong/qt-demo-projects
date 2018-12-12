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

#include "qqmusic_api.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

QQMusicAPI::QQMusicAPI(QObject *parent)
        : QObject(parent)
{
    http = new QNetworkAccessManager(this);

    getKey();
}

void QQMusicAPI::search(const QString &keyword, const int &page)
{
    QUrl url = QString("http://c.y.qq.com/soso/fcgi-bin/client_search_cp");
    QUrlQuery query;
    query.addQueryItem("t", "0");
    query.addQueryItem("aggr", "1");
    query.addQueryItem("lossless", "1");
    query.addQueryItem("cr", "1");
    query.addQueryItem("catZhida", "1");
    query.addQueryItem("format", "json");
    query.addQueryItem("p", QString::number(page));
    query.addQueryItem("n", "20");
    query.addQueryItem("w", keyword);
    url.setQuery(query.toString(QUrl::FullyEncoded));

    QNetworkRequest request(url);
    QNetworkReply *reply = http->get(request);

    connect(reply, &QNetworkReply::finished, this, &QQMusicAPI::searchFinished);
}

void QQMusicAPI::getKey()
{
    QUrl url = QString("https://c.y.qq.com/base/fcgi-bin/fcg_musicexpress.fcg");
    QUrlQuery query;
    query.addQueryItem("json", "3");
    query.addQueryItem("format", "json");
    query.addQueryItem("guid", "85880580");
    url.setQuery(query.toString(QUrl::FullyEncoded));

    QNetworkRequest request(url);
    request.setRawHeader("Referer", "http://y.qq.com/portal/player.html");
    QNetworkReply *reply = http->get(request);

    connect(reply, &QNetworkReply::finished, this, &QQMusicAPI::getKeyFinished);
}

QString QQMusicAPI::getSongUrl(const QString &song_mid)
{
    return "http://dl.stream.qqmusic.qq.com/M500" + song_mid + ".mp3?vkey=" + key + "&guid=85880580&fromtag=30";
}

void QQMusicAPI::searchFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    if (!reply->error()) {
        QByteArray array = reply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(array);
        QJsonObject object = document.object();
        QJsonObject song = object.value("data").toObject().value("song").toObject();
        QJsonArray list = song["list"].toArray();

        for (int i=0; i<list.size(); ++i) {
            QString song_name = list.at(i).toObject().value("songname").toString();
            QString singer_name = list.at(i).toObject().value("singer").toArray().at(0).toObject().value("name").toString();
            QString song_mid = list.at(i).toObject().value("songmid").toString();
            QString album_mid = list.at(i).toObject().value("albummid").toString();
            QString album_cover = QString("https://y.gtimg.cn/music/photo_new/T002R300x300M000%1.jpg").arg(album_mid);
            QString album_cover_big = QString("https://y.gtimg.cn/music/photo_new/T002R500x500M000%1.jpg").arg(album_mid);
            QString album_cover_small = QString("https://y.gtimg.cn/music/photo_new/T002R150x150M000%1.jpg").arg(album_mid);

            qDebug() << "http://dl.stream.qqmusic.qq.com/M500" + song_mid + ".mp3?vkey=" + key +"&guid=85880580&fromtag=30";
            qDebug() << QString("%1 - %2  %3").arg(song_name).arg(singer_name).arg(song_mid);
             qDebug() << "album_cover: " << album_cover_small;
            qDebug() << "\n";

            emit searchList(song_name + " - " + singer_name, "http://dl.stream.qqmusic.qq.com/M500" + song_mid + ".mp3?vkey=" + key +"&guid=85880580&fromtag=30", album_cover_small);

        }

    }
}

void QQMusicAPI::getKeyFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    if (!reply->error()) {
        QByteArray array = reply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(array);
        QJsonObject object = document.object();

        key = object.value("key").toString();
    }

}
