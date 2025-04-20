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
QMenu *MainWindow::commandExampleMenu()
{   QMenu *menu = new QMenu(this);

   QPushButton *updateCommandButton= new QPushButton;
   updateCommandButton->setFixedSize(200, 30);
   updateCommandButton->setIconSize(QSize(200,30));
   updateCommandButton->setText(" Güncelle");
   updateCommandButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
   updateCommandButton->setFlat(true);

   connect(updateCommandButton, &QPushButton::clicked, [=]() {

       commandFileL->setText("apt-get update");
       menu->close();
});

   QPushButton *updateProblemCommandButton= new QPushButton;
   updateProblemCommandButton->setFixedSize(200, 30);
   updateProblemCommandButton->setIconSize(QSize(200,30));
   updateProblemCommandButton->setText(" Paket Problemleri Düzelt");
   updateProblemCommandButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
   updateProblemCommandButton->setFlat(true);

   connect(updateProblemCommandButton, &QPushButton::clicked, [=]() {

       commandFileL->setText("apt-get install -f");
       menu->close();
});

   QPushButton *installCommandButton= new QPushButton;
   installCommandButton->setFixedSize(200, 30);
   installCommandButton->setIconSize(QSize(200,30));
   installCommandButton->setText(" Paket Yükleme");
   installCommandButton->setStyleSheet("Text-align:left;  font-size:"+font+"px;");
   installCommandButton->setFlat(true);

   connect(installCommandButton, &QPushButton::clicked, [=]() {

       commandFileL->setText("apt-get install paket");
       menu->close();
});

   QPushButton *removeCommandButton= new QPushButton;
   removeCommandButton->setFixedSize(200, 30);
   removeCommandButton->setIconSize(QSize(200,30));
   removeCommandButton->setText(" Paket Kaldırma");
   removeCommandButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
   removeCommandButton->setFlat(true);

   connect(removeCommandButton, &QPushButton::clicked, [=]() {

       commandFileL->setText("apt-get remove paket ");
       menu->close();
});

   QPushButton *mkdirCommandButton= new QPushButton;
   mkdirCommandButton->setFixedSize(200, 30);
   mkdirCommandButton->setIconSize(QSize(200,30));
   mkdirCommandButton->setText(" Klasör Oluştur");
   mkdirCommandButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
   mkdirCommandButton->setFlat(true);

   connect(mkdirCommandButton, &QPushButton::clicked, [=]() {

       commandFileL->setText("mkdir klasor ");
       menu->close();
});
   QPushButton *rmdirCommandButton= new QPushButton;
   rmdirCommandButton->setFixedSize(200, 30);
   rmdirCommandButton->setIconSize(QSize(200,30));
   rmdirCommandButton->setText(" Klasör Sil");
   rmdirCommandButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
   rmdirCommandButton->setFlat(true);

   connect(rmdirCommandButton, &QPushButton::clicked, [=]() {

       commandFileL->setText("rmdir klasor");
       menu->close();
});
   /*************************************/
       QPushButton *sessionLoginCommandButton= new QPushButton;
       sessionLoginCommandButton->setFixedSize(200, 30);
       sessionLoginCommandButton->setIconSize(QSize(200,30));
       sessionLoginCommandButton->setText(" Oturum Aç");
       sessionLoginCommandButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
       sessionLoginCommandButton->setFlat(true);

       connect(sessionLoginCommandButton, &QPushButton::clicked, [=]() {

           commandFileL->setText("sshlogin <user> <password>");
    menu->close();
    });

   /*************************************/
       QPushButton *closePcCommandButton= new QPushButton;
       closePcCommandButton->setFixedSize(200, 30);
       closePcCommandButton->setIconSize(QSize(200,30));
       closePcCommandButton->setText(" Pc'yi Kapat");
       closePcCommandButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
       closePcCommandButton->setFlat(true);

       connect(closePcCommandButton, &QPushButton::clicked, [=]() {

           commandFileL->setText("poweroff");
    menu->close();
    });
    /*************************************************/
       QPushButton *rebootPcCommandButton= new QPushButton;
       rebootPcCommandButton->setFixedSize(200, 30);
       rebootPcCommandButton->setIconSize(QSize(200,30));
       rebootPcCommandButton->setText(" Pc'yi Yeniden Başlat");
       rebootPcCommandButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");
       rebootPcCommandButton->setFlat(true);

       connect(rebootPcCommandButton, &QPushButton::clicked, [=]() {

           commandFileL->setText("reboot");
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
QMenu *MainWindow::kilitMenu()
{
    QMenu *menu = new QMenu(this);
    int yukseklik=en*14;
  /*************************************/

    QPushButton *kilitAllButton= new QPushButton;
    kilitAllButton->setFixedSize(yukseklik*1.7, yukseklik/3);
    kilitAllButton->setIconSize(QSize(yukseklik*1.7,yukseklik/3));

    kilitAllButton->setText(" Tümünü Kilitle");
    kilitAllButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    kilitAllButton->setFlat(true);
    kilitAllButton->setIcon(QIcon(":icons/lock.svg"));

    connect(kilitAllButton, &QPushButton::clicked, [=]() {
          slotKilitAll();
        menu->close();
    });




    QPushButton *kilitAcAllButton= new QPushButton;
    kilitAcAllButton->setFixedSize(yukseklik*1.7, yukseklik/3);
    kilitAcAllButton->setIconSize(QSize(yukseklik*1.7,yukseklik/3));
     kilitAcAllButton->setText(" Tüm Kilitleri Aç");
    kilitAcAllButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    kilitAcAllButton->setFlat(true);
    kilitAcAllButton->setIcon(QIcon(":icons/unlock.svg"));

    connect(kilitAcAllButton, &QPushButton::clicked, [=]() {
        slotKilitAcAll();
        menu->close();
    });

    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
   layout->addWidget(kilitAllButton, 5,0,1,1);
  layout->addWidget(kilitAcAllButton, 6,0,1,1);

    // layout->addWidget(new QLabel("<font size=1>Ayarları Kaydet</font>"),6,1,1,1,Qt::AlignHCenter);
      //layout->setColumnStretch(6, 255);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

     menu->setStyleSheet("QMenu { width: "+QString::number(yukseklik*1.7)+" px; height: "+QString::number(yukseklik/1.5) +"px; }");
   return menu;




}

QMenu *MainWindow::transparanKilitMenu()
{
    QMenu *menu = new QMenu(this);
    int yukseklik=en*14;
  /*************************************/
    QPushButton *transparanKilitAllButton= new QPushButton;
    transparanKilitAllButton->setFixedSize(yukseklik*1.7, yukseklik/3);
    transparanKilitAllButton->setIconSize(QSize(yukseklik*1.7,yukseklik/3));
    transparanKilitAllButton->setText(" Tümünü Kilitle");
    transparanKilitAllButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    transparanKilitAllButton->setFlat(true);
    transparanKilitAllButton->setIcon(QIcon(":icons/transparanlock.svg"));

    connect(transparanKilitAllButton, &QPushButton::clicked, [=]() {
         slotTransparanKilitAll();
      menu->close();
      });



   QPushButton *transparankilitAcAllButton= new QPushButton;
   transparankilitAcAllButton->setFixedSize(yukseklik*1.7, yukseklik/3);
   transparankilitAcAllButton->setIconSize(QSize(yukseklik*1.7,yukseklik/3));
   transparankilitAcAllButton->setText(" Tüm Kilitleri Aç");
   transparankilitAcAllButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
   transparankilitAcAllButton->setFlat(true);
   transparankilitAcAllButton->setIcon(QIcon(":icons/transparanunlock.svg"));

   connect(transparankilitAcAllButton, &QPushButton::clicked, [=]() {

       slotTransparanKilitAcAll();
    menu->close();

});

    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
   // layout->addWidget(kilitButton, 2,0,1,2);
  // layout->addWidget(kilitAllButton, 3,0,1,2);
  // layout->addWidget(logoutButton, 4,0,1,2);
  layout->addWidget(transparanKilitAllButton, 5,0,1,1);
  layout->addWidget(transparankilitAcAllButton, 6,0,1,1);

    // layout->addWidget(new QLabel("<font size=1>Ayarları Kaydet</font>"),6,1,1,1,Qt::AlignHCenter);
      //layout->setColumnStretch(6, 255);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

     menu->setStyleSheet("QMenu { width: "+QString::number(yukseklik*1.7)+" px; height: "+QString::number(yukseklik/1.5) +"px; }");
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
    closeAllButton->setText("Tümünü Kapat");
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
    rebootAllButton->setText("Tümünü Y. Başlat");
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
    screenStartAll->setText("Tüm Ekranları İzle");
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
    screenStopAll->setText("İzlemeleri Durdur");
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
   kilitButton->setText(" Seçili Pc'de Çalıştır");
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
   kilitAllButton->setText(" Tüm Pc'lerde Çalıştır");
   kilitAllButton->setFlat(true);
   kilitAllButton->setStyleSheet("Text-align:left; font-size:"+font+"px;");

  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(kilitAllButton, &QPushButton::clicked, [=]() {
         for(int i=0;i<btnlist.count();i++)
       {
        udpSendData("x11komut",lineEdit_message->text(),btnlist[i]->ip);
       }
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
     logoutAllButton->setText("Oturumları Kapat");
    logoutAllButton->setFlat(true);
   connect(logoutAllButton, &QPushButton::clicked, [=]() {
       //slotLogoutAll();
         menu->close();
 });
   QPushButton *loginAllButton= new QPushButton;
   loginAllButton->setFixedSize(yukseklik*1.7, yukseklik/3);
   loginAllButton->setIconSize(QSize(yukseklik*1.7,yukseklik/3));
   loginAllButton->setIcon(QIcon(":icons/login.svg"));
   loginAllButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    loginAllButton->setText("Oturumları Aç");
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
    vncButton->setText(" Vnc-Seçili Pc'ye Bağlan");
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
   serverEkranYansitButton->setText(" Ekranı Pc'lere Yansıt");
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
   serverEkranYansitKapatButton->setText(" Ekran Yansıtmayı Durdur");
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
   serverEkranYansitSeciliPcButton->setText(" Seçili Pc'lere Yansıt");
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
   serverEkranYansitKapatSeciliPcButton->setText(" Seçili Pc'lerden Ynst Durdur");
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
   rdpConnectButton->setText(" Rdp-Seçili Pc'ye Bağlan");
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


#endif // MENU_H
