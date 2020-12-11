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
#include "mainwindow.h"
#include<QDebug>
#include <QProcess>
#include <QtNetwork/qnetworkinterface.h>
#include <QtNetwork/QHostAddress>
#include<QtNetwork/QTcpSocket>
#include<QDir>
#include<filecrud.h>
#include<QString>
#include<createbutton.h>
#include<QDataStream>
#include<menu.h>
#include<butonclick.h>
#include <QScrollArea>
#include<QApplication>
#include<QDesktopWidget>
#include<QtWidgets>
#include<tcpudp.h>
#include<init.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    auto appIcon = QIcon(":/icons/E-Ag.ico");
    this->setWindowIcon(appIcon);

    localDir="/usr/share/E-Ag/";

    timerClick = new QTimer(this);
    connect(timerClick, SIGNAL(timeout()), this, SLOT(timerClickSlot()));
    timerClick->start(500);
       /********************* Broadcast Message yollanıyor *****************************************/
    udpSocket = new QUdpSocket(this);
    timerUdpSocket = new QTimer(this);
    connect(timerUdpSocket, SIGNAL(timeout()), this, SLOT(sendBroadcastDatagram()));
    timerUdpSocket->start(10000);

    init(); //buton ve label editbox nesneleri oluşturuluyor...
/*********************************************************************/

    m_server = new QTcpServer();
    if(m_server->listen(QHostAddress::Any,tcpPort->text().toInt()))
    {
       connect(this,SIGNAL(newMessage(QString)),this,SLOT(displayMessage(QString)));
       connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));
       mesajSlot("Server is listening...");
    /**********Clientlara gidecek hostport dosyası oluşturuluyor **************/
       QStringList lst;
        hostAddressMacButtonSlot();
     lst.append(myIpAddress+"|"+tcpPort->text()+"|Server");
      listToFile(lst,"hostport");
     // qDebug()<<"hostport dosyası hazırlandı.....";
       /*************************/

    }
   else
    {
        QMessageBox::critical(this,"QTCPServer",QString("Unable to start the server: %1.").arg(m_server->errorString()));
        exit(EXIT_FAILURE);
    }
    /*********************************************************/
   // listePcSlot();
  //  enableButton();
    tw->hide();
    lst->show();
    hostListReset();
    pcListeGuncelleSlot();
}

void MainWindow::pcListeSlot()
{
    tw->hide();
    macListSaveButton->hide();
    lst->show();
    pcListeGuncelleSlot();
}

