#include "dict.h"
#include <QDebug>

Dict::Dict(QObject *parent)
    : QObject(parent)
{
    http = new QNetworkAccessManager(this);

    connect(http, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyfinished(QNetworkReply *)));
}

void Dict::queryWord(const QString &word)
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://www.shanbay.com/api/v1/bdc/search/?word=" + word));
    request.setRawHeader("Accept","application/json, text/javascript, */*; q=0.01");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Host","www.shanbay.com");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36");
    http->get(request);
}

void Dict::replyfinished(QNetworkReply *reply)
{
    QJsonDocument m_json;
    QJsonObject m_object, m_data, m_pron, m_audio;

    QByteArray wordInformation = reply->readAll();

    m_json = QJsonDocument::fromJson(wordInformation);

    if (!m_json.isNull())
    {
        m_object = m_json.object();
        m_data = m_object.value("data").toObject();
        m_pron = m_data.value("pronunciations").toObject();
        m_audio = m_data.value("audio_addresses").toObject();

        name = m_data.value("content").toString();
        ukPron = m_pron.value("uk").toString();
        usPron = m_pron.value("us").toString();
        chinese = m_data.value("definition").toString();
        ukAudio = m_audio.value("uk").toString();
        usAudio = m_audio.value("us").toString();
    }

    QString message = m_object.value("msg").toString();

    emit signalQueryFinished(name, ukPron, usPron, chinese, ukAudio, usAudio, message);
}
