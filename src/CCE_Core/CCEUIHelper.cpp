#include "CCE_Core/CCEUIHelper.h"

#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>
#include <QLineF>
#include <QRectF>
#include <QPolygonF>

QString CCEUIHelper::appName()
{
    //没有必要每次都获取,只有当变量为空时才去获取一次
    static QString appName;
    if (appName.isEmpty()) {
        appName = qApp->applicationFilePath();
        QStringList list = appName.split("/");
        appName = list.at(list.count() - 1).split(".").at(0);
    }

    return appName;
}

QString CCEUIHelper::appPath()
{
    return qApp->applicationDirPath();
}

QString CCEUIHelper::appDocumentsPath()
{
    static QString appDocumentsPath;
    if (appDocumentsPath.isEmpty()) {
        QString tempPath= QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        tempPath.append(appName());
        appDocumentsPath=tempPath;
    }
    return appDocumentsPath;
}

QString CCEUIHelper::appDataLocation()
{
    static QString appDataLocation;
    if (appDataLocation.isEmpty()) {
        QDir _appPath(appPath());
        QString tempPath = _appPath.absolutePath();
        QDir dir;
        if (dir.mkpath(tempPath)) {
            appDataLocation = tempPath;
        }
    }
    return appDataLocation;
}

QString CCEUIHelper::appConfigDataLocation()
{
    static QString appConfigDataLocation;
    if (appConfigDataLocation.isEmpty()) {
        QString tempPath = CCEUIHelper::appDocumentsPath();
        tempPath.append(tr("/Config"));
        QDir dir;
        if (dir.mkpath(tempPath)) {
            appConfigDataLocation = tempPath;
        }
    }
    return appConfigDataLocation;
}

QString CCEUIHelper::appParamDataLocation()
{
    static QString appParamDataLocation;
    if (appParamDataLocation.isEmpty()) {
        QString tempPath = CCEUIHelper::appDataLocation();
        tempPath.append(tr("/Parameter"));
        QDir dir;
        if (dir.mkpath(tempPath)) {
            appParamDataLocation = tempPath;
        }
    }
    return appParamDataLocation;
}

QString CCEUIHelper::appLocalsLocation()
{
    static QString appLocalsLocation;
    if (appLocalsLocation.isEmpty()) {
        QString tempPath = CCEUIHelper::appDataLocation();
        tempPath.append(tr("/Locals"));
        QDir dir;
        if (dir.mkpath(tempPath)) {
            appLocalsLocation = tempPath;
        }
    }
    return appLocalsLocation;
}

QString CCEUIHelper::appDocLocation()
{
    static QString appLocalsLocation;
    if (appLocalsLocation.isEmpty()) {
        QString tempPath = CCEUIHelper::appDataLocation();
        tempPath.append(tr("/doc"));
        QDir dir;
        if (dir.mkpath(tempPath)) {
            appLocalsLocation = tempPath;
        }
    }
    return appLocalsLocation;
}

QString CCEUIHelper::appLogDataLocation()
{
    static QString path;
    if (path.isEmpty()) {
        QString tempPath = CCEUIHelper::appDocumentsPath();
        tempPath.append(tr("/Log"));
        QDir dir;
        if (dir.mkpath(tempPath)) {
            path = tempPath;
        }
    }
    return path;
}

QString CCEUIHelper::appRunTimeDataLocation()
{
    static QString path;
    if (path.isEmpty()) {
        QString tempPath = CCEUIHelper::appDocumentsPath();
        tempPath.append(tr("/RunTime"));
        QDir dir;
        if (dir.mkpath(tempPath)) {
            path = tempPath;
        }
    }
    return path;
}

static bool bEnableCommunicatLog = false;
void CCEUIHelper::setEnableCommunicatLog(bool enable)
{
    bEnableCommunicatLog = enable;
}

bool CCEUIHelper::enableCommunicatLog()
{
    return bEnableCommunicatLog;
}

QString CCEUIHelper::appRunTimeConnectionDataFileName()
{
    static QString name;
    if (name.isEmpty()) {
        name.append(tr("connectionData.bin"));
    }
    return name;
}

bool CCEUIHelper::isIP(const QString &ip)
{
    QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    return RegExp.exactMatch(ip);
}

bool CCEUIHelper::isMac(const QString &mac)
{
    QRegExp RegExp("^[A-F0-9]{2}(-[A-F0-9]{2}){5}$");
    return RegExp.exactMatch(mac);
}

bool CCEUIHelper::isTel(const QString &tel)
{
    if (tel.length() != 11) {
        return false;
    }

    if (!tel.startsWith("13") && !tel.startsWith("14") && !tel.startsWith("15") && !tel.startsWith("18")) {
        return false;
    }

    return true;
}

bool CCEUIHelper::isEmail(const QString &email)
{
    if (!email.contains("@") || !email.contains(".com")) {
        return false;
    }

    return true;
}

