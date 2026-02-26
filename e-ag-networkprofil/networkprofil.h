
#ifndef NETWORKPROFIL_H
#define NETWORKPROFIL_H
#include <QTcpSocket>
#include <QDataStream>
#include<QTimer>
#include<QUdpSocket>
#include<QNetworkInterface>
#include<QProcess>
#include<QObject>
#include<QSysInfo>
#include<QDir>
#include<QFileSystemWatcher>
class IpMac
{
public:
    QString ip;
    QString mac;
    QString broadcast;
    QString subnet;
    QNetworkInterface iface;   // BUNU EKLE
};

class NetProfil
{
public:
    QString networkIndex;
    bool selectedNetworkProfil;
    QString networkName;
    QString serverAddress;
    QString networkBroadCastAddress;
    QString subnet;
    QString networkTcpPort;
    QString ftpPort;
    QString rootPath;
    QString language;
    bool lockScreenState;
    bool webblockState;
};

class NewtworkProfil: public QObject
{
  Q_OBJECT
public:
    NewtworkProfil();
    ~NewtworkProfil();

signals:
  public slots:
    void networkProfilLoad();
    bool stringToBool(const QString& str) {
        return str.toLower() == "true"; // Büyük/küçük harf duyarsız karşılaştırma
    }
private slots:
    void hostAddressMacButtonSlot();
    void sendBroadcastDatagram();
 private:
    QProcess process;
    QList<IpMac> interfaceList;
    QList<NetProfil> NetProfilList;
    QString localDir;
    QString localDir1;
    QUdpSocket *udpBroadCastSend = nullptr;
    bool networkProfilLoadStatus=false;
    QHostAddress multicastGroup;
    QString multicastAddress;
    quint16 multicastPort;
    QFileSystemWatcher networkProfilWather;
};

#endif // NETWORKPROFIL_H
