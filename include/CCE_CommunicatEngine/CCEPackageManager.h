/*********************************************************************************************************
** This file is part of the CCE_CommunicatEngine module of the CCE Toolkit.
*********************************************************************************************************/
#ifndef CHROMX_H_CCEPACKAGEMANAGER
#define CHROMX_H_CCEPACKAGEMANAGER
#pragma once

#include <CCE_CommunicatEngine/CCEPackage>

#include <QMap>

class CCE_COMMUNICATENGINE_EXPORT CCEPackageManager
{
public:
	typedef QMap<quint16, std::function<quint16(const QByteArray&)>> CmdMap;
	typedef QMap<quint8, CmdMap> ProtocolMap;
	CCEPackageManager();
	virtual ~CCEPackageManager();

	template <class T>
	bool registerPackage(const T &package, std::function<quint16(const QByteArray&)>cb)
	{
		quint8 protocolNum = package.CmdProtocolNum();
		quint16 cmdNum = package.CmdRetNum();
		ProtocolMap::iterator iProtocolMap = m_maps.find(protocolNum);
		if (iProtocolMap != m_maps.end()) {
			CmdMap::iterator iCmdNumber = iProtocolMap.value().find(cmdNum);
			if (iCmdNumber != iProtocolMap.value().end()) {
				qDebug() << "CCEPackageManager" << 
					QString("registerPackage failed cmd name : %1   cmd number : %2 is existed").arg(protocolNum).arg(QString::number(cmdNum, 16));
				return false;
			}
		}

		/*T *p_t = new T();
		qDebug() << "CCEPackageManager" << QString("registerPackage cmd name : %1   cmd number : %2.").arg(protocolNum).arg(QString::number(cmdNum, 16));
		p_t->setPackageCallBack(cb);*/

		m_maps[protocolNum][cmdNum] = cb;
		return true;
	}

	void unregisterPackage(CCEPackage package);
	void unregisterAll();

	quint16 handle(const CCEPackage &package);
private:
	ProtocolMap m_maps;
};
#endif
