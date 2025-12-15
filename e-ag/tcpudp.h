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

void  MainWindow::udpSendData(QString _mesajTur,QString _gorev,QString _ekmesaj,QString komutMesaji, bool mesajVisible)
{
    QString uport="7879";
    udpSendDataStatus=true;
    ///qDebug()<<"Mesaj Gönderilecek:"<<_mesajTur;
    for (const NetProfil &item : NetProfilList) {
        if (item.serverAddress=="") continue;
        if (item.selectedNetworkProfil==false) continue;
       /* if(item.networkBroadCastAddress!=""&&
            item.serverAddress.section(".",0,2)==item.networkBroadCastAddress.section(".",0,2)&&
            item.serverAddress.section(".",0,2)==item.ipAddress.section(".",0,2))
        {*/

    for(int i=0;i<onlinePcList.count();i++)
    {

        if(onlinePcList[i]->connectState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect))
        {
            uport=onlinePcList[i]->netProfil.networkTcpPort;
            std::reverse(uport.begin(), uport.end());
            QString smesajVisible="0";
            if (mesajVisible) smesajVisible="1";
            //QString msg=_mesajTur+"|"+_gorev+"|"+_ekmesaj+"|"+komutMesaji+"|"+smesajVisible+"|"+onlinePcList[i]->netProfil.serverAddress+"|"+uport;

            // mesaj bilgilerini ekle
            QJsonObject sendJson;
            sendJson["mainmessagetype"] = _mesajTur;
            sendJson["submessagetype"] =_gorev ;
            sendJson["mission"] = _ekmesaj;
            sendJson["missionmessage"]=komutMesaji;
            sendJson["messagevisible"]=smesajVisible;
            sendJson["server_address"] = onlinePcList[i]->netProfil.serverAddress;
            sendJson["port"] = uport;

            QByteArray datagram = QJsonDocument(sendJson).toJson(QJsonDocument::Compact);
            udpSocketSend->writeDatagram(datagram,QHostAddress(onlinePcList[i]->ip), uport.toInt());
            ///qDebug()<<"Mesaj Gönderildi:"<<msg;
        }
    }
    }
    udpSendDataStatus=false;
}

void MainWindow::eagtraySendDataDetached(const QString &cmd)
{
    qDebug() << "e-ag-tray DataDetached Uygulamasına Giden Komut:" << cmd;

    QLocalSocket *socket = new QLocalSocket(this);

    // Bağlandıktan sonra komutu gönder
    connect(socket, &QLocalSocket::connected, this, [socket, cmd]() {
        socket->write((cmd + "\n").toUtf8());
        socket->flush();
        socket->disconnectFromServer();   // hemen kapat
    });

    // Hata olursa soketi sil (C++11 uyumlu)
    connect(socket, &QLocalSocket::errorOccurred, this,
            [socket](QLocalSocket::LocalSocketError){
                socket->deleteLater();
            });

    // Kapatılınca sil
    connect(socket, &QLocalSocket::disconnected, this, [socket]() {
        socket->deleteLater();
    });

    socket->connectToServer("eag_tray_Detached");
}

void MainWindow::eagtraySendData(const QString &cmd,TrayResponseCallback callback)
{
    qDebug()<<"e-ag-tray Uygulamasına Giden Komut:"<<cmd;
    QLocalSocket *socket = new QLocalSocket(this);
    // Bağlantı sonrası komutu gönderen fonksiyon
    auto sendCommand = [socket, cmd]() {
        if (socket->state() == QLocalSocket::ConnectedState) {
            socket->write((cmd + "\n").toUtf8());
            socket->flush();
        }
    };


    connect(socket, &QLocalSocket::connected, this, sendCommand);

    connect(socket, &QLocalSocket::readyRead, this, [socket, callback]() {
        QString reply = QString::fromUtf8(socket->readAll());
        if (callback) callback(reply);
        socket->disconnectFromServer();
    });

    connect(socket, &QLocalSocket::disconnected, this, [socket]() {
        socket->deleteLater();
    });

    connect(socket, &QLocalSocket::errorOccurred, this, [socket](QLocalSocket::LocalSocketError err) {
        qWarning() << "Tray socket error:" << err;
        socket->deleteLater();
    });

    // Bağlantı isteği
    socket->connectToServer("eag_tray");

    // Eğer çok hızlı bağlanmışsa → connected sinyali gelmeyebilir
    /* if (socket->waitForConnected(50)) {
        sendCommand();   // garanti gönderim

    }
    if (!socket.waitForConnected(500)) {
        qWarning() << "Tray uygulamasına bağlanılamadı!";
        return;
    }*/
}

