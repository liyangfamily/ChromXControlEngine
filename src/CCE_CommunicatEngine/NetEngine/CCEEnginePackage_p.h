#ifndef CVTE_H_CCEENGINEPACKAGE_P
#define CVTE_H_CCEENGINEPACKAGE_P
#pragma once
#include <CCE_CommunicatEngine/CCEEnginePackage>


class SPackageData
{
public:
    inline SPackageData() : role(-1) {}
    inline SPackageData(int r, const QVariant &v) : role(r), value(v) {}
    int role;
    QVariant value;
    inline bool operator==(const SPackageData &other) const { return role == other.role && value == other.value; }
};
Q_DECLARE_METATYPE(SPackageData);

class SPackagePrivate
{
public:
    SPackagePrivate(){}

    ECommunicatType packType = ECommunicatType::ECT_NULL;
    EPackageFromType packFromType = EPackageFromType::EPFT_NULL;

    QObject* socketObj = 0;
    QByteArray dataArray;
    //UDP
    QString udpHostAddress;
    quint16 udpHostPort;

    //QVector<SPackageData> values;
};
#endif
