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
#ifndef MENU_H
#define MENU_H
#include<QWidgetAction>
#include <QDesktopWidget>
#include<QVBoxLayout>
#include<QTranslator>
#include <QApplication>
#include<QSettings>
QMenu *MainWindow::commandExampleMenu()
{   QMenu *menu = new QMenu(this);

   QPushButton *updateCommandButton= new QPushButton;
   updateCommandButton->setFixedSize(200, 30);
   updateCommandButton->setIconSize(QSize(200,30));
   updateCommandButton->setText(tr("Güncelle"));
   updateCommandButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
   updateCommandButton->setFlat(true);

   connect(updateCommandButton, &QPushButton::clicked, [=]() {

       commandEdit->setText("apt-get update");
       menu->close();
});

   QPushButton *updateProblemCommandButton= new QPushButton;
   updateProblemCommandButton->setFixedSize(200, 30);
   updateProblemCommandButton->setIconSize(QSize(200,30));
   updateProblemCommandButton->setText(tr(" Paket Problemleri Düzelt"));
   updateProblemCommandButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
   updateProblemCommandButton->setFlat(true);

   connect(updateProblemCommandButton, &QPushButton::clicked, [=]() {

       commandEdit->setText("apt-get install -f");
       menu->close();
});

   QPushButton *installCommandButton= new QPushButton;
   installCommandButton->setFixedSize(200, 30);
   installCommandButton->setIconSize(QSize(200,30));
   installCommandButton->setText(tr(" Paket Yükleme"));
   installCommandButton->setStyleSheet("Text-align:left;  font-size:"+font+"px;");
   installCommandButton->setFlat(true);

   connect(installCommandButton, &QPushButton::clicked, [=]() {

       commandEdit->setText(tr("apt-get install paket"));
       menu->close();
});

   QPushButton *removeCommandButton= new QPushButton;
   removeCommandButton->setFixedSize(200, 30);
   removeCommandButton->setIconSize(QSize(200,30));
   removeCommandButton->setText(tr(" Paket Kaldırma"));
   removeCommandButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
   removeCommandButton->setFlat(true);

   connect(removeCommandButton, &QPushButton::clicked, [=]() {

       commandEdit->setText("apt-get remove paket ");
       menu->close();
});

   QPushButton *mkdirCommandButton= new QPushButton;
   mkdirCommandButton->setFixedSize(200, 30);
   mkdirCommandButton->setIconSize(QSize(200,30));
   mkdirCommandButton->setText(tr(" Klasör Oluştur"));
   mkdirCommandButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
   mkdirCommandButton->setFlat(true);

   connect(mkdirCommandButton, &QPushButton::clicked, [=]() {

       commandEdit->setText(tr("mkdir klasor "));
       menu->close();
});
   QPushButton *rmdirCommandButton= new QPushButton;
   rmdirCommandButton->setFixedSize(200, 30);
   rmdirCommandButton->setIconSize(QSize(200,30));
   rmdirCommandButton->setText(tr(" Klasör Sil"));
   rmdirCommandButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
   rmdirCommandButton->setFlat(true);

   connect(rmdirCommandButton, &QPushButton::clicked, [=]() {

       commandEdit->setText(tr("rmdir klasor"));
       menu->close();
});
   /*************************************/
       QPushButton *sessionLoginCommandButton= new QPushButton;
       sessionLoginCommandButton->setFixedSize(200, 30);
       sessionLoginCommandButton->setIconSize(QSize(200,30));
       sessionLoginCommandButton->setText(tr(" Oturum Aç"));
       sessionLoginCommandButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
       sessionLoginCommandButton->setFlat(true);

       connect(sessionLoginCommandButton, &QPushButton::clicked, [=]() {

           commandEdit->setText(tr("sshlogin <user> <password>"));
    menu->close();
    });

   /*************************************/
       QPushButton *closePcCommandButton= new QPushButton;
       closePcCommandButton->setFixedSize(200, 30);
       closePcCommandButton->setIconSize(QSize(200,30));
       closePcCommandButton->setText(tr(" Pc'yi Kapat"));
       closePcCommandButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
       closePcCommandButton->setFlat(true);

       connect(closePcCommandButton, &QPushButton::clicked, [=]() {

           commandEdit->setText("poweroff");
    menu->close();
    });
    /*************************************************/
       QPushButton *rebootPcCommandButton= new QPushButton;
       rebootPcCommandButton->setFixedSize(200, 30);
       rebootPcCommandButton->setIconSize(QSize(200,30));
       rebootPcCommandButton->setText(tr(" Pc'yi Yeniden Başlat"));
       rebootPcCommandButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
       rebootPcCommandButton->setFlat(true);

       connect(rebootPcCommandButton, &QPushButton::clicked, [=]() {

           commandEdit->setText("reboot");
    menu->close();
    });

    /******************************************************/

    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(updateCommandButton, 5,0,1,2);
    layout->addWidget(updateProblemCommandButton, 10,0,1,2);
    layout->addWidget(installCommandButton, 15,0,1,2);
    layout->addWidget(removeCommandButton, 20,0,1,2);
    layout->addWidget(mkdirCommandButton, 25,0,1,2);
    layout->addWidget(rmdirCommandButton, 30,0,1,2);
    layout->addWidget(sessionLoginCommandButton, 35,0,1,2);

    layout->addWidget(closePcCommandButton, 40,0,1,2);
     layout->addWidget(rebootPcCommandButton, 42,0,1,2);

     // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

     menu->setStyleSheet("QMenu { width: 190 px; height: 250 px; font-size:"+font+"px;}");
   return menu;
}

