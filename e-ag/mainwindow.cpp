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
#include<QString>
#include<QDataStream>
#include<menu.h>
#include <QScrollArea>
#include<QApplication>
#include<QDesktopWidget>
#include<QtWidgets>
#include<tcpudp.h>
#include<init.h>
#include<funtion.h>
#include<SettingsWidget.h>
#include<lockWidget.h>
#include<volumeWidget.h>
#include<powerrebootWidget.h>
#include<loginLogoutWidget.h>
#include<screenViewWidget.h>
#include<vncrdpWidget.h>
#include<runcommandWidget.h>
#include<filecopyWidget.h>
#include<messageWidget.h>
#include<languageWidget.h>
#include<videoWidget.h>
#include<wolWidget.h>
#include<sliderWidget.h>
#include<baseWidget.h>
#include<groupWidget.h>
#include<webInternetWidget.h>
#include<keyboardmouseWidget.h>
#include<deviceWidget.h>
#include<multicastaddressdialog.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //QTermWidget *qterm=new QTermWidget();
    //qterm->sendData();
      /*****************************************************/
    QSize screenSize = qApp->screens()[0]->size();
    boy=screenSize.height()/153.6;
    en=boy*1.1;
    int e=en;
    int b=boy;
    this->resize(boy*200,en*105);
    int x = (screenSize.width() - this->width())/2;
    int y = (screenSize.height() - this->height()) / 2;
    this->move(x, y);
   // qDebug()<<"aşama1";

    mainWidget=new QWidget();
#if defined(Q_OS_WIN)
    localDir="c:/e-ag/";
#elif defined(Q_OS_LINUX)
    localDir="/usr/share/e-ag/";
#endif


    hostAddressMacButtonSlot();
    rb1=new QRadioButton();
    rb2=new QRadioButton();
    //system("systemctl restart e-ag-networkprofil.service");
    networkProfilLoad();///hesap ve ayarların yüklenmesi yapılıyor...
//setMouseTracking(true);
//installEventFilter(this);
    /************************version*******************************************/
    QStringList arguments;
    arguments << "-c" << "dpkg -s e-ag|grep -i version";
    QString resultVersion;
    QProcess process;
    process.start("/bin/bash",arguments);
    if(process.waitForFinished())
    {
        resultVersion = process.readAll();
    }
    resultVersion.chop(1);
    QString version = resultVersion.right(5);
    setWindowTitle("e-ag "+version);
    /***********************************************************************/
    auto appIcon = QIcon(":/icons/e-ag.svg");
    this->setWindowIcon(appIcon);

   /***********************************************************************/
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
    hostListe->setObjectName("hostListe");

    rubberBand = new QRubberBand(QRubberBand::Rectangle, hostListe);
    //hostListe->setStyleSheet("QWidget#hostListe{border: 0.5px solid rgb(0, 0,0,255);}");
    scrollArea=new QScrollArea();
    scrollArea->setWidget(hostListe);
    scrollArea->setFixedSize(e*180,b*56);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // scrollArea->setStyleSheet("background-color: #ff5533");

    /// hostListe->hide();
    layout = new QGridLayout(hostListe);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setSpacing(3);
    //hostListe->setLayout(layout);

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
    tabwid->addTab(baseWidget(),QIcon(":/icons/toolbox.svg"),tr("Temel İşlemler"));
    tabwid->addTab(rdpWidget(),QIcon(":/icons/vnc.svg"),tr("Ekran Paylaş"));
    tabwid->addTab(commandWidget(),QIcon(":/icons/bash.svg"),tr("Komut Çalıştır"));
    tabwid->addTab(webInternetWidget(),QIcon(":/icons/web.svg"),tr("Internet"));
    tabwid->addTab(messageWidget(),QIcon(":/icons/message.svg"),tr("Mesaj Yaz"));
    tabwid->addTab(fileWidget(),QIcon(":/icons/filecopy.svg"),tr("Dosya Kopyala"));
    tabwid->addTab(videoWidget(),QIcon(":/icons/camera.svg"),tr("Video/Kamera"));
    tabwid->addTab(deviceWidget(),QIcon(":/icons/device.svg"),tr("Donanım"));

    tabwid->addTab(settingsWidget(),QIcon(":/icons/settings.svg"),tr("Ayarlar"));
    tabwid->addTab(textBrowser_receivedMessages,QIcon(":/icons/log.svg"),tr("İşlem Raporu"));
    tabwid->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    tabwid->setTabPosition(QTabWidget::North);
    /***********************************************************************/
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

    //newPcDetectTimer= new QTimer(this);
    //connect(newPcDetectTimer, SIGNAL(timeout()), this, SLOT(pcDetect()));
    //newPcDetectTimer->start(5000);
    /********************* Broadcast Message yollanıyor *****************************************/
    QString uport="7879";
    if(NetProfilList.count()>0)
        uport=NetProfilList.first().networkTcpPort;

    udpSocketSend = new QUdpSocket(this);
    udpSocketGet = new QUdpSocket();
    udpSocketGet->bind(uport.toInt(), QUdpSocket::ShareAddress);
    QObject::connect(udpSocketGet,&QUdpSocket::readyRead,[&](){udpSocketServerRead();});
    //qDebug()<<"Port.:"<<uport;
    /*********************************************************/

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

 /*************************************************************************/
 DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
 QJsonArray dizi=db->Oku();
 //QJsonArray dizi=db->Ara("selectedNetworkProfil",true);

 if(dizi.count()>0)
 {
     for (const QJsonValue &item : dizi) {
         QJsonObject veri=item.toObject();
         //qDebug()<<"Yüklenen Ağ Profili:" <<veri;
         bool findedStatus=false;
         for(int i=0;i<onlinePcList.count();i++)
         {
             if(onlinePcList[i]->mac.toUpper()==veri["mac"].toString().toUpper())
             {
                 findedStatus=true;
             }
         }
         if(!findedStatus){
             slotPcEkle(veri["mac"].toString().toUpper(),veri["ip"].toString());
         }

     }
 }

