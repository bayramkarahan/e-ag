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
#include<QDataStream>
#include<menu.h>
#include<butonclick.h>
#include <QScrollArea>
#include<QApplication>
#include<QDesktopWidget>
#include<QtWidgets>
#include<tcpudp.h>
#include<init.h>
#include<funtion.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{


    /*****************************************************/
    QSize screenSize = qApp->screens()[0]->size();
    boy=screenSize.height()/153.6;
    en=boy*1.1;
    int e=en;
    int b=boy;
    this->resize(boy*180,en*105);
    int x = (screenSize.width() - this->width())/2;
    int y = (screenSize.height() - this->height()) / 2;
    this->move(x, y);
   // qDebug()<<"aşama1";

    mainWidget=new QWidget();
    localDir="/usr/share/e-ag/";
    hostAddressMacButtonSlot();



    rb1=new QRadioButton();
    rb2=new QRadioButton();

    acountLoad();///hesap ve ayarların yüklenmesi yapılıyor...
//setMouseTracking(true);
//installEventFilter(this);
    setWindowTitle("e-ag");

    auto appIcon = QIcon(":/icons/e-ag.svg");
    this->setWindowIcon(appIcon);

   /************************************************************/
    pcMac=new QLabel();
    pcName=new QLabel();
    pcIp=new QLabel();
    statusbar=new QStatusBar(this);
    statusbar->showMessage(tr("..."));
    statusbar->setStyleSheet("font-size:"+QString::number(font.toInt()-4)+"px;");
    //qDebug()<<"aşama0";
      /************************************************************/
    hostListe=new QWidget();
    hostListe->setFixedSize(e*178,b*56);
    hostListe->setObjectName("pclistewidget");
   /// hostListe->setStyleSheet("background-color: #aaaadd");
   // qDebug()<<"aşama2";
    scrollArea=new QScrollArea();
    scrollArea->setWidget(hostListe);
    scrollArea->setFixedSize(e*180,b*56);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
   /// scrollArea->setStyleSheet("background-color: #ff5533");

   /// hostListe->hide();
    layout = new QGridLayout();
    layout->setContentsMargins(0, 0, 0,0);
    layout->setSpacing(3);
    hostListe->setLayout(layout);

   // qDebug()<<"aşama5";
    /*********************************************************************/
    selectPc();
// qDebug()<<"aşama51";
    /********************************************************************/
    textBrowser_receivedMessages=new QPlainTextEdit();
    textBrowser_receivedMessages->hide();
    textBrowser_receivedMessages->resize(this->width(),b*24-2);
    textBrowser_receivedMessages->setStyleSheet("background-color: #a3a3a3");
   /***********************************************************************/
    tabwid=new QTabWidget();
    tabwid->setFixedSize(this->width(),boy*24);
    tabwid->addTab(pcInfo(),QIcon(":/icons/toolbox.svg"),"Temel İşlemler");
    tabwid->addTab(rdpWidget(),QIcon(":/icons/vnc.svg"),"Ekran Paylaşımı");
    tabwid->addTab(sshCommandWidget(),QIcon(":/icons/ssh.svg"),"Komut Çalıştır");
    tabwid->addTab(duyuruWidget(),QIcon(":/icons/message.svg"),"Mesaj Yaz");
    tabwid->addTab(sshScpWidget(),QIcon(":/icons/filecopy.svg"),"Dosya Kopyala");
    tabwid->addTab(videoWidget(),QIcon(":/icons/camera.svg"),"Video/Kamera");
    tabwid->addTab(ayarlarWidget(),QIcon(":/icons/settings.svg"),"Ayarlar");
    tabwid->addTab(textBrowser_receivedMessages,QIcon(":/icons/log.svg"),"İşlem Raporu");
    tabwid->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    tabwid->setTabPosition(QTabWidget::North);
    /***********************************************************************/