void MainWindow::pcListeGuncelleSlot()
{
    /****************************************************/
    for(int i=0;i<btnlist.count();i++)
    {
        delete btnlist[i];
        btnlist.removeAt(i);
    }

 /*****************************************************/
    QStringList list;
    QStringList list_=fileToList("iplistname");
    int gercekliste=0;
    for(int i=0;i<list_.count();i++)
     {
        QString line=list_[i];
        if(line!="")
        {
        QStringList lst=line.split("|");
        if(lst[8]=="e") {
            gercekliste++;
            list<<line;
        }


        }
    }
  ////  qDebug()<<"gerçekliste:"<<gercekliste;
 /****************************************************/
      //QStringList list=fileToList("iplistname");
      qSort(list.begin(), list.end());
/*********************************************************/
   int sira=0;

    sira=gercekliste;
    int satir=sira/10;
    int mod=sira%10;
    if (mod!=0) satir++;
    int sutun=10;
    int sn=0;
    lst->resize(en*180,(satir+1)*boy*20);

     for(int i=1;i<=satir;i++)
     {
         for(int j=1;j<=10;j++)
         {
             QString line=list[sn];
             //line.chop(1);
            /// if(line!="")
            /// {
                 QStringList ls=line.split("|");
                 //QWidget *cpc=createPc(ls[5],ls[1],ls[2],ls[3],ls[4],ls[6],80,80,false,"");
                 //qDebug()<<"Gösterim Durumu:"<<line<<ls[7];

                 if(ls[8]=="e")
                 {
                    Pc *cpc=new Pc();
                     cpc->setMac(ls[1],en*16,boy*16);
                     layout->addWidget(cpc, i,j,1,1);
                     // cpc->setCaption("deneme");
                     btnlist.append(cpc);

                 }
                 sn++;
                 if (sira==sn) break;
            /// }
         }
     }

      mesajSlot("Bilgisayarlar Listelendi!");
}
void MainWindow::resizeEvent(QResizeEvent *event)
{
//qDebug()<<"değişti";
//MainWindow(this);
}
void MainWindow::pcButtonGuncelleSlot(QString mac, bool setImage, QString iconname, bool pcupdate)
{   // sshAramaButtonSlot();//Eklenen pc'nin ssh bağlantısı varmı kontrol ediliyor
    // vncAramaButtonSlot();//Eklenen pc'nin vnc bağlantısı varmı kontrol ediliyor
//qDebug()<<"geldin"<<mac;
    QStringList lst=fileToList("iplistname");
    QString line=listGetLine(lst,mac);
    bool find=false;
    int index=0;
   if (line!="")
   {
       QStringList ls=line.split("|");
       for(int i=0;i<btnlist.count();i++)
              {

                  if(btnlist[i]->toolTip()== mac){find=true;index=i;}

              }

       if(find)
       {
           for(int i=0;i<btnlist.count();i++)
           {
            if(btnlist[i]->toolTip()==mac)
            {

           //// qDebug()<<"bulundu değişiyor";
            btnlist[i]->setUpdate(mac,pcupdate);
            if(setImage) btnlist[i]->setIcon(iconname);
            }
           }

       }
      else
       {
      if(!pcEkranImageAllStatus&&!pcEkranImageStatus)
      {
           //  QWidget *cpc=createPc(ls[5],ls[1],ls[2],ls[3],ls[4],ls[6],80,80,setImage,iconname);
          // btnlist.removeAt(index);
           ///btnlist.append(cpc);


         /*  int sira=btnlist.count();
           int satir=sira/10;
           int sutun=sira-satir*10;
           if ((sira-sutun*satir)!=0) satir++;*/
     ////     qDebug()<<"bulunmadı ekleniyor";//<<satir<<sutun;
          //qDebug()<<ls[0]<<ls[1]<<ls[2]<<ls[3]<<ls[4]<<ls[5]<<ls[6]<<ls[7];

        /*   Pc *cpc=new Pc();
           cpc->setMac(mac,80,80);
           cpc->setUpdate(mac,pcupdate);
           btnlist.append(cpc);
           */
          // layout->addWidget(cpc, satir,sutun,1,1);

           pcListeGuncelleSlot();



          // layout->update();
           //lst->update();
      }

       }

   }

}
void MainWindow::hostAddressButtonSlot()
{
    QHostAddress localhost = QHostAddress(QHostAddress::LocalHost);
        for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
            if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
               {
            //      qDebug() <<"deenem"<< address.toString();

            QString adres=address.toString();


            adres.chop(3);
            QString adr=adres.split(".")[0]+"."+adres.split(".")[1]+"."+adres.split(".")[2]+".255";
          //  adres.append("255");
              //adres.append("*");
           // qDebug()<<adres;

            broadCastAddress=adr;
           // le->setText(adres);
            return;
            }
        }
}
void MainWindow::agTaraButtonSlot()
{

     textBrowser_receivedMessages->clear();
  //  qDebug()<<"Tarama Başlatıldı";
    mesajSlot("Ağ Taramassı Başlatıldı!");
       QString leip;
   // if (localNetwork->text()!="")
    //{
        leip=localNetwork->text();
        leip.chop(3);
        leip.append("*");
    //}
    //else
    //{
     //   leip=broadCastAddress;
       // leip.chop(3);
   // }

    QStringList arguments;
    QString  komut;
   // qDebug()<<leip;
    //+" 'echo "+password->text()+" | sudo -S' "+
    komut.append("echo ").append(localPassword->text()).append(" |nohup sudo -S ").append("nmap -sn -n -sP ").append(leip).append(" | awk '/Nmap scan report/{  printf $5;printf \"|\";getline;getline;printf $3;printf \"|\";print $4;}'|grep -v \"report\">"+localDir+"/iplist");
   // qDebug()<<komut;
    arguments << "-c" << komut;
    //sudo nmap -n -sP 10.107.248.* | awk '/Nmap scan report/{printf $5;printf ":";getline;getline;print $3}'>iplist
    // arguments << "-c" << "nmap  -sn 192.168.23.\\*";
    QProcess process;
    process.start("/bin/bash",arguments);
    process.waitForFinished(); // will wait forever until finished
    //qDebug()<<"Tarama Tamamlandı";1
    mesajSlot("Ağ Taraması Tamamlandı!");
    //hostTableListButtonSlot();
  //  hostTableListSaveButtonSlot();
   // listePcSlot();
     /*********************************************************/
    QStringList fiplist=fileToList("iplist");
    QStringList fip=fileToList("ip");
    QStringList fiplistname=fileToList("iplistname");
    hostAddressMacButtonSlot();//localhost ip detected
    for(int i=0;i<fiplist.count();i++)
    {
        QStringList line=fiplist[i].split("|");
        QString ip = line[0];
        QString mac = line[1].toLower();
        if(ip!=myIpAddress)//mac=myMacAddress;//localhost devre dışı    bırakılacak
        {
            if(mac!="")
            {
                fip<<ip; //ip dosyası oluşturulacak..
                /**********************************************************************************/
                QString lin=listGetLine(fiplistname,mac); //değiştirilecek satır getiriliyor
                if(lin!="") //iplistname dosyasında varsa
                {
                    fiplistname=listRemove(fiplistname,mac); //değişecek satır siliniyor
                    fiplistname<<ip+"|"+mac+"|" +"pcopen"+"|" +lin.split("|")[3]+"|" +lin.split("|")[4]+"|"+lin.split("|")[5]+"|"+lin.split("|")[6]+"|" +lin.split("|")[7]+"|" +lin.split("|")[8]+"|" +lin.split("|")[9]+"|"+lin.split("|")[10]+"|"+lin.split("|")[11]+"|"+lin.split("|")[12]+"|"+lin.split("|")[13];
                }
                else
                {
                    fiplistname<<ip+"|"+mac+"|" +"pcopen"+"|" +"sshclose"+"|" +"vncclose|ftpclose|offline"+"|???|e|"+"nmapscan"+"|nmapscan"+"|e|e|e";
                }

                /*********************************************************************************/
                /*************************************************/
                 ///onLinePcList=listRemove(onLinePcList,mac);//önceden varsa siliniyor
                 ////onLinePcList<<ip+"|"+mac+"|" +"pcopen"+"|" +"sshclose"+"|" +"vncclose|ftpclose|online|???"+"|"+"9999"+"|9999";
                /********************************************************/
            }
        }
         listToFile(fiplistname,"iplistname");
         pcButtonGuncelleSlot(mac,false, "",false);

    }
    listToFile(fip,"ip");

   // fileHostportCopyAllSlot();
   // pcListeGuncelleSlot();
    //  mesajSlot("Ağ Taraması Listelendi.");

}