QMenu *MainWindow::poweroffRebootMenu()
{
    QMenu *menu = new QMenu(this);
    int yukseklik=en*14;
  /*************************************/
    QPushButton *closeAllButton= new QPushButton;
    closeAllButton->setFixedSize(yukseklik*1.8, yukseklik/3);
    closeAllButton->setIconSize(QSize(yukseklik*1.8,yukseklik/3));
    closeAllButton->setIcon(QIcon(":icons/close.svg"));
    closeAllButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    closeAllButton->setText(tr("Tümünü Kapat"));
    closeAllButton->setFlat(true);
    connect(closeAllButton, &QPushButton::clicked, [=]() {
        slotPowerOffAll();
        menu->close();

    });


    QPushButton *rebootAllButton= new QPushButton;
    rebootAllButton->setFixedSize(yukseklik*1.8, yukseklik/3);
    rebootAllButton->setIconSize(QSize(yukseklik*1.8,yukseklik/3));
    rebootAllButton->setIcon(QIcon(":icons/reboot.svg"));
    rebootAllButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    rebootAllButton->setText(tr("Tümünü Y. Başlat"));
    rebootAllButton->setFlat(true);
    connect(rebootAllButton, &QPushButton::clicked, [=]() {
        slotRebootAll();
      menu->close();
 });



    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    //  layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(closeAllButton, 5,0,1,1);
    layout->addWidget(rebootAllButton, 6,0,1,1);
    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
    //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

     menu->setStyleSheet("QMenu { width: "+QString::number(yukseklik*1.8)+" px; height: "+QString::number(yukseklik/1.5) +"px; }");
   return menu;

}

QMenu *MainWindow::ekranImageMenu()
{
    QMenu *menu = new QMenu(this);
    int yukseklik=en*14;
  /*************************************/
    QPushButton *screenStartAll= new QPushButton;
    screenStartAll->setFixedSize(yukseklik*1.8, yukseklik/3);
    screenStartAll->setIconSize(QSize(yukseklik*1.8,yukseklik/3));
    screenStartAll->setIcon(QIcon(":icons/monitor.svg"));
    screenStartAll->setText(tr("Tüm Ekranları İzle"));
   screenStartAll->setFlat(true);
   screenStartAll->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");

   connect(screenStartAll, &QPushButton::clicked, [=]() {
       slotEkranIzleAll();
       menu->close();
   });

    QPushButton *screenStopAll= new QPushButton;
    screenStopAll->setFixedSize(yukseklik*1.8, yukseklik/3);
    screenStopAll->setIconSize(QSize(yukseklik*1.8,yukseklik/3));
    screenStopAll->setIcon(QIcon(":icons/monitorstop.svg"));
    screenStopAll->setText(tr("İzlemeleri Durdur"));
    screenStopAll->setFlat(true);
    screenStopAll->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");

    connect(screenStopAll, &QPushButton::clicked, [=]() {
        slotEkranIzleAllDurdur();
        menu->close();
 });


    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
   layout->addWidget(screenStartAll, 5,0,1,1);
  layout->addWidget(screenStopAll, 6,0,1,1);

    // layout->addWidget(new QLabel("<font size=1>Ayarları Kaydet</font>"),6,1,1,1,Qt::AlignHCenter);
      //layout->setColumnStretch(6, 255);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

     menu->setStyleSheet("QMenu { width: "+QString::number(yukseklik*1.8)+" px; height: "+QString::number(yukseklik/1.5) +"px; }");
   return menu;

}

