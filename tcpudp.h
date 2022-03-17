/*****************************************************************************
 *   Copyright (C) 2020 by Bayram KARAHAN                                    *
 *   <bayramk@gmail.com>                                                     *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 3 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .          *
 *****************************************************************************/
#ifndef TCPUDP_H
#define TCPUDP_H
void  MainWindow::udpSendData(QString _mesajTur,QString _mesaj,QString _ip)
{
    QString uport=tcpPort;
    std::reverse(uport.begin(), uport.end());

       hostAddressMacButtonSlot();
    for(int i=0;i<ipmaclist.count();i++)
    {
       // qDebug()<<"ip:"<<ipmaclist[i].ip<<broadCastAddress1<<broadCastAddress2<<_ip;
        if(broadCastAddress1!=""&&
                ipmaclist[i].ip.section(".",0,2)==broadCastAddress1.section(".",0,2)&&
                ipmaclist[i].ip.section(".",0,2)==_ip.section(".",0,2))
        {

           QString msg=_mesajTur+"|"+_mesaj+"|"+ipmaclist[i].ip+"|"+uport+"|"+localUserName+"|"+localPassword+"|"+remoteUserName+"|"+remotePassword;
            QByteArray datagram = msg.toUtf8();
           udpSocketSend->writeDatagram(datagram,QHostAddress(_ip), uport.toInt());
        }
        if(broadCastAddress2!=""&&
                ipmaclist[i].ip.section(".",0,2)==broadCastAddress2.section(".",0,2)&&
                ipmaclist[i].ip.section(".",0,2)==_ip.section(".",0,2))
        {
            QString msg=_mesajTur+"|"+_mesaj+"|"+ipmaclist[i].ip+"|"+uport+"|"+localUserName+"|"+localPassword+"|"+remoteUserName+"|"+remotePassword;
            QByteArray datagram = msg.toUtf8();
            udpSocketSend->writeDatagram(datagram,QHostAddress(_ip), uport.toInt());
        }
        system("sleep 0.1");
    }
}

void MainWindow::udpSocketServerRead()
{
    // qDebug()<<"Client Gelen Udp Mesaj:";
               QByteArray datagram;
    QStringList mesaj;

    while (udpSocketGet->hasPendingDatagrams()) {
        datagram.resize(int(udpSocketGet->pendingDatagramSize()));
        QHostAddress sender;
        quint16 senderPort;

        udpSocketGet->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString rmesaj=datagram.constData();
      /// qDebug()<<"Client Gelen Udp Mesaj:"<<rmesaj;

        mesaj=rmesaj.split("|");
         // qDebug()<<"Client Gelen Udp Mesaj:"<<mesaj[0]<<mesaj[1]<<mesaj[2]<<mesaj[3];
        QStringList lst;
        QString _mac=mesaj[2];
        for(int i=0;i<btnlist.count();i++)
        {
            btnlist[i]->tcpConnectCounter++;
                        if(btnlist[i]->tcpConnectCounter>btnlist.count()+3)
                        {
                            btnlist[i]->setTcpConnect(false);
                            btnlist[i]->setSshConnect(false);
                            btnlist[i]->setVncConnect(false);
                            btnlist[i]->setFtpConnect(false);
                            btnlist[i]->setUser("noLogin");
                            btnlist[i]->tcpConnectCounter=0;
                        }

            if(_mac.toUpper()==btnlist[i]->mac.toUpper()&&mesaj[3]=="portStatus"){
                btnlist[i]->tcpConnectCounter=0;

                qDebug()<<"gelen mesaj:"<<rmesaj<<mesaj.count();
                // btnlist[i]->tcpConnectCounter=0;
                btnlist[i]->setPcState(true);
                btnlist[i]->setTcpConnect(true);
                btnlist[i]->ip=mesaj[1];

                if(mesaj.count()==19)
                {
                    btnlist[i]->setUser(mesaj[5]);
                    btnlist[i]->setDisplay(mesaj[6]);
                    btnlist[i]->setOs(mesaj[14]);

                    if(mesaj[7]=="1")
                        btnlist[i]->setKilitControlState(true);
                    else
                        btnlist[i]->setKilitControlState(false);


                    if(mesaj[8]=="1")
                        btnlist[i]->setKilitTransparanControlState(true);
                    else
                        btnlist[i]->setKilitTransparanControlState(false);

                    if(mesaj[9]=="1")
                        btnlist[i]->setIconControlState(true);
                    else
                        btnlist[i]->setIconControlState(false);

                    if(mesaj[16]=="1")
                        btnlist[i]->setSshConnect(true);
                    else
                        btnlist[i]->setSshConnect(false);

                    if(mesaj[17]=="1")btnlist[i]->setVncConnect(true);
                    else btnlist[i]->setVncConnect(false);

                    if(mesaj[18]=="1")btnlist[i]->setFtpConnect(true);
                    else btnlist[i]->setFtpConnect(false);
                }
            }

        }

    }


}
void MainWindow::sendBroadcastDatagram()
{
    if(remoteUserName==""||remotePassword==""||
            localUserName==""||localPassword=="") return;
    QString uport=tcpPort;
    std::reverse(uport.begin(), uport.end());
    /// qDebug()<<"tcp"<<tcpPort->text()<<"udp:"<<port;
    hostAddressMacButtonSlot();
    for(int i=0;i<ipmaclist.count();i++)
    {
        if(broadCastAddress1!=""&&
                ipmaclist[i].ip.section(".",0,2)==broadCastAddress1.section(".",0,2))
        {
            QString msg="hostport|"+ipmaclist[i].ip+"|"+ipmaclist[i].mac+"|"+tcpPort;
            QByteArray datagram = msg.toUtf8();// +QHostAddress::LocalHost;
            udpSocketSend->writeDatagram(datagram,QHostAddress(broadCastAddress1), uport.toInt());
            qDebug()<<"Udp<<Post>>.."<<uport<<broadCastAddress1;

        }
        if(broadCastAddress2!=""&&
                ipmaclist[i].ip.section(".",0,2)==broadCastAddress2.section(".",0,2))
        {
            QString msg="hostport|"+ipmaclist[i].ip+"|"+ipmaclist[i].mac+"|"+tcpPort;
            QByteArray datagram = msg.toUtf8();// +QHostAddress::LocalHost;
            udpSocketSend->writeDatagram(datagram,QHostAddress(broadCastAddress2), uport.toInt());
            qDebug()<<"Udp<<Post>>.."<<uport<<broadCastAddress2;

        }
    }

}
void MainWindow::hostAddressMacButtonSlot()
{
    QHostAddress localhost = QHostAddress(QHostAddress::LocalHost);
ipmaclist.clear();
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
                  ipmaclist.append(im);

                 // qDebug()<<"mac:"<<networkInterface.hardwareAddress();
                  //qDebug()<<"ip  address:"<<entry.ip().toString();
                 // qDebug()<<"broadcast  address:"<<entry.broadcast().toString();
              }
           }
       }