//qDebug()<<"aşama52";
    /*****************************************************/
      /******************************************/
    ekranScale = new QComboBox();
    ekranScale->setFixedSize(en*2,boy);
    ekranScale->setFrame(true);
    ekranScale->setStyleSheet("background-color: #dcdcdc; font-size:"+QString::number(font.toInt()-4)+"px;");
    ekranScale->addItem("800x600");
    ekranScale->addItem("1024x768");
    ekranScale->addItem("1280x1024");
    ekranScale->addItem("1366x768");
    ekranScale->setCurrentIndex(3);
    /*********************************************************************/
    timerUdpSocketSend = new QTimer(this);
    newPcDetectTimer= new QTimer(this);
    connect(newPcDetectTimer, SIGNAL(timeout()), this, SLOT(newPcDetect()));
    newPcDetectTimer->start(5000);
    connect(timerUdpSocketSend, SIGNAL(timeout()), this, SLOT(sendBroadcastDatagram()));
    timerUdpSocketSend->start(10000);

    /********************* Broadcast Message yollanıyor *****************************************/
    udpSocketSend = new QUdpSocket(this);
    udpSocketGet = new QUdpSocket();
    udpSocketGet->bind(tcpPort.toInt(), QUdpSocket::ShareAddress);
    QObject::connect(udpSocketGet,&QUdpSocket::readyRead,[&](){udpSocketServerRead();});
    /*********************************************************/

   ///qDebug()<<"aşama6";
/******************************************************************/

   /****************************************************************/
 QGridLayout* layoutMain = new QGridLayout(mainWidget);
 layoutMain->setContentsMargins(0, 0, 0,0);
 layoutMain->setVerticalSpacing(0);
 layoutMain->setHorizontalSpacing(0);
 layoutMain->addWidget(tabwid, 0,0,1,1);
 //layoutMain->addWidget(toolBar, 3,0,1,1);

 layoutMain->addWidget(selectWidget, 4,0,1,1);
 layoutMain->addWidget(scrollArea, 6,0,1,1);
 layoutMain->addWidget(statusbar,7,0,1,1);

setMinimumSize(width(),height());
mainWidget->setLayout(layoutMain);
this->setCentralWidget(mainWidget);


statusbar->addPermanentWidget(sliderWidget(),0);

/*************************************************************************/
 hostListe->show();

