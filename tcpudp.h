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
void MainWindow::newConnection()
{
    while (m_server->hasPendingConnections())
        appendToSocketList(m_server->nextPendingConnection());
}

void MainWindow::appendToSocketList(QTcpSocket* socket)
{
    connection_list.append(socket);
    qintptr id = (qintptr)&connection_list.last();

    connect(socket, SIGNAL(readyRead()), this , SLOT(readSocket()));
    connect(socket, SIGNAL(disconnected()), this , SLOT(discardSocket()));
    QString ip;
    if (socket->peerAddress().toString().count()>15)
        ip=socket->peerAddress().toString().split(":")[3];
    else
        ip=socket->peerAddress().toString();//.split(":")[3];

    qDebug()<<"Bağlantı Kuruldu:"<<id<<"gelen ip:"<<ip;
    QString mac=getMacForIP(ip);
    hostAddressMacButtonSlot();
    if(ip!=myIpAddress)//mac=myMacAddress;
    {
            QStringList iplistname=fileToList("iplistname");  //liste olşturuluyor
        QString line=listGetLine(iplistname,mac); //değiştirilecek satır getiriliyor

        if(line!="") //iplistname dosyasında varsa
        {
            QStringList lst1=line.split("|");
            iplistname=listRemove(iplistname,mac); //değişecek satır siliniyor
            iplistname<<ip+"|"+mac+"|" +"pcopen"+"|" +lst1[3]+"|" +lst1[4]+"|" +lst1[5]+"|online"+"|"+lst1[7]+"|"+lst1[8]+"|" +QString::number(socket->socketDescriptor())+"|"+QString::number(id)+"|e|e|e";
            listToFile(iplistname,"iplistname");

           // qDebug()<<"önceden var bağlandı değiştirildi";
        }else
        {
            iplistname<<ip+"|"+mac+"|" +"pcopen"+"|" +"sshclose"+"|" +"vncclose"+"|"+"ftpclose"+"|online"+"|??"+"|e"+"|" +QString::number(socket->socketDescriptor())+"|"+QString::number(id)+"|e|e|e";
            listToFile(iplistname,"iplistname");
          //  qDebug()<<"önceden yok bağlandı eklendi";
        }
    }
    pcButtonGuncelleSlot(mac,false, "",true);
    connectControl();

}

void MainWindow::connectControl()
{
    hostAddressButtonSlot();
  ////  qDebug()<<"ilk soket sayısı"<<connection_list.size();
    for (int i=0;i<connection_list.size();i++)
    {
        bool find=false;
        QStringList list=fileToList("iplistname");

        for(int k=0;k<list.count();k++)
        {
            QString line=list[k];

            if(line!="") //iplistname dosyasında varsa
            {
                QStringList lst=line.split("|");

                if(lst[6]=="online")
                {

                    if(QString::number(connection_list[i]->socketDescriptor())== lst[9])
                    {
                        find=true;
                    }
                }
            }

        }


        if(!find)
        {
            qDebug()<<"Olmayan Soket id:"<<QString::number(connection_list[i]->socketDescriptor());

            connection_list[i]->close();
           // connection_list[i]->deleteLater();
             continue;
        }
        QString lip;
        if (connection_list[i]->localAddress().toString().count()>15)
            lip=connection_list[i]->localAddress().toString().split(":")[3];
        else
            lip=connection_list[i]->localAddress().toString();
         if(myIpAddress!=lip) {
             connection_list[i]->close();
             qDebug()<<"server adres uyusuzluğu"<<myIpAddress<<lip;
             continue;
            }



    }

   /// qDebug()<<"son soket sayısı"<<connection_list.size();
}
void MainWindow::readSocket()
{
     QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

   QByteArray block = socket->readAll();
    QDataStream in(&block, QIODevice::ReadOnly);
    //in.setVersion(QDataStream::Qt_5_11);

    while (!in.atEnd())
    {
        QString receiveString;
        in >> receiveString;
        receiveString.prepend(QString("%1").arg(socket->socketDescriptor()));
        //nt fd = socket->socketDescriptor();
       // qDebug()<<fd;
       //receiveString.append("|"+socket->socketDescriptor());
        /********************************************************/
      //  QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

        for (int i=0;i<connection_list.size();i++)
        {
          //   qintptr de =  socket;
           // qDebug()<<"aaa"<<de;
            if (connection_list.at(i) == socket)
            {
                //receiveString.append("|"+QString::number(socket->socketDescriptor()));
                qintptr id = (qintptr)&connection_list.at(i);
               // int j = (int)id;
                QString ip;
                    if (socket->peerAddress().toString().count()>15)
                     ip=socket->peerAddress().toString().split(":")[3];
                    else
                     ip=socket->peerAddress().toString();//.split(":")[3];

                receiveString.append("|"+ip+"|"+QString::number(id));
               // qDebug()<<"bu bağlantıya mesaj geldi"<<id;
              //  connection_list.removeAt(i);
                break;
            }
        }
        /************************************************/
       emit newMessage(receiveString);
    }

  //  readData();

}