/*************************************************************************/
 }
/*
bool MainWindow::karsilastirMyPc(const MyPc *mypc1, const MyPc *mypc2) {
    //qDebug()<<"adlar: "<<mypc1->caption;
    mypc1->hostnameVisible
        mypc1->hostname
    return mypc1->caption < mypc2->caption; // caption göre sırala
 }*/
 bool MainWindow::karsilastirMyPc(const MyPc *mypc1, const MyPc *mypc2)
 {
     QString name1 = mypc1->hostnameVisible ? mypc1->hostname : mypc1->caption;
     QString name2 = mypc2->hostnameVisible ? mypc2->hostname : mypc2->caption;

     return name1 < name2;
 }

void MainWindow::pcListeGuncelleSlot(QString mission)
{
    qDebug()<<"pcListeGuncelleSlot:"<<mission;
    /***********************************************/
    //Sıralama yapıldı caption göre
    std::sort(onlinePcList.begin(), onlinePcList.end(),karsilastirMyPc);
    //sadece gizli olmayanlar filtreleniyor
    std::vector<MyPc*> onlinePcList1;
    //pc listesi temizlendi
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->setParent(nullptr);
        }
        delete item;
    }
    //gruplamaya göre liste hazırlanıyor.
    std::copy_if(onlinePcList.begin(), onlinePcList.end(),
                 std::back_inserter(onlinePcList1),
                 [](const MyPc* mypc) {
                     // Grup listesinde eşleşen ve seçili grup var mı?
                     for (const groupList &g : PcData::groupListe) {

                         if (g.groupSelect && g.groupName == mypc->groupname&&mypc->visibleState)
                         {
                             ///qDebug()<<"gözükecekler"<<mypc->caption<<mypc->groupname<<mypc->visibleState<<g.groupSelect << g.groupName;
                             return true;
                         }
                     }
                     return false;
                 });
     hostsCountLabel->setText(tr("Açık Hosts : ")+QString::number(onlinePcList1.size()));