pcListeSlot();

 if(btnlist.count()>0)
{
btnlist[btnlist.count()-1]->slotMouseClick();

pcClickSlot(btnlist[btnlist.count()-1]->mac);
}
/*************************************************************************/

 }

 void MainWindow::pcListeSlot()
 {

    double nwidth=en*13*slider->value()/100;
    double nheight=en*15*slider->value()/100;
    int columnSayisi=hostListe->width()/(nwidth+en*4);
    pcListeGuncelleSlot(columnSayisi,nwidth,nheight);

    qDebug()<<"Liste Yenilendi.......";


   /// sshAramaButtonSlot();
    if(selectMac=="")selectMac=pcMac->text();

    pcClickSlot(selectMac);


}

 void MainWindow::mouseMoveEvent(QMouseEvent *event)
 {
      if(mouseClickState)
     {
         if (Pc *w =(Pc*) qApp->widgetAt(QCursor::pos())) {
              if(w->objectName()=="btnpc"||w->objectName()=="iconLabel"||w->objectName()=="selectLabel")
             {
               // qDebug()<<"pc seçildi"<<w->parentWidget();
                Pc* pc= dynamic_cast<Pc*>(w->parentWidget());
               pc->slotSelectPc();
            }
         }


     }
 }
 void MainWindow::mouseReleaseEvent(QMouseEvent *event)
 {
   // slotMouseDoubleClick();
      qDebug()<<"release";
     mouseClickState=false;
 }
 void MainWindow::mousePressEvent(QMouseEvent *event)
 {
   // slotMouseDoubleClick();
      qDebug()<<"press";
      mouseClickState=true;
      if (auto *w =qApp->widgetAt(QCursor::pos())) {
        //  if(w->objectName()=="btnpc"||w->objectName()=="iconLabel"||w->objectName()=="selectLabel")
        // {
          if(w->objectName()=="qt_scrollarea_viewport"||
                  w->objectName()=="pclistewidget"||
                  w->objectName()=="btnpc"||
                  w->objectName()=="iconLabel"||
                  w->objectName()=="selectLabel")
          {
            /// qDebug()<<"pc seçildi"<<w->objectName();
              for(int i=0;i<btnlist.count();i++)
                   {
                      // btnlist[i]->select=!(btnlist[i]->select);
                     //  btnlist[i]->slotUnselectPc();

                    }
         }
      }

 }
 void MainWindow::resizeEvent(QResizeEvent *event)
 {
    // this->resize(sizeHint());
 qDebug()<<"main boyut değişti";
 selectWidget->setFixedSize(this->width(),selectWidget->height());
// ustMenuWidget->setFixedSize(this->width(),ustMenuWidget->height());
 textBrowser_receivedMessages->setFixedSize(this->width(),boy*19-2);
 tabwid->setFixedSize(this->width(),boy*22);
 hostListe->setFixedSize(this->width()-en*3.5,this->height()-tabwid->height()-selectWidget->height()-boy);
 scrollArea->setFixedSize(this->width(),this->height()-tabwid->height()-selectWidget->height());
 ///QWidget::resizeEvent(event);
 }


 void MainWindow::pcListeGuncelleSlot(int _ColumnSayisi,int pcw,int pch)
{
    qDebug()<<"Hosts Listesi Güncellendi..";
    hostListReset();
    layoutTemizle();

   QStringList mactoiplist=arpListInit();
   ///iptal listToFile(mactoiplist,"iplistname");
    PcData::onlinePcListe=mactoiplist;

       /*****************************************************/
    QStringList list;
   ////iptal QStringList list_=fileToList("iplistname");
    QStringList list_=PcData::onlinePcListe;

    gercekliste=0;pcopencount=0;
    for(int i=0;i<list_.count();i++)
     {
        //qDebug()<<list_[i];
        QString line=list_[i];
        if(line!="")
        {
        QStringList lst=line.split("|");
        if(lst[2]=="pcopen") {
            pcopencount++;

        }

        if(lst[8]=="e"&&lst[2]=="pcopen") {
            gercekliste++;
            list<<line;
        }
        }
    }

    int hsize=gercekliste;
    hostsCountLabel->setText("Açık Hosts : "+QString::number(gercekliste));

   // qDebug()<<"pc sayısı:"<<hsize<<slider->value();
    //if(hsize<=40)
    double nlstheight=(en*(gercekliste/_ColumnSayisi+1)*13.8)*slider->value()/100;
    hostListe->setFixedSize(hostListe->width(),nlstheight);
 /****************************************************/
      list=listSort(list,7);//pcname göre sıralama

    // qSort(list.begin(), list.end());
        /*********************************************************/
   int sira=0;

    sira=gercekliste;
    int satir=sira/_ColumnSayisi;
    int mod=sira%_ColumnSayisi;
    if (mod!=0) satir++;
    int sutun=_ColumnSayisi;
    int sn=0;
   // lst->resize(en*180,(satir+1)*boy*20);

     for(int i=1;i<=satir;i++)
     {
         for(int j=1;j<=_ColumnSayisi;j++)
         {
             QString line=list[sn];
              //line.chop(1);
            /// if(line!="")
            /// {
                 QStringList ls=line.split("|");
                 //QWidget *cpc=createPc(ls[5],ls[1],ls[2],ls[3],ls[4],ls[6],80,80,false,"");
                // qDebug()<<"Gösterim Durumu:"<<ls[7];

              if(ls[8]=="e"&&ls[2]=="pcopen")
                 {
                 /***************************************************************/
                     Pc *tempPc=new Pc();
                     bool oldhave=false;
                     for(int p=0;p<tempbtnlist.count();p++)
                     {
                         if(tempbtnlist[p]->mac==ls[1])
                         {
                             //qDebug()<<"bulunan pc:"<<tempbtnlist[p]->mac;
                             tempPc=tempbtnlist[p];
                             oldhave=true;
                         }
                     }
                 /****************************************************************/

                    Pc *cpc=new Pc();
                   // cpc->onlinePcListe=this->onlinePcListe;

                   //cpc->installEventFilter(this);///************
                   // cpc->setMouseTracking(true);
                    cpc->setSshConnect(false);
                    cpc->setVncConnect(false);
                    cpc->vncport="0";
                    cpc->setFtpConnect(false);
                    cpc->setUser("noLogin");
                    cpc->pcname=ls[7];
                    cpc->lss=ls[8];
                    cpc->ip=ls[0];
                    connect(cpc, SIGNAL(pcClickSignal(QString)),
                            this, SLOT(pcClickSlot(QString)));

                    connect(cpc, SIGNAL(pcListeSignal()),
                            this, SLOT(pcListeSlot()));

                    connect(cpc, SIGNAL(pcTcpPortControlSignal(QString,QString)),
                            this, SLOT(pcTcpPortControlSignalSlot(QString,QString)));

                    connect(cpc, SIGNAL(pcSshPortControlSignal(QString,QString)),
                            this, SLOT(pcSshPortControlSignalSlot(QString,QString)));

                    connect(cpc, SIGNAL(pcVncPortControlSignal(QString,QString)),
                            this, SLOT(pcVncPortControlSignalSlot(QString,QString)));

                    connect(cpc, SIGNAL(pcFtpPortControlSignal(QString,QString)),
                            this, SLOT(pcFtpPortControlSignalSlot(QString,QString)));

                    connect(cpc, SIGNAL(pcKilitStateControlSignal(QString,QString,bool)),
                            this, SLOT(pcKilitStateControlSignalSlot(QString,QString,bool)));

                    connect(cpc, SIGNAL(pcKilitTransparanStateControlSignal(QString,QString,bool)),
                            this, SLOT(pcKilitTransparanStateControlSignalSlot(QString,QString,bool)));

                    connect(cpc, SIGNAL(pcIconStateControlSignal(QString,QString,bool)),
                            this, SLOT(pcIconStateControlSignalSlot(QString,QString,bool)));

                    connect(cpc, SIGNAL(pcMenuSignal(QString,QString,QString)),
                            this, SLOT(pcMenuSignalSlot(QString,QString,QString)));

                    connect(cpc, SIGNAL(pcListeStateSignal()),
                            this, SLOT(pcListeStateSlot()));

                     cpc->setAcount(remoteUserName,remotePassword);

                   //  cpc->setMac(ls[1],en*13,en*15,font);
                     cpc->setMac(ls[1],pcw,pch,font);

                    /**************************************************************/
                     cpc->setPcState(true);
                     if(oldhave)
                     {
                         if(tempPc->select)
                         {
                             //qDebug()<<"Seçilen olan mac:"<<tempPc->mac;
                             selectMac=tempPc->mac;
                             cpc->select=tempPc->select;
                             cpc->slotMouseClick();

                         }
                         if(tempPc->multiSelect)cpc->slotMouseDoubleClick();

                         if(tempPc->ss=="sshopen")cpc->setSshConnect(true);
                         else cpc->setSshConnect(false);
                         if(tempPc->vs=="vncopen")cpc->setVncConnect(true);
                         else cpc->setVncConnect(false);
                         if(tempPc->fs=="ftpopen")cpc->setFtpConnect(true);
                         else cpc->setFtpConnect(false);

                         if(tempPc->cs=="online"){

                             cpc->setTcpConnect(true);}

                         if(tempPc->kilitControlState) cpc->setKilitControlState(true);

                         if(tempPc->transparanKilitControlState)cpc->setKilitTransparanControlState(true);

                         if(tempPc->iconControlState)cpc->setIconControlState(true);
                         cpc->setUser(tempPc->user);
                         cpc->setDisplay(tempPc->display);

                     }
                      oldhave=false;
                     /*************************************************************/



                     layout->addWidget(cpc, i,j,1,1);
                     // cpc->setCaption("deneme");

                     //cpc->setFixedSize(en*15,boy*14);
                    // cpc->setObjectName("buyukKutu");

                             btnlist.append(cpc);
                           }
                 sn++;
                 if (sira==sn) break;
            /// }
         }
     }

     mesajSlot("Bilgisayarlar Listelendi!");
}
void MainWindow::pcListeStateSlot()
{

     pcListeSlot();
}
void MainWindow::newPcDetect()
{
    if(remoteUserName==""||remotePassword==""||
            localUserName==""||localPassword=="") return;

    /*************hiç olmayan hostun bulunması için gerekli bölüm..*********/
   /// qDebug()<<"olmayan hostlar bulunacak";
   ///iptal system("cat /proc/net/arp |awk '$3==\"0x2\" {print $1\"|\"$4}'>/usr/share/e-ag/pcarplist");
   ///iptal QStringList arpList=fileToList("pcarplist",localDir);
   QStringList arpList=readArp();
   ///iptal QStringList arpListTemp=fileToList("pcarplist",localDir);
   QStringList arpListTemp=readArp();

   ///iptal  QStringList iplist=fileToList("iplistname");

    QStringList iplist=PcData::onlinePcListe;

    /*************tekrar eden mac adresleri düzenleniyor***************/
        for(int i=0;i<arpListTemp.count();i++)
        {
            for(int j=0;j<arpList.count();j++)
            {
                if(arpListTemp[i].split("|")[1]==arpList[j].split("|")[1])
                {
                     arpList=listRemove(arpList,arpList[j].split("|")[1]);
                    arpList<<arpListTemp[i];
                }
            }

        }
    /******************************************************************/

///qDebug()<<"arp sayısı:"<<arpList.count()<<"btnlist sayısı:"<<pcopencount;
if(arpList.count()<pcopencount)
{
      qDebug()<<"host kapatıldı.";
pcListeSlot();//Yenileme butonu çalışacak
return;
}
if(arpList.count()>pcopencount)
{
qDebug()<<"host açıldı.";
pcListeSlot();//Yenileme butonu çalışacak
return;
}

}
void MainWindow::pcTcpPortControlSignalSlot(QString _mac,QString _ip)
{

     udpSendData("tcpporttest","",_ip);

 for(int i=0;i<btnlist.count();i++)
 {
     if(_mac.toLower()==btnlist[i]->mac.toLower()){
        btnlist[i]->tcpConnectCounter++;
      }
 }
//qDebug()<<"send tcp:"<<_mac<<_ip;
}
void MainWindow::pcSshPortControlSignalSlot(QString _mac,QString _ip)
{
      udpSendData("sshporttest","",_ip);
}
void MainWindow::pcVncPortControlSignalSlot(QString _mac,QString _ip)
{
   udpSendData("vncporttest","",_ip);
}
void MainWindow::pcFtpPortControlSignalSlot(QString _mac,QString _ip)
{
   udpSendData("ftpporttest","",_ip);
}
void MainWindow::pcKilitStateControlSignalSlot(QString _mac,QString _ip,bool kilitstate)
{
  if (kilitstate)
   udpSendData("kilitstatetrue","",_ip);
  else
   udpSendData("kilitstatefalse","",_ip);
}
void MainWindow::pcKilitTransparanStateControlSignalSlot(QString _mac,QString _ip,bool transparankilitstate)
{
    if (transparankilitstate)
       udpSendData("transparankilitstatetrue","",_ip);
    else
      udpSendData("transparankilitstatefalse","",_ip);
}
void MainWindow::pcIconStateControlSignalSlot(QString _mac,QString _ip,bool iconstate)
{
       if (iconstate)
      udpSendData("ekranimagestatetrue","",_ip);
      else
       udpSendData("ekranimagestatefalse","",_ip);
}