QMenu *MainWindow::komutMenu()
{   QMenu *menu = new QMenu(this);

   QPushButton *kilitButton= new QPushButton;
   kilitButton->setFixedSize(170, 30);
   kilitButton->setIconSize(QSize(150,30));
   kilitButton->setText(tr(" Seçili Pc'de Çalıştır"));
   kilitButton->setFlat(true);
   kilitButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");


  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(kilitButton, &QPushButton::clicked, [=]() {
    slotCommand("");
       menu->close();
});

   QPushButton *kilitAllButton= new QPushButton;
   kilitAllButton->setFixedSize(170, 30);
   kilitAllButton->setIconSize(QSize(150,30));
   kilitAllButton->setText(tr(" Tüm Pc'lerde Çalıştır"));
   kilitAllButton->setFlat(true);
   kilitAllButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");

  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(kilitAllButton, &QPushButton::clicked, [=]() {
        /* for(int i=0;i<onlinePcList.count();i++)
       {
        udpSendData("x11komut",lineEdit_message->text(),onlinePcList[i]->ip);
       }*/
        udpSendData("x11command",lineEdit_message->text(),"","",false);
        menu->close();
});

    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(kilitButton, 2,0,1,2);
   layout->addWidget(kilitAllButton, 3,0,1,2);
    // layout->addWidget(new QLabel("<font size=1>Ayarları Kaydet</font>"),6,1,1,1,Qt::AlignHCenter);
      //layout->setColumnStretch(6, 255);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

     menu->setStyleSheet("QMenu { width: 170 px; height: 60 px; }");
   return menu;
}

QMenu *MainWindow::sessionMenu()
{
    QMenu *menu = new QMenu(this);
    int yukseklik=en*14;
  /*************************************/
    QPushButton *logoutAllButton= new QPushButton;
    logoutAllButton->setFixedSize(yukseklik*1.7, yukseklik/3);
    logoutAllButton->setIconSize(QSize(yukseklik*1.7,yukseklik/3));
    logoutAllButton->setIcon(QIcon(":icons/session.svg"));
    logoutAllButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
     logoutAllButton->setText(tr("Oturumları Kapat"));
    logoutAllButton->setFlat(true);
   connect(logoutAllButton, &QPushButton::clicked, [=]() {
       slotLogoutAll();
         menu->close();
 });
   QPushButton *loginAllButton= new QPushButton;
   loginAllButton->setFixedSize(yukseklik*1.7, yukseklik/3);
   loginAllButton->setIconSize(QSize(yukseklik*1.7,yukseklik/3));
   loginAllButton->setIcon(QIcon(":icons/login.svg"));
   loginAllButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    loginAllButton->setText(tr("Oturumları Aç"));
   loginAllButton->setFlat(true);
  connect(loginAllButton, &QPushButton::clicked, [=]() {
      //slotLoginAll();
        menu->close();
});

    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
   layout->addWidget(logoutAllButton, 5,0,1,1);
   layout->addWidget(loginAllButton, 6,0,1,1);

  // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

     menu->setStyleSheet("QMenu { width: "+QString::number(yukseklik*1.7)+" px; height: "+QString::number(yukseklik/1.5) +"px; }");
   return menu;




}