void MainWindow::hostListReset()
{
    QStringList list=fileToList("iplistname");
    QStringList list_;
    for(int i=0;i<list.count();i++)
     {
        QString line=list[i];
        if(line!="")
        {
        QStringList lst=line.split("|");
        //list=listRemove(list,lst[1]);
        list_<<lst[0]+"|"+lst[1]+"|" +"pcclose|sshclose|vncclose|ftpclose|offline|"+lst[7]+"|" +lst[8]+"|disconnect|disconnect"+"|h|h|h";

        }
    }
    listToFile(list_,"iplistname");
 mesajSlot("Mac Listesi Yüklendi.");
}

void MainWindow::sshAramaButtonSlot()
{

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
       //if(lst[2]=="pcopen")
           ip_liste<<lst[0];
       }
   }
   listToFile(ip_liste,"ip");
/*************************ssiplist oluşturuldu*************************************/

    QStringList arguments;
    QString  komut;
//    echo '1'|sudo -S nmap  -n -p 22 -iL ip | awk '/Nmap scan report/{print $5;}'
    komut.append("echo ").append(localPassword->text()).append(" | sudo -S ").append("nmap  -n -p 22 --open ").append("-iL "+localDir+"/ip").append(" | awk '/Nmap scan report/{print $5;}'>"+localDir+"/sshiplist");
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
        liste_<<(lst[0]+"|"+lst[1]+"|" +lst[2]+"|" +"sshclose"+"|" +lst[4]+"|" +lst[5]+"|"+lst[6]+"|" +lst[7]+"|" +lst[8]+"|" +lst[9]+"|" +lst[10]+"|" +lst[11]+"|" +lst[12]+"|" +lst[13]);
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
                liste_<<lst1[0]+"|"+lst1[1]+"|" +lst1[2]+"|" +"sshopen"+"|" +lst1[4]+"|" +lst1[5]+"|"+lst1[6]+"|" +lst1[7]+"|" +lst1[8]+"|" +lst1[9]+"|" +lst1[10]+"|" +lst1[11]+"|" +lst1[12]+"|" +lst1[13];
             }
 listToFile(liste_,"iplistname");
            pcButtonGuncelleSlot(mac,false, "",false);
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
        //if(lst[2]=="pcopen")
            ip_liste<<lst[0];
        }
    }
    listToFile(ip_liste,"ip");
 /*************************vnciplist oluşturuldu*************************************/
    mesajSlot("vnc Tarama Başlatıldı");
     QStringList arguments;
     QString  komut;
 //    echo '1'|sudo -S nmap  -n -p 5900  -iL ip | awk '/Nmap scan report/{print $5;}'
     komut.append("echo ").append(localPassword->text()).append(" | sudo -S ").append("nmap  -n -p 5900 --open ").append("-iL "+localDir+"/ip").append(" | awk '/Nmap scan report/{print $5;}'>"+localDir+"/vnciplist");
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
         liste_<<(lst[0]+"|"+lst[1]+"|" +lst[2]+"|" +lst[3]+"|" +"vncclose"+"|" +lst[5]+"|"+lst[6]+"|"+lst[7]+"|" +lst[8]+"|" +lst[9]+"|" +lst[10]+"|" +lst[11]+"|" +lst[12]+"|" +lst[13]);
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
                 liste_<<lst1[0]+"|"+lst1[1]+"|" +lst1[2]+"|" +lst1[3]+"|" +"vncopen"+"|" +lst1[5]+"|"+lst1[6]+"|" +lst1[7]+"|" +lst1[8]+"|" +lst1[9]+"|" +lst1[10]+"|" +lst1[11]+"|" +lst1[12]+"|" +lst1[13];
              }
               listToFile(liste_,"iplistname");
                          pcButtonGuncelleSlot(mac,false, "",false);

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
        //if(lst[2]=="pcopen")
            ip_liste<<lst[0];
        }
    }
    listToFile(ip_liste,"ip");
 /*************************vnciplist oluşturuldu*************************************/
    mesajSlot("ftp Tarama Başlatıldı");
     QStringList arguments;
     QString  komut;
 //    echo '1'|sudo -S nmap  -n -p 21  -iL ip | awk '/Nmap scan report/{print $5;}'
     komut.append("echo ").append(localPassword->text()).append(" | sudo -S ").append("nmap  -n -p 21 --open ").append("-iL "+localDir+"/ip").append(" | awk '/Nmap scan report/{print $5;}'>"+localDir+"/ftpiplist");
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
         liste_<<(lst[0]+"|"+lst[1]+"|" +lst[2]+"|" +lst[3]+"|" +lst[4]+"|" +"ftpclose"+"|"+lst[6]+"|"+lst[7]+"|" +lst[8]+"|" +lst[9]+"|" +lst[10]+"|" +lst[11]+"|" +lst[12]+"|" +lst[13]);
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
                 liste_<<lst1[0]+"|"+lst1[1]+"|" +lst1[2]+"|" +lst1[3]+"|" +lst1[4]+"|" +"ftpopen"+"|"+lst1[6]+"|" +lst1[7]+"|" +lst1[8]+"|" +lst1[9]+"|" +lst1[10]+"|" +lst1[11]+"|" +lst1[12]+"|" +lst1[13];
              }
               listToFile(liste_,"iplistname");
                          pcButtonGuncelleSlot(mac,false, "",false);

         }
     }
     //listToFile(liste_,"iplistname");
      /****************************************************************/