void MainWindow::pcMenuSignalSlot(QString _mac,QString _ip,QString _slot)
{
    //qDebug()<<_mac<<_ip<<_slot;
    if(_slot=="slotVnc0"){slotVnc(_display);}
    if(_slot=="slotVnc1"){slotVnc("1");}
    if(_slot=="slotVnc2"){slotVnc("2");}

    if(_slot=="slotFtp"){slotFtp();}
    if(_slot=="slotKilit"){slotKilit();}
    if(_slot=="slotKilitAc"){slotKilitAc();}
    if(_slot=="slotEkranIzle"){slotEkranIzle();}
    if(_slot=="slotEkranIzleDurdur"){slotEkranIzleDurdur();}

    if(_slot=="slotReboot"){slotReboot();}
    if(_slot=="slotPowerOff"){slotPowerOff();}
    if(_slot=="slotLogout"){slotLogout();}
    //if(_slot=="slotMesaj"){duyuruButtonSlot();}
    //if(_slot=="slotCommand"){x11CommandButtonSlot();}
}

void MainWindow::layoutTemizle()
{
     qDebug()<<"Hosts Layout Temizlendi.";
     tempbtnlist.clear();

    while(btnlist.count()>0)
    {
       for(int i=0;i<btnlist.count();i++)
       {
           /*************************************************************/
           Pc *tmpPc=new Pc();
           tmpPc->mac=btnlist[i]->mac;
           tmpPc->pcname=btnlist[i]->pcname;

           if(!tamReset)///burası tam reset için gerekli çok önemli
           {
          tmpPc->cs=btnlist[i]->cs;

           }
           tmpPc->ps=btnlist[i]->ps;
           tmpPc->ss=btnlist[i]->ss;
           tmpPc->vs=btnlist[i]->vs;
           tmpPc->fs=btnlist[i]->fs;
           tmpPc->fs=btnlist[i]->fs;
           tmpPc->kilitState=btnlist[i]->kilitState;
           tmpPc->kilitControlState=btnlist[i]->kilitControlState;
           tmpPc->transparanKilitState=btnlist[i]->transparanKilitState;
           tmpPc->transparanKilitControlState=btnlist[i]->transparanKilitControlState;
           tmpPc->iconState=btnlist[i]->iconState;
           tmpPc->iconControlState=btnlist[i]->iconControlState;
           tmpPc->select=btnlist[i]->select;
           tmpPc->multiSelect=btnlist[i]->multiSelect;
           tmpPc->user=btnlist[i]->user;
           tmpPc->display=btnlist[i]->display;


           tempbtnlist.append(tmpPc);
          /**************************************************************/
           layout->removeWidget(btnlist[i]);
         delete btnlist[i];
         btnlist.removeAt(i);

       }
    }

    tamReset=false;
}


