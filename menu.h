#ifndef MENU_H
#define MENU_H
#include<QWidgetAction>


QMenu *MainWindow::kilitMenu()
{   QMenu *menu = new QMenu(this);

   QPushButton *kilitButton= new QPushButton;
   kilitButton->setFixedSize(150, 30);
   kilitButton->setIconSize(QSize(150,30));
   kilitButton->setText(" Seçili Pc Kilitle");
   kilitButton->setStyleSheet("Text-align:left");
   kilitButton->setFlat(true);
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(kilitButton, &QPushButton::clicked, [=]() {


         //   tcpKomut="ekrankilit||"+remoteUsername->text()+"|"+remotePassword->text();
      // lineEdit_message->setText(komut);
       QString komut="ekrankilit|"+lineEdit_message->text()+"|"+remoteUsername->text()+"|"+remotePassword->text();
       lineEdit_message->setText(komut);

       if(socketNumberLabel->text()=="Broadcast")
       {
           socketNumberLabel->setText("");
           destlabel->setText("Hedef( )");
       }
       //socketNumberLabel->setText("Broadcast");
       //socketNumberLabel->hide();
       //destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();
       lineEdit_message->setText("");
       menu->close();
});

   QPushButton *kilitAllButton= new QPushButton;
   kilitAllButton->setFixedSize(150, 30);
   kilitAllButton->setIconSize(QSize(150,30));
   kilitAllButton->setText(" Tüm Pc'leri Kilitle");
   kilitAllButton->setStyleSheet("Text-align:left");
   kilitAllButton->setFlat(true);
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(kilitAllButton, &QPushButton::clicked, [=]() {
      // tcpKomut="ekrankilit||"+remoteUsername->text()+"|"+remotePassword->text();
       //lineEdit_message->setText(komut);
       QString komut="ekrankilit|"+lineEdit_message->text()+"|"+remoteUsername->text()+"|"+remotePassword->text();
       lineEdit_message->setText(komut);

       socketNumberLabel->setText("Broadcast");
       socketNumberLabel->hide();
       destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();
       lineEdit_message->setText("");
        menu->close();
});


   QPushButton *kilitAcButton= new QPushButton;
   kilitAcButton->setFixedSize(150, 30);
   kilitAcButton->setIconSize(QSize(150,30));
   kilitAcButton->setText(" Seçili Pc Kilit Aç");
   kilitAcButton->setStyleSheet("Text-align:left");
   kilitAcButton->setFlat(true);
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(kilitAcButton, &QPushButton::clicked, [=]() {
       tcpKomut="ekrankilitac||"+remoteUsername->text()+"|"+remotePassword->text();
      // lineEdit_message->setText(komut);
       if(socketNumberLabel->text()=="Broadcast")
       {
           socketNumberLabel->setText("");
           destlabel->setText("Hedef( )");
       }
       //socketNumberLabel->setText("Broadcast");
       //socketNumberLabel->hide();
       //destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();
        menu->close();
});

   QPushButton *kilitAcAllButton= new QPushButton;
   kilitAcAllButton->setFixedSize(150, 30);
   kilitAcAllButton->setIconSize(QSize(150,30));
   kilitAcAllButton->setText(" Tüm Pc'leri Kilit Aç");
   kilitAcAllButton->setStyleSheet("Text-align:left");
   kilitAcAllButton->setFlat(true);
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(kilitAcAllButton, &QPushButton::clicked, [=]() {
       tcpKomut="ekrankilitac||"+remoteUsername->text()+"|"+remotePassword->text();
     //  lineEdit_message->setText(komut);
       socketNumberLabel->setText("Broadcast");

       destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();
       socketNumberLabel->setText("");
       socketNumberLabel->show();
        menu->close();
});



    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(kilitButton, 2,0,1,2);
    layout->addWidget(kilitAcButton, 3,0,1,2);
    layout->addWidget(kilitAllButton, 4,0,1,2);
    layout->addWidget(kilitAcAllButton, 5,0,1,2);

    // layout->addWidget(new QLabel("<font size=1>Ayarları Kaydet</font>"),6,1,1,1,Qt::AlignHCenter);
     // layout->setColumnStretch(6, 255);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

     menu->setStyleSheet("QMenu { width: 150 px; height: 120 px; }");
   return menu;
}