//qDebug()<<"ip  address:"<<ipmaclist.count();


}

QString MainWindow::getMacForIP(QString ipAddress)
{
    // qDebug()<<"mac adresleri:";
    system("cat /proc/net/arp |awk '$3==\"0x2\" {print $1\"|\"$4}'>/usr/share/e-ag/mactoiplist");
    QStringList mactoiplist=fileToList("mactoiplist");
     for(int i=0;i<mactoiplist.count();i++)
     {
        if(mactoiplist[i]!="")
        {
            QStringList line=mactoiplist[i].split("|");
            QString ip = line[0];
            QString mac = line[1].toLower();
            if(mac!=""&&ip==ipAddress)
            {
                return mac;
                //qDebug()<<"mac adresi"<<ip<<mac<<ipAddress;
            }
        }
    }
     return "";
}

QString MainWindow::getIpPortStatus(QString service)
{
    QString result="";
    QStringList arguments;
    arguments << "-c" << QString(service);
    QProcess process;
    process.start("/bin/bash",arguments);
    if(process.waitForFinished(-1))
    {
        result = process.readAll();
        result.chop(1);
    }
    qDebug()<<"Port sorgulama:"<<result<<service;
    if(result.toInt()>0){ return "open";}
    else {return "close";}
}


void MainWindow::sshAramaButtonSlot()
{
   /// qDebug()<<"ssh Tarama Başlatıldı";

     textBrowser_receivedMessages->clear();
      mesajSlot("ssh Tarama Başlatıldı");

   /************************ip dosyası oluşturuluyor***************/
    QStringList liste=fileToList("iplistname");
    QStringList ip_liste;

   for(int i=0;i<liste.count();i++)
   {
       QString line=liste[i];
        if(line!="")
       {
       QStringList lst=line.split("|");

           if(lst[2]=="pcopen"&&lst[8]=="e") ip_liste<<lst[0];
       }
   }
   listToFile(ip_liste,"ip");
/*************************ssiplist oluşturuldu*************************************/

    QStringList arguments;
    QString  komut;
//    echo '1'|sudo -S nmap  -n -p 22 -iL ip | awk '/Nmap scan report/{print $5;}'
    komut.append("echo ").append(localPassword).append(" | sudo -S ").append("nmap  -n -p 22 --open ").append("-iL "+localDir+"/ip").append(" | awk '/Nmap scan report/{print $5;}'>"+localDir+"/sshiplist");
   // komut= QString("").arg();

    //qDebug()<<komut;
    arguments << "-c" << komut;
     QProcess process;
    process.start("/bin/bash",arguments);
    process.waitForFinished(-1); // will wait forever until finished
     mesajSlot("ssh Tarama Tamamlandı");
  /*********************************************************/
     QStringList liste2=fileToList("iplistname");
    // qDebug()<<"komut çalışacak";
     QStringList sshiplist=fileToList("sshiplist");
    //  qDebug()<<"komut çalışacak";
     QStringList liste_;
  /*********** iplistname dosyası sshclose yapılıyor***********************************/
    for(int i=0;i<liste2.count();i++)
    {
        QString line=liste2[i];
       if(line!="")
        {
        QStringList lst=line.split("|");
        liste_<<(lst[0]+"|"+lst[1]+"|" +lst[2]+"|" +"sshclose"+"|" +lst[4]+"|" +lst[5]+"|"+lst[6]+"|" +lst[7]+"|" +lst[8]);
        }
    }
     //listToFile(liste_,"iplistname");
    /***********sshiplist dosyasında bulunan satırlar iplistname dosyasında sshopen yapılıyor***********************************/
    for(int i=0;i<sshiplist.count();i++)
    {
        QString line=sshiplist[i];
        if(line!="")
        {
            QStringList lst=line.split("|");
            QString mac=getMacForIP(lst[0]);
            QString iplistnameline=listGetLine(liste_,mac); // satır çekiliyor

            liste_=listRemove(liste_,mac);//listeden önceki siliniyor
            if(iplistnameline!="")
            {
                QStringList lst1=iplistnameline.split("|");
                liste_<<lst1[0]+"|"+lst1[1]+"|" +lst1[2]+"|" +"sshopen"+"|" +lst1[4]+"|" +lst1[5]+"|"+lst1[6]+"|" +lst1[7]+"|" +lst1[8];
            }
            listToFile(liste_,"iplistname");

            for(int i=0;i<btnlist.count();i++)
            {
                if(btnlist[i]->mac== mac)
                    btnlist[i]->setSshConnect(true);
            }
        }

    }

     /****************************************************************/
//pcListeGuncelleSlot();
}