/***********seçili olmayanları unselect yapmak için işlemler**************************/
     std::vector<MyPc*> farkListesi;
     for (MyPc* pc : onlinePcList) {
         if (std::find(onlinePcList1.begin(),
                       onlinePcList1.end(),
                       pc) == onlinePcList1.end()) {
             farkListesi.push_back(pc);
         }
     }
     for (MyPc *pc : farkListesi) {
         for (MyPc *pc1 : onlinePcList) {
         if (pc->mac.toUpper() == pc1->mac.toUpper()) {
                 pc1->multiSelect=false;
                 pc1->select=false;
                 pc1->slotUnselectPc();
                 qDebug()<<pc1->mac;
             }
         }
     }
    /*******************************************************************/
     float olcek = slider->value() / 100.0f;
     //qDebug() << "olcek:" << slider->value() << olcek;
     double nwidth=en*20*olcek;
     double nheight=en*15*olcek;
     int columnSayisi=hostListe->width()/(nwidth*1.4);
     int listeSayisi=onlinePcList1.size();
     int satir=listeSayisi/columnSayisi;
     int mod=listeSayisi%columnSayisi;
     if (mod!=0) satir++;
     int sutun=columnSayisi;
     if(listeSayisi<columnSayisi)sutun=listeSayisi;
     /************************************************************/
     double nlstheight=satir*(nheight*1.4);
     //double nlstheight=(en*(gercekliste/columnSayisi+1)*13.8)*slider->value()/100;
     double tempnlstheight=(this->height()-tabwid->height()-selectWidget->height()-7*boy);
    //qDebug()<<"satir"<<satir<<"sutun"<<sutun<<"liste sayısı"<<listeSayisi<<tempnlstheight<<nlstheight;
     if(nlstheight>tempnlstheight)
        hostListe->setFixedSize(hostListe->width(),nlstheight);
     else
        hostListe->setFixedSize(hostListe->width(),tempnlstheight);


     /************************************************************/
     //qDebug()<<"Hosts Listesi Güncellendi..new";//<<columnSayisi<<nwidth<<nheight;
   /// qDebug()<<"Hosts Listesi Güncellendi..new"<<mission;
     int sn=0;
     for(int i=0;i<satir;i++)
     {
         for(int k=0;k<sutun;k++)
         {
             if((sn+1)>listeSayisi) continue;
             if(onlinePcList1[sn]->visibleState)
             {
                 //qDebug()<<onlinePcList1[sn]->ip;
                 layout->addWidget(onlinePcList1[sn], i,k,1,1);
                 onlinePcList1[sn]->setSize(nwidth,nheight,font);
             }
             sn++;
        }
     }

/***************pc seçimi yapılıyor önemli***********************/

     if(onlinePcList1.size()>0)
     {
         onlinePcList1[0]->slotMouseClick();
         //pcClickSlot(onlinePcList1[onlinePcList1.size()-1]->mac);
     }

 }

void MainWindow::pcSettingUpdateSignalSlot(QString _mac,QString mission)
{
    //grup güncelleniyor yeniden oluşturuluyor
    groupwidget1=groupWidget(groupwidget1);
    //pc listesi güncelleniyor yeniden oluşturuluyor
    pcListeGuncelleSlot(mission);
}

void MainWindow::pcScreenViewSignalSlot(QString _mac,QString _ip)
{
    for (MyPc *mypc : onlinePcList) {
        if (mypc->mac.toUpper() == _mac.toUpper()) {
            if(mypc->connectState)
            {
                ///qDebug()<<"ekran izle";
                mypc->setIconControlState(true);
                udpSendData("x11command","x11command","pkill serverscreen","",false);
                udpSendData("x11command","x11command","pkill ffmpeg","",false);
                system("sleep 1");
                QString uport="7879";
                uport=mypc->netProfil.networkTcpPort;
                std::reverse(uport.begin(), uport.end());
                //QString msg="x11command|x11command|serverscreen "+mypc->ip+"||0|"+mypc->netProfil.serverAddress+"|"+uport;
                //QByteArray datagram = msg.toUtf8();
                //udpSocketSend->writeDatagram(datagram,QHostAddress(mypc->ip), uport.toInt());

                QJsonObject sendJson;
                sendJson["mainmessagetype"] = "x11command";
                sendJson["submessagetype"] ="x11command" ;
                sendJson["mission"] = "serverscreen "+mypc->ip;
                sendJson["missionmessage"]="";
                sendJson["messagevisible"]="0";
                sendJson["server_address"] = mypc->netProfil.serverAddress;
                sendJson["port"] = uport;

                QByteArray datagram = QJsonDocument(sendJson).toJson(QJsonDocument::Compact);
                udpSocketSend->writeDatagram(datagram,QHostAddress(mypc->ip), uport.toInt());

                mesajSlot(tr("Seçili Ekran İzlemeler Başlatıldı."));
                ////qDebug()<<"izle......";
            }
        }
    }

    /*
*/

}

void MainWindow::pcHideSignalSlot(QString _mac)
 {
    for(int i=0;i<onlinePcList.count();i++)
         {
         if(onlinePcList[i]->mac==_mac)
         {
            //qDeleteAll(hostListe->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
            layout->removeWidget(onlinePcList[i]);
            //hostListe->removeWidget(onlinePcList[i]);
            delete onlinePcList[i];
            onlinePcList.removeAt(i);
            //pcDetect();
            break;
         }
        }

 }

void MainWindow::mesajSlot(QString msg)
{

    textBrowser_receivedMessages->moveCursor (QTextCursor::End);
    textBrowser_receivedMessages->insertPlainText (msg+"\n");
    statusbar->showMessage(msg);
}

