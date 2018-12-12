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

#ifndef QQMUSICAPI_H
#define QQMUSICAPI_H

#include <QObject>
#include <QJsonObject>

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;
class QUrl;

class QQMusicAPI : public QObject
{
    Q_OBJECT
    
public:
    QQMusicAPI(QObject *parent = 0);

    void search(const QString &keyword, const int &page);
    void getKey();
    QString getSongUrl(const QString &song_mid);

private slots:
    void searchFinished();
    void getKeyFinished();
    
private:
    QNetworkAccessManager *http;
    QString key;

signals:
    void searchList(QString, QString, QString);
};

#endif