QMenu *MainWindow::rdpMenu()
{   QMenu *menu = new QMenu(this);


    QPushButton *vncButton= new QPushButton;
    vncButton->setFixedSize(220, 30);
    vncButton->setIconSize(QSize(150,30));
    vncButton->setText(tr(" Vnc-Seçili Pc'ye Bağlan"));
    vncButton->setFlat(true);
    vncButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
   // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));
  //  sshpass -p 1 ssh -o StrictHostKeyChecking=no -n etapadmin@192.168.1.121 "echo 1 | sudo -S loginctl user-status Debian-gdm|grep 'State'"

    connect(vncButton, &QPushButton::clicked, [=]() {
        slotVnc("0");
        menu->close();

 });

   QPushButton *serverEkranYansitButton= new QPushButton;
   serverEkranYansitButton->setFixedSize(180, 30);
   serverEkranYansitButton->setIconSize(QSize(150,30));
   serverEkranYansitButton->setText(tr(" Ekranı Pc'lere Yansıt"));
   serverEkranYansitButton->setFlat(true);
   serverEkranYansitButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(serverEkranYansitButton, &QPushButton::clicked, [=]() {
slotVncFlipAll(ekranScale->currentText(),"-viewonly");

       menu->close();
});
   QPushButton *serverEkranYansitKapatButton= new QPushButton;
   serverEkranYansitKapatButton->setFixedSize(180, 30);
   serverEkranYansitKapatButton->setIconSize(QSize(150,30));
   serverEkranYansitKapatButton->setText(tr(" Ekran Yansıtmayı Durdur"));
   serverEkranYansitKapatButton->setFlat(true);
   serverEkranYansitKapatButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(serverEkranYansitKapatButton, &QPushButton::clicked, [=]() {
       slotVncFlipAllStop();
       menu->close();
});
   QPushButton *serverEkranYansitSeciliPcButton= new QPushButton;
   serverEkranYansitSeciliPcButton->setFixedSize(180, 30);
   serverEkranYansitSeciliPcButton->setIconSize(QSize(150,30));
   serverEkranYansitSeciliPcButton->setText(tr(" Seçili Pc'lere Yansıt"));
   serverEkranYansitSeciliPcButton->setFlat(true);
   serverEkranYansitSeciliPcButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(serverEkranYansitSeciliPcButton, &QPushButton::clicked, [=]() {
    slotVncFlip(ekranScale->currentText(),"-viewonly");
    menu->close();
});
   QPushButton *serverEkranYansitKapatSeciliPcButton= new QPushButton;
   serverEkranYansitKapatSeciliPcButton->setFixedSize(200, 30);
   serverEkranYansitKapatSeciliPcButton->setIconSize(QSize(150,30));
   serverEkranYansitKapatSeciliPcButton->setText(tr(" Seçili Pc'lerden Ynst Durdur"));
   serverEkranYansitKapatSeciliPcButton->setFlat(true);
   serverEkranYansitKapatSeciliPcButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(serverEkranYansitKapatSeciliPcButton, &QPushButton::clicked, [=]() {
     slotVncFlipStop();
       menu->close();
});

   QPushButton *rdpConnectButton= new QPushButton;
   rdpConnectButton->setFixedSize(180, 30);
   rdpConnectButton->setIconSize(QSize(150,30));
   rdpConnectButton->setText(tr(" Rdp-Seçili Pc'ye Bağlan"));
   rdpConnectButton->setFlat(true);
   rdpConnectButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(rdpConnectButton, &QPushButton::clicked, [=]() {
      slotRdp();
       menu->close();
});

    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(vncButton, 4,0,1,2);
  //  layout->addWidget(vncButton1, 5,0,1,2);

   layout->addWidget(serverEkranYansitButton, 6,0,1,2);
   layout->addWidget(serverEkranYansitKapatButton, 7,0,1,2);
   layout->addWidget(serverEkranYansitSeciliPcButton, 8,0,1,2);
   layout->addWidget(serverEkranYansitKapatSeciliPcButton, 9,0,1,2);
   layout->addWidget(rdpConnectButton, 11,0,1,2);


   // layout->addWidget(new QLabel("<font size=1>Ayarları Kaydet</font>"),6,1,1,1,Qt::AlignHCenter);
   //layout->setColumnStretch(6, 255);

   // add a widget action to the context menu
   auto wa = new QWidgetAction(this);
   //  wa->setIcon(QIcon(":/icon1"));
   wa->setDefaultWidget(widget);
   menu->addAction(wa);

   menu->setStyleSheet("QMenu { width: 200 px; height: 180 px; }");
   return menu;
}