void MainWindow::pcDoubleClickSignalSlot(QString _mac)
{
    qDebug() << "Çift tıklandı:" << _mac;

    MyPc *targetPc = nullptr;

    for (MyPc *pc : onlinePcList) {
        if (pc->mac.trimmed().toUpper() == _mac.trimmed().toUpper()) {
            targetPc = pc;
            break;
        }
    }

    if (!targetPc) {
        mesajSlot(tr("Belirtilen MAC adresine sahip bilgisayar bulunamadı."));
        return;
    }

    qDebug() << "VNC Port dizisi:" << targetPc->vncport;

    QStringList portList = targetPc->vncport.split("-", Qt::SkipEmptyParts);
    QString chosenPort = "5900";

    // 5900 haricinde varsa onu seç
    for (const QString &p : portList) {
        if (p != "5900" && !p.isEmpty()) {
            chosenPort = p;
            break;
        }
    }


    qDebug() << "Seçilen port:" << chosenPort;

    float scaleValue = ekranSlider->value() * 0.01f;
    if(targetPc->vncviwerpid!=0&&
        QFile::exists(QString("/proc/%1").arg(targetPc->vncviwerpid))) {
        qDebug() << "önceden çalışmış"<<targetPc->vncviwerpid;
        QString kmt="kill "+QString::number(targetPc->vncviwerpid);
        //qDebug()<<kmt;
        QThread::msleep(200); // 200–300 ms yeterli
        system(kmt.toStdString().c_str());
        //return;
    }
    // güvenlik: ip/port/scale gibi değerleri kontrol et/validate etmeden shell'e koyma!
   QString program = "ssvncviewer";
   QStringList args;
   args << "-scale" << QString::number(scaleValue)
        << QString("%1:%2").arg(targetPc->ip).arg(chosenPort)
        << "-passwd" << "/usr/bin/x11vncpasswd";

    qint64 pid = 0;
    bool ok = QProcess::startDetached(program,args, QString(), &pid);
    if (ok) {
        qDebug() << "Detached started, pid =" << pid;
        targetPc->vncviwerpid=pid;

    } else {
        qWarning() << "Detached start failed";
    }

    //qDebug() << "VNC başlatıldı:" << args.join(" ");
    mesajSlot(tr("Seçili hostta VNC başlatıldı."));
}

void MainWindow::pcClickSlot(QString _mac)
{
    QPalette palet;
    for(int i=0;i<onlinePcList.length();i++)
     {
        if(onlinePcList[i]->mac!=_mac)
        {
         onlinePcList[i]->select=false;
        /// btnlist[i]->slotUnselectPc();
         palet.setColor(QPalette::Window, QColor(0,0,0,0));
         onlinePcList[i]->setPalette(palet);
         onlinePcList[i]->setAutoFillBackground(true);
        }
        else
        {
            #if defined(Q_OS_WIN)
                //system("del ~/ssh &");
            #elif defined(Q_OS_LINUX)
                system("rm -rf ~/.ssh &");
            #endif

           pcIp->setText(onlinePcList[i]->ip);
           pcMac->setText(onlinePcList[i]->mac);
           pcName->setText(onlinePcList[i]->caption);
          /// btnlist[i]->slotUnselectPc();
            pcNamelbl->setText(tr("Pc Adı: ")+pcName->text());
            pcIplbl->setText(tr("Ip: ")+pcIp->text());
            pcMaclbl->setText(tr("Mac: ")+pcMac->text());
            pcUserlbl->setText(tr("Kullanıcı: ")+onlinePcList[i]->user);
           /// pcScreenlbl->setText("Ekran: "+onlinePcList[i]->display);
            pcSystemlbl->setText(tr("Sistem: ")+onlinePcList[i]->hostname.trimmed());
            pcVersionlbl->setText(tr("Version: ")+onlinePcList[i]->version);
         }
      }
    selectMac=pcMac->text();

}

void MainWindow::pcRightClickSignalSlot()
{
    pcrightmenu=true;
}