//pcListeGuncelleSlot();
}

void MainWindow::mesajSlot(QString msg)
{

    textBrowser_receivedMessages->moveCursor (QTextCursor::End);
    textBrowser_receivedMessages->insertPlainText (msg+"\n");
}

void MainWindow::macListSaveButtonSlot()
{
    QStringList iplistname=fileToList("iplistname");  //liste olşturuluyor

    for(int i=0;i<=tw->rowCount()-1;i++)
               {

                   QString pcname;
                   QString ip=tw->item(i, 0)->text();
                   QString mac=tw->item(i, 1)->text();
                   QString pcstate=tw->item(i, 2)->text();
                   QString sshstate=tw->item(i, 3)->text();
                   QString vncstate=tw->item(i, 4)->text();
                   QString ftpstate=tw->item(i, 5)->text();
                   QString connectstate=tw->item(i, 6)->text();

                   if(tw->item(i, 7)) pcname=tw->item(i, 7)->text();
                   else pcname="";

                   iplistname=listRemove(iplistname,mac); //değişecek satır siliniyor


                   QString iptaleh=tw->item(i, 8)->text();
                   QString socketid=tw->item(i, 9)->text();
                   QString linkid=tw->item(i, 10)->text();
                   QString S=tw->item(i, 11)->text();
                   QString V=tw->item(i, 12)->text();
                   QString F=tw->item(i, 13)->text();

                 iplistname<<ip+"|"+mac+"|" +pcstate+"|" +sshstate+"|" +vncstate+"|" +ftpstate+"|"+connectstate+"|"+pcname+"|"+iptaleh+"|"+socketid+"|"+linkid+"|"+S+"|"+V+"|"+F;
                 listToFile(iplistname,"iplistname");

                 QStringList persistlist=fileToList("persistlist");
                 persistlist=listRemove(persistlist,mac); //değişecek satır siliniyor
                 persistlist<<ip+"|"+mac+"|" +pcstate+"|" +sshstate+"|" +vncstate+"|" +ftpstate+"|"+connectstate+"|"+pcname+"|"+iptaleh+"|"+socketid+"|"+linkid+"|"+S+"|"+V+"|"+F;
                 listToFile(persistlist,"persistlist");


    }


    //qDebug()<<"Mac Listesi Kaydedildi!";
   mesajSlot("Mac Listesi Kaydedildi!");
}