void MainWindow::vncAramaButtonSlot()
{
 textBrowser_receivedMessages->clear();
    /************************ip dosyası oluşturuluyor***************/
     QStringList liste=fileToList("iplistname");
     QStringList ip_liste;

    for(int i=0;i<liste.count();i++)
    {
        QString line=liste[i];
         if(line!="")
        {
        QStringList lst=line.split("|");
        if(lst[2]=="pcopen"&&lst[8]=="e")
            ip_liste<<lst[0];
        }
    }
    listToFile(ip_liste,"ip");
 /*************************vnciplist oluşturuldu*************************************/
    mesajSlot("vnc Tarama Başlatıldı");
     QStringList arguments;
     QString  komut;
 //    echo '1'|sudo -S nmap  -n -p 5900  -iL ip | awk '/Nmap scan report/{print $5;}'
     komut.append("echo ").append(localPassword).append(" | sudo -S ").append("nmap  -n -p 5900 --open ").append("-iL "+localDir+"/ip").append(" | awk '/Nmap scan report/{print $5;}'>"+localDir+"/vnciplist");
     //qDebug()<<komut;
     arguments << "-c" << komut;
      QProcess process;
     process.start("/bin/bash",arguments);
     process.waitForFinished(-1); // will wait forever until finished
      mesajSlot("vnc Tarama Tamamlandı");
   /*********************************************************/
      QStringList liste2=fileToList("iplistname");
     // qDebug()<<"komut çalışacak";
      QStringList sshiplist=fileToList("vnciplist");
     //  qDebug()<<"komut çalışacak";
      QStringList liste_;
   /*********** iplistname dosyası vncclose yapılıyor***********************************/
     for(int i=0;i<liste2.count();i++)
     {
         QString line=liste2[i];
        if(line!="")
         {
         QStringList lst=line.split("|");
         liste_<<(lst[0]+"|"+lst[1]+"|" +lst[2]+"|" +lst[3]+"|" +"vncclose"+"|" +lst[5]+"|"+lst[6]+"|"+lst[7]+"|" +lst[8]);
         }
     }
      //listToFile(liste_,"iplistname");
     /***********sshiplist dosyasında bulunan satırlar iplistname dosyasında vncopen yapılıyor***********************************/
     for(int i=0;i<sshiplist.count();i++)
     {
         QString line=sshiplist[i];
         if(line!="")
         {
             QStringList lst=line.split("|");
             QString mac=getMacForIP(lst[0]);
             QString iplistnameline=listGetLine(liste_,mac); // satır çekiliyor

             liste_=listRemove(liste_,mac);//listeden önceki siliniyor
             if(iplistnameline!="")
             {
                 QStringList lst1=iplistnameline.split("|");
                 liste_<<lst1[0]+"|"+lst1[1]+"|" +lst1[2]+"|" +lst1[3]+"|" +"vncopen"+"|" +lst1[5]+"|"+lst1[6]+"|" +lst1[7]+"|" +lst1[8];
             }
             listToFile(liste_,"iplistname");
             for(int i=0;i<btnlist.count();i++)
             {
                 if(btnlist[i]->mac== mac)
                     btnlist[i]->setVncConnect(true);
             }

         }
     }
     //  listToFile(liste_,"iplistname");
      /****************************************************************/
//pcListeGuncelleSlot();
}