quint8 CCEUIHelper::getCheckSum(const QByteArray & data)
{
    //计算和
    if (data.isEmpty() || data.isNull())
    {
        return 0;
    }

    unsigned char sum = 0;
    for (int i = 0; i < data.size(); i++)
    {
        sum += data.at(i);
    }
    return sum;
}

int CCEUIHelper::strHexToDecimal(const QString &strHex)
{
    bool ok;
    return strHex.toInt(&ok, 16);
}

QString CCEUIHelper::decimalToStrHex(int decimal)
{
    QString temp = QString::number(decimal, 16);
    if (temp.length() == 1) {
        temp = "0" + temp;
    }

    return temp;
}

QString CCEUIHelper::byteArrayToAsciiStr(const QByteArray &data)
{
    QString temp;
    int len = data.size();

    for (int i = 0; i < len; i++) {
        //0x20为空格,空格以下都是不可见字符
        char b = data.at(i);

        if (0x00 == b) {
            temp += QString("\\NUL");
        } else if (0x01 == b) {
            temp += QString("\\SOH");
        } else if (0x02 == b) {
            temp += QString("\\STX");
        } else if (0x03 == b) {
            temp += QString("\\ETX");
        } else if (0x04 == b) {
            temp += QString("\\EOT");
        } else if (0x05 == b) {
            temp += QString("\\ENQ");
        } else if (0x06 == b) {
            temp += QString("\\ACK");
        } else if (0x07 == b) {
            temp += QString("\\BEL");
        } else if (0x08 == b) {
            temp += QString("\\BS");
        } else if (0x09 == b) {
            temp += QString("\\HT");
        } else if (0x0A == b) {
            temp += QString("\\LF");
        } else if (0x0B == b) {
            temp += QString("\\VT");
        } else if (0x0C == b) {
            temp += QString("\\FF");
        } else if (0x0D == b) {
            temp += QString("\\CR");
        } else if (0x0E == b) {
            temp += QString("\\SO");
        } else if (0x0F == b) {
            temp += QString("\\SI");
        } else if (0x10 == b) {
            temp += QString("\\DLE");
        } else if (0x11 == b) {
            temp += QString("\\DC1");
        } else if (0x12 == b) {
            temp += QString("\\DC2");
        } else if (0x13 == b) {
            temp += QString("\\DC3");
        } else if (0x14 == b) {
            temp += QString("\\DC4");
        } else if (0x15 == b) {
            temp += QString("\\NAK");
        } else if (0x16 == b) {
            temp += QString("\\SYN");
        } else if (0x17 == b) {
            temp += QString("\\ETB");
        } else if (0x18 == b) {
            temp += QString("\\CAN");
        } else if (0x19 == b) {
            temp += QString("\\EM");
        } else if (0x1A == b) {
            temp += QString("\\SUB");
        } else if (0x1B == b) {
            temp += QString("\\ESC");
        } else if (0x1C == b) {
            temp += QString("\\FS");
        } else if (0x1D == b) {
            temp += QString("\\GS");
        } else if (0x1E == b) {
            temp += QString("\\RS");
        } else if (0x1F == b) {
            temp += QString("\\US");
        } else if (0x7F == b) {
            temp += QString("\\x7F");
        } else if (0x5C == b) {
            temp += QString("\\x5C");
        } else if (0x20 >= b) {
            temp += QString("\\x%1").arg(decimalToStrHex((quint8)b));
        } else {
            temp += QString("%1").arg(b);
        }
    }

    return temp.trimmed();
}