void MainWindow::hostListReset()
{
    qDebug()<<"hosts reset çalıştı";
    ///iptal QStringList list=fileToList("iplistname");
    QStringList list=PcData::onlinePcListe;

    QStringList list_;
    for(int i=0;i<list.count();i++)
     {
        QString line=list[i];
        if(line!="")
        {
        QStringList lst=line.split("|");
        //list=listRemove(list,lst[1]);
        list_<<lst[0]+"|"+lst[1]+"|" +"pcclose|sshclose|vncclose|ftpclose|offline|"+lst[7]+"|" +lst[8];

        }
    }
   ///iptal listToFile(list_,"iplistname");
    PcData::onlinePcListe=list_;

 mesajSlot("Hosts Reset Yapıldı.");
}

QStringList MainWindow::arpListInit()
{
    qDebug()<<"Hosts Arp Listesi Alındı";
   ///iptal system("cat /proc/net/arp |awk '$3==\"0x2\" {print $1\"|\"$4}'>/usr/share/e-ag/mactoiplist");
   ///iptal QStringList arpList=fileToList("mactoiplist",localDir);
   ///iptal QStringList arpListTemp=fileToList("mactoiplist",localDir);
    QStringList arpList=readArp();
    QStringList arpListTemp=readArp();

    ///iptal QStringList list=fileToList("iplistname");
    QStringList list=PcData::onlinePcListe;
    QStringList perlist=fileToList("persistlist",localDir);

/*************tekrar eden mac adresleri düzenleniyor***************/
    for(int i=0;i<arpListTemp.count();i++)
    {
        for(int j=0;j<arpList.count();j++)
        {
            if(arpListTemp[i].split("|")[1]==arpList[j].split("|")[1])
            {
                 arpList=listRemove(arpList,arpList[j].split("|")[1]);
                arpList<<arpListTemp[i];
            }
        }

    }
/******************************************************************/

   // qDebug()<<"temp arp"<<arpListTemp.count()<<"old arp"<<arpList.count();

    for(int i=0;i<arpList.count();i++)
    {
        QString line=arpList[i];
        if(line!="")
        {

            QStringList lst=line.split("|");
            QString ln=listGetLine(list,lst[1]); //değiştirilecek satır getiriliyor
           list=listRemove(list,lst[1]);

            if(ln!="") //iplistname dosyasında varsa
            {
                QStringList lnlst=ln.split("|");
                 QString perline=listGetLine(perlist,lst[1]);
                 QString name="???";
                 QString visible="e";
                 if(perline!=""){name=perline.split("|")[7];}
                 if(perline!=""){visible=perline.split("|")[8];}
                 //qDebug()<<"bulunan ad: "<<lst[1]<<name;
                list<<lst[0]+"|"+lst[1]+"|" +"pcopen|sshclose|vncclose|ftpclose|offline|"+name+"|"+visible;
               if(perline==""){
                   //qDebug()<<"Kalıcı Listede Yok: "<<lst[1]<<name;
                   QStringList per=fileToList("persistlist",localDir);
                   per=listRemove(per,lst[1]); //değişecek satır siliniyor
                   per<<lst[0]+"|"+lst[1]+"|" +"pcopen|sshclose|vncclose|ftpclose|offline|"+name+"|"+visible;

                   listToFile(per,"persistlist");
                }

            }
            else
            {
                QString perline=listGetLine(perlist,lst[1]);
                QString name="???";
                QString visible="e";
                if(perline!=""){name=perline.split("|")[7];}
                if(perline!=""){visible=perline.split("|")[8];}

                list<<lst[0]+"|"+lst[1]+"|" +"pcopen|sshclose|vncclose|ftpclose|offline|"+name+"|"+visible;

                if(perline==""){
                   // qDebug()<<"Kalıcı Listede Yok: "<<lst[1]<<name;
                    QStringList per=fileToList("persistlist",localDir);
                    per=listRemove(per,lst[1]); //değişecek satır siliniyor
                    per<<lst[0]+"|"+lst[1]+"|" +"pcopen|sshclose|vncclose|ftpclose|offline|"+name+"|"+visible;

                    listToFile(per,"persistlist");

                }
            }

          }


    }
    // qDebug()<<"list"<<list.count()<<"arp"<<arpList.count();

    return list;
}