void MainWindow::macListButtonSlot()
{

    macListSaveButton->show();
    lst->hide();
    tw->show();
    QStringList list=fileToList("iplistname");

    tw->setRowCount(0);
    for(int i=0;i<list.count();i++)
     {
        QString line=list[i];
        QStringList lst=line.split("|");
        tw->setRowCount(tw->rowCount()+1);
   //  tw->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
     tw->setItem(i, 0, new QTableWidgetItem(lst[0]));//ip
     tw->setItem(i, 1, new QTableWidgetItem(lst[1]));//mac
     tw->setItem(i, 2, new QTableWidgetItem(lst[2]));//pcstate
     tw->setItem(i, 3, new QTableWidgetItem(lst[3]));//sshstate
     tw->setItem(i, 4, new QTableWidgetItem(lst[4]));//vncstate
     tw->setItem(i, 5, new QTableWidgetItem(lst[5]));//ftpstate
     tw->setItem(i, 6, new QTableWidgetItem(lst[6]));//connectstate
     tw->setItem(i, 7, new QTableWidgetItem(lst[7]));//pcname
     tw->setItem(i, 8, new QTableWidgetItem(lst[8]));//iptal(e/h)
     tw->setItem(i, 9, new QTableWidgetItem(lst[9]));//Socketid
     tw->setItem(i, 10, new QTableWidgetItem(lst[10]));//linkip
     tw->setItem(i, 11, new QTableWidgetItem(lst[11]));//Ssh-S
     tw->setItem(i, 12, new QTableWidgetItem(lst[12]));//VNC-V
     tw->setItem(i, 13, new QTableWidgetItem(lst[13]));//Ftp-F

    }
    //qDebug()<<"Mac Listelendi";
    mesajSlot("Mac Adresleri Listelendi.");
}

void MainWindow::ftpConnectButtonSlot()
{

textBrowser_receivedMessages->clear();

    QStringList arguments;
    QString  komut;
    komut.append("nohup dolphin fish://").append(remoteUsername->text()+":").append(remotePassword->text()).append("@"+pcIp->text()+" &");
  // qDebug()<<komut;
     arguments << "-c" << komut;
    QProcess process;
    process.start("/bin/bash",arguments);
    process.waitForFinished(-1); // will wait forever until finished

}
void MainWindow::createTable()
{
    tw=new QTableWidget(this);
    tw->resize(en*180,this->height()-boy*71);
    tw->move(0,boy*40);

    tw->setColumnCount(14);
    tw->setRowCount(0);
   // tw->setColumnWidth(0, 40);
    tw->setColumnWidth(0, 100);
    tw->setColumnWidth(1, 115);
    tw->setColumnWidth(2, 60);
    tw->setColumnWidth(3, 60);
    tw->setColumnWidth(4, 60);
    tw->setColumnWidth(5, 60);
    tw->setColumnWidth(6, 45);
    tw->setColumnWidth(7, 100);
    tw->setColumnWidth(8, 5);
    tw->setColumnWidth(9, 77);
    tw->setColumnWidth(10, 80);
    tw->setColumnWidth(11, 5);
    tw->setColumnWidth(12, 5);
    tw->setColumnWidth(13, 5);

   //  tw->setHorizontalHeaderItem(0, new QTableWidgetItem("Sıra"));
    tw->setHorizontalHeaderItem(0, new QTableWidgetItem("İp Adres"));
    tw->setHorizontalHeaderItem(1, new QTableWidgetItem("Mac Adres"));
    tw->setHorizontalHeaderItem(2, new QTableWidgetItem("Durum"));
    tw->setHorizontalHeaderItem(3, new QTableWidgetItem("Ssh"));
    tw->setHorizontalHeaderItem(4, new QTableWidgetItem("Vnc"));
    tw->setHorizontalHeaderItem(5, new QTableWidgetItem("Ftp"));
    tw->setHorizontalHeaderItem(6, new QTableWidgetItem("Link"));
    tw->setHorizontalHeaderItem(7, new QTableWidgetItem("Pc Adı"));
    tw->setHorizontalHeaderItem(8, new QTableWidgetItem("L"));
    tw->setHorizontalHeaderItem(9, new QTableWidgetItem("SocketId"));
    tw->setHorizontalHeaderItem(10, new QTableWidgetItem("linkId"));
    tw->setHorizontalHeaderItem(11, new QTableWidgetItem("S"));
    tw->setHorizontalHeaderItem(12, new QTableWidgetItem("V"));
    tw->setHorizontalHeaderItem(13, new QTableWidgetItem("F"));

    QFont fn( "Arial", 9, QFont::Normal);
    tw->setFont(fn);


    //tw->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    //connect( tw, SIGNAL( cellPressed(int, int)), this, SLOT( changeLocalSongData( int, int )));
    tw->setSelectionBehavior(QAbstractItemView::SelectRows);
    tw->setSelectionMode(QAbstractItemView::SingleSelection);
    //connect(tw, &QTableWidget::cellClicked, this, cellClicked());
    connect(tw, SIGNAL(cellDoubleClicked(int,int)),SLOT(cellDoubleClicked(int,int)));



}
void MainWindow::cellDoubleClicked(int iRow, int iColumn)
{
     QString mac= tw->item(iRow, 2)->text();
     QStringList list=fileToList("iplistname");
/******************************************************************/
    //QMessageBox::StandardButton reply;
    // reply = QMessageBox::question(this, "Uyarı", "Bilgisayar Silinecek! Emin misiniz?",
      //                             QMessageBox::Yes|tr(QMessageBox::No);
      QMessageBox messageBox(this);
      messageBox.setText("Uyarı");
      messageBox.setInformativeText("Host İçin İşlem Seçiniz!");
      QAbstractButton *evetButton =messageBox.addButton(tr("Sil"), QMessageBox::ActionRole);
      QAbstractButton *hayirButton =messageBox.addButton(tr("Düzenle"), QMessageBox::ActionRole);
      messageBox.setIcon(QMessageBox::Question);
              messageBox.exec();
              if (messageBox.clickedButton() == evetButton) {
                 // qDebug()<<"evet basıldı";
                  list=listRemove(list,mac);
                  listToFile(list,"iplistname");
                  mesajSlot("Bilgisayar Listeden Silindi!");
                  macListButtonSlot();

              }
              if (messageBox.clickedButton() == hayirButton) {
                  //qDebug()<<"hayır basıldı";
              }


}
MainWindow::~MainWindow()
{
    FileCrud *fc=new FileCrud();
    fc->dosya=localDir+"click";
    if(fc->fileExists()) fc->fileRemove();

    foreach (QTcpSocket* socket, connection_list)
    {
        socket->close();
        socket->deleteLater();
    }

    m_server->close();
    m_server->deleteLater();

    //delete ui;
}
QStringList MainWindow::listRemove(QStringList list,QString data)
 {
    // qDebug()<<"deneme-ddd"<<data;
    // QStringList list;
     //  qDebug()<<list;
     QRegularExpression re(data);
     for(int i=0;i<list.count();i++)if(list[i].contains(re)) list.removeAt(i);
    // qDebug()<<list;
     return list;
 }
