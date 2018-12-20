#ifndef DICT_H
#define DICT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class Dict : public QObject
{
    Q_OBJECT

public:
    Dict(QObject *parent = 0);

    void queryWord(const QString &word);

    QNetworkAccessManager * http;

    QString name;
    QString ukPron;
    QString usPron;
    QString ukAudio;
    QString usAudio;
    QString chinese;

public slots:
    void replyfinished(QNetworkReply *);

signals:
    void signalQueryFinished(QString name, QString ukPron, QString usPron, QString chinese, QString ukAudio, QString usAudio, QString message);
};

#endif // DICT_H