void MainWindow::mesajSlot(QString msg)
{

    textBrowser_receivedMessages->moveCursor (QTextCursor::End);
    textBrowser_receivedMessages->insertPlainText (msg+"\n");
    statusbar->showMessage(msg);
}


void MainWindow::pcClickSlot(QString _mac)
{

if(remoteUserName==""||remotePassword==""||
        localUserName==""||localPassword=="")
{
    ///localNetwork!=""||tcpPort!="")
    QMessageBox msgBox;
     msgBox.setText("Uygulamanın Sorunsuz Çalışması İçin Eksik Bilgileri Doldurunuz!");
     msgBox.exec();
   acountButtonSlot();
}


    QPalette palet;
    for(int i=0;i<btnlist.length();i++)
     {
        if(btnlist[i]->mac!=_mac)
        {
         btnlist[i]->select=false;
        /// btnlist[i]->slotUnselectPc();
         palet.setColor(QPalette::Window, QColor(0,0,0,0));
         btnlist[i]->setPalette(palet);
         btnlist[i]->setAutoFillBackground(true);
        }
        else
        {
            system("nohup rm -rf ~/.ssh &");

           pcIp->setText(btnlist[i]->ip);
           pcMac->setText(btnlist[i]->mac);
           pcName->setText(btnlist[i]->pcname);
          /// btnlist[i]->slotUnselectPc();
            pcNamelbl->setText("Pc Adı: "+pcName->text());
            pcIplbl->setText("Ip: "+pcIp->text());
            pcMaclbl->setText("Mac: "+pcMac->text());

            pcUserlbl->setText("Kullanıcı: "+btnlist[i]->user);
            pcScreenlbl->setText("Ekran: "+btnlist[i]->display);
            pcSystemlbl->setText("Sistem: "+btnlist[i]->os.trimmed());
            if(btnlist[i]->display=="")  _display="0";
            else
                _display=btnlist[i]->display.right(1);


        }
      }
    selectMac=pcMac->text();

}
void MainWindow::ftpConnectButtonSlot()
{

    system("cp /usr/share/e-ag/filezilla.xml ~/.config/filezilla/");
textBrowser_receivedMessages->clear();
if(ftpState(pcMac->text())==false){ mesajSlot("Pc Seçiniz"); return;}

    QStringList arguments;
    QString  komut;
    komut.append("nohup filezilla ").append(remoteUserName+":").append(remotePassword).append("@"+pcIp->text()+" &");
  // qDebug()<<komut;
     arguments << "-c" << komut;
    QProcess process;
    process.start("/bin/bash",arguments);
    process.waitForFinished(-1); // will wait forever until finished

}