QString MainWindow::listGetLine(QStringList list,QString data)
 {
     //QStringList list;
     //list << "bayram|sun" << "cloud" << "sun|" << "|rain";
     QRegularExpression re(data);
     for(int i=0;i<list.count();i++) if(list[i].contains(re)) return list[i];
     //qDebug()<<list;
     return "";
 }
QStringList MainWindow::fileToList(QString filename)
 {
    FileCrud *fcc=new FileCrud();
    fcc->dosya=localDir+filename;
    QStringList list;
    for(int i=1;i<=fcc->fileCount();i++)
    {
         QString line=fcc->fileGetLine(i);
         if(line!="")
         {
             line.chop(1);
             QStringList lst=line.split("|");
             QString ln="";
             if(lst.count()>0)ln.append(lst[0]);
             if(lst.count()>1)ln.append("|").append(lst[1]);
             if(lst.count()>2)ln.append("|").append(lst[2]);
             if(lst.count()>3)ln.append("|").append(lst[3]);
             if(lst.count()>4)ln.append("|").append(lst[4]);
             if(lst.count()>5)ln.append("|").append(lst[5]);
             if(lst.count()>6)ln.append("|").append(lst[6]);
             if(lst.count()>7)ln.append("|").append(lst[7]);
             if(lst.count()>8)ln.append("|").append(lst[8]);
             if(lst.count()>9)ln.append("|").append(lst[9]);
             if(lst.count()>10)ln.append("|").append(lst[10]);
             if(lst.count()>11)ln.append("|").append(lst[11]);
             if(lst.count()>12)ln.append("|").append(lst[12]);
             if(lst.count()>13)ln.append("|").append(lst[13]);

             list <<ln;
            // qDebug()<<ln;
             // list <<lst[0]+"|"+lst[1]+"|"+lst[2]+"|"+lst[3]+"|"+lst[4]+"|"+lst[5];

         }
    }
       return list;
 }
void MainWindow::listToFile(QStringList list, QString filename)
 {
    FileCrud *fcc=new FileCrud();
    fcc->dosya=localDir+filename;
    fcc->fileRemove();
    for(int i=0;i<list.count();i++)
    {
         QString line=list[i];
         if(line!="")
         {
             //line.chop(1);
             QStringList lst=line.split("|");
             //qDebug()<<line;
             QString ln="";
             if(lst.count()>0)ln.append(lst[0]);
             if(lst.count()>1)ln.append("|").append(lst[1]);
             if(lst.count()>2)ln.append("|").append(lst[2]);
             if(lst.count()>3)ln.append("|").append(lst[3]);
             if(lst.count()>4)ln.append("|").append(lst[4]);
             if(lst.count()>5)ln.append("|").append(lst[5]);
             if(lst.count()>6)ln.append("|").append(lst[6]);
             if(lst.count()>7)ln.append("|").append(lst[7]);
             if(lst.count()>8)ln.append("|").append(lst[8]);
             if(lst.count()>9)ln.append("|").append(lst[9]);
             if(lst.count()>10)ln.append("|").append(lst[10]);
             if(lst.count()>11)ln.append("|").append(lst[11]);
             if(lst.count()>12)ln.append("|").append(lst[12]);
             if(lst.count()>13)ln.append("|").append(lst[13]);

             //qDebug()<<ln;
             fcc->fileWrite(ln);

         }

    }
 }