QByteArray CCEUIHelper::asciiStrToByteArray(const QString &str)
{
    QByteArray buffer;
    int len = str.length();
    QString letter;
    QString hex;

    for (int i = 0; i < len; i++) {
        letter = str.at(i);

        if (letter == "\\") {
            i++;
            letter = str.mid(i, 1);

            if (letter == "x") {
                i++;
                hex = str.mid(i, 2);
                buffer.append(strHexToDecimal(hex));
                i++;
                continue;
            } else if (letter == "N") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "U") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "L") {           //NUL=0x00
                        buffer.append((char)0x00);
                        continue;
                    }
                } else if (hex == "A") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "K") {           //NAK=0x15
                        buffer.append(0x15);
                        continue;
                    }
                }
            } else if (letter == "S") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "O") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "H") {           //SOH=0x01
                        buffer.append(0x01);
                        continue;
                    } else {                    //SO=0x0E
                        buffer.append(0x0E);
                        i--;
                        continue;
                    }
                } else if (hex == "T") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "X") {           //STX=0x02
                        buffer.append(0x02);
                        continue;
                    }
                } else if (hex == "I") {        //SI=0x0F
                    buffer.append(0x0F);
                    continue;
                } else if (hex == "Y") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "N") {           //SYN=0x16
                        buffer.append(0x16);
                        continue;
                    }
                } else if (hex == "U") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "B") {           //SUB=0x1A
                        buffer.append(0x1A);
                        continue;
                    }
                }
            } else if (letter == "E") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "T") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "X") {           //ETX=0x03
                        buffer.append(0x03);
                        continue;
                    } else if (hex == "B") {    //ETB=0x17
                        buffer.append(0x17);
                        continue;
                    }
                } else if (hex == "O") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "T") {           //EOT=0x04
                        buffer.append(0x04);
                        continue;
                    }
                } else if (hex == "N") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "Q") {           //ENQ=0x05
                        buffer.append(0x05);
                        continue;
                    }
                } else if (hex == "M") {        //EM=0x19
                    buffer.append(0x19);
                    continue;
                } else if (hex == "S") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "C") {           //ESC=0x1B
                        buffer.append(0x1B);
                        continue;
                    }
                }
            } else if (letter == "A") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "C") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "K") {           //ACK=0x06
                        buffer.append(0x06);
                        continue;
                    }
                }
            } else if (letter == "B") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "E") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "L") {           //BEL=0x07
                        buffer.append(0x07);
                        continue;
                    }
                } else if (hex == "S") {        //BS=0x08
                    buffer.append(0x08);
                    continue;
                }
            } else if (letter == "C") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "R") {               //CR=0x0D
                    buffer.append(0x0D);
                    continue;
                } else if (hex == "A") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "N") {           //CAN=0x18
                        buffer.append(0x18);
                        continue;
                    }
                }
            } else if (letter == "D") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "L") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "E") {           //DLE=0x10
                        buffer.append(0x10);
                        continue;
                    }
                } else if (hex == "C") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "1") {           //DC1=0x11
                        buffer.append(0x11);
                        continue;
                    } else if (hex == "2") {    //DC2=0x12
                        buffer.append(0x12);
                        continue;
                    } else if (hex == "3") {    //DC3=0x13
                        buffer.append(0x13);
                        continue;
                    } else if (hex == "4") {    //DC2=0x14
                        buffer.append(0x14);
                        continue;
                    }
                }
            } else if (letter == "F") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "F") {               //FF=0x0C
                    buffer.append(0x0C);
                    continue;
                } else if (hex == "S") {        //FS=0x1C
                    buffer.append(0x1C);
                    continue;
                }
            } else if (letter == "H") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "T") {               //HT=0x09
                    buffer.append(0x09);
                    continue;
                }
            } else if (letter == "L") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "F") {               //LF=0x0A
                    buffer.append(0x0A);
                    continue;
                }
            } else if (letter == "G") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "S") {               //GS=0x1D
                    buffer.append(0x1D);
                    continue;
                }
            } else if (letter == "R") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "S") {               //RS=0x1E
                    buffer.append(0x1E);
                    continue;
                }
            } else if (letter == "U") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "S") {               //US=0x1F
                    buffer.append(0x1F);
                    continue;
                }
            } else if (letter == "V") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "T") {               //VT=0x0B
                    buffer.append(0x0B);
                    continue;
                }
            } else if (letter == "\\") {
                //如果连着的是多个\\则对应添加\对应的16进制0x5C
                buffer.append(0x5C);
                continue;
            } else {
                //将对应的\[前面的\\也要加入
                buffer.append(0x5C);
                buffer.append(letter.toLatin1());
                continue;
            }
        }

        buffer.append(str.mid(i, 1).toLatin1());

    }

    return buffer;
}


QByteArray CCEUIHelper::hexStrToByteArray(const QString &str)
{
    QByteArray senddata;
    int hexdata, lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len / 2);
    char lstr, hstr;

    for (int i = 0; i < len;) {
        hstr = str.at(i).toLatin1();
        if (hstr == ' ') {
            i++;
            continue;
        }

        i++;
        if (i >= len) {
            break;
        }

        lstr = str.at(i).toLatin1();
        hexdata = convertHexChar(hstr);
        lowhexdata = convertHexChar(lstr);

        if ((hexdata == 16) || (lowhexdata == 16)) {
            break;
        } else {
            hexdata = hexdata * 16 + lowhexdata;
        }

        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }

    senddata.resize(hexdatalen);
    return senddata;
}

char CCEUIHelper::convertHexChar(char ch)
{
    if ((ch >= '0') && (ch <= '9')) {
        return ch - 0x30;
    } else if ((ch >= 'A') && (ch <= 'F')) {
        return ch - 'A' + 10;
    } else if ((ch >= 'a') && (ch <= 'f')) {
        return ch - 'a' + 10;
    } else {
        return (-1);
    }
}

QString CCEUIHelper::byteArrayToHexStr(const QByteArray &data)
{
    QString temp = "";
    QString hex = data.toHex();

    for (int i = 0; i < hex.length(); i = i + 2) {
        temp += hex.mid(i, 2) + " ";
    }

    return temp.trimmed().toUpper();
}

