#include "networkprofil.h"
#include<QDebug>
#include<QProcess>
#include <QtCore/QTimer>
#include <stdio.h>
#include <QtCore/QCoreApplication>
#include<Database.h>

NewtworkProfil::NewtworkProfil()
{
    localDir="/usr/share/e-ag/";
    networkProfilWather.addPath(localDir+"e-ag.json");
    connect(&networkProfilWather, &QFileSystemWatcher::fileChanged, this,
            [this](){
                qDebug()<<"Ayarlar güncellendi...";
                networkProfilLoad();  // burada tekrar addPath() çağırılacak
            });
    networkProfilLoad();
    if(multicastAddress=="")multicastAddress="239.255.0.11";
    qDebug()<<"multicastAddress: "<<multicastAddress;//networkProfilLoad(); çalışmalı öncesinde

    udpBroadCastSend = new QUdpSocket(this);
    udpBroadCastSend->bind(QHostAddress::AnyIPv4,0,
        QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    udpBroadCastSend->setSocketOption(QAbstractSocket::MulticastTtlOption, 2);
    multicastGroup = QHostAddress("239.255.0.11");
    multicastPort = 45454;
    udpBroadCastSend->setSocketOption(QAbstractSocket::MulticastTtlOption, 32);

    /**************************************************************************/
    QTimer *udpSocketSendConsoleTimer = new QTimer(this);
    connect(udpSocketSendConsoleTimer, &QTimer::timeout,
            this, &NewtworkProfil::sendBroadcastDatagram);
    udpSocketSendConsoleTimer->start(5000);


}

void NewtworkProfil::sendBroadcastDatagram()
{
    ///hostAddressMacButtonSlot();
    if(interfaceList.count()==0||!networkProfilLoadStatus) {
        networkProfilLoadStatus=false;
        networkProfilLoad();
    }

      for (const NetProfil &item : NetProfilList) {
        if (item.serverAddress.isEmpty()) continue;
        if (item.selectedNetworkProfil==false) continue;
        for(int k=0;k<interfaceList.count();k++)
        {
            if(item.networkBroadCastAddress==interfaceList[k].broadcast)
            {
                ///qDebug()<<"Broadcast Yapılan Ağ:" <<networkBroadCastAddress<<networkTcpPort;
                QString uport=item.networkTcpPort;
                std::reverse(uport.begin(), uport.end());
                QJsonObject sendJson;
                sendJson["mainmessagetype"] = "eagconf";
                sendJson["server_address"] =item.serverAddress;
                sendJson["networkBroadCastAddress"] =item.networkBroadCastAddress;
                sendJson["subnet"] =item.subnet;
                sendJson["networkTcpPort"] =item.networkTcpPort;
                sendJson["ftpPort"] =item.ftpPort;
                sendJson["rootPath"] =item.rootPath;
                sendJson["language"] =item.language;
                sendJson["multicastAddress"] =item.multicastAddress;

                sendJson["webblockState"] =item.webblockState;
                sendJson["lockScreenState"] =item.lockScreenState;

                udpBroadCastSend->setMulticastInterface(interfaceList[k].iface);
                QByteArray datagram = QJsonDocument(sendJson).toJson(QJsonDocument::Compact);
                udpBroadCastSend->writeDatagram(datagram,multicastGroup,multicastPort);
                qDebug()<<"ServerBroadCast"<<item.networkIndex<<item.networkBroadCastAddress<<sendJson<<uport.toInt()+uport.toInt();
             }
        }
    }
}

NewtworkProfil::~NewtworkProfil()
{
    //QString data="portStatus|mydisp|noLogin|0|0|0|0|myenv|noLogin|0|0|0|0|0|0|0|close";
    udpBroadCastSend->close();
    udpBroadCastSend->deleteLater();
}

void NewtworkProfil::networkProfilLoad()
{
   /* qDebug()<<"networkProfilLoad: "<<NetProfilList.count()
             <<"interfaceList: "<<interfaceList.count()
             <<"networkProfilLoadStatus"<<networkProfilLoadStatus;*/
    hostAddressMacButtonSlot();
    if(interfaceList.count()==0)  return;

    DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag.json");
    //QJsonArray dizi=db->Oku();
    QJsonArray dizi=db->Ara("selectedNetworkProfil",true);

    if(dizi.count()>0)
    {
        NetProfilList.clear();
        for (const QJsonValue &item : dizi) {
            QJsonObject veri=item.toObject();
            //qDebug()<<"Yüklenen Ağ Profili:" <<veri;
            NetProfil np;
            np.networkIndex=veri["networkIndex"].toString();
            np.selectedNetworkProfil=veri["selectedNetworkProfil"].toBool();
            np.networkName=veri["networkName"].toString();
            np.networkTcpPort=veri["networkTcpPort"].toString();
            np.networkBroadCastAddress=veri["networkBroadCastAddress"].toString();
            np.subnet=veri["subnet"].toString();
            np.serverAddress=veri["serverAddress"].toString();
            np.ftpPort=veri["ftpPort"].toString();
            np.rootPath=veri["rootPath"].toString();
            np.language=veri["language"].toString();
            np.multicastAddress=veri["multicastAddress"].toString();
            multicastAddress=veri["multicastAddress"].toString();
            np.lockScreenState=veri["lockScreenState"].toBool();
            np.webblockState=veri["webblockState"].toBool();
            NetProfilList.append(np);
            networkProfilLoadStatus=true;
        }
    }else{
        qDebug()<<"Yeni Network Ekleniyor.";

        hostAddressMacButtonSlot();
        bool appendStatus=false;
        for(int i=0;i<interfaceList.count();i++)
        {   
            appendStatus=true;
            //qDebug()<<"broadcast address:"<<i<<ipmaclist[i].broadcast;
            QJsonObject veri;
            veri["networkIndex"] =QString::number(db->getIndex("networkIndex"));
            veri["selectedNetworkProfil"] =true;
            veri["networkName"] = "network";
            veri["networkTcpPort"] = "7879";
            veri["serverAddress"]=interfaceList[i].ip;
            veri["networkBroadCastAddress"]=interfaceList[i].broadcast;
            veri["subnet"]=interfaceList[i].subnet;
            veri["ftpPort"]="12345";
            veri["rootPath"]="/tmp/";
            veri["language"]="tr_TR";
            veri["multicastAddress"]="239.255.0.11";
            multicastAddress="239.255.0.11";
            veri["lockScreenState"]=false;
            veri["webblockState"]=false;
            if(interfaceList[i].ip.contains("172.17"))veri["selectedNetworkProfil"] =false;
            db->Sil("networkBroadCastAddress",interfaceList[i].broadcast);
            db->Ekle(veri);
        }
        if(appendStatus){  networkProfilLoad();}
        //qDebug()<<"eagconf bilgileri farklı güncelleniyor.";
        //system("systemctl restart e-ag-client-console.service");
        //system("systemctl restart e-ag-client-networkprofil.service");
    }
}

void NewtworkProfil::hostAddressMacButtonSlot()
{
    interfaceList.clear();

    const QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

    for (const QNetworkInterface &networkInterface : interfaces)
    {
        if (!(networkInterface.flags() & QNetworkInterface::IsUp) ||
            !(networkInterface.flags() & QNetworkInterface::IsRunning))
            continue;

        for (const QNetworkAddressEntry &entry : networkInterface.addressEntries())
        {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol &&
                !entry.ip().isLoopback())
            {
                IpMac im;
                im.ip        = entry.ip().toString();
                im.mac       = networkInterface.hardwareAddress();
                im.broadcast = entry.broadcast().toString();
                im.subnet    = entry.netmask().toString();
                im.iface     = networkInterface;   // 🔥 kritik satır

                interfaceList.append(im);

                QString program = "ethtool -s " + networkInterface.name() + " wol g &";
                system(program.toStdString().c_str());
            }
        }
    }
}