QMenu *MainWindow::panoMenu()
{   QMenu *menu = new QMenu(this);

   QPushButton *panoAcButton= new QPushButton;
   panoAcButton->setFixedSize(150, 30);
   panoAcButton->setIconSize(QSize(150,30));
   panoAcButton->setText(" Seçili Pc Pano Aç");
   panoAcButton->setStyleSheet("Text-align:left");
   panoAcButton->setFlat(true);
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(panoAcButton, &QPushButton::clicked, [=]() {


         //   tcpKomut="ekrankilit||"+remoteUsername->text()+"|"+remotePassword->text();
      // lineEdit_message->setText(komut);
       QString komut="ekranpanoac|"+lineEdit_message->text()+"|"+remoteUsername->text()+"|"+remotePassword->text();
       lineEdit_message->setText(komut);

       if(socketNumberLabel->text()=="Broadcast")
       {
           socketNumberLabel->setText("");
           destlabel->setText("Hedef( )");
       }
       //socketNumberLabel->setText("Broadcast");
       //socketNumberLabel->hide();
       //destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();
       lineEdit_message->setText("");
       menu->close();
});

   QPushButton *panoAcAllButton= new QPushButton;
   panoAcAllButton->setFixedSize(150, 30);
   panoAcAllButton->setIconSize(QSize(150,30));
   panoAcAllButton->setText(" Tüm Pc'leri Pano Aç");
   panoAcAllButton->setStyleSheet("Text-align:left");
   panoAcAllButton->setFlat(true);
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(panoAcAllButton, &QPushButton::clicked, [=]() {
      // tcpKomut="ekrankilit||"+remoteUsername->text()+"|"+remotePassword->text();
       //lineEdit_message->setText(komut);
       QString komut="ekranpanoac|"+lineEdit_message->text()+"|"+remoteUsername->text()+"|"+remotePassword->text();
       lineEdit_message->setText(komut);

       socketNumberLabel->setText("Broadcast");
       socketNumberLabel->hide();
       destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();
       lineEdit_message->setText("");
        menu->close();
});


   QPushButton *panoKapatButton= new QPushButton;
   panoKapatButton->setFixedSize(150, 30);
   panoKapatButton->setIconSize(QSize(150,30));
   panoKapatButton->setText(" Seçili Pc Pano Kapat");
   panoKapatButton->setStyleSheet("Text-align:left");
   panoKapatButton->setFlat(true);
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(panoKapatButton, &QPushButton::clicked, [=]() {
       tcpKomut="ekranpanokapat||"+remoteUsername->text()+"|"+remotePassword->text();
      // lineEdit_message->setText(komut);
       if(socketNumberLabel->text()=="Broadcast")
       {
           socketNumberLabel->setText("");
           destlabel->setText("Hedef( )");
       }
       //socketNumberLabel->setText("Broadcast");
       //socketNumberLabel->hide();
       //destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();
       //lineEdit_message->setText("");
        menu->close();
});

   QPushButton *panoKapatAllButton= new QPushButton;
   panoKapatAllButton->setFixedSize(170, 30);
   panoKapatAllButton->setIconSize(QSize(150,30));
   panoKapatAllButton->setText(" Tüm Pc'lerde Pano Kapat");
   panoKapatAllButton->setStyleSheet("Text-align:left");
   panoKapatAllButton->setFlat(true);
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(panoKapatAllButton, &QPushButton::clicked, [=]() {
       tcpKomut="ekranpanokapat||"+remoteUsername->text()+"|"+remotePassword->text();
     //  lineEdit_message->setText(komut);
       socketNumberLabel->setText("Broadcast");

       destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();
       socketNumberLabel->setText("");
       socketNumberLabel->show();
        menu->close();
});



    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(panoAcButton, 2,0,1,2);
    layout->addWidget(panoAcAllButton, 3,0,1,2);
    layout->addWidget(panoKapatButton, 4,0,1,2);
    layout->addWidget(panoKapatAllButton, 5,0,1,2);

    // layout->addWidget(new QLabel("<font size=1>Ayarları Kaydet</font>"),6,1,1,1,Qt::AlignHCenter);
     // layout->setColumnStretch(6, 255);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

     menu->setStyleSheet("QMenu { width: 170 px; height: 120 px; }");
   return menu;
}