void MainWindow::enableButton()
{
//sendMessageButton->setEnabled(!username->text().isEmpty()&&!password->text().isEmpty());
//sendMessageAllButton->setEnabled(!password->text().isEmpty()&&!username->text().isEmpty());
tcpekranImageButton->setEnabled(!remoteUsername->text().isEmpty()&&!remotePassword->text().isEmpty());
tcpekranKilitButton->setEnabled(!remoteUsername->text().isEmpty()&&!remotePassword->text().isEmpty());
tcpduyuruMesajButton->setEnabled(!remoteUsername->text().isEmpty()&&!remotePassword->text().isEmpty());
tcppcKapatButton->setEnabled(!remoteUsername->text().isEmpty()&&!remotePassword->text().isEmpty());
tcpcommandsendMessageButton->setEnabled(!remoteUsername->text().isEmpty()&&!remotePassword->text().isEmpty());
commandExecuteButton->setEnabled(!lineEdit_message->text().isEmpty()&&!remoteUsername->text().isEmpty()&&!remotePassword->text().isEmpty());
commandExecuteAllButton->setEnabled(!lineEdit_message->text().isEmpty()&&!remoteUsername->text().isEmpty()&&!remotePassword->text().isEmpty());
fileCopyButton->setEnabled(!lineEdit_message->text().isEmpty()&&!remoteUsername->text().isEmpty()&&!remotePassword->text().isEmpty());
fileCopyAllButton->setEnabled(!lineEdit_message->text().isEmpty()&&!remoteUsername->text().isEmpty()&&!remotePassword->text().isEmpty());
fileSelectButton->setEnabled(!remoteUsername->text().isEmpty()&&!remotePassword->text().isEmpty());
}
void MainWindow::barStatusSlot()
{
     bar->setValue(barValue++);
 }