void MainWindow::discardSocket()
{ //qDebug()<<"aaa";
    QString mac;
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    for (int i=0;i<connection_list.size();i++)
    {
      //   qintptr de =  socket;
       // qDebug()<<"aaa"<<de;
        if (connection_list.at(i) == socket)
        {
     QString ip;
                if (socket->peerAddress().toString().count()>15)
                 ip=socket->peerAddress().toString().split(":")[3];
                else
                 ip=socket->peerAddress().toString();//.split(":")[3];
                 qintptr id = (qintptr)&connection_list.at(i);
            qDebug()<<"Bağlantı Kesildi ip:"<<ip;
           // qDebug()<<"online liste"<<onLinePcList;
            QStringList list=fileToList("iplistname");

            QString ln=listGetLine(list,ip);//silinecek satır getiriliyor
            //qDebug()<<"id aranacak"<<QString::number(id);
           //  qDebug()<<ln;
           if (ln!="")
            {
                mac=ln.split("|")[1];
              ///  onLinePcList=listRemove(onLinePcList,mac);//onlinepclist listesinden siliniyor
                QStringList iplistname=fileToList("iplistname");//iplistname listesi oluşturuldu
                QString line=listGetLine(iplistname,mac); //değiştirilecek satır getiriliyor
                QStringList lst=line.split("|");
                iplistname=listRemove(iplistname,mac);//iplistname listesinden satır siliniyor
                iplistname<<lst[0]+"|"+lst[1]+"|" +lst[2]+"|" +lst[3]+"|" +lst[4]+"|" +lst[5]+"|"+"offline"+"|"+lst[7]+"|"+lst[8]+"|" +"disconnect"+"|"+"disconnect"+"|h|h|h";
                listToFile(iplistname,"iplistname"); //dosya kaydedildi
             }

            connection_list.removeAt(i);

            //pcListeGuncelleSlot();
            pcButtonGuncelleSlot(mac,false,"",false);
            socket->deleteLater();
            disconnect(socket, SIGNAL(readyRead()), this , SLOT(readSocket()));
            disconnect(socket, SIGNAL(disconnected()), this , SLOT(discardSocket()));

           // qDebug()<<"Online PC Sayısı:"<<onLinePcList.count();
            break;

        }
    }



}

void MainWindow::sendMessageInit()
{
    QString receiver = socketNumberLabel->text();
   if(receiver=="Broadcast")
    {
       // qDebug()<<"mesaj yeri";
        foreach (QTcpSocket* socket,connection_list)
        {
            sendMessage(socket);

        }
    }

    else if(receiver!="")
    {

             foreach (QTcpSocket* socket,connection_list)
                {
                    if(socket->socketDescriptor() == receiver.toLongLong())
                    {
                       // qDebug()<<receiver.toLongLong();
                        sendMessage(socket);
                        break;
                    }
                }
        }
   if(tcpKomut.length()>0)
   {

      tcpKomut="";
   }
   else //if(lineEdit_message->text().length()>0)
   {

       lineEdit_message->clear();
   }

  //
}