void MainWindow::pcMenu(bool singlepc)
{
    pContextMenu = new QMenu();
    pContextMenu->setStyleSheet("width:165px; background-color: gray; font-size:"+font+"px;");
    bool wolState=false;
    if (singlepc)
    {
        //qDebug()<<"tek pc seçilmiş";
        for(int i=0;i<onlinePcList.length();i++)
        {
            if(onlinePcList[i]->mac==selectMac&&onlinePcList[i]->connectState)
              {
                wolState=true;
            //qDebug()<<btnlist[i]->ip;
            //qDebug()<<btnlist[i]->mac;
            //qDebug()<<btnlist[i]->vncport.split("-");
                QStringList vncports=onlinePcList[i]->vncport.split("-");
                if(vncports.length()>0)
                {
                    if(vncports[0]!="0"&&vncports[0]!=""){
                    QAction *pVncAction0 = new QAction(tr("Vnc Bağlan-")+vncports[0],this);
                    pVncAction0->setIcon(QIcon(":/icons/vnc.svg"));
                    pVncAction0->setIconVisibleInMenu(true);
                    connect(pVncAction0 ,SIGNAL(triggered()),this,SLOT(slotVnc0()));
                    pContextMenu->addAction(pVncAction0 );
                    }
                }

                if(vncports.length()>1)
                {
                    if(vncports[1]!="0"&&vncports[1]!=""){
                    QAction *pVncAction1 = new QAction(tr("Vnc Bağlan-")+vncports[1],this);
                    pVncAction1->setIcon(QIcon(":/icons/vnc.svg"));
                    pVncAction1->setIconVisibleInMenu(true);
                    connect(pVncAction1 ,SIGNAL(triggered()),this,SLOT(slotVnc1()));
                    pContextMenu->addAction(pVncAction1 );
                    }
                }
                if(vncports.length()>2)
                {
                    if(vncports[2]!="0"&&vncports[2]!=""){
                    QAction *pVncAction2 = new QAction(tr("Vnc Bağlan-")+vncports[2],this);
                    pVncAction2->setIcon(QIcon(":/icons/vnc.svg"));
                    pVncAction2->setIconVisibleInMenu(true);
                    connect(pVncAction2 ,SIGNAL(triggered()),this,SLOT(slotVnc2()));
                    pContextMenu->addAction(pVncAction2 );
                    }
                }

            }
        }
    }
   // else
        //qDebug()<<"çoklu pc seçilmiş";
   /* QAction *pcaptionAction = new QAction("Seçilenlere Uygula",this);
    pcaptionAction->setIconVisibleInMenu(true);
    pContextMenu->addAction(pcaptionAction );
*/
    pContextMenu->setStyleSheet("width:165px; background-color: gray; font-size:"+font+"px;");

    QAction *pPcOpenAction = new QAction(tr("Pc Aç"),this);
    pPcOpenAction->setIcon(QIcon(":/icons/wol.svg"));
    pPcOpenAction->setIconVisibleInMenu(true);
    //connect(pPcOpenAction ,SIGNAL(triggered()),this,SLOT(slotVncFlip()));
     QObject::connect(pPcOpenAction, &QAction::triggered, [&]() {

    for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState==false&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect))
        {
            ///qDebug()<<onlinePcList[i]->ip<<onlinePcList[i]->mac;
            slotWakeOnLan(onlinePcList[i]->ip,onlinePcList[i]->mac);
        }
    }
    });

    QAction *pVncFlipAction = new QAction(tr("Ekranı Yansıt"),this);
    pVncFlipAction->setIcon(QIcon(":/icons/vnc.svg"));
    pVncFlipAction->setIconVisibleInMenu(true);
    //connect(pVncFlipAction ,SIGNAL(triggered()),this,SLOT(slotVncFlip()));

    QAction *pVncFlipStopAction = new QAction(tr("Ekranı Yansıtmayı Durdur"),this);
    pVncFlipStopAction->setIcon(QIcon(":/icons/vnc.svg"));
    pVncFlipStopAction->setIconVisibleInMenu(true);
    //connect(pVncFlipStopAction ,SIGNAL(triggered()),this,SLOT(slotVncFlipStop()));

    QAction *pRdpAction = new QAction("Rdp Bağlan",this);
    pRdpAction->setIcon(QIcon(":/icons/rdp.svg"));
    pRdpAction->setIconVisibleInMenu(true);
    //connect(pRdpAction ,SIGNAL(triggered()),this,SLOT(slotRdp()));

    QAction *pFtpAction = new QAction(tr("Ftp"),this);
    pFtpAction->setIcon(QIcon(":/icons/ftp.svg"));
    pFtpAction->setIconVisibleInMenu(true);
    //connect(pFtpAction ,SIGNAL(triggered()),this,SLOT(slotFtp()));


    QAction *pKilitAction = new QAction(tr("Kilitle"),this);
    pKilitAction->setIcon(QIcon(":/icons/lock.svg"));
    pKilitAction->setIconVisibleInMenu(true);
    connect(pKilitAction ,SIGNAL(triggered()),this,SLOT(slotKilit()));

    QAction *pKilitAcAction = new QAction(tr("Kilit Aç"),this);
    pKilitAcAction->setIcon(QIcon(":/icons/unlock.svg"));
    pKilitAcAction->setIconVisibleInMenu(true);
    connect(pKilitAcAction ,SIGNAL(triggered()),this,SLOT(slotKilitAc()));

    QAction *pRebootAction = new QAction(tr("Yeniden Başlat"),this);
    pRebootAction->setIcon(QIcon(":/icons/reboot.svg"));
    pRebootAction->setIconVisibleInMenu(true);
    connect(pRebootAction ,SIGNAL(triggered()),this,SLOT(slotReboot()));

    QAction *pKapatAction = new QAction(tr("Kapat"),this);
    pKapatAction->setIcon(QIcon(":/icons/close.svg"));
    pKapatAction->setIconVisibleInMenu(true);
    connect(pKapatAction ,SIGNAL(triggered()),this,SLOT(slotPowerOff()));

    QAction *pLoginAction = new QAction(tr("Oturum Aç"),this);
    pLoginAction->setIcon(QIcon(":/icons/login.svg"));
    pLoginAction->setIconVisibleInMenu(true);
    connect(pLoginAction ,SIGNAL(triggered()),this,SLOT(slotLogin()));

    QAction *pLogoutAction = new QAction(tr("Oturum Kapat"),this);
    pLogoutAction->setIcon(QIcon(":/icons/session.svg"));
    pLogoutAction->setIconVisibleInMenu(true);
    connect(pLogoutAction ,SIGNAL(triggered()),this,SLOT(slotLogout()));

    QAction *pMesajAction = new QAction(tr("Duyuru İlet"),this);
    pMesajAction->setIcon(QIcon(":/icons/message.svg"));
    pMesajAction->setIconVisibleInMenu(true);
    //connect(pMesajAction ,SIGNAL(triggered()),this,SLOT(slotMesaj()));

    QAction *pEkranIzleAction = new QAction(tr("Ekran İzle"),this);
    pEkranIzleAction->setIcon(QIcon(":/icons/command.svg"));
    pEkranIzleAction->setIconVisibleInMenu(true);
    //connect(pEkranIzleAction ,SIGNAL(triggered()),this,SLOT(slotEkranIzle()));

    QAction *pEkranIzleDurdurAction = new QAction(tr("Ekran İzlemeyi Durdur"),this);
    pEkranIzleDurdurAction->setIcon(QIcon(":/icons/command.svg"));
    pEkranIzleDurdurAction->setIconVisibleInMenu(true);
    //connect(pEkranIzleDurdurAction ,SIGNAL(triggered()),this,SLOT(slotEkranIzleDurdur()));

    QAction *pCommandAction = new QAction(tr("Komut Çalıştır"),this);
    pCommandAction->setIcon(QIcon(":/icons/command.svg"));
    pCommandAction->setIconVisibleInMenu(true);
    //connect(pCommandAction ,SIGNAL(triggered()),this,SLOT(slotCommand()));

    QAction *pvolumeonAction = new QAction(tr("Ses Aç"),this);
    pvolumeonAction->setIcon(QIcon(":/icons/volumeon.svg"));
    pvolumeonAction->setIconVisibleInMenu(true);
    QObject::connect(pvolumeonAction, &QAction::triggered, [&]() {
         udpSendData("x11command","volumeon","","volumeon",true);
    });
    QAction *pvolumeoffAction = new QAction(tr("Ses Kapat"),this);
    pvolumeoffAction->setIcon(QIcon(":/icons/volumeoff.svg"));
    pvolumeoffAction->setIconVisibleInMenu(true);
    QObject::connect(pvolumeoffAction, &QAction::triggered, [&]() {
        udpSendData("x11command","volumeoff","","volumeoff",true);
    });
    QAction *pshowhostAction = new QAction(tr("Listeden Gizle"),this);
    pshowhostAction->setIcon(QIcon(":/icons/showhost.svg"));
    pshowhostAction->setIconVisibleInMenu(true);
     QObject::connect(pshowhostAction, &QAction::triggered, [&]() {
        bool updateState=false;
        for(int i=0;i<onlinePcList.count();i++)
        {
            if(onlinePcList[i]->mac==pcMac->text())
            {
                onlinePcList[i]->slothidePc();
                updateState=true;
            }
        }
        if(updateState) pcHideSignalSlot(pcMac->text());
        //pcListeGuncelleSlotnew("Gizlenecek");
    });


    //pContextMenu->addAction(pVncAction1 );
    // pContextMenu->addAction(pVncAction2 );
    //pContextMenu->addAction(pVncFlipAction );
    //pContextMenu->addAction(pVncFlipStopAction );
    // pContextMenu->addAction(pRdpAction );
    //pContextMenu->addAction(pFtpAction );
    /* if(!wolState)
     {

         return;
     }*/
    pContextMenu->addAction(pPcOpenAction);
    pContextMenu->addAction(pKilitAction);
    pContextMenu->addAction(pKilitAcAction );
    //pContextMenu->addAction(pEkranIzleAction );
    //pContextMenu->addAction(pEkranIzleDurdurAction );

    pContextMenu->addAction(pRebootAction );
    pContextMenu->addAction(pKapatAction );
    // pContextMenu->addAction(pLoginAction );
    pContextMenu->addAction(pLogoutAction );
    //pContextMenu->addAction(pMesajAction );
    ///pContextMenu->addAction(pshowhostAction );
    // pContextMenu->addAction(pserviceAction );
    // pContextMenu->addAction(psettingAction );
     pContextMenu->addAction(pvolumeoffAction );
    pContextMenu->addAction(pvolumeonAction );
    //btnpc->setMenu(pContextMenu);
    //btnpc->setPopupMode(QToolButton::MenuButtonPopup);
    // btnayar->setMenu(pContextMenu);
    //btnayar->setPopupMode(QToolButton::InstantPopup);

    /***************************************************************/
    //pContextMenu->exec();


}
void MainWindow::slotVnc0(){
    for(int i=0;i<onlinePcList.length();i++)
    {
        if(onlinePcList[i]->mac==selectMac)
        {
            QStringList vncports=onlinePcList[i]->vncport.split("-");
            QString komut="";
            komut.append("nohup ssvncviewer -scale 0.9 ").append(onlinePcList[i]->ip).append(":"+vncports[0]+" \-passwd \/usr\/bin\/x11vncpasswd &");
            qDebug()<<"vnc:"<<komut;
            system(komut.toStdString().c_str());
        }
    }

}
void MainWindow::slotVnc1(){
    //emit pcClickSignal(mac);//nesneler arası data transferi***
    //emit pcMenuSignal(mac,ip,"slotVnc1");
    for(int i=0;i<onlinePcList.length();i++)
    {
        if(onlinePcList[i]->mac==selectMac)
        {
            QStringList vncports=onlinePcList[i]->vncport.split("-");
    QString komut="";
    komut.append("nohup ssvncviewer -scale 0.9 ").append(onlinePcList[i]->ip).append(":"+vncports[1]+" \-passwd \/usr\/bin\/x11vncpasswd &");
    qDebug()<<"vnc:"<<komut;
    system(komut.toStdString().c_str());
        }
    }
}
void MainWindow::slotVnc2(){
    for(int i=0;i<onlinePcList.length();i++)
    {
        if(onlinePcList[i]->mac==selectMac)
        {
            QStringList vncports=onlinePcList[i]->vncport.split("-");
            QString komut="";
            komut.append("nohup ssvncviewer -scale 0.9 ").append(onlinePcList[i]->ip).append(":"+vncports[2]+" \-passwd \/usr\/bin\/x11vncpasswd &");
            qDebug()<<"vnc:"<<komut;
            system(komut.toStdString().c_str());
        }
    }
}

