#include <CCE_Core/CCECoreGlobal>
#include <QObject>
#include <QRectF>
#include <QString>
#include <QMap>
#include <QUuid>
#include <QJsonDocument>

class CCE_CORE_EXPORT CCEJsonHelper
{
public:
    CCEJsonHelper(){};
    CCEJsonHelper(const QString &path);

    bool isJsonHelperVaild();

    bool saveJson(const qint8 version = 0);
    bool saveJsonAs(const QString &path ,const qint8 version = 0);

    bool readJson(const qint8 version = 0);
    bool readJsonFrom(const QString &path ,const qint8 version = 0);

    QJsonDocument jsonDoc() const
    {
        return m_doc;
    }
    void setJsonDoc(const QJsonDocument &doc)
    {
        if (doc.isEmpty() || doc.isNull())
        {
            return;
        }
        m_doc = doc;
    }

    QString jsonPath() const
    {
        return m_path;
    }
    void setJsonPath(const QString &path)
    {
        if (path.isEmpty() || path.isNull())
        {
            return;
        }
        m_path = path;
    }

public:
    virtual bool buildJson(QJsonDocument &doc ,const qint8 version = 0) = 0;
    virtual bool parseJson(const QJsonDocument &doc ,const qint8 version = 0) = 0;

private:
    bool write(const QString &path, const QJsonDocument &doc);
    bool read(const QString &path, QJsonDocument &doc);

private:
    QString m_path;
    QJsonDocument m_doc;
};