void MainWindow::udpSocketServerRead()
{
    // sendBroadcastStatus=false;
    QByteArray datagram;
    while (udpSocketGet->hasPendingDatagrams()) {
        datagram.resize(int(udpSocketGet->pendingDatagramSize()));
        QHostAddress sender;
        quint16 senderPort;
        udpSocketGet->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        //QString rmesaj=datagram.constData();
        //qDebug()<<"Gelen veri:"<<rmesaj;

        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(datagram, &parseError);

        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "JSON parse hatası:" << parseError.errorString();
            //continue;
            return;
        }

        if (!doc.isObject()) {
            qDebug() << "JSON object bekleniyor!";
            //continue;
            return;
        }

        QJsonObject json = doc.object();
        QString messageType = json["messagetype"].toString();

        if (messageType == "eagclientconf") {
            clientConfUpdate(json);
        }
        else if (messageType == "sendfileclient") {
            fileReceiveProcess(json);
        }
        else if (messageType == "commandstateclient") {
            clientCommandState(json);
            }
        else {
            qDebug() << "Bilinmeyen message type:" << messageType;
        }

    }



}

void MainWindow::clientConfUpdate(const QJsonObject &json)
{
    QString mac = json["mac_address"].toString();
    QString ip  = json["ip_address"].toString();

    // Console bilgileri
    bool console_sshstate = json["console_sshstate"].toBool();
    bool console_xrdpstate = json["console_xrdpstate"].toBool();
    QString console_vncports = json["console_vncports"].toString();
    QString console_hostname = json["console_hostname"].toString();

    // Tray bilgileri
    QString tray_user = json["tray_user"].toString();
    /*bool tray_volume=false;
    if (json.contains("tray_volume"))
        pc->setTrayLock(json["tray_volume"].toBool());*/

    if (mac.isEmpty())
        return;

    // onlinePcList içinde MAC adresine göre ara ve update yap
    bool found = false;
    for (MyPc *pc : onlinePcList) {
        if (pc->mac.toUpper() == mac.toUpper()) {
            pc->tcpConnectCounter=0;
            pc->setConnectState(true);
            pc->ip=ip;
            //qDebug()<<"ekleniyor"<<ip<<mac;
            //pc->volumeState=json["tray_volume"].toBool();
            pc->setVolumeState(json["tray_volume"].toBool());
            pc->setKeyboardState(json["console_keyboardState"].toBool());
            pc->setMouseState(json["console_mouseState"].toBool());
            pc->setInternetState(json["console_internetState"].toBool());
            pc->setWebblockState(json["console_webblockState"].toBool());
            pc->setYoutubeState(json["console_youtubeState"].toBool());
            pc->setKilitTransparanState(json["tray_tlock"].toBool());
            pc->setKilitState(json["tray_lock"].toBool());
            pc->setUser(tray_user);
            pc->setHostname(console_hostname);
            if(console_sshstate) pc->setSshState("o");
            else pc->setSshState("c");

            if(console_vncports!="0"){pc->setVncState("o"); pc->vncport=console_vncports;}
            else {pc->setVncState("c");pc->vncport=console_vncports;}

            if(console_xrdpstate)pc->setXrdpState("o");
            else pc->setXrdpState("c");
            //pc->setLastUpdate(QDateTime::currentDateTime());*/

            if (json.contains("command_status"))
            {
                QString kmt=json["command"].toString();
                QString kmtdeteail=json["command_detail"].toString();
                QString kmtstate=json["command_status"].toString();
                pc->setCommandState(kmt,kmtdeteail,kmtstate);
            }

            found = true;
            break;
        }
    }

    // Eğer listede yoksa, yeni bir client ekle
    if (!found) {
        slotPcEkle(mac.toUpper(),ip);
    }
}

void MainWindow::clientCommandState(const QJsonObject &json)
{

    qDebug()<<"komut çıktısı"<<json["command"].toString()<<
        json["command_detail"].toString()<<
        json["command_status"].toString();

    QString mac = json["mac_address"].toString();
    QString ip  = json["ip_address"].toString();

    for (MyPc *pc : onlinePcList) {
        if (pc->mac.toUpper() == mac.toUpper()) {
            //pc->tcpConnectCounter=0;
            //pc->setConnectState(true);
            //pc->ip=ip;
            QString kmt=json["command"].toString();
            QString kmtdeteail=json["command_detail"].toString();
            QString kmtstate=json["command_status"].toString();
            pc->setCommandState(kmt,kmtdeteail,kmtstate);
            break;
        }

    }
}
void MainWindow::fileReceiveProcess(const QJsonObject &json)
{

    UserPrivilegeHelper helper;
    QString user = helper.detectActiveUser();
    UserInfo info = helper.getUserInfo(user);
    QString guiusername = info.username;

    if (guiusername.isEmpty()) {
        qWarning() << "Aktif kullanıcı bulunamadı!";
        return;
    }
    QString mac = json["mac_address"].toString();
    for (MyPc *pc : onlinePcList) {
        if (pc->mac.toUpper() == mac.toUpper()) {
            QString filename = json["filename"].toString();
            qDebug()<<"Dosya Geldi: "<<filename;
            QString kmt01="mkdir -p /home/"+guiusername+"/Masaüstü/e-ag-dosya";
            QString kmt02="chmod 777 /home/"+guiusername+"/Masaüstü/e-ag-dosya";
            QString kmt03="chown "+guiusername+":"+guiusername+" /home/"+guiusername+"/Masaüstü/e-ag-dosya";
            system(kmt01.toStdString().c_str());QThread::msleep(50);  // milisaniye
            system(kmt02.toStdString().c_str());QThread::msleep(50);  // milisaniye
            system(kmt03.toStdString().c_str());QThread::msleep(50);  // milisaniye

            QString kmt1="cp /tmp/"+filename+" /home/"+guiusername+"/Masaüstü/e-ag-dosya/";
            QString kmt2="chmod 777 /home/"+guiusername+"/Masaüstü/e-ag-dosya/"+filename;
            QString kmt3="chown "+guiusername+":"+guiusername+" /home/"+guiusername+"/Masaüstü/e-ag-dosya/"+filename;

            system(kmt1.toStdString().c_str());QThread::msleep(50);  // milisaniye
            system(kmt2.toStdString().c_str());QThread::msleep(50);  // milisaniye
            system(kmt3.toStdString().c_str());QThread::msleep(50);  // milisaniye
            qDebug() << "Dosya alındı:" << filename;
            break;
        }
    }
}