void MainWindow::sendMessage(QTcpSocket* socket)
{
    if(socket)
    {
        if(socket->isOpen())
        {
            QString str;// = lineEdit_message->text();
            if(tcpKomut.length()>0)
            {
                str=tcpKomut;

            }
            else //if(lineEdit_message->text().length()>0)
            {
                str= lineEdit_message->text();

            }
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);

            //out.setVersion(QDataStream::Qt_5_11);
            out << str;
            socket->write(block);
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");
}

void MainWindow::displayMessage(const QString& str)
{
    mesajSlot(str);
}

void MainWindow::ekranImageRead()
{
  while( ekranSocketServer->hasPendingDatagrams() )
  {
    QByteArray buffer( ekranSocketServer->pendingDatagramSize(), 0 );
    ekranSocketServer->readDatagram( buffer.data(), buffer.size() );

    QDataStream stream( buffer );
   // stream.setVersion( QDataStream::Qt_4_0 );

    quint16 width, height, y;
    stream >> width >> height >> y;

    if( !ekranImages )
      ekranImages = new QImage( width, height, QImage::Format_RGB32 );
    else if( ekranImages->width() != width || ekranImages->height() != height )
    {
      delete ekranImages;
      ekranImages = new QImage( width, height, QImage::Format_RGB32 );
    }

    for( int x=0; x<width; ++x )
    {
      quint8 red, green, blue;
      stream >> red >> green >> blue;

      ekranImages->setPixel( x, y, qRgb( red, green, blue ) );
    }
  }

  //setText( "" );
  for(int i=0;i<btnlist.count();i++)
  {
      if(btnlist[i]->toolTip()== pcMac->text())
      {
      ////btnlist[i]->setIcon(QIcon(QPixmap::fromImage( *ekranImages )));
    //  btnlist[i]->setIconSize(btnlist[i]->size());
      }
  }



  //setPixmap( QPixmap::fromImage( *ekranImage ) );
  //resize( ekranImage->size() );
}

QString MainWindow::getMacForIP(QString ipAddress)
{
   // qDebug()<<"mac beni çağırdın..";
    QString MAC="";
    QStringList arguments;
            arguments << "-c" << QString("arp -a %1|awk {'print $4'}").arg(ipAddress);
            QProcess process;
            process.start("/bin/bash",arguments);
           // process.waitForFinished(-1); // will wait forever until finished
            //QString stdout = process.readAllStandardOutput();

   // qDebug()<<ipAddress;
   // process.start(QString("arp -a %1|awk {'print $4'}").arg(ipAddress));
    //process.start(QString("arp \-a %1").arg(ipAddress));
     //qDebug()<<"deneme"<<QString("arp -a %1 | awk {'print $4'}").arg(ipAddress);
    if(process.waitForFinished())
    {
        //QString result = process.readAll();
       MAC = process.readAll();
       /* QStringList list = result.split(QRegularExpression("\\t"));
        if(list.contains(ipAddress))
            MAC = list.at(list.indexOf(ipAddress) + 1);*/
       // result.chop(1);
       MAC.chop(1);
    }
   // qDebug()<<"deneme:"<<MAC;
    return MAC;
}

void MainWindow::sendBroadcastDatagram()
{
    QHostAddress myBroadcastAddress;
    QString remoteNetwork=localNetwork->text();
        qDebug()<<"Udp<<Post>>..";
    hostAddressMacButtonSlot();
    QString msg="Server Mesaj|"+myIpAddress+"|"+myMacAddress+"|"+tcpPort->text();
    QByteArray datagram = msg.toUtf8();// +QHostAddress::LocalHost;
    QString port=tcpPort->text();
    std::reverse(port.begin(), port.end());
    //qDebug()<<"tcp"<<serverPort<<"udp:"<<port;
  //  udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 8889);
    remoteNetwork.chop(3);
     for(int i=1;i<=254;i++)
    {
       //  remoteNetwork.append(QString::number(i));
       myBroadcastAddress=QHostAddress(remoteNetwork+QString::number(i));
       //qDebug()<<"remoteNetwork:"<<myBroadcastAddress<<port;
       // fileHostportCopyAllSlot();
       udpSocket->writeDatagram(datagram,myBroadcastAddress, port.toInt());

    }

     system("cat /proc/net/arp |awk '$3==\"0x2\" {print $1\"|\"$4}'>/usr/share/E-Ag/mactoiplist");

     /*********************************************************/
     hostAddressMacButtonSlot();//localhost ip detected
      /********************arp dosyasında olmayan pc listesi bulunuyor********************************/
      /************tamamen kapatılan makinanın tespiti yapılıyor***/
        QStringList arplist=fileToList("mactoiplist");
        QStringList list=fileToList("iplistname");
        for(int i=0;i<arplist.count();i++)
         {
            if(arplist[i]!="")
            {
                QStringList line=arplist[i].split("|");
                QString mac = line[1].toLower();
                if(mac!="")
                {
                list=listRemove(list,mac);
                }
            }
        }
       // listToFile(list,"iplistnamekalan");
         /*************************************************************/
        /****************arp tablosunda olmayanları pcclose yapıyoruz**************/
        QStringList list_=fileToList("iplistname");

        for(int i=0;i<list.count();i++)
        {
            QString line=list[i];
            if(line!="")
            {
                QStringList lst=line.split("|");
                QString ln=listGetLine(list_,lst[1]); //değiştirilecek satır getiriliyor
                if(ln!="") //iplistname dosyasında varsa
                {
                    if(ln.split("|")[2]=="pcopen")
                    {
                        list_=listRemove(list_,lst[1]); //değişecek satır siliniyor
                        list_<<lst[0]+"|"+lst[1]+"|"+"pcclose"+"|"+"sshclose"+"|"+"vncclose"+"|" +"ftpclose"+"|"+"offline"+"|" +lst[7]+"|"+lst[8]+"|" +lst[9]+"|"+lst[10]+"|h|h|h";
                        listToFile(list_,"iplistname");
                        ///   pcButtonGuncelleSlot(lst[1],false, "",false);
                        qDebug()<<"kapanan makina tespit edildi";
                        for (int i=0;i<connection_list.size();i++)
                        {
                            if(QString::number(connection_list[i]->socketDescriptor())== lst[9])
                            {
                                // qDebug()<<"socket bulundu"<<lst[9];
                                ///pcButtonGuncelleSlot(lst[1],false,"",false);
                                //  connection_list[i]->deleteLater();
                                //   connection_list->atRemove(i);
                                //disconnect(connection_list[i], SIGNAL(readyRead()), this , SLOT(readSocket()));
                                //disconnect(connection_list[i], SIGNAL(disconnected()), this , SLOT(discardSocket()));

                                connection_list[i]->close();
                                // connection_list[i]->deleteLater();
                            }
                        }
                    }
                }
            }

        }



        /****************************************************/

       QStringList iplistname=fileToList("iplistname");

    QString mac;
    for(int i=0;i<arplist.count();i++)
    {
        if(arplist[i]!="")
        {
            QStringList line=arplist[i].split("|");
            QString ip = line[0];
            mac = line[1].toLower();
            bool updatestate=false;
            if(mac!="")
            {
                QString ln=listGetLine(iplistname,mac); //değiştirilecek satır getiriliyor
                if(ln!="") //iplistname dosyasında varsa
                {
                    if(ln.split("|")[2]=="pcclose")
                    {
                        iplistname=listRemove(iplistname,mac); //değişecek satır siliniyor
                        iplistname<<ip+"|"+mac+"|" +"pcopen"+"|" +ln.split("|")[3]+"|" +ln.split("|")[4]+"|" +ln.split("|")[5]+"|"+ln.split("|")[6]+"|"+ln.split("|")[7]+"|"+ln.split("|")[8]+"|" +ln.split("|")[9]+"|"+ln.split("|")[10]+"|h|h|h";
                        updatestate=true;
                    }
                }
                else
                {
                    iplistname<<ip+"|"+mac+"|" +"pcopen"+"|" +"sshclose"+"|" +"vncclose"+"|" +"ftpclose"+"|offline|???"+"|e"+"|arpscan"+"|arpscan"+"|h|h|h";
                    updatestate=true;
                }

            }
            else
            {
                qDebug()<<"arp table not finded";

            }
            listToFile(iplistname,"iplistname");
            if(updatestate)
            {
                // qDebug()<<"arp table modifed or update";
                pcButtonGuncelleSlot(mac,false, "",false);
            }

        }

    }
}

void MainWindow::hostAddressMacButtonSlot()
{
    int a=0;
    foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
        {
            // Return only the first non-loopback MAC Address
            if (!(netInterface.flags() & QNetworkInterface::IsLoopBack))
            {++a;
                if(a==1)
                {
                    myMacAddress=netInterface.hardwareAddress();


                }

            }

        }

    QHostAddress localhost = QHostAddress(QHostAddress::LocalHost);
        for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
            if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
               {
                //  qDebug() <<"deenem"<< address.toString();

            myIpAddress=address.toString();


            return;
            }
        }


}

#endif // TCPUDP_H
