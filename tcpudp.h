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

                    if(mesaj[17]!="0"){
                        btnlist[i]->setVncConnect(true);
                        btnlist[i]->vncport=mesaj[17];
                    }
                    else {
                        btnlist[i]->setVncConnect(false);
                        btnlist[i]->vncport=mesaj[17];
                    }

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
            QString msg;
            if(sendBroadcastStatus==false)
            {
                sendBroadcastStatus=true;
                msg="hostport|"+ipmaclist[i].ip+"|"+ipmaclist[i].mac+"|"+tcpPort+"|0";
            }else
            {
                msg="hostport|"+ipmaclist[i].ip+"|"+ipmaclist[i].mac+"|"+tcpPort+"|1";
            }
            QByteArray datagram = msg.toUtf8();// +QHostAddress::LocalHost;

            //qDebug()<<broadCastAddress1.section(".",0,2)+".";
            for(int i=1;i<255;i++)
            {
                QString broadadres;
                broadadres=broadCastAddress1.section(".",0,2)+"."+QString::number(i);
               // qDebug()<<broadadres;
                //udpSocketSend->writeDatagram(datagram,QHostAddress(broadCastAddress1), uport.toInt());
                udpSocketSend->writeDatagram(datagram,QHostAddress(broadadres), uport.toInt());

            }

            qDebug()<<"Udp<<Post-1>>.."<<uport<<broadCastAddress1;

        }
        if(broadCastAddress2!=""&&
                ipmaclist[i].ip.section(".",0,2)==broadCastAddress2.section(".",0,2))
        {
            ///QString msg="hostport|"+ipmaclist[i].ip+"|"+ipmaclist[i].mac+"|"+tcpPort;

            QString msg;
            if(sendBroadcastStatus==false)
            {
                sendBroadcastStatus=true;
                msg="hostport|"+ipmaclist[i].ip+"|"+ipmaclist[i].mac+"|"+tcpPort+"|0";
            }else
            {
                msg="hostport|"+ipmaclist[i].ip+"|"+ipmaclist[i].mac+"|"+tcpPort+"|1";
            }

               QByteArray datagram = msg.toUtf8();// +QHostAddress::LocalHost;
            for(int i=1;i<255;i++)
            {
                QString broadadres;
                broadadres=broadCastAddress1.section(".",0,2)+"."+QString::number(i);
               // qDebug()<<broadadres;
                //udpSocketSend->writeDatagram(datagram,QHostAddress(broadCastAddress2), uport.toInt());
                udpSocketSend->writeDatagram(datagram,QHostAddress(broadadres), uport.toInt());

            }
            qDebug()<<"Udp<<Post-2>>.."<<uport<<broadCastAddress2;

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
QStringList MainWindow::readArp()
{
    QStringList list;
    const int size = 256;

        char ip_address[size];
        int hw_type;
        int flags;
        char mac_address[size];
        char mask[size];
        char device[size];

        FILE* fp = fopen("/proc/net/arp", "r");
        if(fp == NULL)
        {
            perror("Error opening /proc/net/arp");
        }

        char line[size];
        fgets(line, size, fp);    // Skip the first line, which consists of column headers.
        while(fgets(line, size, fp))
        {
            sscanf(line, "%s 0x%x 0x%x %s %s %s\n",
                   ip_address,
                   &hw_type,
                   &flags,
                   mac_address,
                   mask,
                   device);
            if(flags==2)
            {
                ///qDebug()<< ip_address<< mac_address<<hw_type<<flags;
                list<<QString(ip_address)+"|"+ QString(mac_address);


            }
        }

        fclose(fp);
   return list;
}
QString MainWindow::getMacForIP(QString ipAddress)
{
    // qDebug()<<"mac adresleri:";
    QString mac="";
    const int size = 256;

        char ip_address[size];
        int hw_type;
        int flags;
        char mac_address[size];
        char mask[size];
        char device[size];

        FILE* fp = fopen("/proc/net/arp", "r");
        if(fp == NULL)
        {
            perror("Error opening /proc/net/arp");
        }

        char line[size];
        fgets(line, size, fp);    // Skip the first line, which consists of column headers.
        while(fgets(line, size, fp))
        {
            sscanf(line, "%s 0x%x 0x%x %s %s %s\n",
                   ip_address,
                   &hw_type,
                   &flags,
                   mac_address,
                   mask,
                   device);
            if(ipAddress==QString(ip_address))
                mac=QString(mac_address);

        }

        fclose(fp);

     return mac;
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



#endif // TCPUDP_H