void MainWindow::hostAddressMacButtonSlot()
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
                  interfaceList.append(im);

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

void MainWindow::pcCloseSignalSlot(QString ip,QString mac)
{
    //qDebug()<<"pcCloseSignalSlot: "<<ip<<mac;
    for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->mac==mac){
            slotPcSil(i,onlinePcList[i]->ip,onlinePcList[i]->mac);
        }
    }
    pcListeGuncelleSlot("closepcDetect");
}

void MainWindow::slotPcEkle(QString _mac,QString _ip)
{
    //qDebug() << "Pc Ekle Başla: "<<_ip;
    qDebug() << "Açılan Pc: "<<_mac<<_ip;
    MyPc *mypc=new MyPc(_mac,_ip);
    mypc->setConnectState(false);

    connect(mypc, SIGNAL(pcClickSignal(QString)),this,
            SLOT(pcClickSlot(QString)));

    connect(mypc, SIGNAL(pcDoubleClickSignal(QString)),this,
            SLOT(pcDoubleClickSignalSlot(QString)));

    connect(mypc, SIGNAL(pcHideSignal(QString)),this,
    SLOT(pcHideSignalSlot(QString)));

    connect(mypc, SIGNAL(pcSettingUpdateSignal(QString,QString)),this,
            SLOT(pcSettingUpdateSignalSlot(QString,QString)));
    connect(mypc, SIGNAL(pcScreenViewSignal(QString,QString)),this,
            SLOT(pcScreenViewSignalSlot(QString,QString)));


    connect(mypc, SIGNAL(pcCloseSignal(QString,QString)),
            this, SLOT(pcCloseSignalSlot(QString,QString)));

    connect(mypc, SIGNAL(pcRightClickSignal()),
            this, SLOT(pcRightClickSignalSlot()));

    mypc->netProfil=NetProfilList.first();
    for (const NetProfil &item : NetProfilList) {
        //qDebug()<<item.networkBroadCastAddress;

        if(_ip.section(".",0,2)==item.networkBroadCastAddress.section(".",0,2))
        {
            mypc->netProfil=item;
        }
    }

    onlinePcList.append(mypc);
    pcopencount++;
/************************grup ekeleme*******************************/
    bool foundg = false;

    for (groupList &g : PcData::groupListe) {
        if (g.groupName == mypc->groupname) {
            foundg = true;
            // Eğer grup varsa ama seçili değilse, seçili hale getir
            if (!g.groupSelect)
                g.groupSelect = true;
            break;
        }
    }

    // Eğer grup bulunmadıysa, yeni olarak ekle
    if (!foundg) {
        PcData::groupListe.append({true, mypc->groupname});
    }

/*******************************************************************/
    //qDebug() << "Pc Ekle Son: "<<_ip<<onlinePcList[0]->groupname;
    //pcListeGuncelleSlot("openpcDetect");
    pcSettingUpdateSignalSlot(_mac.toUpper(),"pc Eklendi");
    mypc->setVolumeState(false);
    mypc->setKeyboardState(false);
    mypc->setMouseState(false);
    mypc->setInternetState(false);
    mypc->setWebblockState(false);
    mypc->setYoutubeState(false);

}

void MainWindow::slotPcSil(int _index,QString _mac,QString _ip)
{
    qDebug() << "Kapatılan Pc: "<<onlinePcList[_index]->ip;
    pcopencount--;
    layout->removeWidget(onlinePcList[_index]);
    onlinePcList[_index]->deleteLater();
    onlinePcList.removeAt(_index);
    //pcListeGuncelleSlot("deletepcDetect");
}

#endif // TCPUDP_H