void MainWindow::ftpAramaButtonSlot()
{
 textBrowser_receivedMessages->clear();
    /************************ip dosyası oluşturuluyor***************/
     QStringList liste=fileToList("iplistname");
     QStringList ip_liste;

    for(int i=0;i<liste.count();i++)
    {
        QString line=liste[i];
         if(line!="")
        {
        QStringList lst=line.split("|");
        if(lst[2]=="pcopen"&&lst[8]=="e")
            ip_liste<<lst[0];
        }
    }
    listToFile(ip_liste,"ip");
 /*************************vnciplist oluşturuldu*************************************/
    mesajSlot("ftp Tarama Başlatıldı");
     QStringList arguments;
     QString  komut;
 //    echo '1'|sudo -S nmap  -n -p 21  -iL ip | awk '/Nmap scan report/{print $5;}'
     komut.append("echo ").append(localPassword).append(" | sudo -S ").append("nmap  -n -p 21 --open ").append("-iL "+localDir+"/ip").append(" | awk '/Nmap scan report/{print $5;}'>"+localDir+"/ftpiplist");
     //qDebug()<<komut;
     arguments << "-c" << komut;
      QProcess process;
     process.start("/bin/bash",arguments);
     process.waitForFinished(-1); // will wait forever until finished
      mesajSlot("ftp Tarama Tamamlandı");
   /*********************************************************/
      QStringList liste2=fileToList("iplistname");
     // qDebug()<<"komut çalışacak";
      QStringList sshiplist=fileToList("ftpiplist");
     //  qDebug()<<"komut çalışacak";
      QStringList liste_;
   /*********** iplistname dosyası vncclose yapılıyor***********************************/
     for(int i=0;i<liste2.count();i++)
     {
         QString line=liste2[i];
        if(line!="")
         {
         QStringList lst=line.split("|");
         liste_<<(lst[0]+"|"+lst[1]+"|" +lst[2]+"|" +lst[3]+"|" +lst[4]+"|" +"ftpclose"+"|"+lst[6]+"|"+lst[7]+"|" +lst[8]);
         }
     }
      //listToFile(liste_,"iplistname");
     /***********sshiplist dosyasında bulunan satırlar iplistname dosyasında vncopen yapılıyor***********************************/
     for(int i=0;i<sshiplist.count();i++)
     {
         QString line=sshiplist[i];
         if(line!="")
         {
             QStringList lst=line.split("|");
             QString mac=getMacForIP(lst[0]);
             QString iplistnameline=listGetLine(liste_,mac); // satır çekiliyor

             liste_=listRemove(liste_,mac);//listeden önceki siliniyor
             if(iplistnameline!="")
             {
                 QStringList lst1=iplistnameline.split("|");
                 liste_<<lst1[0]+"|"+lst1[1]+"|" +lst1[2]+"|" +lst1[3]+"|" +lst1[4]+"|" +"ftpopen"+"|"+lst1[6]+"|" +lst1[7]+"|" +lst1[8];
             }
             listToFile(liste_,"iplistname");
             for(int i=0;i<btnlist.count();i++)
             {
                 if(btnlist[i]->mac== mac)
                     btnlist[i]->setFtpConnect(true);
             }

         }
     }
     //listToFile(liste_,"iplistname");
      /****************************************************************/
//pcListeGuncelleSlot();
}


#endif // TCPUDP_H
