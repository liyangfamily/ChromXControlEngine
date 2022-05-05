#include "CCE_Core/CCEJsonHelper.h"
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

/**
 * CCEJsonHelper
 *
 */

bool CCEJsonHelper::isJsonHelperVaild()
{
    if (m_path.isEmpty())
    {
        qDebug() << "file path is Empty.";
        return false;
    }
    if (m_doc.isEmpty())
    {
        qDebug() << "jsonDocument is Empty.";
        return false;
    }
    return true;
}

bool CCEJsonHelper::saveJson(const qint8 version)
{
    if (!buildJson(m_doc,version))
    {
        qDebug() << "json build faild.";
        return false;
    }

    if (!isJsonHelperVaild())
    {
        qDebug() << "json is not vaild.";
        return false;
    }

    if (!write(m_path, m_doc))
    {
        qDebug() << "json file write faild.";
        return false;
    }
    qDebug() << "json write succeed.";
    return true;
}

bool CCEJsonHelper::saveJsonAs(const QString &path ,const qint8 version)
{
    m_path = path;
    return saveJson(version);
}

bool CCEJsonHelper::readJson(const qint8 version)
{
    if (!read(m_path, m_doc))
    {
        qDebug() << "json file read faild.";
        return false;
    }

    if (!isJsonHelperVaild())
    {
        qDebug() << "json is not vaild.";
        return false;
    }

    if (!parseJson(m_doc,version))
    {
        qDebug() << "json parse faild.";
        return false;
    }
    qDebug() << "json parse succeed.";
    return true;
}

bool CCEJsonHelper::readJsonFrom(const QString &path ,const qint8 version)
{
    m_path = path;
    return readJson(version);
}

bool CCEJsonHelper::write(const QString &path, const QJsonDocument &doc)
{
    QFile file(path);
    if (!file.open(QFile::WriteOnly | QFile::Truncate))
    {
        qDebug() << "json file open faild.";
        return false;
    }
    file.write(doc.toJson());
    file.flush();
    file.close();
    return true;
}

bool CCEJsonHelper::read(const QString &path, QJsonDocument &doc)
{
    QFile file(path);
    if (!file.open(QFile::ReadOnly))
    {
        qDebug() << "json file open faild.";
        return false;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonParseError error;
    doc = QJsonDocument::fromJson(data, &error);
    if (doc.isEmpty())
    {
        qDebug() << error.errorString();
    }
    return true;
}
