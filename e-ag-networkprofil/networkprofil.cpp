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
    localDir1="/tmp/";
    udpBroadCastSend = new QUdpSocket();
    networkProfilLoad();
     /**************************************************************************/
    QTimer *udpSocketSendConsoleTimer = new QTimer();
    QObject::connect(udpSocketSendConsoleTimer, &QTimer::timeout, [&](){
        sendBroadcastDatagram();
    });
    udpSocketSendConsoleTimer->start(5000);

}

void NewtworkProfil::sendBroadcastDatagram()
{
    hostAddressMacButtonSlot();
    if(interfaceList.count()==0||!networkProfilLoadStatus) {
        networkProfilLoadStatus=false;
        networkProfilLoad();
    }

      for (const NetProfil &item : NetProfilList) {
        if (item.serverAddress=="") continue;
        if (item.selectedNetworkProfil==false) continue;
        for(int k=0;k<interfaceList.count();k++)
        {
            if(item.networkBroadCastAddress==interfaceList[k].broadcast)
            {
                QString lockScreenStatestr= "false";
                QString webblockStatestr="false";
                if(item.lockScreenState)lockScreenStatestr="true";
                if(item.webblockState)webblockStatestr="true";
                ///qDebug()<<"Broadcast Yapılan Ağ:" <<networkBroadCastAddress<<networkTcpPort;
                QString uport=item.networkTcpPort;
                std::reverse(uport.begin(), uport.end());
                QString msg;
                msg="eagconf|"+item.serverAddress+"|"+
                      item.networkBroadCastAddress+"|"+
                      item.networkTcpPort+"|"+
                      item.ftpPort+"|"+
                      item.rootPath+"|"+
                      item.language+"|"+
                      lockScreenStatestr+"|"+
                      webblockStatestr;
                QByteArray datagram = msg.toUtf8();// +QHostAddress::LocalHost;
                QString broadCastAdres;
                ///qDebug()<<datagram;
                for(int i=1;i<255;i++)
                {
                    broadCastAdres=item.networkBroadCastAddress.section(".",0,2)+"."+QString::number(i);
                    //udpSocketSend->writeDatagram(datagram,QHostAddress("255.255.255.255"), uport.toInt());
                    udpBroadCastSend->writeDatagram(datagram,QHostAddress(broadCastAdres), uport.toInt()+uport.toInt());
                }
                qDebug()<<"ServerBroadCast"<<item.networkIndex<<item.networkBroadCastAddress<<msg<<uport.toInt()+uport.toInt();
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
            np.serverAddress=veri["serverAddress"].toString();
            np.ftpPort=veri["ftpPort"].toString();
            np.rootPath=veri["rootPath"].toString();
            np.language=veri["language"].toString();
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
            veri["ftpPort"]="12345";
            veri["rootPath"]="/tmp/";
            veri["language"]="tr_TR";
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
    QHostAddress localhost = QHostAddress(QHostAddress::LocalHost);
interfaceList.clear();
    foreach (const QNetworkInterface& networkInterface, QNetworkInterface::allInterfaces()) {
           foreach (const QNetworkAddressEntry& entry, networkInterface.addressEntries()) {
               QHostAddress *hostadres=new QHostAddress(entry.ip().toString());
               if(hostadres->protocol() == QAbstractSocket::IPv4Protocol &&
                       !hostadres->isLoopback() )
               {
                  IpMac im;
                  im.ip=entry.ip().toString();
                  im.mac=networkInterface.hardwareAddress();
                  im.broadcast=entry.broadcast().toString();
                  im.subnet=entry.netmask().toString();
                  interfaceList.append(im);
                 // qDebug()<<"mac:"<<networkInterface.hardwareAddress();
                  //qDebug()<<"ip  address:"<<entry.ip().toString();
                  // qDebug()<<"broadcast  address:"<<entry.broadcast().toString();
                  // qDebug()<<"broadcast  address:"<<entry.broadcast().toString();
               ///  qDebug()<<"type:"<<networkInterface.name()<<networkInterface.type();
                QString program="ethtool -s "+networkInterface.name()+" wol g &";
                system(program.toStdString().c_str());
                  /*
                 if(networkInterface.type()==QNetworkInterface::Ethernet)
                 {

                     //QString program = "notepad.exe"; // Çalıştırılacak uygulamanın yolu (Windows için)
                     QStringList arguments;
                     arguments << "&"; // Uygulamaya geçirilecek argümanlar (isteğe bağlı)

                     QProcess *process = new QProcess();

                     // Uygulamanın başlamasıyla ilgili bir sinyali bağlayabiliriz (isteğe bağlı)
                     QObject::connect(process, &QProcess::started, [=](){
                         qDebug() << "Uygulama başlatıldı:" << program;
                     });

                     // Uygulamanın bitmesiyle ilgili bir sinyali bağlayabiliriz (isteğe bağlı)
                     QObject::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                                      [=](int exitCode, QProcess::ExitStatus exitStatus){
                                          qDebug() << "Uygulama bitti. Çıkış kodu:" << exitCode
                                                   << ", Durum:" << (exitStatus == QProcess::NormalExit ? "Normal" : "Çökme");
                                          process->deleteLater(); // İşlem nesnesini sil
                                      });

                     // Uygulamayı asenkron olarak başlat
                     process->start(program, arguments);

                     if (!process->waitForStarted(1000)) { // Uygulamanın başlayıp başlamadığını kısa bir süre kontrol et (isteğe bağlı)
                         qDebug() << "Uygulama başlatılamadı:" << process->errorString();
                         process->deleteLater();
                     } else {
                         qDebug() << "Uygulama başlatılıyor ve ana akış devam ediyor...";
                         // Burada ana uygulamanızın diğer işlemleri devam edebilir.
                     }

                  //system(kmt27.toStdString().c_str());

                 }*/
               }
           }
       }


}