MainWindow::~MainWindow()
{
    qDebug()<<"Kapatıldı.";
    videoProcess.terminate();

}

QStringList MainWindow::listMerge(QStringList list1, QStringList list2, int dataIndex)
{
    for(int i=0;i<list1.count();i++)
    {
        QString line=list1[i];
        if(line!="")
        {

            QStringList lst=line.split("|");
            list2=listRemove(list2,lst[dataIndex]);
        }
    }
    for(int i=0;i<list1.count();i++)
    {
       list2.append(list1[i]);
    }
    return list2;
}

QStringList MainWindow::listRemoveToList(QStringList sourceList, QStringList removeList, int dataIndex)
{
    for(int i=0;i<removeList.count();i++)
    {
        QString line=removeList[i];
        if(line!="")
        {

            QStringList lst=line.split("|");
            sourceList=listRemove(sourceList,lst[dataIndex]);
        }
    }

    return sourceList;
}

QStringList MainWindow::listSort(QStringList list, int dataIndex)
{
    QStringList yeniList;
    for(int i=0;i<list.count();i++)
    {
        QString satir=list[i];
        QString splitdata=list[i].split("|")[dataIndex];
        QString yenisatir=splitdata+"|"+satir;
        yeniList.append(yenisatir.toLower());
        //qDebug()<<yenisatir;
    }
    qSort(yeniList.begin(), yeniList.end());
    QStringList sonList;
    for(int i=0;i<yeniList.count();i++)
    {
        QString satir=yeniList[i];
        QString splitdata=yeniList[i].split("|")[0]+"|";

        QString yenisatir=satir.mid(splitdata.count());
        sonList.append(yenisatir);
        //qDebug()<<yenisatir;
    }

    return sonList;
}