QMenu *MainWindow::kapatMenu()
{   QMenu *menu = new QMenu(this);

   QPushButton *closeButton= new QPushButton;
   closeButton->setFixedSize(180, 30);
   closeButton->setIconSize(QSize(150,30));
   closeButton->setText(" Seçili Pc Kapat");
   closeButton->setStyleSheet("Text-align:left");
   closeButton->setFlat(true);
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(closeButton, &QPushButton::clicked, [=]() {
       sshAramaButtonSlot();
      // textBrowser_receivedMessages->clear();
       // sshAramaButtonSlot();
       sshCommandSlot("init 0");
      // lineEdit_message->setText("");
       mesajSlot("Kapatma Komutu Çalıştırıldı");
        /* QString komut="pckapat|poweroff|"+remoteUsername->text()+"|"+remotePassword->text();
       lineEdit_message->setText(komut);*/
       if(socketNumberLabel->text()=="Broadcast")
       {
           socketNumberLabel->setText("");
           destlabel->setText("Hedef( )");

       }
     //  socketNumberLabel->setText("Broadcast");
      // socketNumberLabel->hide();
      // destlabel->setText("Hedef(Broadcast)");
      // sendMessageInit();
       menu->close();
});

   QPushButton *closeAllButton= new QPushButton;
   closeAllButton->setFixedSize(180, 30);
   closeAllButton->setIconSize(QSize(150,30));
   closeAllButton->setText(" Tüm Pc'leri Kapat");
   closeAllButton->setStyleSheet("Text-align:left");
   closeAllButton->setFlat(true);
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(closeAllButton, &QPushButton::clicked, [=]() {
       sshAramaButtonSlot();
       sshCommandAllSlot("init 0");
       mesajSlot("Komut Ağ'da Çalıştırıldı");
      /* QString komut="pckapat|poweroff|"+remoteUsername->text()+"|"+remotePassword->text();
       lineEdit_message->setText(komut);
       socketNumberLabel->setText("Broadcast");
       socketNumberLabel->hide();
       destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();*/
       menu->close();
});


   QPushButton *rebootButton= new QPushButton;
   rebootButton->setFixedSize(180, 30);
   rebootButton->setIconSize(QSize(150,30));
   rebootButton->setText(" Seçili Pc Yeniden Başlat");
   rebootButton->setStyleSheet("Text-align:left");
   rebootButton->setFlat(true);
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(rebootButton, &QPushButton::clicked, [=]() {
       sshAramaButtonSlot();
       sshCommandSlot("init 6");
       //lineEdit_message->setText("");
       mesajSlot("Komut Çalıştırıldı");

      /* QString komut="pckapat|poweroff|"+remoteUsername->text()+"|"+remotePassword->text();
       lineEdit_message->setText(komut);*/
       if(socketNumberLabel->text()=="Broadcast")
       {
           socketNumberLabel->setText("");
           destlabel->setText("Hedef( )");

       }
      /* QString komut="pcbaslat|reboot|"+remoteUsername->text()+"|"+remotePassword->text();
       lineEdit_message->setText(komut);
       if(socketNumberLabel->text()=="Broadcast")
       {
           socketNumberLabel->setText("");
           destlabel->setText("Hedef( )");
       }
     //  socketNumberLabel->setText("Broadcast");
      // socketNumberLabel->hide();
      // destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();*/

        menu->close();
});

   QPushButton *rebootAllButton= new QPushButton;
   rebootAllButton->setFixedSize(180, 30);
   rebootAllButton->setIconSize(QSize(150,30));
   rebootAllButton->setText(" Tüm Pc'leri Yeniden Başlat");
   rebootAllButton->setStyleSheet("Text-align:left");
   rebootAllButton->setFlat(true);
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(rebootAllButton, &QPushButton::clicked, [=]() {
       sshAramaButtonSlot();
       sshCommandAllSlot("init 6");
       mesajSlot("Komut Ağ'da Çalıştırıldı");

      /* QString komut="pcbaslat|reboot|"+remoteUsername->text()+"|"+remotePassword->text();
       lineEdit_message->setText(komut);
       socketNumberLabel->setText("Broadcast");
       socketNumberLabel->hide();
       destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();*/
        menu->close();
});
    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(closeButton, 2,1,1,2);
    layout->addWidget(closeAllButton, 3,1,1,2);
    layout->addWidget(rebootButton, 4,1,1,2);
    layout->addWidget(rebootAllButton, 5,1,1,2);

    // layout->addWidget(new QLabel("<font size=1>Ayarları Kaydet</font>"),6,1,1,1,Qt::AlignHCenter);
      //layout->setColumnStretch(6, 255);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

     menu->setStyleSheet("QMenu { width: 180 px; height: 120 px; }");
   return menu;
}