QMenu *MainWindow::languageMenu()
{
    QMenu *menu = new QMenu(this);
    int yukseklik=en;

    auto widget = new QWidget;
    auto layout = new QVBoxLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    /**********************************************************************************/
    // .qm dosyalarının bulunduğu dizini belirtin
    QString directory = localDir+"translations"; // Örnek olarak "./translations" dizini

    QStringList qmFiles = listQmFiles(directory);
    int dilSayisi=0;
    if (qmFiles.isEmpty()) {
        qDebug() << "Belirtilen dizinde .qm dosyası bulunamadı.";
    } else {
        //qDebug() << ".qm dosyaları:";
        for (const QString &file : qmFiles) {

            QFileInfo fi(file);
            QString name = fi.fileName();
            //qDebug() << name.split(".")[0];
            QString dil=name.split(".")[0];
            QPushButton *languageButton= new QPushButton;
            languageButton->setFixedSize(yukseklik*10, yukseklik*5);
            languageButton->setIconSize(QSize(yukseklik*10,yukseklik*5));
            //languageButton->setIcon(QIcon(":icons/login.svg"));
            languageButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
            languageButton->setText(dil);
            languageButton->setFlat(true);
            connect(languageButton, &QPushButton::clicked, [=]() {
                DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag.json");
                QJsonArray dizi=db->Ara("selectedNetworkProfil",true);
                if(dizi.count()>0)
                {
                    for (const QJsonValue &item : dizi) {
                        QJsonObject veri=item.toObject();
                        //qDebug()<<"Yüklenen Ağ Profili:" <<veri;
                        veri["language"]=languageButton->text();// önemli kısım
                        db->Sil("networkBroadCastAddress",veri["networkBroadCastAddress"].toString());
                        db->Ekle(veri);
                    }
                }
                QMessageBox msgBox;
                msgBox.setText(tr("Uygulama dilinin değişmesi için uygulamayı yeniden başlatın."));
                msgBox.exec();
            });
            //  layout->setColumnMinimumWidth(0, 37);
            layout->addWidget(languageButton);
            dilSayisi++;
        }
    }
    /*******************************************************************************/

      /*************************************/




    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
    //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

    menu->setStyleSheet("QMenu { width: "+QString::number(yukseklik*10)+" px; height: "+QString::number(yukseklik*dilSayisi*5.2) +"px; }");
    return menu;



}

QStringList MainWindow::listQmFiles(const QString &directory) {
    QDir dir(directory);
    QStringList files;

    if (!dir.exists()) {
        qDebug() << "Belirtilen dizin bulunamadı:" << directory;
        return files;
    }

    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    dir.setNameFilters(QStringList() << "*.qm");

    files = dir.entryList();
    for (int i = 0; i < files.size(); ++i) {
        files[i] = dir.absoluteFilePath(files[i]);
    }

    return files;
}
#endif // MENU_H