void MainWindow::fileSelectSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Dosya Seç"),"/home/etapadmin/", tr("Files (*.*)"));
//qDebug()<<fileName;
    lineEdit_message->setText(fileName);

}
void MainWindow::fileCopySlot()
{
    sshAramaButtonSlot();
    // textBrowser_receivedMessages->clear();
    //sshpass -p $parola scp $dosya $username@$name:/home/$username/
    //sshpass -p 1 scp -o StrictHostKeyChecking=no /home/etapadmin/ipa etapadmin@192.168.1.111:/home/etapadmin/
    QString komut="sshpass -p "+remotePassword->text()+" scp -o StrictHostKeyChecking=no "+lineEdit_message->text()+" "+
            remoteUsername->text()+"@"+pcIp->text()+":\/home\/"+remoteUsername->text()+"\/";

    //qDebug()<<komut;
       mesajSlot(komut);
    QStringList arguments;
    //QString  komut;
    //komut.append("vncviewer ").append(pcIp->text()).append(" \-passwd \/usr\/bin\/x11vncpasswd");
    arguments << "-c" << komut;
    QProcess process;
    process.start("/bin/bash",arguments);
    process.waitForFinished(-1); // will wait forever until finished
mesajSlot("Dosya Kopyalandı");
}
void MainWindow::fileCopyAllSlot()
{
    sshAramaButtonSlot();
    // textBrowser_receivedMessages->clear();
  //  qDebug()<<"Komut Ağ'da Çalıştırıldı";
    mesajSlot("Komut Ağ'da Çalıştırıldı");
    QStringList liste=fileToList("iplistname");

/*********************************************************/

   for(int i=0;i<liste.count();i++)
   {
       QString line=liste[i];
       line.chop(1);
       QStringList lst=line.split("|");

      // qDebug()<<lst[0]<<lst[3];
                if (lst[3]=="sshopen")//sshstate
                    {
                    //sshpass -p $parola scp $dosya $username@$name:/home/$username/
                      QString komut="sshpass -p "+remotePassword->text()+" scp -o StrictHostKeyChecking=no "+lineEdit_message->text()+" "+
                            remoteUsername->text()+"@"+lst[0]+":\/home\/"+remoteUsername->text()+"\/";
             //         sshpass -p 1299+1923tr  scp -o StrictHostKeyChecking=no iplistname etapadmin@10.107.248.247:/usr/share/E-Ag/

                    qDebug()<<komut;
                    QStringList arguments;
                    //QString  komut;
                    //komut.append("vncviewer ").append(pcIp->text()).append(" \-passwd \/usr\/bin\/x11vncpasswd");
                    arguments << "-c" << komut;
                    QProcess process;
                    process.start("/bin/bash",arguments);
                    process.waitForFinished(-1); // will wait forever until finished

                    }

     }

        //qDebug()<<"Dosya Ağ'da Bütün Pc'lere Kopyalandı";
mesajSlot("Dosya Ağ'da Bütün Pc'lere Kopyalandı");
}
void MainWindow::fileHostportCopyAllSlot()
{

      mesajSlot("Hostport Ağ'da Dağıtıldı");
    QStringList liste=fileToList("iplistname");

/*********************************************************/

   for(int i=0;i<liste.count();i++)
   {
       QString line=liste[i];
       line.chop(1);
       QStringList lst=line.split("|");

      // qDebug()<<lst[0]<<lst[3];
                if (lst[3]=="sshopen")//sshstate
                    {
                    //sshpass -p $parola scp $dosya $username@$name:/home/$username/
                      QString komut="nohup sshpass -p "+remotePassword->text()+" scp -o StrictHostKeyChecking=no "+localDir+"hostport "+
                            remoteUsername->text()+"@"+lst[0]+":/usr/share/E-Ag/&";

             //         sshpass -p 1299+1923tr  scp -o StrictHostKeyChecking=no iplistname etapadmin@10.107.248.247:/usr/share/E-Ag/

                    qDebug()<<komut;
                    QStringList arguments;
                    //QString  komut;
                    //komut.append("vncviewer ").append(pcIp->text()).append(" \-passwd \/usr\/bin\/x11vncpasswd");
                    arguments << "-c" << komut;
                    QProcess process;
                    process.start("/bin/bash",arguments);
                    process.waitForFinished(-1); // will wait forever until finished

                    }
              /*  if (lst[3]=="sshopen")//sshstate
                    {
                    //sshpass -p $parola scp $dosya $username@$name:/home/$username/
                    QString komut="sshpass -p "+remotePassword->text()+" ssh -o StrictHostKeyChecking=no -n "+
                            remoteUsername->text()+"@"+lst[0]+" 'echo "+remotePassword->text()+" | sudo -S' chmod 777 /usr/share/E-Ag/* &";
              //sshpass -p 1299+1923tr ssh -o StrictHostKeyChecking=no -n etapadmin@10.107.248.241 'echo 1299+1923tr | sudo -S' mkdir /usr/share/E-Ag/deneme
                     qDebug()<<komut;
                    QStringList arguments;
                    //QString  komut;
                    //komut.append("vncviewer ").append(pcIp->text()).append(" \-passwd \/usr\/bin\/x11vncpasswd");
                    arguments << "-c" << komut;
                    QProcess process;
                    process.start("/bin/bash",arguments);
                    process.waitForFinished(-1); // will wait forever until finished

                    }


              */


     }
  // sshCommandAllSlot("rm /usr/share/E-Ag/E-AgClientOk");
       //  system("sleep 2");
        //sshCommandAllSlot("killall Client");
         //system("sleep 2");
        // sshCommandAllSlot("Client");

        //qDebug()<<"Dosya Ağ'da Bütün Pc'lere Kopyalandı";
mesajSlot("Dosya Ağ'da Bütün Pc'lere Kopyalandı");
}
void MainWindow::sshCommandSlot(QString kmt)
{

   // textBrowser_receivedMessages->clear();
    //sshpass -p $parola ssh -o StrictHostKeyChecking=no -n $username@$name "echo $parola | sudo -S" $komut
QString komut="nohup sshpass -p "+remotePassword->text()+" ssh -o StrictHostKeyChecking=no -n "+
        remoteUsername->text()+"@"+pcIp->text()+" 'echo "+remotePassword->text()+" | sudo -S' "+kmt+" &";

mesajSlot(komut);
//qDebug()<<komut;
QStringList arguments;
//QString  komut;
//komut.append("vncviewer ").append(pcIp->text()).append(" \-passwd \/usr\/bin\/x11vncpasswd");
arguments << "-c" << komut;
QProcess process;
process.start("/bin/bash",arguments);
process.waitForFinished(-1); // will wait forever until finished



}
void MainWindow::sshCommandAllSlot(QString kmt)
{
 sshAramaButtonSlot();
/*********************************************************/
    QStringList liste=fileToList("iplistname");
   for(int i=0;i<liste.count();i++)
   {
       QString line=liste[i];
       line.chop(1);
       QStringList lst=line.split("|");

                 if (lst[3]=="sshopen")//sshstate
                    {

                     QString komut="nohup sshpass -p "+remotePassword->text()+" ssh -X -o StrictHostKeyChecking=no -n "+
                             remoteUsername->text()+"@"+lst[0]+" 'echo "+remotePassword->text()+" | sudo -S' "+kmt+" &";
                     mesajSlot(komut);
                    // qDebug()<<komut;
                     QStringList arguments;
                     arguments << "-c" << komut;
                     QProcess process;
                     process.start("/bin/bash",arguments);
                     process.waitForFinished(-1); // will wait forever until finished

                   // system(komut.toStdString().c_str());
                    }

     }

}
void MainWindow::commandExecuteAllSlot()
{
    sshAramaButtonSlot();
    sshCommandAllSlot(lineEdit_message->text());
    lineEdit_message->setText("");
    mesajSlot("Komut Ağ'da Çalıştırıldı");

}
void MainWindow::commandExecuteSlot()
{
    sshAramaButtonSlot();
    sshCommandSlot(lineEdit_message->text());
    lineEdit_message->setText("");
    mesajSlot("Komut Çalıştırıldı");

}