MainWindow::~MainWindow()
{
    qDebug()<<"e-ag Kapatıldı.";
    QThread::sleep(1); // saniye cinsinden
    //system("sleep 1");
    slotVncFlipStop();
    //system("sleep 1");
    QThread::sleep(1); // saniye cinsinden
    udpSendData("x11command","x11command","pkill clientscreen","server-closed",true);

#if defined(Q_OS_WIN)

    if(streamState)
    {
         killProcessByName("ffmpeg.exe");
         killProcessByName("servervideo.exe");
         killProcessByName("clientvideo.exe");
         //system("pkill servercamera");
         system("taskkill /IM servercamera /F");
         //system("pkill clientcamera");
         system("taskkill /IM clientcamera /F");
    }
#elif defined(Q_OS_LINUX)

    if(streamState)
    {
        system("pkill servervideo");
        system("pkill clientvideo");
        system("pkill servercamera");
        system("pkill clientcamera");
        system("pkill serverscreen");
        system("pkill ffmpeg");
    }
#endif

}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug()<<"main move";
    int hostListePos=tabwid->height()+selectWidget->height();
    /* if (Pc *w =(Pc*) qApp->widgetAt(QCursor::pos())) {
         if(w->objectName()=="hostListe")
         {
       */      //qDebug()<<"main move22";
    rubberBand->setGeometry(QRect(QPoint(origin.x(),origin.y()-hostListePos),QPoint(event->pos().x(),event->pos().y()-hostListePos)).normalized());
    // }
    //}
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // qDebug()<<"main release"<<mouseClickState;
    if(mouseClickState)
    {
        rubberBand->hide();
        QRect selectionRect = rubberBand->geometry();
        for (MyPc *mypc : findChildren<MyPc *>()) {
            if (selectionRect.intersects(mypc->geometry())) {
                mypc->slotSelectPc();
            } else {
                mypc->slotUnselectPc();
            }
        }
    }
    mouseClickState=false;

}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // qDebug()<<"main press";
    origin =( event->pos());
    int hostListePos=tabwid->height()+selectWidget->height();
    rubberBand->setGeometry(QRect(QPoint(origin.x(),origin.y()-hostListePos),QSize(0,0)));
    rubberBand->show();
    mouseClickState=true;
    if (event->button()==Qt::RightButton)
    {
        //qDebug()<<"burası main sağtuş";
        int  pcmultiselect=0;
        //if(pcrightmenu) pcmultiselect++;
        for(int i=0;i<onlinePcList.length();i++)
        {
            //if(btnlist[i]->mac==selectMac)
            //  {
            if(onlinePcList[i]->multiSelect||onlinePcList[i]->select){
                // if (QWidget *w =(QWidget*) qApp->widgetAt(QCursor::pos())) {
                // if(w->objectName()=="hostListe")
                //  {
                pcmultiselect++;
                //}
                //}
            }
            // }
        }
        ///

        if(pcmultiselect>0)
        {
            bool singleSelectPcStatus=false;
            bool multiSelectPcStatus=false;
            bool hostListeRightClick=false;
            bool hostListeRightClickStatus=false;
            if (QWidget *w =(QWidget*) qApp->widgetAt(QCursor::pos())) {
                if(w->objectName()=="hostListe")
                {
                    hostListeRightClick=true;
                }
            }

            if(pcmultiselect==1&&pcrightmenu) singleSelectPcStatus=true;
            if(pcmultiselect>1&&pcrightmenu) multiSelectPcStatus=true;
            if(pcmultiselect>1&&hostListeRightClick) hostListeRightClickStatus=true;

            qDebug()<<"seçilen pc sayısı: "<<pcmultiselect<<pcrightmenu<<singleSelectPcStatus<<multiSelectPcStatus<<hostListeRightClickStatus;
            if(singleSelectPcStatus||multiSelectPcStatus||hostListeRightClickStatus)
            {
                if(singleSelectPcStatus)
                    pcMenu(true); //single select pc
                else
                    pcMenu(false); //multi select pc

                pContextMenu->exec(mapToGlobal(event->pos()),nullptr);
                // qDebug()<<"burası main sağ menu"<<mouseClickState;
                mouseClickState=false;
                pcrightmenu=false;
                pcmultiselect=0;
            }
        }
    }

}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ///qDebug()<<"main boyut değişti";
    selectWidget->setFixedSize(this->width(),selectWidget->height());
    //ustMenuWidget->setFixedSize(this->width(),ustMenuWidget->height());
    textBrowser_receivedMessages->setFixedSize(this->width(),boy*19-2);
    tabwid->setFixedSize(this->width(),boy*22);
    hostListe->setFixedSize(this->width()-en*3.5,this->height());
   // scrollArea->setFixedSize(this->width(),this->height()-boy*5);

   // hostListe->setFixedSize(this->width()-en*3.5,this->height()-tabwid->height()-selectWidget->height()-boy*7);
    scrollArea->setFixedSize(this->width(),this->height()-tabwid->height()-selectWidget->height()-boy*6);
   /* if(firstRun){
        pcListeGuncelleSlot("mainresize");
    }
    else{firstRun=true;}*/
    pcListeGuncelleSlot("mainresize");
    ///QWidget::resizeEvent(event);
}
