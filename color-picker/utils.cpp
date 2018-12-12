#include "utils.h"
#include <QFile>

QString Utils::getFileContent(const QString &path)
{
    QFile file(path);
    QString content = "";

    if (file.open(QFile::ReadOnly)) {
        content = file.readAll();
        file.close();
    }

    return content;
}