quint16 CCEUIHelper::bigLittleSwap16(quint16 v)
{
    return CCEUIHelper::byteToUShort(CCEUIHelper::ushortToByteRec(v));
}

quint32 CCEUIHelper::bigLittleSwap32(quint32 v)
{
    return CCEUIHelper::byteToInt(CCEUIHelper::intToByteRec(v));
}

QByteArray CCEUIHelper::intToByte(int i)
{
    QByteArray result;
    result.resize(4);
    result[3] = (uchar)(0x000000ff & i);
    result[2] = (uchar)((0x0000ff00 & i) >> 8);
    result[1] = (uchar)((0x00ff0000 & i) >> 16);
    result[0] = (uchar)((0xff000000 & i) >> 24);
    return result;
}

QByteArray CCEUIHelper::intToByteRec(int i)
{
    QByteArray result;
    result.resize(4);
    result[0] = (uchar)(0x000000ff & i);
    result[1] = (uchar)((0x0000ff00 & i) >> 8);
    result[2] = (uchar)((0x00ff0000 & i) >> 16);
    result[3] = (uchar)((0xff000000 & i) >> 24);
    return result;
}

int CCEUIHelper::byteToInt(const QByteArray &data)
{
    int i = data.at(3) & 0x000000ff;
    i |= ((data.at(2) << 8) & 0x0000ff00);
    i |= ((data.at(1) << 16) & 0x00ff0000);
    i |= ((data.at(0) << 24) & 0xff000000);
    return i;
}

int CCEUIHelper::byteToIntRec(const QByteArray &data)
{
    int i = data.at(0) & 0x000000ff;
    i |= ((data.at(1) << 8) & 0x0000ff00);
    i |= ((data.at(2) << 16) & 0x00ff0000);
    i |= ((data.at(3) << 24) & 0xff000000);
    return i;
}

quint32 CCEUIHelper::byteToUInt(const QByteArray &data)
{
    quint32 i = data.at(3) & 0x000000ff;
    i |= ((data.at(2) << 8) & 0x0000ff00);
    i |= ((data.at(1) << 16) & 0x00ff0000);
    i |= ((data.at(0) << 24) & 0xff000000);
    return i;
}

quint32 CCEUIHelper::byteToUIntRec(const QByteArray &data)
{
    quint32 i = data.at(0) & 0x000000ff;
    i |= ((data.at(1) << 8) & 0x0000ff00);
    i |= ((data.at(2) << 16) & 0x00ff0000);
    i |= ((data.at(3) << 24) & 0xff000000);
    return i;
}

QByteArray CCEUIHelper::ushortToByte(ushort i)
{
    QByteArray result;
    result.resize(2);
    result[1] = (uchar)(0x000000ff & i);
    result[0] = (uchar)((0x0000ff00 & i) >> 8);
    return result;
}

QByteArray CCEUIHelper::ushortToByteRec(ushort i)
{
    QByteArray result;
    result.resize(2);
    result[0] = (uchar) (0x000000ff & i);
    result[1] = (uchar) ((0x0000ff00 & i) >> 8);
    return result;
}

int CCEUIHelper::byteToUShort(const QByteArray &data)
{
    int i = data.at(1) & 0x000000FF;
    i |= ((data.at(0) << 8) & 0x0000FF00);

    if (i >= 32768) {
        i = i - 65536;
    }

    return i;
}

int CCEUIHelper::byteToUShortRec(const QByteArray &data)
{
    int i = data.at(0) & 0x000000FF;
    i |= ((data.at(1) << 8) & 0x0000FF00);

    if (i >= 32768) {
        i = i - 65536;
    }

    return i;
}

QString CCEUIHelper::getXorEncryptDecrypt(const QString &str, char key)
{
    QByteArray data = str.toLatin1();
    int size = data.size();
    for (int i = 0; i < size; i++) {
        data[i] = data[i] ^ key;
    }

    return QLatin1String(data);
}

uchar CCEUIHelper::getOrCode(const QByteArray &data)
{
    int len = data.length();
    uchar result = 0;

    for (int i = 0; i < len; i++) {
        result ^= data.at(i);
    }

    return result;
}

//CRC16校验
QByteArray CCEUIHelper::getCRCCode(const QByteArray &dataArray)
{
    quint16 i,j;
    quint16 crc=0;
    int len = dataArray.size();
    for(i=0;i<len;++i){
        crc = ((quint8)dataArray.at(i))^crc;
        for(j=0;j<8;++j){
            if(crc&0x0001){
                crc=(crc>>1)^0xA001;
            }
            else{
                crc= crc>>1;
            }
        }
    }
    return CCEUIHelper::ushortToByte(crc);
}