QMenu *MainWindow::duyuruMesajMenu()
{   QMenu *menu = new QMenu(this);

   QPushButton *selectPcDuyuruButton= new QPushButton;
   selectPcDuyuruButton->setFixedSize(170, 30);
   selectPcDuyuruButton->setIconSize(QSize(150,30));
   selectPcDuyuruButton->setText(" Seçili Pc'ye Duyuru");
     selectPcDuyuruButton->setStyleSheet("Text-align:left");
   selectPcDuyuruButton->setFlat(true);
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(selectPcDuyuruButton, &QPushButton::clicked, [=]() {
       QString komut="ekranmesaj|"+lineEdit_message->text()+"|"+remoteUsername->text()+"|"+remotePassword->text();
       lineEdit_message->setText(komut);
       if(socketNumberLabel->text()=="Broadcast")
       {
           socketNumberLabel->setText("");
           destlabel->setText("Hedef( )");
       }
      // socketNumberLabel->setText("Broadcast");
      // socketNumberLabel->hide();
       //destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();
       lineEdit_message->setText("");
        menu->close();
});

   QPushButton *selectPcDuyuruAllButton= new QPushButton;
   selectPcDuyuruAllButton->setFixedSize(170, 30);
   selectPcDuyuruAllButton->setIconSize(QSize(150,30));
   selectPcDuyuruAllButton->setText(" Tüm Pc'lere Duyuru");
   selectPcDuyuruAllButton->setFlat(true);
     selectPcDuyuruAllButton->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(selectPcDuyuruAllButton, &QPushButton::clicked, [=]() {
       QString komut="ekranmesaj|"+lineEdit_message->text()+"|"+remoteUsername->text()+"|"+remotePassword->text();
       lineEdit_message->setText(komut);
       socketNumberLabel->setText("Broadcast");
       socketNumberLabel->hide();
       destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();
       lineEdit_message->setText("");
       menu->close();
});

   QPushButton *selectPcMesajButton= new QPushButton;
   selectPcMesajButton->setFixedSize(170, 30);
   selectPcMesajButton->setIconSize(QSize(150,30));
   selectPcMesajButton->setText(" Seçili Pc'ye Mesaj");
   selectPcMesajButton->setFlat(true);
     selectPcMesajButton->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(selectPcMesajButton, &QPushButton::clicked, [=]() {
       QString komut="mesaj|"+lineEdit_message->text();
       lineEdit_message->setText(komut);
       if(socketNumberLabel->text()=="Broadcast")
       {
           socketNumberLabel->setText("");
           destlabel->setText("Hedef( )");
       }
       //socketNumberLabel->setText("Broadcast");
       //socketNumberLabel->hide();
       //destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();
       lineEdit_message->setText("");
       menu->close();
});

   QPushButton *selectPcMesajAllButton= new QPushButton;
   selectPcMesajAllButton->setFixedSize(170, 30);
   selectPcMesajAllButton->setIconSize(QSize(150,30));
   selectPcMesajAllButton->setText(" Tüm Pc'lere Mesaj");
   selectPcMesajAllButton->setFlat(true);
     selectPcMesajAllButton->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(selectPcMesajAllButton, &QPushButton::clicked, [=]() {
       QString komut="mesaj|"+lineEdit_message->text();
       lineEdit_message->setText(komut);
       socketNumberLabel->setText("Broadcast");
       socketNumberLabel->hide();
       destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();
       lineEdit_message->setText("");
       menu->close();
});
    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(selectPcDuyuruButton, 2,0,1,2);
    layout->addWidget(selectPcDuyuruAllButton, 3,0,1,2);
  //  layout->addWidget(selectPcMesajButton, 4,0,1,2);
   // layout->addWidget(selectPcMesajAllButton, 5,0,1,2);

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

QMenu *MainWindow::ekranImageMenu()
{   QMenu *menu = new QMenu(this);

   QPushButton *selectPcScreenStart= new QPushButton;
   selectPcScreenStart->setFixedSize(190, 30);
   selectPcScreenStart->setIconSize(QSize(150,30));
   selectPcScreenStart->setText(" Seçili Ekranı İzle");
   selectPcScreenStart->setFlat(true);
   selectPcScreenStart->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(selectPcScreenStart, &QPushButton::clicked, [=]() {
     timerEkranImage->start(5000);//image tetikleniyor
     pcEkranImageStatus=true;
    // ekranImage();
     if(socketNumberLabel->text()=="Broadcast")
     {
         socketNumberLabel->setText("");
         destlabel->setText("Hedef( )");
     }
        menu->close();
});

   QPushButton *selectPcScreenStop= new QPushButton;
   selectPcScreenStop->setFixedSize(190, 30);
   selectPcScreenStop->setIconSize(QSize(150,30));
   selectPcScreenStop->setText(" Seçili Ekran İzlemeyi Durdur");
   selectPcScreenStop->setFlat(true);
   selectPcScreenStop->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(selectPcScreenStop, &QPushButton::clicked, [=]() {
     timerEkranImage->stop();
     pcEkranImageStatus=false;
     //ekranImage();
     if(socketNumberLabel->text()=="Broadcast")
     {
         socketNumberLabel->setText("");
         destlabel->setText("Hedef( )");
     }
        menu->close();
});

   QPushButton *selectPcScreenStartAll= new QPushButton;
   selectPcScreenStartAll->setFixedSize(190, 30);
   selectPcScreenStartAll->setIconSize(QSize(150,30));
   selectPcScreenStartAll->setText(" Tüm Ekranları İzle");
  selectPcScreenStartAll->setFlat(true);
  selectPcScreenStartAll->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(selectPcScreenStartAll, &QPushButton::clicked, [=]() {
        timerEkranImageAll->start(5000);
        pcEkranImageAllStatus=true;
        menu->close();
});

   QPushButton *selectPcScreenStopAll= new QPushButton;
   selectPcScreenStopAll->setFixedSize(190, 30);
   selectPcScreenStopAll->setIconSize(QSize(150,30));
   selectPcScreenStopAll->setText(" Ekranları İzlemeyi Durdur");
   selectPcScreenStopAll->setFlat(true);
   selectPcScreenStopAll->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(selectPcScreenStopAll, &QPushButton::clicked, [=]() {
        timerEkranImageAll->stop();
        pcEkranImageAllStatus=false;
        menu->close();
});

    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(selectPcScreenStart, 1,0,1,2);
    layout->addWidget(selectPcScreenStop, 2,0,1,2);
    layout->addWidget(selectPcScreenStartAll, 3,0,1,2);
    layout->addWidget(selectPcScreenStopAll, 4,0,1,2);

    // layout->addWidget(new QLabel("<font size=1>Ayarları Kaydet</font>"),6,1,1,1,Qt::AlignHCenter);
      //layout->setColumnStretch(6, 255);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

     menu->setStyleSheet("QMenu { width: 190 px; height: 120 px; }");
   return menu;
}

void MainWindow::ekranImage()
{

  tcpKomut="ekranimage||"+localUsername->text()+"|"+localPassword->text()+"|"+socketNumberLabel->text();
    sendMessageInit();
    QStringList list=fileToList("iplistname");

      QString line=listGetLine(list,pcMac->text());
     // qDebug()<<line;
   /*  if (line!="")
     {
         for(int i=0;i<btnlist.count();i++)
                {

                    if(btnlist[i]->toolTip()== pcMac->text())
                       {


                   ///  btnlist[i]->setIcon(QIcon(image));


                                   }
                }
     }
*/   QString filename=line.split("|")[9]+".png";
   //   QPixmap image =  QPixmap(QDir::homePath()+"/"+filename);
     // qDebug()<<QDir::homePath()+"/"+filename;
       pcButtonGuncelleSlot(line.split("|")[1],true,QDir::homePath()+"/"+filename,false);
}

void MainWindow::ekranImageAll()
{
    QStringList list=fileToList("iplistname");


    for(int j=0;j<list.count();j++)
    {
        QString line=list[j];
        //   qDebug()<<line;
        if (line!="")
        {
            if(line.split("|")[6]=="online")
            {
                socketNumberLabel->setText(line.split("|")[9]);
                tcpKomut="ekranimage||"+localUsername->text()+"|"+localPassword->text()+"|"+socketNumberLabel->text();
                sendMessageInit();
            }
        }
    }
    for(int i=0;i<btnlist.count();i++)
    {

        for(int j=0;j<list.count();j++)
        {
            QString line=list[j];
            //qDebug()<<line;
            if (line!="")
            {
                if(line.split("|")[6]=="online")
                {
                    if(btnlist[i]->toolTip()== line.split("|")[1]) //mac adresi eşleştriliyor
                    {
                        // QPixmap image =  QPixmap(QDir::homePath()+"/"+line.split("|")[7]+".png"); //socket numarası eşleştiriliyor
                        ///   btnlist[i]->setIcon(QIcon(image));
                        pcButtonGuncelleSlot(line.split("|")[1],true, QDir::homePath()+"/"+line.split("|")[9]+".png",false);
                    }
                }
            }
        }
    }

}

QMenu *MainWindow::komutMenu()
{   QMenu *menu = new QMenu(this);

   QPushButton *kilitButton= new QPushButton;
   kilitButton->setFixedSize(170, 30);
   kilitButton->setIconSize(QSize(150,30));
   kilitButton->setText(" Seçili Pc'de Çalıştır");
   kilitButton->setFlat(true);
   kilitButton->setStyleSheet("Text-align:left");


  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(kilitButton, &QPushButton::clicked, [=]() {
       QString komut="komut|"+lineEdit_message->text()+"|"+remoteUsername->text()+"|"+remotePassword->text();
       lineEdit_message->setText(komut);
       if(socketNumberLabel->text()=="Broadcast")
       {
           socketNumberLabel->setText("");
           destlabel->setText("Hedef( )");
       }
       //socketNumberLabel->setText("Broadcast");
       //socketNumberLabel->hide();
       //destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();
       textBrowser_receivedMessages->clear();

      // commandExecuteSlot();
        menu->close();
});

   QPushButton *kilitAllButton= new QPushButton;
   kilitAllButton->setFixedSize(170, 30);
   kilitAllButton->setIconSize(QSize(150,30));
   kilitAllButton->setText(" Tüm Pc'lerde Çalıştır");
   kilitAllButton->setFlat(true);
   kilitAllButton->setStyleSheet("Text-align:left");

  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(kilitAllButton, &QPushButton::clicked, [=]() {
       QString komut="komut|"+lineEdit_message->text()+"|"+remoteUsername->text()+"|"+remotePassword->text();
       lineEdit_message->setText(komut);
       socketNumberLabel->setText("Broadcast");
       socketNumberLabel->hide();
       destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();

       //commandExecuteAllSlot();
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

QMenu *MainWindow::taramaMenu()
{   QMenu *menu = new QMenu(this);

   QPushButton *agTaramaButton= new QPushButton;
   agTaramaButton->setFixedSize(150, 30);
   agTaramaButton->setIconSize(QSize(150,30));
   agTaramaButton->setText(" Açık Pc Tara");
   agTaramaButton->setFlat(true);
   agTaramaButton->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(agTaramaButton, &QPushButton::clicked, [=]() {
     agTaraButtonSlot();
        menu->close();
});

   QPushButton *sshTaramaButton= new QPushButton;
   sshTaramaButton->setFixedSize(150, 30);
   sshTaramaButton->setIconSize(QSize(150,30));
   sshTaramaButton->setText(" ssh Servisli Pc Tara");
   sshTaramaButton->setFlat(true);
   sshTaramaButton->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(sshTaramaButton, &QPushButton::clicked, [=]() {
     sshAramaButtonSlot();
        menu->close();
});

   QPushButton *vncTaramaButton= new QPushButton;
   vncTaramaButton->setFixedSize(150, 30);
   vncTaramaButton->setIconSize(QSize(150,30));
   vncTaramaButton->setText(" vnc Servisli Pc Tara");
   vncTaramaButton->setFlat(true);
   vncTaramaButton->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(vncTaramaButton, &QPushButton::clicked, [=]() {
      vncAramaButtonSlot();
        menu->close();
});


   QPushButton *ftpTaramaButton= new QPushButton;
   ftpTaramaButton->setFixedSize(150, 30);
   ftpTaramaButton->setIconSize(QSize(150,30));
   ftpTaramaButton->setText(" ftp Servisli Pc Tara");
   ftpTaramaButton->setFlat(true);
   ftpTaramaButton->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(ftpTaramaButton, &QPushButton::clicked, [=]() {

       QString kmt="nohup rm /home/"+QDir::homePath()+"/.ssh/known_hosts &";

           system(kmt.toStdString().c_str());

      ftpAramaButtonSlot();
        menu->close();
});

   QPushButton *clientCloseButton= new QPushButton;
   clientCloseButton->setFixedSize(150, 30);
   clientCloseButton->setIconSize(QSize(150,30));
   clientCloseButton->setText(" Tüm Client'ları Kapat");
   clientCloseButton->setFlat(true);
   clientCloseButton->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(clientCloseButton, &QPushButton::clicked, [=]() {
      //ftpAramaButtonSlot();
       sshCommandAllSlot("killall Client");

        menu->close();
});


   QPushButton *clientStartButton= new QPushButton;
   clientStartButton->setFixedSize(150, 30);
   clientStartButton->setIconSize(QSize(150,30));
   clientStartButton->setText(" Tüm Client'ları Başlat");
   clientStartButton->setFlat(true);
   clientStartButton->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(clientStartButton, &QPushButton::clicked, [=]() {
      //ftpAramaButtonSlot();

       sshCommandAllSlot("Client");
//lst[2].toStdString().c_str()
        menu->close();
});

   QPushButton *clienthostportCopyButton= new QPushButton;
   clienthostportCopyButton->setFixedSize(160, 30);
   clienthostportCopyButton->setIconSize(QSize(150,30));
   clienthostportCopyButton->setText(" Client Ayarlarını Güncelle");
   clienthostportCopyButton->setFlat(true);
   clienthostportCopyButton->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(clienthostportCopyButton, &QPushButton::clicked, [=]() {
      //
     //  qDebug()<<QDir::homePath();
      // .toStdString().c_str()
       QString kmt="rm "+QDir::homePath()+"/.ssh/known_hosts";
        //   system(kmt.toStdString().c_str());
        //  system("sleep 1");
       sshCommandAllSlot("nohup chmod 777 /usr/share/E-Ag/*&");
       sshCommandAllSlot("systemctl restart E-AgClient.service");

//system("sleep 2");
       fileHostportCopyAllSlot();
        menu->close();
});


      auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(agTaramaButton, 2,0,1,2);
   layout->addWidget(sshTaramaButton, 3,0,1,2);
   layout->addWidget(vncTaramaButton, 4,0,1,2);
   layout->addWidget(ftpTaramaButton, 5,0,1,2);
   layout->addWidget(clienthostportCopyButton, 12,0,1,2);

    // layout->addWidget(new QLabel("<font size=1>Ayarları Kaydet</font>"),6,1,1,1,Qt::AlignHCenter);
      //layout->setColumnStretch(6, 255);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

     menu->setStyleSheet("QMenu { width: 170 px; height: 155 px; }");
   return menu;
}

QMenu *MainWindow::rdpMenu()
{   QMenu *menu = new QMenu(this);


    QPushButton *vncButton= new QPushButton;
    vncButton->setFixedSize(220, 30);
    vncButton->setIconSize(QSize(150,30));
    vncButton->setText(" Vnc-Seçili Pc'ye Bağlan(Login)");
    vncButton->setFlat(true);
    vncButton->setStyleSheet("Text-align:left");
   // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

    connect(vncButton, &QPushButton::clicked, [=]() {
        QString  komut;
        komut.append("nohup vncviewer ").append(pcIp->text()).append(":0 \-passwd \/usr\/bin\/x11vncpasswd &");
     system(komut.toStdString().c_str());

        menu->close();
 });
    QPushButton *vncButton1= new QPushButton;
    vncButton1->setFixedSize(220, 30);
    vncButton1->setIconSize(QSize(150,30));
    vncButton1->setText(" Vnc-Seçili Pc'ye Bağlan(Desktop)");
    vncButton1->setFlat(true);
    vncButton1->setStyleSheet("Text-align:left");
   // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

    connect(vncButton1, &QPushButton::clicked, [=]() {
        QString  komut;
        komut.append("nohup vncviewer ").append(pcIp->text()).append(":1 \-passwd \/usr\/bin\/x11vncpasswd &");
     system(komut.toStdString().c_str());

        menu->close();
 });

   QPushButton *serverEkranYansitButton= new QPushButton;
   serverEkranYansitButton->setFixedSize(180, 30);
   serverEkranYansitButton->setIconSize(QSize(150,30));
   serverEkranYansitButton->setText(" Ekranı Pc'lere Yansıt");
   serverEkranYansitButton->setFlat(true);
   serverEkranYansitButton->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(serverEkranYansitButton, &QPushButton::clicked, [=]() {
      // sshCommandAllSlot("/usr/bin/E-AgRunPrg.sh");
       hostAddressMacButtonSlot();
       QString  kmt;
       kmt.append("vncviewer ").append(myIpAddress).append(" \-passwd \/usr\/bin\/x11vncpasswd");

       QString komut="komut|"+kmt+"|"+remoteUsername->text()+"|"+remotePassword->text();
       lineEdit_message->setText(komut);
       socketNumberLabel->setText("Broadcast");
       socketNumberLabel->hide();
       destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();

       menu->close();
});
   QPushButton *serverEkranYansitKapatButton= new QPushButton;
   serverEkranYansitKapatButton->setFixedSize(180, 30);
   serverEkranYansitKapatButton->setIconSize(QSize(150,30));
   serverEkranYansitKapatButton->setText(" Ekran Yansıtmayı Durdur");
   serverEkranYansitKapatButton->setFlat(true);
   serverEkranYansitKapatButton->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(serverEkranYansitKapatButton, &QPushButton::clicked, [=]() {
        QString  kmt;
        kmt.append("killall vncviewer");

       QString komut="komut|"+kmt+"|"+remoteUsername->text()+"|"+remotePassword->text();
       lineEdit_message->setText(komut);
       socketNumberLabel->setText("Broadcast");
       socketNumberLabel->hide();
       destlabel->setText("Hedef(Broadcast)");
       sendMessageInit();

       menu->close();
});
   QPushButton *serverEkranYansitSeciliPcButton= new QPushButton;
   serverEkranYansitSeciliPcButton->setFixedSize(180, 30);
   serverEkranYansitSeciliPcButton->setIconSize(QSize(150,30));
   serverEkranYansitSeciliPcButton->setText(" Ekranı Seçili Pc'ye Yansıt");
   serverEkranYansitSeciliPcButton->setFlat(true);
   serverEkranYansitSeciliPcButton->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(serverEkranYansitSeciliPcButton, &QPushButton::clicked, [=]() {
        hostAddressMacButtonSlot();
        QString  kmt;
        kmt.append("vncviewer ").append(myIpAddress).append(" \-passwd \/usr\/bin\/x11vncpasswd");
        QString komut="komut|"+kmt+"|"+remoteUsername->text()+"|"+remotePassword->text();
        lineEdit_message->setText(komut);
        if(socketNumberLabel->text()=="Broadcast")
        {
            socketNumberLabel->setText("");
            destlabel->setText("Hedef( )");
        }
        //socketNumberLabel->setText("Broadcast");
        //socketNumberLabel->hide();
        //destlabel->setText("Hedef(Broadcast)");
        sendMessageInit();
        textBrowser_receivedMessages->clear();

       menu->close();
});
   QPushButton *serverEkranYansitKapatSeciliPcButton= new QPushButton;
   serverEkranYansitKapatSeciliPcButton->setFixedSize(180, 30);
   serverEkranYansitKapatSeciliPcButton->setIconSize(QSize(150,30));
   serverEkranYansitKapatSeciliPcButton->setText(" Ek. Yan. Seç. Pc Durdur");
   serverEkranYansitKapatSeciliPcButton->setFlat(true);
   serverEkranYansitKapatSeciliPcButton->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(serverEkranYansitKapatSeciliPcButton, &QPushButton::clicked, [=]() {
        QString  kmt;
        kmt.append("killall vncviewer");

        QString komut="komut|"+kmt+"|"+remoteUsername->text()+"|"+remotePassword->text();
        lineEdit_message->setText(komut);
        if(socketNumberLabel->text()=="Broadcast")
        {
            socketNumberLabel->setText("");
            destlabel->setText("Hedef( )");
        }
        //socketNumberLabel->setText("Broadcast");
        //socketNumberLabel->hide();
        //destlabel->setText("Hedef(Broadcast)");
        sendMessageInit();
        textBrowser_receivedMessages->clear();

       menu->close();
});

   QPushButton *rdpConnectButton= new QPushButton;
   rdpConnectButton->setFixedSize(180, 30);
   rdpConnectButton->setIconSize(QSize(150,30));
   rdpConnectButton->setText(" Seçili Pc'ye rdp Bağlan");
   rdpConnectButton->setFlat(true);
   rdpConnectButton->setStyleSheet("Text-align:left");
  // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(rdpConnectButton, &QPushButton::clicked, [=]() {
        hostAddressMacButtonSlot();
        QString  komut;
        komut.append("nohup rdesktop ").append(" -u ").append(remoteUsername->text()).append(" -p ").append(remotePassword->text()+" ").append(pcIp->text()).append(" -g 75% &");
     system(komut.toStdString().c_str());

qDebug()<<komut;
       menu->close();
});

    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(vncButton, 4,0,1,2);
    layout->addWidget(vncButton1, 5,0,1,2);

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

     menu->setStyleSheet("QMenu { width: 220 px; height: 210 px; }");
   return menu;
}

#endif // MENU_H
