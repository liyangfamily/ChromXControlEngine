/*********************************************************************************************************
** This file is part of the CCE_Core module of the CCE Toolkit.
*********************************************************************************************************/
#ifndef CHROMX_H_CCEUIHELPER
#define CHROMX_H_CCEUIHELPER
#pragma once
#include <CCE_Core/CCECoreGlobal>

#include <QObject>
QT_BEGIN_NAMESPACE
class QLineF;
class QRectF;
QT_END_NAMESPACE
class CCE_CORE_EXPORT CCEUIHelper : public QObject
{
    Q_OBJECT
public:
    //程序本身文件名称
    static QString appName();
    //程序当前所在路径
    static QString appPath();
    //程序文档所在路径
    static QString appDocumentsPath();
    //程序数据路径
    static QString appDataLocation();

    //程序参数数据路径-exe
    static QString appParamDataLocation();
    //程序语言路径-exe
    static QString appLocalsLocation();
    //程序文档路径-exe
    static QString appDocLocation();
    //程序配置数据路径-doc
    static QString appConfigDataLocation();
    //程序Log数据路径-doc
    static QString appLogDataLocation();
    //程序runtime数据路径-doc
    static QString appRunTimeDataLocation();

    //设置是否打印通信log
    static void setEnableCommunicatLog(bool enable);
    static bool enableCommunicatLog();

    //程序runtime连接关系保存路径
    static QString appRunTimeConnectionDataFileName();

    //判断是否是IP地址
    static bool isIP(const QString &ip);

    //判断是否是MAC地址
    static bool isMac(const QString &mac);

    //判断是否是合法的电话号码
    static bool isTel(const QString &tel);

    //判断是否是合法的邮箱地址
    static bool isEmail(const QString &email);

    //获取校验和
    static quint8 getCheckSum(const QByteArray &data);


    //16进制字符串转10进制
    static int strHexToDecimal(const QString &strHex);

    //10进制转16进制字符串,补零.
    static QString decimalToStrHex(int decimal);

    //字节数组转Ascii字符串
    static QString byteArrayToAsciiStr(const QByteArray &data);

    //Ascii字符串转字节数组
    static QByteArray asciiStrToByteArray(const QString &str);

    //16进制字符串转字节数组
    static QByteArray hexStrToByteArray(const QString &str);
    static char convertHexChar(char ch);

    //字节数组转16进制字符串
    static QString byteArrayToHexStr(const QByteArray &data);

#define ISUNSIGNED(x) (decltype(x)(x)>=0&&decltype(x)(~(x))>=0)
#define ISSINGNED(x)   (decltype(x)(x)>=0?(decltype(x)(~(x))<0?true:false):true)
    template<class T>
    static bool bitSet(T & _t, unsigned int _pos, bool bTrue)
    {
        T _tt = _t;
        //只能是无符号数
        if (ISSINGNED(_tt))
        {
            return false;
        }
        //移位限制
        if (_pos > sizeof(T) * 8 - 1)
        {
            return false;
        }
        //是否为1
        if (bTrue)
        {
            _t = (_t | (0x01 << _pos));
        }
        else
        {
            _t = (_t & (~(0x01 << _pos)));
        }
        return true;
    }

    template<class T>
    static bool bitGet(T _t, unsigned int _pos)
    {
        //移位限制
        if (_pos > sizeof(T) * 8 - 1)
        {
            return false;
        }
        return _t & (0x01 << _pos) ? true : false;
    }
};

#endif