QStringList MainWindow::listReplace(QStringList list, QString oldData, QString newData, int index)
 {
    QStringList liste;
         QRegularExpression re(oldData);
     for(int i=0;i<list.count();i++)
     {
         if(list[i].contains(re))
         {
             QStringList lst=list[i].split("|");
             lst[index].replace(oldData, newData);
            // qDebug()<<lst;

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

            // list.removeAt(i);
             liste.append(ln);
         }else
         {
             liste.append(list[i]);
         }
     }
    // qDebug()<<list;
     return liste;
 }

QStringList MainWindow::listGetList(QStringList list, QString data,int index)
 {
    QStringList liste;
    QRegularExpression re(data);
     for(int i=0;i<list.count();i++)
     {
         if(list[i].contains(re))
         {
            liste.append(list[i]);

         }
     }
    // qDebug()<<list;
     return liste;
 }

QStringList MainWindow::listRemove(QStringList list,QString data)
 {
       QRegularExpression re(data);
     for(int i=0;i<list.count();i++)if(list[i].contains(re)) list.removeAt(i);
    // qDebug()<<list;
     return list;
 }
QString MainWindow::listGetLine(QStringList list,QString data)
 {
      QRegularExpression re(data);
     for(int i=0;i<list.count();i++) if(list[i].contains(re)) return list[i];
     //qDebug()<<list;
     return "";
 }
QStringList MainWindow::fileToList(QString filename,QString path)
 {
    FileCrud *fcc=new FileCrud();
    fcc->dosya=path+filename;
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
bool MainWindow::vncState(QString _mac)
{
    bool state=false;
    ///iptal QStringList liste=fileToList("iplistname");
    QStringList liste=PcData::onlinePcListe;

    for(int i=0;i<liste.count();i++)
    {
        QString line=liste[i];
        line.chop(1);
        QStringList lst=line.split("|");
        if(lst[1]== _mac&&lst[4]=="vncopen"){
          return true;
         // qDebug()<<"vnc durum: "<<btnlist[i]->vs<<btnlist[i]->V<<btnlist[i]->mac<<_mac;
        }
    }
 return false;
}

bool MainWindow::ftpState(QString _mac)
{
    ///iptal QStringList liste=fileToList("iplistname");
    QStringList liste=PcData::onlinePcListe;

    for(int i=0;i<liste.count();i++)
    {
        QString line=liste[i];
        line.chop(1);
        QStringList lst=line.split("|");
        if(lst[1]== _mac&&lst[5]=="ftpopen"){
          return true;
         // qDebug()<<"vnc durum: "<<btnlist[i]->vs<<btnlist[i]->V<<btnlist[i]->mac<<_mac;
        }
    }
 return false;
}
