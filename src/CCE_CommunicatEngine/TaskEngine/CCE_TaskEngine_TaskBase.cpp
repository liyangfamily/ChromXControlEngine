#include "CCE_TaskEngine_TaskBase.h"

CCE_TaskEngine_TaskBase::CCE_TaskEngine_TaskBase(QObject *parent /*= 0*/) :
    QObject(parent)
{
    m_refCount = 0;
}

CCE_TaskEngine_TaskBase::~CCE_TaskEngine_TaskBase()
{
}

int CCE_TaskEngine_TaskBase::push_new_data(const CCEEnginePackage & dataArray)
{
    int res = 0;
    m_mutex_rawData.lock();

    m_list_RawData.push_back(dataArray);
    res = m_list_RawData.size();
    m_mutex_rawData.unlock();
    m_last_Report = QDateTime::currentDateTime();
    return res;
}

QObject * CCE_TaskEngine_TaskBase::socketObj()
{
    return m_pSocket;
}

void CCE_TaskEngine_TaskBase::setHostName(QString name)
{
    m_strTaskName = name;
}

QString CCE_TaskEngine_TaskBase::hostName()
{
    return m_strTaskName;
}

int CCE_TaskEngine_TaskBase::addRef()
{
    QMutexLocker locker(&m_mutex_ref);
    m_refCount++;

    return m_refCount;
}

int CCE_TaskEngine_TaskBase::delRef()
{
    QMutexLocker locker(&m_mutex_ref);
    m_refCount--;

    return m_refCount;
}

int CCE_TaskEngine_TaskBase::ref()
{
    QMutexLocker locker(&m_mutex_ref);
    //return 1;
    return m_refCount;
}

bool CCE_TaskEngine_TaskBase::lockRun()
{
    return m_mutex_run.tryLock();
}

void CCE_TaskEngine_TaskBase::unlockRun()
{
    return m_mutex_run.unlock();
}
