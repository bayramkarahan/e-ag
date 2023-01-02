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
#ifndef BUTONCLICK_H
#define BUTONCLICK_H
#include<QAbstractButton>
#include<QTableWidget>
#include<QApplication>
#include<QDesktopServices>
void MainWindow::ayarKaydetButtonSlot()
{
    QString kmt23="echo "+localPassword+"|sudo -S mkdir /usr/share/e-ag > /dev/null 2>&1";
    system(kmt23.toStdString().c_str());
    QString kmt24="echo "+localPassword+"|sudo -S chmod 777 /usr/share/e-ag";
    system(kmt24.toStdString().c_str());


    QString kmt26="echo "+localPassword+"|sudo -S chmod 777 /usr/share/e-ag/*";
    system(kmt26.toStdString().c_str());


    hostAddressMacButtonSlot();
    QStringList ayar;
    QString ru="remoteUser|"+remoteUserName+"|"+remotePassword;
    QString lu="localUser|"+localUserName+"|"+localPassword;
    QString rn1="broadCastAddress1|"+broadCastAddress1;
    QString rn2="broadCastAddress2|"+broadCastAddress2;

    QString tcp="tcpPort|"+tcpPort;
    QString webstate="webblockstate|"+QString::number(webblockstate);
    ayar<<ru<<lu<<rn1<<rn2<<tcp<<webstate;
    listToFile(ayar,"e-ag.conf");



  }
void MainWindow::wolSlot()
{
   // qDebug()<<"ayar click";
    QDialog * d = new QDialog();
    d->setWindowTitle("Kapalı Host Listesi");
    d->setFixedSize(QSize(boy*100,boy*100));
    d->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    auto appIcon = QIcon(":/icons/e-ag.svg");
    d->setWindowIcon(appIcon);

    /***********************************************************************/
   twl=new QTableWidget;

    twl->setFixedSize(QSize(boy*95,boy*75));
    twl->setColumnCount(4);
    //twl->setRowCount(0);

    twl->setHorizontalHeaderItem(0, new QTableWidgetItem("Seç"));
    twl->setHorizontalHeaderItem(1, new QTableWidgetItem("Ip"));
    twl->setHorizontalHeaderItem(2, new QTableWidgetItem("Mac"));
    twl->setHorizontalHeaderItem(3, new QTableWidgetItem("Adı"));

    twl->setSelectionBehavior(QAbstractItemView::SelectRows);
    twl->setSelectionMode(QAbstractItemView::SingleSelection);
    //connect(tw, &QTableWidget::cellClicked, this, cellClicked());
    twl->setRowCount(0);
    twl->setColumnWidth(0, boy*5);
    twl->setColumnWidth(1, boy*25);
    twl->setColumnWidth(2,boy*30);
    twl->setColumnWidth(3,boy*30);
    ///iptal QStringList iplist=fileToList("iplistname");
 QStringList iplist=PcData::onlinePcListe;

    QStringList list=fileToList("persistlist",localDir);
    int sr=0;
    for(int i=0;i<list.count();i++)
    {
        QString line=list[i];
        QStringList lst=line.split("|");
        if(lst[0]!=""&&lst[1]!="")
        {
            QString result=listGetLine(iplist,lst[1]);

            if ((result!="")&&result.split("|")[6]!="online"||result=="")
            {
                twl->setRowCount(twl->rowCount()+1);
                QCheckBox *mCheck = new QCheckBox();
                mCheck->setChecked(false);
                twl->setCellWidget(sr,0,mCheck);

                twl->setItem(sr, 1, new QTableWidgetItem(lst[0]));//ip
                twl->setItem(sr, 2, new QTableWidgetItem(lst[1]));//mac
                twl->setItem(sr, 3, new QTableWidgetItem(lst[7]));//name
                sr++;
            }
        }

    }
          /********************************************************************/
        QToolButton *powerOnButton= new QToolButton;
        powerOnButton->setFixedSize(QSize(boy*40,boy*10));
        powerOnButton->setIconSize(QSize(boy*40,boy*5));
        powerOnButton->setStyleSheet("Text-align:center");
        powerOnButton->setIcon(QIcon(":/icons/boot.svg"));
        powerOnButton->setAutoRaise(true);
        powerOnButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        // powerOnButton->setFont(f2);
        powerOnButton->setText("Seçili Pc'leri Aç");

        connect(powerOnButton, &QPushButton::clicked, [=]() {
            int numRows = twl->rowCount();

            for ( int i = 0 ; i < numRows ; i++)
            {

                QCheckBox* mBox = static_cast<QCheckBox*> (twl->cellWidget(i,0));
                 if (mBox->isChecked())
                {
                     QString _ip = twl->model()->data(twl->model()->index(i, 1)).toString().simplified();
                     QString _mac = twl->model()->data(twl->model()->index(i, 2)).toString().simplified();
                     QString ad = twl->model()->data(twl->model()->index(i, 3)).toString().simplified();
                   // qDebug()<<i<<mBox->isChecked()<<_ip<<_mac<<ad;

                      slotWakeOnLan(_ip,_mac);
                }
            }

        });
        /*********************************************************************/
        /********************************************************************/
      QToolButton *powerOnButtonAll= new QToolButton;
      powerOnButtonAll->setFixedSize(QSize(boy*40,boy*10));
      powerOnButtonAll->setIconSize(QSize(boy*40,boy*5));
      powerOnButtonAll->setStyleSheet("Text-align:center");
      powerOnButtonAll->setIcon(QIcon(":/icons/boot.svg"));
      powerOnButtonAll->setAutoRaise(true);
      powerOnButtonAll->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
      // powerOnButtonAll->setFont(f2);
      powerOnButtonAll->setText("Tüm Pc'leri Aç");

      connect(powerOnButtonAll, &QPushButton::clicked, [=]() {
          int numRows = twl->rowCount();
          for ( int i = 0 ; i < numRows ; i++)
          {
              QString _ip = twl->model()->data(twl->model()->index(i, 1)).toString().simplified();
              QString _mac = twl->model()->data(twl->model()->index(i, 2)).toString().simplified();
              // QString ad = twl->model()->data(twl->model()->index(i, 3)).toString().simplified();
              // qDebug()<<i<<mBox->isChecked()<<ip<<mac<<ad;
              slotWakeOnLan(_ip,_mac);
          }
      });
      /*********************************************************************/

        QVBoxLayout * vbox = new QVBoxLayout();
        vbox->addWidget(twl);
        QHBoxLayout * hbox = new QHBoxLayout();
        hbox->addWidget(powerOnButton);
        hbox->addWidget(powerOnButtonAll);
        vbox->addLayout(hbox);

        d->setLayout(vbox);
        d->exec();


}
void MainWindow::webBlockSlot()
{
   // qDebug()<<"ayar click";
    QDialog * d = new QDialog();
    d->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    auto appIcon = QIcon(":/icons/e-ag.svg");
    d->setWindowIcon(appIcon);
    d->setWindowTitle("Web Engelleme Listesi");
    d->setFixedSize(en*55,en*65);

    QLineEdit * webadres = new QLineEdit();
    webadres->setFixedSize(en*50,en*6);

    QLabel *webadresLabel=new QLabel("Web Site Adresleri");
    QToolButton *webadresEkleButton= new QToolButton;
    webadresEkleButton->setFixedSize(QSize(en*50,en*6));
    webadresEkleButton->setIconSize(QSize(en*50,en*3));
    webadresEkleButton->setStyleSheet("Text-align:center");
  //  webadresEkleButton->setIcon(QIcon(":/icons/save.svg"));
    webadresEkleButton->setAutoRaise(true);
    webadresEkleButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //webadresEkleButton->setFont(f2);
    webadresEkleButton->setText("Web Listesine Kaydet");

    connect(webadresEkleButton, &QPushButton::clicked, [=]() {
        QStringList webblocklist=fileToList("webblocklist",localDir);

            webblocklist<<webadres->text();

        listToFile(webblocklist,"webblocklist");
        for(int i=0;i<webblocklist.count();i++)
        {
            QString line=webblocklist[i];
            QStringList lst=line.split("|");
            twl->setRowCount(i+1);
            twl->setItem(i, 0, new QTableWidgetItem(lst[0]));//ip

        }

});

    /***********************************************************************/
   twl=new QTableWidget;
    twl->setFixedSize(QSize(en*50,en*25));
    twl->setColumnCount(1);
    //twl->setRowCount(0);
    twl->setColumnWidth(0, en*50);

    twl->setHorizontalHeaderItem(0, new QTableWidgetItem("Web Adresi"));
    twl->setSelectionBehavior(QAbstractItemView::SelectRows);
    twl->setSelectionMode(QAbstractItemView::SingleSelection);
    //connect(tw, &QTableWidget::cellClicked, this, cellClicked());
    connect(twl, SIGNAL(cellDoubleClicked(int,int)),SLOT(webTableCellDoubleClicked(int,int)));
    twl->setRowCount(0);
    QStringList list=fileToList("webblocklist",localDir);
    for(int i=0;i<list.count();i++)
    {
        QString line=list[i];
        QStringList lst=line.split("|");
        twl->setRowCount(twl->rowCount()+1);
        twl->setItem(i, 0, new QTableWidgetItem(lst[0]));//ip

    }

    /**********************************************************/
       /* if(webblockstate)
        {
           // QString strwebblockstate=listGetLine(list,"webblockstate").split("|")[1];
            //qDebug()<<strwebblockstate;
            webblockstate=strwebblockstate.toInt();
        }*/
        /*******************************************************/
        /***************************************************************************/
        QCheckBox *webblockcb= new QCheckBox("Her Açılışta Web Sitelerini Engelle.");
        QFont f1( "Arial", 8, QFont::Normal);
        webblockcb->setFont(f1);
        webblockcb->setChecked(webblockstate);
        /// qDebug()<<"copystate1"<<copyState;
        connect(webblockcb, &QCheckBox::clicked, [=]() {
            QMessageBox msgBox;
             msgBox.setText("Bu Değişiklik Kalıcı olarak Kaydedildi!");
             msgBox.exec();

            webblockstate=webblockcb->checkState();
            ayarKaydetButtonSlot();
           // qDebug()<<copyState;
        });


        /*********************************************************************/
        /********************************************************************/
        QToolButton *webAyarGuncelleButton= new QToolButton;
        webAyarGuncelleButton->setFixedSize(QSize(en*50,en*8));
        webAyarGuncelleButton->setIconSize(QSize(en*50,en*3));
        webAyarGuncelleButton->setStyleSheet("Text-align:center");
        webAyarGuncelleButton->setIcon(QIcon(":/icons/clientrefresh.svg"));
        webAyarGuncelleButton->setAutoRaise(true);
        webAyarGuncelleButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
       // webAyarGuncelleButton->setFont(f2);
        webAyarGuncelleButton->setText("Seçili Pc'lerin Web Ayarlarını Güncelle");

        connect(webAyarGuncelleButton, &QPushButton::clicked, [=]() {

            sshSelectPcCommandSlot("rm -rf /usr/share/e-ag/webblocklist");
            system("sleep 0.2");
            sshSelectFileCopySlot("/usr/share/e-ag/webblocklist","/usr/share/e-ag/webblocklist");
            system("sleep 0.2");
            sshSelectPcCommandSlot("/usr/share/e-ag/webdisable.sh");
            system("sleep 0.2");


            hostAddressMacButtonSlot();
            for(int k=0;k<ipmaclist.count();k++)
            {
               for(int i=0;i<btnlist.count();i++)
                {
                    if(btnlist[i]->cs=="online"&&
                    (btnlist[i]->select||btnlist[i]->multiSelect)&&
                     ipmaclist[k].ip.section(".",0,2)==btnlist[i]->ip.section(".",0,2))
                    {
                        udpSendData("webblock",QString::number(webblockstate),btnlist[i]->ip);

                    }
                }
                system("sleep 0.1");
            }

     });
        /*********************************************************************/
    // messageBox.setIcon(QMessageBox::Question);

           QDialogButtonBox * buttonBox = new QDialogButtonBox();

            buttonBox->addButton("Kaydet", QDialogButtonBox::AcceptRole);
            buttonBox->addButton("Vazgeç", QDialogButtonBox::RejectRole);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    QVBoxLayout * vbox = new QVBoxLayout();
    QHBoxLayout * hbox1= new QHBoxLayout();
    QHBoxLayout * hbox2= new QHBoxLayout();
    QHBoxLayout * hbox3= new QHBoxLayout();
    QHBoxLayout * hbox4= new QHBoxLayout();
    QHBoxLayout * hbox5= new QHBoxLayout();
    QHBoxLayout * hbox6= new QHBoxLayout();

    hbox1->addWidget(webadresLabel);

    hbox2->addWidget(webadres);

    hbox3->addWidget(webadresEkleButton);

    hbox4->addWidget(twl);

    hbox5->addWidget(webblockcb);
    hbox6->addWidget(webAyarGuncelleButton);


    //vbox->addWidget(pcnameLabel);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox3);
    vbox->addLayout(hbox4);
    vbox->addLayout(hbox5);
    vbox->addLayout(hbox6);
    //vbox->addWidget(buttonBox);

    d->setLayout(vbox);

    int result = d->exec();
    if(result == QDialog::Accepted)
    {
       // qDebug()<<"tamam";
      /* remoteUserName= remoteUserNameLE->text();
       remotePassword= remotePasswordLE->text();
       localUserName= localUserNameLE->text();
       localPassword= localPasswordLE->text();
       localNetwork= localNetworkLE->text();
       tcpPort= tcpPortLE->text();
        ayarKaydetButtonSlot();
        */
    }

    if(result == QDialog::Rejected)
    {
        qDebug()<<"iptal";

    }

}
void MainWindow::webTableCellDoubleClicked(int iRow, int iColumn)
{
     QString webadres= twl->item(iRow, 0)->text();
     QStringList list=fileToList("webblocklist",localDir);
/******************************************************************/
    //QMessageBox::StandardButton reply;
    // reply = QMessageBox::question(this, "Uyarı", "Bilgisayar Silinecek! Emin misiniz?",
      //                             QMessageBox::Yes|tr(QMessageBox::No);
     QMessageBox messageBox(this);
     messageBox.setText("Uyarı");
     messageBox.setInformativeText("Web Adresi İçin İşlem Seçiniz!");
     QAbstractButton *evetButton =messageBox.addButton(tr("Sil"), QMessageBox::ActionRole);
     QAbstractButton *hayirButton =messageBox.addButton(tr("Düzenle"), QMessageBox::ActionRole);
     messageBox.setIcon(QMessageBox::Question);
             messageBox.exec();
             if (messageBox.clickedButton() == evetButton) {
                 // qDebug()<<"evet basıldı";
                 list=listRemove(list,webadres);
                // komutSudoExpect("sudo iptables -I OUTPUT -m tcp -p tcp -d "+webadres+" --dport 443 -j ACCEPT",rootusername,rootpassword);
                 listToFile(list,"webblocklist");
                 if(list.count()==0) twl->setRowCount(0);
                 for(int i=0;i<list.count();i++)
                 {
                     QString line=list[i];
                     QStringList lst=line.split("|");
                     twl->setRowCount(i+1);
                     twl->setItem(i, 0, new QTableWidgetItem(lst[0]));//ip
                 }
             }
             if (messageBox.clickedButton() == hayirButton) {
                 //qDebug()<<"hayır basıldı";
             }


}
QWidget* MainWindow::macListWidget()
{
    int bw,bh;
    bw=en*10;
    bh=boy*10;
    QWidget *wd=new QWidget();
   // wd->setWindowFlags(Qt::WindowStaysOnTopHint);
    wd->setWindowTitle("İstemci Listesi");
    auto appIcon = QIcon(":/icons/e-ag.svg");
    wd->setWindowIcon(appIcon);

    wd->setFixedSize(this->width(),boy*80);
    wd->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - wd->width())/2;
    int y = (screenGeometry.height() - wd->height()) / 2;
    wd->move(x, y);

    QToolButton *macListSaveButton = new QToolButton(wd);
    macListSaveButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    macListSaveButton->setIcon(QIcon(":icons/save.svg"));
    macListSaveButton->setIconSize(QSize(bw,bh/2));
    macListSaveButton->setAutoRaise(true);
    macListSaveButton->setAutoFillBackground(true);
    macListSaveButton->setStyleSheet(" font-size:"+QString::number(font.toInt()-2)+"px;");
    macListSaveButton->resize(bw,bh);
    macListSaveButton->move(wd->width()/2-bw,wd->height()-bh);
    macListSaveButton->setText("Kaydet");
    connect(macListSaveButton, SIGNAL(clicked()),this, SLOT(macListSaveButtonSlot()));
    /***************************************************************/
    QToolButton *printButton = new QToolButton(wd);
    printButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    printButton->setIcon(QIcon(":icons/print.svg"));
    printButton->setIconSize(QSize(bw,bh/2));
    printButton->setAutoRaise(true);
    printButton->setAutoFillBackground(true);
    printButton->setStyleSheet(" font-size:"+QString::number(font.toInt()-2)+"px;");
    printButton->resize(bw,bh);
    printButton->move(wd->width()/2+bw,wd->height()-bh);
    printButton->setText("Yazdır");
    connect(printButton, SIGNAL(clicked()),this, SLOT(printButtonSlot()));
   // printButton->hide();


    //  macListSaveButton->hide();

   // printButton->show();
    //macListSaveButton->show();
    // macListSaveButton->setVisible(true);
     tablewidget=new QTableWidget(wd);
    tablewidget->setFixedSize(wd->width(),wd->height()-bh);
/******************************************************************/
    tablewidget->setColumnCount(9);
    tablewidget->setRowCount(0);
   // tablewidget->setColumnWidth(0, 40);
    tablewidget->setColumnWidth(0, boy*30);
    tablewidget->setColumnWidth(1, boy*30);
    tablewidget->setColumnWidth(2,boy*15);
    tablewidget->setColumnWidth(3, boy*15);
    tablewidget->setColumnWidth(4, boy*15);
    tablewidget->setColumnWidth(5, boy*15);
    tablewidget->setColumnWidth(6, boy*15);
    tablewidget->setColumnWidth(7, boy*30);
    tablewidget->setColumnWidth(8, boy*5);

   //  tw->setHorizontalHeaderItem(0, new QTableWidgetItem("Sıra"));
    tablewidget->setHorizontalHeaderItem(0, new QTableWidgetItem("İp Adres"));
    tablewidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Mac Adres"));
    tablewidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Durum"));
    tablewidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Ssh"));
    tablewidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Vnc"));
    tablewidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Ftp"));
    tablewidget->setHorizontalHeaderItem(6, new QTableWidgetItem("Link"));
    tablewidget->setHorizontalHeaderItem(7, new QTableWidgetItem("Pc Adı"));
    tablewidget->setHorizontalHeaderItem(8, new QTableWidgetItem("L"));

    QFont fn( "Arial", 9, QFont::Normal);
    tablewidget->setFont(fn);


    //tw->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    //connect( tw, SIGNAL( cellPressed(int, int)), this, SLOT( changeLocalSongData( int, int )));
    tablewidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tablewidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //connect(tw, &QTableWidget::cellClicked, this, cellClicked());
    connect(tablewidget, SIGNAL(cellDoubleClicked(int,int)),SLOT(cellDoubleClicked(int,int)));

    /**************************************************************************/
    tablewidget->setRowCount(0);
    QStringList list=fileToList("persistlist",localDir);
   //qDebug()<<"liste sayısı................:"<<list.count();
    int sr=0;
    for(int i=0;i<list.count();i++)
     {
         QString line=list[i];
        QStringList lst=line.split("|");
        if(lst[1]!="")
        {
        tablewidget->setRowCount(tablewidget->rowCount()+1);
   //  tablewidget->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
     tablewidget->setItem(sr, 0, new QTableWidgetItem(lst[0]));//ip
    tablewidget->setItem(sr, 1, new QTableWidgetItem(lst[1]));//mac
     tablewidget->setItem(sr, 2, new QTableWidgetItem(lst[2]));//pcstate
     tablewidget->setItem(sr, 3, new QTableWidgetItem(lst[3]));//sshstate
    tablewidget->setItem(sr, 4, new QTableWidgetItem(lst[4]));//vncstate
     tablewidget->setItem(sr, 5, new QTableWidgetItem(lst[5]));//ftpstate
     tablewidget->setItem(sr, 6, new QTableWidgetItem(lst[6]));//connectstate
      tablewidget->setItem(sr, 7, new QTableWidgetItem(lst[7]));//pcname
     tablewidget->setItem(sr, 8, new QTableWidgetItem(lst[8]));//iptal(e/h)
sr++;
  }
    }
    //qDebug()<<"Mac Listelendi";
   /// mesajSlot("Mac Adresleri Listelendi.");
   return wd;
}
QWidget*  MainWindow::sliderWidget()
{
    QWidget *sWidget=new QWidget();

    slider = new QSlider(sWidget);

    slider->setMinimum(100);
    slider->setMaximum(300);
    slider->setValue(100);
    slider->setSingleStep(10);
    //slider->setSingleStep(10);
    slider->setFixedSize(100,25);

     slider->setOrientation(Qt::Horizontal);
     slider->setStyleSheet("QSlider::groove:horizontal { "
                               "border: 0px solid #990000; "
                               "height: 5px; "
                               "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4); "
                               "margin: 5px 0px; "
                               "} "
                               "QSlider::handle:horizontal { "
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #b4b4b4); "
                               "border: 0px solid #00005c; "
                               "width: 15px; "
                               "height: 8px; "
                               "margin: -8px 0px; "
                               "} ");

         QLabel *label1 = new QLabel("100",sWidget);
         QLabel *label2 = new QLabel("200",sWidget);
         QLabel *label3 = new QLabel("300",sWidget);
         sliderValuelabel = new QLabel("100",sWidget);
         int fnt=font.toInt();
         label1->setStyleSheet("font-size:"+QString::number(fnt-5)+"px; background-color:rgba(0,255,0,0);");
         label2->setStyleSheet("font-size:"+QString::number(fnt-5)+"px; background-color:rgba(0,255,0,0);");
         label3->setStyleSheet("font-size:"+QString::number(fnt-5)+"px; background-color:rgba(0,255,0,0);");
         sliderValuelabel->setStyleSheet("font-size:"+QString::number(fnt-5)+"px; background-color:rgba(0,255,0,0);");
         sliderValuelabel->setFixedSize(en*3,boy*4);
         QGridLayout *layouts = new QGridLayout(sWidget);
         layouts->setContentsMargins(0, 0, 0,0);
         layouts->setVerticalSpacing(0);
         layouts->setHorizontalSpacing(0);

         layouts->addWidget(slider, 0, 0, 1, 3,Qt::AlignCenter);
         layouts->addWidget(sliderValuelabel, 0, 3, 2, 1,Qt::AlignCenter);
         layouts->addWidget(label1, 1, 0, 1, 1,Qt::AlignLeft);
         layouts->addWidget(label2, 1, 1, 1, 1,Qt::AlignCenter);
         layouts->addWidget(label3, 1, 2, 1, 1,Qt::AlignRight);
         connect(slider, SIGNAL(valueChanged(int)), SLOT(updateSlider(int)),Qt::QueuedConnection);
         sWidget->setFixedSize(en*23,boy*5);
       //  sWidget->setStyleSheet("background-color: #5533ff");

         sWidget->setLayout(layouts);

         return sWidget;

   // return 0;
}
QWidget* MainWindow::sshCommandWidget()
{
    int e=en;
    int b=boy;
   // qDebug()<<"ayar click";
    QFont ff( "Arial", 20, 0);
    int yukseklik=b*8;
    QWidget * d = new QWidget();
    d->setWindowTitle("ssh Komut Çalıştırma Penceresi");
    commandFileL = new QLineEdit();
    commandFileL->setFixedSize(e*76,boy*15);
    commandFileL->setStyleSheet("font-size:"+QString::number(font.toInt()+2)+"px;");

    //commandFileL->setFont(ff);
    QLabel *commandFileLabel=new QLabel("ssh Komutu");
    commandFileLabel->setFixedSize(e*12,yukseklik);

    commandExampleButton=new QToolButton();
    commandExampleButton->setFixedSize(e*10,yukseklik*2);
    commandExampleButton->setAutoRaise(true);
    //commandExampleButton->setAutoFillBackground(true);
    commandExampleButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
     commandExampleButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    commandExampleButton->setText("Hazır\nKomutlar");
    commandExampleButton->setIcon(QIcon(":icons/command.svg"));
    commandExampleButton->setIconSize(QSize(b*6,yukseklik));

    commandExampleButton->setMenu(commandExampleMenu());
    commandExampleButton->setPopupMode(QToolButton::InstantPopup);
   // connect(commandExecuteButton, SIGNAL(clicked()),this, SLOT(commandExecuteSlot()));
    connect(commandExampleButton, &QToolButton::clicked, [=]() {

    //  sshButtonSlot();
      //  QMenu *commandExampleMenus=commandExampleMenu();
      //  commandExampleMenus->exec(mapToGlobal(commandExampleButton->pos() + QPoint(0,b*13)));
});

    commandExecuteButton=new QToolButton();
    commandExecuteButton->setFixedSize(e*32,yukseklik);
    commandExecuteButton->setAutoRaise(true);
   // commandExecuteButton->setAutoFillBackground(true);
    commandExecuteButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
     commandExecuteButton->setIcon(QIcon(":/icons/network.svg"));
    commandExecuteButton->setIconSize(QSize(b*6,yukseklik/2));
    commandExecuteButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

     commandExecuteButton->setText("Seçili Pc'lerde Çalıştır");
     connect(commandExecuteButton, &QToolButton::clicked, [=]() {
         if(pcMac->text()==""){mesajSlot("Pc Seçiniz");return;}
         sshSelectPcCommandSlot(commandFileL->text());
         mesajSlot("Komut Çalıştırıldı");
 });



     commandExecuteAllButton=new QToolButton();
     commandExecuteAllButton->setFixedSize(e*32,yukseklik);
     commandExecuteAllButton->setAutoRaise(true);
     //commandExecuteAllButton->setAutoFillBackground(true);
      commandExecuteAllButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
      commandExecuteAllButton->setIcon(QIcon(":/icons/networkall.svg"));
     commandExecuteAllButton->setIconSize(QSize(b*6,yukseklik/2));
     commandExecuteAllButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

     commandExecuteAllButton->setText("Tüm Pc'lerde Çalıştır");
      connect(commandExecuteAllButton, &QToolButton::clicked, [=]() {
         sshCommandAllSlot(commandFileL->text());
         mesajSlot("Komut Ağda Çalıştırıldı");
 });

      QToolButton *x11CommandButton=new QToolButton();
       x11CommandButton->setFixedSize(e*32,yukseklik);
       x11CommandButton->setAutoRaise(true);
       //x11CommandButton->setAutoFillBackground(true);
       x11CommandButton->setText("Seçili Açık Masaüstünde Çalıştır");
       x11CommandButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
       x11CommandButton->setIcon(QIcon(":/icons/user.svg"));
       x11CommandButton->setIconSize(QSize(b*6,yukseklik/2));
       x11CommandButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        connect(x11CommandButton, &QToolButton::clicked, [=]() {
            if(pcMac->text()==""){mesajSlot("Pc Seçiniz");return;}
          slotPcCommandSelect(commandFileL->text());
            mesajSlot("Seçili Pc'ye Komut Gönderildi.");
    });



       QToolButton *x11CommandAllButton=new QToolButton();
        x11CommandAllButton->setFixedSize(e*32,yukseklik);
        x11CommandAllButton->setAutoRaise(true);
        //x11CommandAllButton->setAutoFillBackground(true);
        x11CommandAllButton->setText("Tüm Açık Masaüstünde Çalıştır");
        x11CommandAllButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
        x11CommandAllButton->setIcon(QIcon(":/icons/userall.svg"));
        x11CommandAllButton->setIconSize(QSize(b*4,yukseklik/2));
        x11CommandAllButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

         connect(x11CommandAllButton, &QToolButton::clicked, [=]() {
               for(int i=0;i<btnlist.count();i++)
             {
                if(btnlist[i]->ps=="pcopen")
                {
                   udpSendData("x11komut",commandFileL->text(),btnlist[i]->ip);

                }
             }

            mesajSlot("Ağ'a Komut Gönderildi.");
    });

         QToolButton *helpButton= new QToolButton;
         helpButton->setFixedSize(e*10,yukseklik*2);
         helpButton->setAutoRaise(true);
        // bilgiButton->setAutoFillBackground(true);
         helpButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
         helpButton->setText("Yardım");
         helpButton->setIcon(QIcon(":/icons/help.svg"));
         helpButton->setIconSize(QSize(b*6,yukseklik/2));
         helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

         connect(helpButton, &QToolButton::clicked, [=]() {
            QTextDocument *doc=new QTextDocument();

             doc->setHtml("<center><h2>Komut Çalıştırma</h2></center>"
                          "<center><img src=\":/icons/sshcommand.png\" /></center> "
                          "<br/>1-Komutlar ssh servisi ile çalıştırılmaktadır."
                          "<center><img src=\":/icons/istemci.png\" /></center>"
                          "<br/>2-İstemci simgelerinin altındaki S işareti ssh servisini ifade eder."
                          "<br/><br/>3-S işareti yeşilse ssh çalışıyor. Kırmızı ise ssh çalışmıyordur."
                          "<br/><br/>4-Sorunsuz komut çalıştırmak için istemcilerde ssh servisinin çalışıyor olması gerekmektedir."
                          "<br/><br/>5-ssh servisinin çalışıp çalışmadığını manuel test etmek için Temel İşlemler bölümünden \"Servis Sorgula\" seçeneğini kullanabilirsiniz."
                          "<br/><br/>6-Komutlar Uzak Kullanıcı hesabı üzerinden çalıştırılmaktadır."
                          "<br/><br/>7-Uzak Kullanıcı Ayarlar bölümünden Uzak/Yerel Hesaplar seçeneğinden ayarlanmaktadır."
                          "<br/><br/>8-İstemcide Uzak Kullanıcı hesabında işlemler olduğu için dikkatli olmak gerekmektedir."
                          "<br/>Örneğin, \"rm cp mv mkdir rmdir vb.\" komutlar Uzak Kullanıcı ev dizini üzerinde yapılır."
                          "<br/><br/>9-Birden fazla istemcide komut çalıştırmak için istemci simgelerine çift tıklayıp seçilerek çalıştırılabilir."
                          "<br/><br/>10-İstemcilerde script dosyası çalıştırmak için;"
                          "<br/>Örneğin: install.sh dosyasını bash istall.sh şeklinde yazıp istemcilerde çalıştırabiliriz."
                                     );
             QPrinter pdf;
                 pdf.setOutputFileName("/tmp/sshcommand.pdf");
                 pdf.setOutputFormat(QPrinter::PdfFormat);
                 doc->print(&pdf);

             QTextEdit *document = new QTextEdit();
             document->setReadOnly(true);
             //  document->show();
              document->setDocument(doc);
             QVBoxLayout * vbox = new QVBoxLayout();
              QHBoxLayout * hbox1= new QHBoxLayout();

             // hbox1->addWidget(commandFileLabel);
              hbox1->addWidget(document);

              vbox->addLayout(hbox1);
              QDialog * d1 = new QDialog();
              d1->setWindowTitle("Komut Çalıştırma Yardım Penceresi");
              d1->setFixedSize(QSize(boy*150,boy*120));
              auto appIcon = QIcon(":/icons/e-ag.svg");
              d1->setWindowIcon(appIcon);

              d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

              d1->setLayout(vbox);
               d1->exec();
      });


    QGridLayout * vbox = new QGridLayout();
    vbox->setContentsMargins(0, 0, 0,0);
    vbox->setVerticalSpacing(0);

    vbox->addWidget(commandFileLabel,1,1,2,1);
    vbox->addWidget(commandExampleButton,1,2,2,1);

    vbox->addWidget(commandFileL,1,3,2,1);

    vbox->addWidget(commandExecuteButton,1,4,1,1);
    vbox->addWidget(commandExecuteAllButton,1,5,1,1);

    vbox->addWidget(x11CommandButton,2,4,1,1);
    vbox->addWidget(x11CommandAllButton,2,5,1,1);

    vbox->addWidget(helpButton,1,6,2,1);


    d->setLayout(vbox);

    return d;

}
QWidget*  MainWindow::sshScpWidget()
{
    int e=en;
    int b=boy;
   // qDebug()<<"ayar click";
    QFont ff( "Arial", 20, 0);
int yukseklik=b*7.5;
    QWidget * d = new QWidget();
    d->setWindowTitle("ssh Dosya Kopyalama Penceresi");
   QLineEdit *le = new QLineEdit();
    le->setFixedSize(e*75,boy*7);
    le->setStyleSheet("font-size:"+QString::number(font.toInt()+2)+"px;");

   // le->setFont(ff);
    QLineEdit * ple = new QLineEdit();
    ple->setFixedSize(e*75,boy*7);
   ple->setStyleSheet("font-size:"+QString::number(font.toInt()+2)+"px;");

    QLabel *commandFileLabel=new QLabel("Dosya");
     commandFileLabel->setFixedSize(e*15,yukseklik);
     commandFileLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    QLabel *pathLabel=new QLabel("Hedef Konum\n/home/user/\n/tmp/");
     pathLabel->setFixedSize(e*15,yukseklik);
     pathLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");



     fileSelectButton=new QToolButton();
     fileSelectButton->setFixedSize(e*24,yukseklik);
     fileSelectButton->setAutoRaise(true);
     //fileSelectButton->setAutoFillBackground(true);
     fileSelectButton->setText("Dosya Seç");
     fileSelectButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
     fileSelectButton->setIcon(QIcon(":/icons/openfile.svg"));
     fileSelectButton->setIconSize(QSize(b*8,yukseklik/2));
     fileSelectButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

      connect(fileSelectButton, &QToolButton::clicked, [=]() {
       //pcClickSlot(pcMac->text());
          QString fileName = QFileDialog::getOpenFileName(this,tr("Dosya Seç"),QDir::homePath(), tr("Files (*.*)"));
          le->setText(fileName);

            QFileInfo fi(le->text());

       mesajSlot("Dosya Seçildi.");
});


     fileCopyButton=new QToolButton();
     fileCopyButton->setFixedSize(e*24,yukseklik);
     fileCopyButton->setAutoRaise(true);
     fileCopyButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
     fileCopyButton->setText("Seçili Pc'lere Kopyala");
     fileCopyButton->setIcon(QIcon(":/icons/selectcopyfile.svg"));
     fileCopyButton->setIconSize(QSize(b*8,yukseklik/2));
     fileCopyButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

         connect(fileCopyButton, &QToolButton::clicked, [=]() {
         QString name = QUrl::fromLocalFile(le->text()).path(QUrl::FullyEncoded);
        name.replace("%20","%5C%20");
         QUrl pth;
         sshSelectFileCopySlot(pth.fromPercentEncoding(name.toUtf8()),ple->text());
         mesajSlot("Dosya Seçili Pc'ye Kopyalandı.");
   });
     fileCopyAllButton=new QToolButton();
     fileCopyAllButton->setFixedSize(e*24,yukseklik);
     fileCopyAllButton->setAutoRaise(true);
     fileCopyAllButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
     fileCopyAllButton->setText("Tüm Pc'lere Kopyala");
     fileCopyAllButton->setIcon(QIcon(":/icons/allcopyfile.svg"));
     fileCopyAllButton->setIconSize(QSize(b*8,yukseklik/2));
     fileCopyAllButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

         connect(fileCopyAllButton, &QToolButton::clicked, [=]() {
             QString name = QUrl::fromLocalFile(le->text()).path(QUrl::FullyEncoded);
            name.replace("%20","%5C%20");
             QUrl pth;
             sshFileCopyAllSlot(pth.fromPercentEncoding(name.toUtf8()),ple->text());


           mesajSlot("Dosya Ağ'a Kopyalandı.");
   });

         QToolButton *fileCopyDesktopNotGetSendButton=new QToolButton();
         fileCopyDesktopNotGetSendButton->setFixedSize(e*24,yukseklik);
         fileCopyDesktopNotGetSendButton->setAutoRaise(true);
         fileCopyDesktopNotGetSendButton->setText("Masaüstlerine Dağıt");
         fileCopyDesktopNotGetSendButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
         fileCopyDesktopNotGetSendButton->setIcon(QIcon(":/icons/senddesktopfile.svg"));
         fileCopyDesktopNotGetSendButton->setIconSize(QSize(b*8,yukseklik/2));
         fileCopyDesktopNotGetSendButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

             connect(fileCopyDesktopNotGetSendButton, &QToolButton::clicked, [=]() {
                 QString name1 = QUrl::fromLocalFile(le->text()).path(QUrl::FullyEncoded);
                name1.replace("%20","%5C%20");
                 QUrl pth;

                 QFileInfo fi(le->text());
                 QString name = fi.fileName();

                 QString uzanti = fi.completeSuffix();
                 QString ad = fi.baseName().replace(" ","");
                 //  qDebug()<<"dosya adı:"<<name<<ad<<uzanti;
                 //QString path=QFileInfo(le->text()).canonicalPath();
                 // path=le->text().replace("+","\\ ");
                 //qDebug()<<"dosya adı:"<<path;

                sshFileCopyAllSlot( pth.fromPercentEncoding(name1.toUtf8()),"/home/"+remoteUserName+"/"+ad+"."+uzanti);

       for(int i=0;i<btnlist.count();i++)
                 {
                     if(btnlist[i]->ss=="sshopen"&&(btnlist[i]->select||btnlist[i]->multiSelect)&&
                             btnlist[i]->user!="")
                     {
sshCommandSlot("cp "+ad+"."+uzanti+" /home/"+btnlist[i]->user+"/Masaüstü/",btnlist[i]->ip);

                     }
                 }

          for(int i=0;i<btnlist.count();i++)
                 {
                     if(btnlist[i]->ss=="sshopen"&&(btnlist[i]->select||btnlist[i]->multiSelect)&&
                             btnlist[i]->user!="")
                     {
sshCommandSlot("chmod 777 /home/"+btnlist[i]->user+"/Masaüstü/"+ad+"."+uzanti,btnlist[i]->ip);
                     }
                 }

                 mesajSlot("Dosya Masaüstlerine Gönderildi.");
       });

         QToolButton *fileCopyDesktopSendButton=new QToolButton();
         fileCopyDesktopSendButton->setFixedSize(e*24,yukseklik);
         fileCopyDesktopSendButton->setAutoRaise(true);
         fileCopyDesktopSendButton->setText("Çalışmaları Dağıt");
         fileCopyDesktopSendButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
         fileCopyDesktopSendButton->setIcon(QIcon(":/icons/senddesktopquiz.svg"));
         fileCopyDesktopSendButton->setIconSize(QSize(b*8,yukseklik/2));
         fileCopyDesktopSendButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

             connect(fileCopyDesktopSendButton, &QToolButton::clicked, [=]() {
                 QString name1 = QUrl::fromLocalFile(le->text()).path(QUrl::FullyEncoded);
                name1.replace("%20","%5C%20");
                 QUrl pth;

                 QFileInfo fi(le->text());
                  QString name = fi.fileName();

                  QString uzanti = fi.completeSuffix();
                 // QString ad = fi.baseName();
                 // qDebug()<<"dosya adı:"<<name<<ad<<uzanti;
                  //QString path=QFileInfo(le->text()).canonicalPath();
                 // path=le->text().replace("+","\\ ");
//qDebug()<<"dosya adı:"<<path;
                  sshFileCopyAllSlot(pth.fromPercentEncoding(name1.toUtf8()),"/home/"+remoteUserName+"/e-ag-server."+uzanti);
                  for(int i=0;i<btnlist.count();i++)
                  {
                      if(btnlist[i]->ss=="sshopen"&&(btnlist[i]->select||btnlist[i]->multiSelect)&&
                              btnlist[i]->user!="")
                      {
 //sshCommandSlot("mv e-ag-server."+uzanti+" /home/"+btnlist[i]->user+"/Masaüstü/",btnlist[i]->ip);
 sshCommandSlot("mv /home/"+btnlist[i]->user+"/Masaüstü/e-ag-server.* /home/"+btnlist[i]->user+"/Masaüstü/e-ag-server.old",btnlist[i]->ip);
                      }
                  }
                 for(int i=0;i<btnlist.count();i++)
                 {
                     if(btnlist[i]->ss=="sshopen"&&(btnlist[i]->select||btnlist[i]->multiSelect)&&
                             btnlist[i]->user!="")
                     {
sshCommandSlot("cp e-ag-server."+uzanti+" /home/"+btnlist[i]->user+"/Masaüstü/",btnlist[i]->ip);
//sshCommandSlot("chmod 777 /home/"+btnlist[i]->user+"/Masaüstü/e-ag-server."+uzanti,btnlist[i]->ip);
                     }
                 }

                 for(int i=0;i<btnlist.count();i++)
                 {
                     if(btnlist[i]->ss=="sshopen"&&(btnlist[i]->select||btnlist[i]->multiSelect)&&
                             btnlist[i]->user!="")
                     {
//sshCommandSlot("cp e-ag-server."+uzanti+" /home/"+btnlist[i]->user+"/Masaüstü/",btnlist[i]->ip);
sshCommandSlot("chmod 777 /home/"+btnlist[i]->user+"/Masaüstü/e-ag-server."+uzanti,btnlist[i]->ip);
                     }
                 }

               mesajSlot("Dosya Masaüstlerine Gönderildi.");
       });

             QToolButton *fileCopyDesktopGetButton=new QToolButton();
             fileCopyDesktopGetButton->setFixedSize(e*24,yukseklik);
             fileCopyDesktopGetButton->setAutoRaise(true);
             //fileCopyDesktopGetButton->setAutoFillBackground(true);
             fileCopyDesktopGetButton->setText("Çalışmaları Topla");
             fileCopyDesktopGetButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
             fileCopyDesktopGetButton->setIcon(QIcon(":/icons/getdesktopquiz.svg"));
             fileCopyDesktopGetButton->setIconSize(QSize(b*8,yukseklik/2));
             fileCopyDesktopGetButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

                 connect(fileCopyDesktopGetButton, &QToolButton::clicked, [=]() {
                      for(int i=0;i<btnlist.count();i++)
                     {
                         if(btnlist[i]->ps=="pcopen")
                         {
                           udpSendData("dosyatopla","",btnlist[i]->ip);


                         }
                     }


                   mesajSlot("Dosya Masaüstlerinden Alındı.");
           });

                 QToolButton *helpButton= new QToolButton;
                 helpButton->setFixedSize(e*10,yukseklik*2);
                 helpButton->setAutoRaise(true);
                // bilgiButton->setAutoFillBackground(true);
                 helpButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
                 helpButton->setText("Yardım");
                 helpButton->setIcon(QIcon(":/icons/help.svg"));
                 helpButton->setIconSize(QSize(b*6,yukseklik/2));
                 helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

                 connect(helpButton, &QToolButton::clicked, [=]() {
                     QTextDocument *doc=new QTextDocument();

                      doc->setHtml("<center><h2>Dosya Kopyalama</h2></center>"
                                   "<center><img src=\":/icons/dosyakopyalama.png\" /></center> "
                                   "1-Kopyalama işlemi ssh servisi ile yapmaktadır."
                                   "<center><img src=\":/icons/istemci.png\" /></center>"
                                   "2-İstemci simgelerinin altındaki S işareti ssh servisini ifade eder."
                                   "<br/><br/>3-S işareti yeşilse ssh çalışıyor. Kırmızı ise ssh çalışmıyordur."
                                   "<br/><br/>4-Sorunsuz kopyalama yapmak için istemcilerde ssh servisinin çalışıyor olması gerekmektedir."
                                   "<br/><br/>5-ssh servisinin çalışıp çalışmadığını manuel test etmek için Temel İşlemler bölümünden \"Servis Sorgula\" seçeneğini kullanabilirsiniz."
                                   "<br/><br/>6-Klasör içeriğinin tamamını kopyalamak için dosya ismi yerine * konulması gerekir;"
                                   "<br/> Örneğin: /home/user/* şeklinde klasör içeriğini kopyalar."
                                   "<br/><br/>7-İstemcide açık kullanıcı masaüstüne dosya kopyalama için Masaüstlerine Dağıt seçeneğini kullanabilirsiniz."
                                   "<br/><br/>8-İstemcide açık kullanıcı masaüstüne çalışma dosyası göndermek için Çalışmaları Dağıt seçeneğini kullanabilirsiniz."
                                   "<br/><br/>9-İstemcide açık kullanıcı masaüstündeki çalışma dosyasını Sunucuya toplamak için Çalışmaları Topla seçeneğini kullanabilirsiniz."
                                   "<br/><br/>10-Dosyalar Uzak Kullanıcı ev dizinine kopyalanacaktır."
                                   "<br/><br/>10-Dosyalar Uzak Kullanıcı ev dizini dışında başka yere kopyalacaksa \"Hedef Konum\" bölünüde belirtilmelidir."
                                   "<br/>Örneğin: /tmp/"
                                   "<br/>11-Birden fazla istemciye kopyalama için istemci simgelerine çift tıklayıp seçilerek kopyalanabilir."
                                               );
                      QPrinter pdf;
                          pdf.setOutputFileName("/tmp/dosyakopyalama.pdf");
                          pdf.setOutputFormat(QPrinter::PdfFormat);
                          doc->print(&pdf);

                      QTextEdit *document = new QTextEdit();
                      document->setReadOnly(true);
                      //  document->show();
                       document->setDocument(doc);
                      QVBoxLayout * vbox = new QVBoxLayout();
                       QHBoxLayout * hbox1= new QHBoxLayout();

                      // hbox1->addWidget(commandFileLabel);
                       hbox1->addWidget(document);

                       vbox->addLayout(hbox1);
                       QDialog * d1 = new QDialog();
                       d1->setWindowTitle("Dosya Kopyalama Yardım Penceresi");
                       d1->setFixedSize(QSize(boy*150,boy*120));
                       auto appIcon = QIcon(":/icons/e-ag.svg");
                       d1->setWindowIcon(appIcon);

                       d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

                       d1->setLayout(vbox);
                        d1->exec();
              });
    QGridLayout * vbox = new QGridLayout();
    vbox->setContentsMargins(0, 0, 0,0);
    vbox->setVerticalSpacing(0);

    vbox->addWidget(commandFileLabel,1,1,1,1);
    vbox->addWidget(le,1,2,1,1);
    vbox->addWidget(fileSelectButton,1,3,1,1);
    vbox->addWidget(fileCopyButton,1,4,1,1);
    vbox->addWidget(fileCopyAllButton,1,5,1,1);
      vbox->addWidget(pathLabel,2,1,1,1);
    vbox->addWidget(ple,2,2,1,1);
    vbox->addWidget(fileCopyDesktopNotGetSendButton,2,3,1,1);

    vbox->addWidget(fileCopyDesktopSendButton,2,4,1,1);
    vbox->addWidget(fileCopyDesktopGetButton,2,5,1,1);

    vbox->addWidget(helpButton,1,6,2,1);

    d->setLayout(vbox);
             return d;
}
QWidget* MainWindow::videoWidget()
{
    int e=en;
    int b=boy;
   // qDebug()<<"ayar click";
    QFont ff( "Arial", 15, 0);
    int yukseklik=b*7.5;

    QWidget * d = new QWidget();
    d->setWindowTitle("video Yayın Penceresi");
    QToolButton *videoStopButton=new QToolButton();
    QToolButton *liveStreamStopButton=new QToolButton();

    QLineEdit *commandFileLE = new QLineEdit();
    commandFileLE->setFixedSize(e*66,yukseklik);
    //commandFileLE->setFont(ff);
    commandFileLE->setStyleSheet("font-size:"+QString::number(font.toInt()+2)+"px;");

    QLabel *commandFileLabel=new QLabel("Video Dosyası:");
     commandFileLabel->setFixedSize(e*20,yukseklik);
     commandFileLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

     QComboBox * kamera = new QComboBox();
     kamera->setFixedSize(e*33,yukseklik);
    // kamera->setFont(ff);
     kamera->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
     /**********************************video giriş listesi alma işlemi******************************************************/

     QStringList kameralst;
     if(QFile::exists("/dev/video0"))kameralst<<"/dev/video0";
     if(QFile::exists("/dev/video1"))kameralst<<"/dev/video1";
     if(QFile::exists("/dev/video2"))kameralst<<"/dev/video2";
     if(QFile::exists("/dev/video3"))kameralst<<"/dev/video3";
     if(QFile::exists("/dev/video4"))kameralst<<"/dev/video4";
     kamera->addItems(kameralst);
     /****************************************************************************************/

      QComboBox * ses = new QComboBox();
      ses->setFixedSize(e*33,yukseklik);
     // ses->setFont(ff);
      ses->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
      /**********************************ses giriş listesi alma işlemi******************************************************/
      QString result="";
      QStringList arguments;
      arguments << "-c" << QString("pactl list short sources|grep 'input'|awk '{print $1,\"|\",$2}'");
      QProcess process;
      process.start("/bin/bash",arguments);
      if(process.waitForFinished(-1))
      {
         result = process.readAll();
         result.chop(1);
      }
      if(result!="")
      {
          QStringList seslst;
          seslst=result.split("\n");
          ses->addItems(seslst);
      }
      /****************************************************************************************/
    QLabel *pathLabel=new QLabel("Kamera ve Ses:");
    pathLabel->setFixedSize(e*20,yukseklik);
    pathLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    // messageBox.setIcon(QMessageBox::Question);



    QToolButton *videoYayinButton=new QToolButton();
    videoYayinButton->setFixedSize(e*25,yukseklik);
    videoYayinButton->setAutoRaise(true);
   // videoYayinButton->setAutoFillBackground(true);
    videoYayinButton->setIcon(QIcon(":/icons/selectpcvideo.svg"));
    videoYayinButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    videoYayinButton->setIconSize(QSize(b*8,yukseklik/2));
    videoYayinButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    videoYayinButton->setText("Seçili Pc'lerde Yayınla");
      connect(videoYayinButton, &QToolButton::clicked, [=]() {
       // if(pcMac->text()==""){mesajSlot("Pc Seçiniz");return;}
          QString name = QUrl::fromLocalFile(commandFileLE->text()).path(QUrl::FullyEncoded);
         name.replace("%20","%5C%20");
          QUrl pth;

        if(commandFileLE->text()!="")
        {
            QString result="";
            QStringList arguments;
            QString kmt="ffmpeg -re -i "+pth.fromPercentEncoding(name.toUtf8())+" -vcodec libx264 -g 20 -s 400x300 -acodec aac -strict -2 -f flv rtmp://127.0.0.1/live/stream";
            qDebug()<<"komut:"<<kmt;
            arguments << "-c" << kmt;

            videoProcess.start("/bin/bash",arguments);
            streamState=true;

            videoStopButton->setStyleSheet("background-color: #ff0000");
             mesajSlot("Komut Çalıştırıldı");

             hostAddressMacButtonSlot();

             for(int k=0;k<ipmaclist.count();k++)
             {

                 QString  kmt;
                 kmt.append("vlc rtmp://"+ipmaclist[k].ip+"/live/stream");

                 for(int i=0;i<btnlist.count();i++)
                 {
                     if(btnlist[i]->cs=="online"&&
                     (btnlist[i]->select||btnlist[i]->multiSelect)&&
                      ipmaclist[k].ip.section(".",0,2)==btnlist[i]->ip.section(".",0,2))
                     {
                         udpSendData("x11komut",kmt,btnlist[i]->ip);

                     }
                 }
                 system("sleep 0.1");
             }



            mesajSlot("Seçili Pc'lere Komut Gönderildi.");



        }
    });



     QToolButton *videoYayinAllButton=new QToolButton();
     videoYayinAllButton->setFixedSize(e*25,yukseklik);
     videoYayinAllButton->setAutoRaise(true);
    // videoYayinAllButton->setAutoFillBackground(true);
     videoYayinAllButton->setIcon(QIcon(":/icons/allpcvideo.svg"));
     videoYayinAllButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

     videoYayinAllButton->setIconSize(QSize(b*8,yukseklik/2));
     videoYayinAllButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
     videoYayinAllButton->setText("Tüm Pc'lerde Yayınla");
     connect(videoYayinAllButton, &QToolButton::clicked, [=]() {
         QString name = QUrl::fromLocalFile(commandFileLE->text()).path(QUrl::FullyEncoded);
        name.replace("%20","%5C%20");
         QUrl pth;

         if(commandFileLE->text()!="")
         {
             QString result="";
             QStringList arguments;
             QString kmt="ffmpeg -re -i "+pth.fromPercentEncoding(name.toUtf8())+" -vcodec libx264 -g 20 -s 400x300 -acodec aac -strict -2 -f flv rtmp://127.0.0.1/live/stream";
             qDebug()<<kmt;

             arguments << "-c" << kmt;
             videoProcess.start("/bin/bash",arguments);
             streamState=true;
             videoStopButton->setStyleSheet("background-color: #ff0000");
             mesajSlot("Komut Ağda Çalıştırıldı");
             /***********************************************/
             hostAddressMacButtonSlot();
             for(int k=0;k<ipmaclist.count();k++)
             {
                 QString  kmt;
                 kmt.append("vlc rtmp://"+ipmaclist[k].ip+"/live/stream");
                 for(int i=0;i<btnlist.count();i++)
                 {
                     if(btnlist[i]->cs=="online"&&
                     ipmaclist[k].ip.section(".",0,2)==btnlist[i]->ip.section(".",0,2))
                     {
                         udpSendData("x11komut",kmt,btnlist[i]->ip);
                     }
                 }
                 system("sleep 0.1");
             }
            mesajSlot("Ağ'a Komut Gönderildi.");
         }
     });

     fileSelectButton=new QToolButton();
     fileSelectButton->setFixedSize(e*5,yukseklik);
     fileSelectButton->setAutoRaise(true);
     fileSelectButton->setIcon(QIcon(":/icons/openfile.svg"));
     fileSelectButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

     fileSelectButton->setIconSize(QSize(b*8,yukseklik/2));
     fileSelectButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
      fileSelectButton->setText("...");
      connect(fileSelectButton, &QToolButton::clicked, [=]() {

          pcClickSlot(pcMac->text());
          QString fileName = QFileDialog::getOpenFileName(this,tr("Dosya Seç"),QDir::homePath(), tr("Files (*.*)"));
      //qDebug()<<fileName;
          commandFileLE->setText(fileName);

       mesajSlot("Dosya Seçildi.");
});


     QToolButton *liveStreamButton=new QToolButton();
     liveStreamButton->setFixedSize(e*31,yukseklik);
     liveStreamButton->setAutoRaise(true);
     liveStreamButton->setIcon(QIcon(":/icons/selectpccamera.svg"));
     liveStreamButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

     liveStreamButton->setIconSize(QSize(b*8,yukseklik/2));
     liveStreamButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
      liveStreamButton->setText("Seçili Pc'lere Yayın");
         connect(liveStreamButton, &QToolButton::clicked, [=]() {
             QString sslst;
             sslst=ses->currentText();
            // if(pcMac->text()==""){mesajSlot("Pc Seçiniz");return;}
              QString result="";
              QStringList arguments;
              QString kmt="ffmpeg -re -i "+kamera->currentText()+" -f pulse -i "+sslst.split("|")[1]+" -ac "+sslst.split("|")[0]+" -vcodec libx264 -g 20 -s 400x300 -acodec aac -strict -2 -f flv rtmp://127.0.0.1/live/stream";
              qDebug()<<kmt;

                      arguments << "-c" << kmt;
               videoProcess.start("/bin/bash",arguments);
               streamState=true;
               liveStreamStopButton->setStyleSheet("background-color: #ff0000");
                mesajSlot("Dosya Seçili Pc'ye Kopyalandı.");
               /****************************************************/
            //  if(pcMac->text()==""){mesajSlot("Pc Seçiniz");return;}
               ///  slotCommand("vlc rtmp://"+myIpAddress+"/live/stream");
                hostAddressMacButtonSlot();
           for(int k=0;k<ipmaclist.count();k++)
                {
                    QString  kmt;
                    kmt.append("vlc rtmp://"+ipmaclist[k].ip+"/live/stream");
                    for(int i=0;i<btnlist.count();i++)
                    {
                        if(btnlist[i]->cs=="online"&&
                        (btnlist[i]->select||btnlist[i]->multiSelect)&&
                        ipmaclist[k].ip.section(".",0,2)==btnlist[i]->ip.section(".",0,2))
                        {
                            udpSendData("x11komut",kmt,btnlist[i]->ip);
                        }
                    }
                    system("sleep 0.1");
                }
              mesajSlot("Seçili Pc'ye Komut Gönderildi.");



   });
    QToolButton *liveStreamAllButton=new QToolButton();
     liveStreamAllButton->setFixedSize(e*25,yukseklik);
     liveStreamAllButton->setAutoRaise(true);
     liveStreamAllButton->setIcon(QIcon(":/icons/allpccamera.svg"));
     liveStreamAllButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

     liveStreamAllButton->setIconSize(QSize(b*8,yukseklik/2));
     liveStreamAllButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
      liveStreamAllButton->setText("Tüm Pc'lere Yayın");
         connect(liveStreamAllButton, &QToolButton::clicked, [=]() {
           if(ses->currentText()!=""&&kamera->currentText()!="")
           {
             QString sslst=ses->currentText();

             QString result="";
             QStringList arguments;
             QString kmt="ffmpeg -re -i "+kamera->currentText()+" -f pulse -i "+sslst.split("|")[1]+" -ac "+sslst.split("|")[0]+" -vcodec libx264 -g 20 -s 400x300 -acodec aac -strict -2 -f flv rtmp://127.0.0.1/live/stream";

             qDebug()<<kmt;

                     arguments << "-c" << kmt;
              videoProcess.start("/bin/bash",arguments);
              streamState=true;
              liveStreamStopButton->setStyleSheet("background-color: #ff0000");
           mesajSlot("video Ağ'a Yayınlandı.");
           /***********************************************/
           hostAddressMacButtonSlot();
      for(int k=0;k<ipmaclist.count();k++)
           {
               QString  kmt;
               kmt.append("vlc rtmp://"+ipmaclist[k].ip+"/live/stream");
               for(int i=0;i<btnlist.count();i++)
               {
                   if(btnlist[i]->cs=="online"&&
                   ipmaclist[k].ip.section(".",0,2)==btnlist[i]->ip.section(".",0,2))
                   {
                       udpSendData("x11komut",kmt,btnlist[i]->ip);
                   }
               }
               system("sleep 0.1");
           }


          mesajSlot("Ağ'a Komut Gönderildi.");
           }
   });
            videoStopButton->setFixedSize(e*23,yukseklik);
          videoStopButton->setAutoRaise(true);
          videoStopButton->setIcon(QIcon(":/icons/videostop.svg"));
          videoStopButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

          videoStopButton->setIconSize(QSize(b*8,yukseklik/2));
          videoStopButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            videoStopButton->setText("Video Durdur");
            connect(videoStopButton, &QToolButton::clicked, [=]() {
                if(streamState)
                {
                    videoProcess.terminate();
                    streamState=false;
                    videoStopButton->setStyleSheet("background-color: #dcdcdc");
                    slotPcCommandSelect("pkill vlc");
                    mesajSlot("Video durduruldu.");
                }

            });


          liveStreamStopButton->setFixedSize(e*23,yukseklik);
          liveStreamStopButton->setAutoRaise(true);
          liveStreamStopButton->setIcon(QIcon(":/icons/camerastop.svg"));
          liveStreamStopButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

          liveStreamStopButton->setIconSize(QSize(b*8,yukseklik/2));
          liveStreamStopButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
          liveStreamStopButton->setText("Kamera Durdur");
          connect(liveStreamStopButton, &QToolButton::clicked, [=]() {
              if(streamState)
              {
                  videoProcess.terminate();
                  streamState=false;
                  liveStreamStopButton->setStyleSheet("background-color: #dcdcdc");
                  slotPcCommandSelect("pkill vlc");
                  mesajSlot("Video durduruldu.");
              }

          });

          QToolButton *helpButton= new QToolButton;
          helpButton->setFixedSize(e*10,yukseklik*2);
          helpButton->setAutoRaise(true);
         // bilgiButton->setAutoFillBackground(true);
          helpButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
          helpButton->setText("Yardım");
          helpButton->setIcon(QIcon(":/icons/help.svg"));
          helpButton->setIconSize(QSize(b*6,yukseklik/2));
          helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

          connect(helpButton, &QToolButton::clicked, [=]() {
              QTextDocument *doc=new QTextDocument();

                   doc->setHtml("<center><h2>Video/Kamera Yayını</h2></center>"
                                "<center><img src=\":/icons/video.png\" /></center> "
                           "<br/>1-Sunucudaki bir Video Dosyası/Kamera login olmuş kullanıcılarda paylaşılabillir."
                           "<center><img src=\":/icons/istemci.png\" /></center>"
                           "<br/><br/>2-Video Dosyası/Kamera sadece X işareti yeşil olan istemcilere paylaşılabilir."
                           "<br/><br/>3-İstemci simgelerinin altındaki X işareti login olmuş kullanıcıyı ifade eder."
                           "<br/><br/>4-X işareti yeşilse kullanıcı login olduğunu ifade eder. Kırmızı ise login olmadığını ifade eder."
                           "<br/><br/>5-Birden fazla istemciye Video Dosyası/Kamera paylaşmak için istemci simgelerine çift tıklayıp seçilerek paylaşılabilir."
                                         );
                   QPrinter pdf;
                   pdf.setOutputFileName("/tmp/video.pdf");
                   pdf.setOutputFormat(QPrinter::PdfFormat);
                   doc->print(&pdf);

                   QTextEdit *document = new QTextEdit();
                   document->setReadOnly(true);
                   //  document->show();
                   document->setDocument(doc);
                   QVBoxLayout * vbox = new QVBoxLayout();
                   QHBoxLayout * hbox1= new QHBoxLayout();

                   // hbox1->addWidget(commandFileLabel);
                   hbox1->addWidget(document);

                   vbox->addLayout(hbox1);
                   QDialog * d1 = new QDialog();
                   d1->setWindowTitle("Video/Kamera Yayın Yardım Penceresi");
                   d1->setFixedSize(QSize(boy*150,boy*120));
                   auto appIcon = QIcon(":/icons/e-ag.svg");
                   d1->setWindowIcon(appIcon);

                   d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

                   d1->setLayout(vbox);
                   d1->exec();

       });
          QGridLayout * vbox = new QGridLayout();
        //  vbox->setSpacing(0);
          vbox->setContentsMargins(0, 0,0,0);
          vbox->setVerticalSpacing(0);

          vbox->addWidget(commandFileLabel,1,1,1,1,Qt::AlignLeft);
          vbox->addWidget(commandFileLE,1,2,1,2,Qt::AlignLeft);
          QHBoxLayout * hbox1= new QHBoxLayout();

          hbox1->addWidget(fileSelectButton);
          QLabel *bl=new QLabel();bl->setFixedSize(e,b);
          hbox1->addWidget(bl);
          hbox1->addWidget(videoYayinButton);
          vbox->addLayout(hbox1,1,4,1,1,Qt::AlignLeft);

          vbox->addWidget(videoYayinAllButton,1,5,1,1,Qt::AlignLeft);
          vbox->addWidget(videoStopButton,1,6,1,1,Qt::AlignLeft);

          vbox->addWidget(pathLabel,2,1,1,1,Qt::AlignLeft);
          vbox->addWidget(kamera,2,2,1,1,Qt::AlignLeft);
          vbox->addWidget(ses,2,3,1,1,Qt::AlignLeft);
          vbox->addWidget(liveStreamButton,2,4,1,1,Qt::AlignLeft);
          vbox->addWidget(liveStreamAllButton,2,5,1,1,Qt::AlignLeft);
          vbox->addWidget(liveStreamStopButton,2,6,1,1,Qt::AlignLeft);

          vbox->addWidget(helpButton,1,7,2,1,Qt::AlignLeft);

          d->setLayout(vbox);
return d;
}
QWidget* MainWindow::duyuruWidget()
{
    int e=en;
    int b=boy;
   // qDebug()<<"ayar click";
    QFont ff( "Arial", 20, 0);
    int yukseklik=b*7;
    QWidget * d = new QWidget();
     d->setFixedSize(this->width(),boy*16);
    d->setWindowTitle("Duyuru Mesaj Penceresi");
    QLineEdit *commandFileLE = new QLineEdit();
    commandFileLE->setFixedSize(e*84,boy*15);
   // commandFileLE->setFont(ff);
    commandFileLE->setStyleSheet("font-size:"+QString::number(font.toInt()+2)+"px;");

    QLabel *commandFileLabel=new QLabel("Mesaj / Duyuru");
    commandFileLabel->setFixedSize(e*15,yukseklik);
    commandFileLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");



   QToolButton *duyuruButton=new QToolButton();
    duyuruButton->setFixedSize(e*24,yukseklik*2);
    duyuruButton->setAutoRaise(true);
   // duyuruButton->setAutoFillBackground(true);
    duyuruButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    duyuruButton->setText("Seçili Pc'lere Gönder");
    duyuruButton->setIcon(QIcon(":/icons/selectpcmessage.svg"));
    duyuruButton->setIconSize(QSize(b*8,yukseklik));
    duyuruButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

     connect(duyuruButton, &QToolButton::clicked, [=]() {
         if(pcMac->text()==""){mesajSlot("Pc Seçiniz");return;}
         slotSelectPcMesaj(commandFileLE->text());

         mesajSlot("Seçili Pc'ye Mesaj Gönderildi.");
 });



    QToolButton *duyuruAllButton=new QToolButton();
     duyuruAllButton->setFixedSize(e*24,yukseklik*2);
     duyuruAllButton->setAutoRaise(true);
    // duyuruAllButton->setAutoFillBackground(true);
     duyuruAllButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
     duyuruAllButton->setText("Tüm Pc'lere Gönder");
     duyuruAllButton->setIcon(QIcon(":/icons/allpcmessage.svg"));
     duyuruAllButton->setIconSize(QSize(b*8,yukseklik));
     duyuruAllButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

      connect(duyuruAllButton, &QToolButton::clicked, [=]() {
            for(int i=0;i<btnlist.count();i++)
          {
              if(btnlist[i]->ps=="pcopen")
              {
                udpSendData("ekranmesaj",commandFileLE->text(),btnlist[i]->ip);

              }
          }
         mesajSlot("Ağ'a Mesaj Gönderildi.");
 });

      QToolButton *helpButton= new QToolButton;
      helpButton->setFixedSize(e*10,yukseklik*2);
      helpButton->setAutoRaise(true);
     // bilgiButton->setAutoFillBackground(true);
      helpButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
      helpButton->setText("Yardım");
      helpButton->setIcon(QIcon(":/icons/help.svg"));
      helpButton->setIconSize(QSize(b*6,yukseklik));
      helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

      connect(helpButton, &QToolButton::clicked, [=]() {
                   QTextDocument *doc=new QTextDocument();

           doc->setHtml("<center><h2>Mesaj Gönderme</h2></center>"
                        "<center><img src=\":/icons/mesaj.png\" /></center> "
                        "<br/>1-Mesaj sadece X işareti yeşil olan istemcilere gönderilebilir."
                        "<center><img src=\":/icons/istemci.png\" /></center>"
                        "<br/><br/>2-İstemci simgelerinin altındaki X işareti login olmuş kullanıcıyı ifade eder."
                        "<br/><br/>3-X işareti yeşilse kullanıcı login olduğunu ifade eder. Kırmızı ise login olmadığını ifade eder."
                        "<br/><br/>4-Birden fazla istemciye mesaj göndermek için istemci simgelerine çift tıklayıp seçilerek gönderilebilir."
                                        );
           QPrinter pdf;
               pdf.setOutputFileName("/tmp/mesaj.pdf");
               pdf.setOutputFormat(QPrinter::PdfFormat);
               doc->print(&pdf);

           QTextEdit *document = new QTextEdit();
           document->setReadOnly(true);
           //  document->show();
            document->setDocument(doc);
           QVBoxLayout * vbox = new QVBoxLayout();
            QHBoxLayout * hbox1= new QHBoxLayout();

           // hbox1->addWidget(commandFileLabel);
            hbox1->addWidget(document);

            vbox->addLayout(hbox1);
            QDialog * d1 = new QDialog();
            d1->setWindowTitle("Mesaj Gönderme Penceresi");
            d1->setFixedSize(QSize(boy*150,boy*120));
            auto appIcon = QIcon(":/icons/e-ag.svg");
            d1->setWindowIcon(appIcon);

            d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

            d1->setLayout(vbox);
             d1->exec();
   });



     auto layout = new QGridLayout(d);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    layout->addWidget(commandFileLabel, 0,0,1,1,Qt::AlignCenter);
    layout->addWidget(commandFileLE, 0,1,1,1,Qt::AlignCenter);
    layout->addWidget(duyuruButton, 0,2,1,1,Qt::AlignCenter);
    layout->addWidget(duyuruAllButton, 0,3,1,1,Qt::AlignCenter);
    layout->addWidget(helpButton, 0,4,1,1,Qt::AlignCenter);


    d->setLayout(layout);

    return d;

}
QWidget* MainWindow::ayarlarWidget()
{
    int e=en;
    int b=boy;
   // qDebug()<<"ayar click";
    QFont ff( "Arial", 20, 0);
    int yukseklik=b*14;
    QWidget * d = new QWidget();
    d->setFixedSize(this->width(),boy*16);

    d->setWindowTitle("Duyuru Mesaj Penceresi");

    QToolButton *acountButton=new QToolButton();
    acountButton->setFixedSize(e*27,yukseklik);
    acountButton->setAutoRaise(true);
   // duyuruButton->setAutoFillBackground(true);
    acountButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    acountButton->setText("Yerel/Uzak Hesaplar");
    acountButton->setIcon(QIcon(":/icons/login.svg"));
    acountButton->setIconSize(QSize(b*8,b*8));
    acountButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

     connect(acountButton, &QToolButton::clicked, [=]() {
        acountButtonSlot();
 });



    QToolButton *macListe1Button=new QToolButton();
     macListe1Button->setFixedSize(e*27,yukseklik);
     macListe1Button->setAutoRaise(true);
    // macListe1Button->setAutoFillBackground(true);
     macListe1Button->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
     macListe1Button->setText("İstemci Liste");
     macListe1Button->setIcon(QIcon(":/icons/maclist.svg"));
     macListe1Button->setIconSize(QSize(b*8,yukseklik/2));
     macListe1Button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

      connect(macListe1Button, &QToolButton::clicked, [=]() {

        macListWidget()->show();
 });


      QToolButton *webblockButton= new QToolButton;
      webblockButton->setFixedSize(e*27,yukseklik);
      webblockButton->setAutoRaise(true);
     // webblockButton->setAutoFillBackground(true);
      webblockButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
      webblockButton->setText("Web Engelleme");
      webblockButton->setIcon(QIcon(":/icons/webblock.svg"));
      webblockButton->setIconSize(QSize(b*8,yukseklik/2));
      webblockButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


      connect(webblockButton, &QToolButton::clicked, [=]() {
       webBlockSlot();

   });




      QToolButton *clientUpdateButton= new QToolButton;
      clientUpdateButton->setFixedSize(e*29,yukseklik);
      clientUpdateButton->setAutoRaise(true);
     // clientUpdateButton->setAutoFillBackground(true);
      clientUpdateButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
      clientUpdateButton->setText("İstemci Ayarlarını Güncelle");
      clientUpdateButton->setIcon(QIcon(":/icons/clientrefresh.svg"));
      clientUpdateButton->setIconSize(QSize(b*8,yukseklik/2));
      clientUpdateButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

      connect(clientUpdateButton, &QToolButton::clicked, [=]() {
         QString kmt="rm "+QDir::homePath()+"/.ssh/known_hosts";
         system(kmt.toStdString().c_str());
         sshCommandAllSlot("systemctl stop e-ag-client.service");
         system("sleep 1");
         sshCommandAllSlot("systemctl start e-ag-client.service");
         system("sleep 1");
         sshCommandAllSlot("systemctl restart e-ag-client.service");
         system("sleep 1");
         sshCommandAllSlot("sed -i 's/#write_enable=YES/write_enable=YES/' /etc/vsftpd.conf");
         system("sleep 1");
         sshCommandAllSlot("systemctl restart vsftpd.service");

     });

      QToolButton *clientShowButton= new QToolButton;
      clientShowButton->setFixedSize(e*27,yukseklik);
      clientShowButton->setAutoRaise(true);
     // clientShowButton->setAutoFillBackground(true);
      clientShowButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
      clientShowButton->setText("Gizli İstemcileri Göster");
      clientShowButton->setIcon(QIcon(":/icons/showhost.svg"));
      clientShowButton->setIconSize(QSize(b*8,yukseklik/2));
      clientShowButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

      connect(clientShowButton, &QToolButton::clicked, [=]() {

         ///iptal QStringList liste2=fileToList("iplistname");
          QStringList liste2=PcData::onlinePcListe;

          QStringList liste3=fileToList("persistlist",localDir);

          QStringList liste_;
       /*********** iplistname dosyası sshclose yapılıyor***********************************/
         for(int i=0;i<liste2.count();i++)
         {
             QString line=liste2[i];
            if(line!="")
             {
             QStringList lst=line.split("|");
             liste_<<(lst[0]+"|"+lst[1]+"|" +lst[2]+"|" +lst[3]+"|" +lst[4]+"|" +lst[5]+"|"+lst[6]+"|" +lst[7]+"|e");
             liste3=listRemove(liste3,lst[1]); //değişecek satır siliniyor
             liste3<<(lst[0]+"|"+lst[1]+"|" +lst[2]+"|" +lst[3]+"|" +lst[4]+"|" +lst[5]+"|"+lst[6]+"|" +lst[7]+"|e");

            }
         }
         listToFile(liste3,"persistlist");

          ///iptal listToFile(liste_,"iplistname");
          PcData::onlinePcListe=liste_;
          pcListeSlot();

   });

      QToolButton *bilgiButton= new QToolButton;
      bilgiButton->setFixedSize(e*20,yukseklik);
      bilgiButton->setAutoRaise(true);
     // bilgiButton->setAutoFillBackground(true);
      bilgiButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
      bilgiButton->setText("Hakkında");
      bilgiButton->setIcon(QIcon(":/icons/about.svg"));
      bilgiButton->setIconSize(QSize(b*8,yukseklik/2));
      bilgiButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

      connect(bilgiButton, &QToolButton::clicked, [=]() {
       bilgiAlButtonSlot();

   });

      QToolButton *helpButton= new QToolButton;
      helpButton->setFixedSize(e*20,yukseklik);
      helpButton->setAutoRaise(true);
     // bilgiButton->setAutoFillBackground(true);
      helpButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
      helpButton->setText("Yardım");
      helpButton->setIcon(QIcon(":/icons/help.svg"));
      helpButton->setIconSize(QSize(b*8,yukseklik/2));
      helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

      connect(helpButton, &QToolButton::clicked, [=]() {
                  QTextDocument *doc=new QTextDocument();

               doc->setHtml("<center><h2>Ayarlar</h2></center>"
                            "<center><img src=\":/icons/ayar.png\" /></center> "

              "Uygulamanın sorunsuz çalışması için;"

                         "<center><img src=\":/icons/userayar.png\" /></center>"
                            "1-Kontrol edilecek istemcilerin kullanıcı adı ve parolası aynı olmalıdır."
                            "<br/><br/>2-Uygulamanın kurulu olduğu makine yönetici hesabıyla açılmış olmalı.."
                            "<br/><br/>3-Uygulamadaki Yerel Ağ: bulunduğumuz ağ örn:192.168.1.255 şeklinde girilmeli."
                            "<br/><br/>4-Uygulamadaki Tcp Port: yazılımın kullandığı port boş bırakılırsa 7879 olarak ayarlar."
                            "<br/><br/>5-Bu bilgiler kaydedildikten sonra mutlaka yazılım yeniden başlatılmalı."
                            "<br/><br/>6-Yapılan parola, ip ve port değişikliklerini İstemcilerin algılaması için;"
                           " Ayarlar menüsünden İstemci Ayarlarını Güncelle seçilmelidir.."
                           "<br/><br/>7-İstemcilerin listesini İstemci Listele seçeneği ile yapabilir ve listeyi yazdırabiliriz."
                            "<br/><br/>8-Gizlenmiş istemcileri tekrar listede görünmesi için Gizli İstemcileri Göster seçeneğini kullanabilirsiniz."
                            "<br/><br/>9-İstemcilerde web sitesini kelime bazlı kısıtlamaları için;"
                            " Web Engeleme seçeneğini kullanabilirsiniz."
                                       );
               QPrinter pdf;
               pdf.setOutputFileName("/tmp/ayar.pdf");
               pdf.setOutputFormat(QPrinter::PdfFormat);
               doc->print(&pdf);

               QTextEdit *document = new QTextEdit();
               document->setReadOnly(true);
               //  document->show();
               document->setDocument(doc);
               QVBoxLayout * vbox = new QVBoxLayout();
               QHBoxLayout * hbox1= new QHBoxLayout();

               // hbox1->addWidget(commandFileLabel);
               hbox1->addWidget(document);

               vbox->addLayout(hbox1);
               QDialog * d1 = new QDialog();
               d1->setWindowTitle("Ayarlar Yardım Penceresi");
               d1->setFixedSize(QSize(boy*150,boy*127));
               auto appIcon = QIcon(":/icons/e-ag.svg");
               d1->setWindowIcon(appIcon);

               d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

               d1->setLayout(vbox);
               d1->exec();


   });

    auto layout = new QGridLayout(d);
   layout->setContentsMargins(0, 0, 0,0);
   layout->setVerticalSpacing(0);
   layout->setHorizontalSpacing(0);

   layout->addWidget(acountButton, 0,0,1,1,Qt::AlignCenter);
   layout->addWidget(clientUpdateButton, 0,1,1,1,Qt::AlignCenter);
   layout->addWidget(macListe1Button, 0,2,1,1,Qt::AlignCenter);
   layout->addWidget(webblockButton, 0,3,1,1,Qt::AlignCenter);
   layout->addWidget(clientShowButton, 0,4,1,1,Qt::AlignCenter);
   layout->addWidget(helpButton, 0,5,1,1,Qt::AlignCenter);
   layout->addWidget(bilgiButton, 0,6,1,1,Qt::AlignCenter);

   d->setLayout(layout);

    return d;

}

QWidget* MainWindow::rdpWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=b*8;

    QWidget *sor=new QWidget();
    sor->setWindowTitle("Ekran Yansıtma Seçenekleri");
    sor->setStyleSheet("font-size:"+QString::number(font.toInt())+"px;");

    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
   // sor->setFixedSize(e*42,b*15);

    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    sor->move(x, y);
    QCheckBox *cb=new QCheckBox(sor);
    cb->setText("");
    cb->setFixedSize(e*3,yukseklik);
    cb->setText("");
    cb->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    QLabel *cbLabel=new QLabel(sor);
    cbLabel->setText("Sunucuyu\nKontrol Edebilsin");
    cbLabel->setFixedSize(e*20,b*5);
    cbLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    cbLabel->setAlignment(Qt::AlignCenter);

    QToolButton *vncPc=new QToolButton();
    vncPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    vncPc->setIcon(QIcon(":/icons/vnc.svg"));
    vncPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    vncPc->setFixedSize(e*25,yukseklik);
    vncPc->setAutoRaise(true);
   // vncPc->setAutoFillBackground(true);
    vncPc->setText("Vnc Ekran Erişimi");
    connect(vncPc, &QToolButton::clicked, [=]() {
        slotVnc(_display);
    });

    QToolButton *rdpPc=new QToolButton();
    rdpPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    rdpPc->setIcon(QIcon(":/icons/rdp.svg"));
    rdpPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    rdpPc->setFixedSize(e*25,yukseklik);
    rdpPc->setAutoRaise(true);
   // rdpPc->setAutoFillBackground(true);
    rdpPc->setText("Rdp Ekran Erişimi");
    connect(rdpPc, &QToolButton::clicked, [=]() {
        slotRdp();
    });
    QLabel *boyutLabel=new QLabel(sor);
    boyutLabel->setText("Sunucu Ekran Boyutu");
    boyutLabel->setFixedSize(e*25,b*5);
    boyutLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    QComboBox *ekranScale1 = new QComboBox();
    ekranScale1->setFixedSize(e*25,yukseklik);
   // ekranScale1->move(0,40);
   // ekranScale1->setFrame(true);
    ekranScale1->setStyleSheet(" font-size:"+QString::number(font.toInt()-2)+"px;");
    ekranScale1->addItem("800x600");
    ekranScale1->addItem("1024x768");
    ekranScale1->addItem("1280x1024");
    ekranScale1->addItem("1366x768");
    ekranScale1->addItem("1920x1080");
    ekranScale1->addItem("3840x2160");

    ekranScale1->setCurrentIndex(3);


    QToolButton *serverEkranYansitSeciliPcButton= new QToolButton();
    serverEkranYansitSeciliPcButton->setFixedSize(e*30,yukseklik);
    //serverEkranYansitSeciliPcButton->setIconSize(QSize(150,30));
    serverEkranYansitSeciliPcButton->setText("Ekranı Seçili Pc'lere Yansıt");
    serverEkranYansitSeciliPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    serverEkranYansitSeciliPcButton->setAutoRaise(true);
  //  serverEkranYansitSeciliPcButton->setAutoFillBackground(true);

    serverEkranYansitSeciliPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    serverEkranYansitSeciliPcButton->setIcon(QIcon(":icons/networkvnc.svg"));

    connect(serverEkranYansitSeciliPcButton, &QPushButton::clicked, [=]() {
     bool cbstate=cb->checkState();
     QString viewState="";
     //qDebug()<<cbstate;
     if (!cbstate) viewState="-viewonly";
        slotVncFlip(ekranScale1->currentText(),viewState);

 });
    QToolButton *serverEkranYansitButton= new QToolButton();
    serverEkranYansitButton->setFixedSize(e*30,yukseklik);
   // serverEkranYansitButton->setIconSize(QSize(150,30));
    serverEkranYansitButton->setText("Ekranı Tüm Pc'lere Yansıt");
   serverEkranYansitButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
   serverEkranYansitButton->setAutoRaise(true);
  // serverEkranYansitButton->setAutoFillBackground(true);

    serverEkranYansitButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    serverEkranYansitButton->setIcon(QIcon(":icons/networkvncall.svg"));
    //serverEkranYansitButton->move(0,sor->height()-50);
    connect(serverEkranYansitButton, &QPushButton::clicked, [=]() {
        bool cbstate=cb->checkState();
        QString viewState="";
        if (!cbstate) viewState="-viewonly";

        slotVncFlipAll(ekranScale1->currentText(),viewState);


 });


    QToolButton* ekranYansitDurdur = new QToolButton();
    ekranYansitDurdur->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    ekranYansitDurdur->setIcon(QIcon(":/icons/networkvncstop.svg"));
    ekranYansitDurdur->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ekranYansitDurdur->setFixedSize(e*30,yukseklik);
    ekranYansitDurdur->setAutoRaise(true);
   // ekranYansitDurdur->setAutoFillBackground(true);
    ekranYansitDurdur->setText("Seçililerde Yansıtmayı Durdur");
    connect(ekranYansitDurdur, &QToolButton::clicked, [=]() {
        //slotEkranIzleDurdur();
        slotVncFlipStop();
    });
    QToolButton* ekranYansitDurdurAll = new QToolButton();
    ekranYansitDurdurAll->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    ekranYansitDurdurAll->setIcon(QIcon(":/icons/networkvncallstop.svg"));
    ekranYansitDurdurAll->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ekranYansitDurdurAll->setFixedSize(e*30,yukseklik);
    ekranYansitDurdurAll->setAutoRaise(true);
  //  ekranYansitDurdurAll->setAutoFillBackground(true);
    ekranYansitDurdurAll->setText("Tümünde Yansıtmayı Durdur");
    connect(ekranYansitDurdurAll, &QToolButton::clicked, [=]() {
        //slotEkranIzleDurdur();
        slotVncFlipStop();
    });
    QToolButton *helpButton= new QToolButton;
    helpButton->setFixedSize(e*10,yukseklik*2);
    helpButton->setAutoRaise(true);
   // bilgiButton->setAutoFillBackground(true);
    helpButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    helpButton->setText("Yardım");
    helpButton->setIcon(QIcon(":/icons/help.svg"));
    helpButton->setIconSize(QSize(b*6,yukseklik/2));
    helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(helpButton, &QToolButton::clicked, [=]() {
        QTextDocument *doc=new QTextDocument();

        doc->setHtml("<center><h2>Ekran Paylaşımı</h2></center>"
                     "<center><img src=\":/icons/ekranpaylasimi.png\" /></center> "
                     "<br/>1-Ekran paylaşımı vnc servisi ile çalıştırılmaktadır."
                     "<center><img src=\":/icons/istemci.png\" /></center>"
                     "<br/>2-İstemci simgelerinin altındaki V işareti vnc servisini ifade eder."
                     "<br/><br/>3-V işareti yeşilse vnc çalışıyor. Kırmızı ise vnc çalışmıyordur."
                     "<br/><br/>4-Sorunsuz ekran paylaşımı yapmak için istemcilerde vnc servisinin çalışıyor olması gerekmektedir."
                     "<br/><br/>5-vnc servisinin çalışıp çalışmadığını manuel test etmek için Temel İşlemler bölümünden \"Servis Sorgula\" seçeneğini kullanabilirsiniz."
                     "<br/><br/>6-Birden fazla istemciye Sunucu ekranı paylaşmak için istemci simgelerine çift tıklayıp seçilerek paylaşılabilir."
                     "<br/><br/>7-Sunucu ekranı paylaşılırken, istemci ekranında hangi çözünürlükte görülmesini istiyorsak çözünürlük seçenekleri kullanılınabilir."
                     "<br/><br/>8-Sunucu ekranı paylaşılırken, istemciler ekranı kontrol edip/edemeyeceği seçilebilir."
                     "<br/><br/>9-Canlı istemci ekranına erişim \"Vnc Ekran Erişimi\" ile yapılabilir."
                     "<br/><br/>10-Canlı istemci ekranından bağımsız erişim \"Rdp Ekran Erişimi\" ile yapılabilir."
                     );
        QPrinter pdf;
            pdf.setOutputFileName("/tmp/ekranpaylasimi.pdf");
            pdf.setOutputFormat(QPrinter::PdfFormat);
            doc->print(&pdf);

        QTextEdit *document = new QTextEdit();
        document->setReadOnly(true);
        //  document->show();
         document->setDocument(doc);
        QVBoxLayout * vbox = new QVBoxLayout();
         QHBoxLayout * hbox1= new QHBoxLayout();

        // hbox1->addWidget(commandFileLabel);
         hbox1->addWidget(document);

         vbox->addLayout(hbox1);
         QDialog * d1 = new QDialog();
         d1->setWindowTitle("Ekran Paylaşımı Yardım Penceresi");
         d1->setFixedSize(QSize(boy*150,boy*120));
         auto appIcon = QIcon(":/icons/e-ag.svg");
         d1->setWindowIcon(appIcon);

         d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

         d1->setLayout(vbox);
          d1->exec();
 });


    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);
    layout->addWidget(vncPc, 4,0,1,1,Qt::AlignCenter);
    layout->addWidget(rdpPc, 5,0,1,1,Qt::AlignCenter);


    layout->addWidget(boyutLabel, 4,2,1,1,Qt::AlignCenter);
    layout->addWidget(ekranScale1, 5,2,1,1,Qt::AlignCenter);

    layout->addWidget(cb, 4,3,1,1,Qt::AlignCenter);
    layout->addWidget(cbLabel, 5,3,1,1,Qt::AlignCenter);

    layout->addWidget(serverEkranYansitSeciliPcButton, 4,4,1,1,Qt::AlignCenter);
    layout->addWidget(serverEkranYansitButton, 5,4,1,1,Qt::AlignCenter);

    layout->addWidget(ekranYansitDurdur, 4,6,1,1,Qt::AlignCenter);
    layout->addWidget(ekranYansitDurdurAll, 5,6,1,1,Qt::AlignCenter);
    layout->addWidget(helpButton, 4,7,2,1,Qt::AlignCenter);

return sor;
   // sor->show();

    //slotVncFlip(ekranScale->currentText());
}
QWidget* MainWindow::kilitWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=b*12;
    QWidget *sor=new QWidget();
    sor->setWindowTitle("Ekran Yansıtma Seçenekleri");
    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
    sor->setFixedSize(yukseklik*1.5,boy*16);
    //sor->setStyleSheet("background-color: #dceded;font-size:"+QString::number(font.toInt()-2)+"px;");

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
   // sor->move(x, y);
    /**************************************************/
    QToolButton *lockPc=new QToolButton();
    lockPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    lockPc->setIcon(QIcon(":/icons/lock.svg"));
    lockPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    lockPc->setFixedSize(yukseklik*1.5,b*7);
    lockPc->setAutoRaise(true);
   // lockPc->setAutoFillBackground(true);
    lockPc->setText("Kilitle");

   // lockPc->setMenu(kilitMenu());
   // lockPc->setPopupMode(QToolButton::MenuButtonPopup);

    connect(lockPc, &QToolButton::clicked, [=]() {
       slotKilit();
     //   qDebug()<<"kilit";
    });
    /**************************************************/
    QToolButton *unlockPc=new QToolButton();
    unlockPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    unlockPc->setIcon(QIcon(":/icons/unlock.svg"));
    unlockPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    unlockPc->setFixedSize(yukseklik*1.5,b*7);
    unlockPc->setAutoRaise(true);
    //unlockPc->setAutoFillBackground(true);
    unlockPc->setText("Kilit Aç");
  //  unlockPc->setMenu(kilitMenu());
    //unlockPc->setPopupMode(QToolButton::MenuButtonPopup);

    connect(unlockPc, &QToolButton::clicked, [=]() {
        slotKilitAc();
    });


    QToolButton *kilitMenuButton= new QToolButton();
   // kilitMenuButton->setIcon(QIcon(":/icons/transparanlock.svg"));
    kilitMenuButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    kilitMenuButton->setFixedSize(e*5,b*2);
    kilitMenuButton->setAutoRaise(true);
    //kilitMenuButton->setAutoFillBackground(true);
     kilitMenuButton->setText("");
    kilitMenuButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    kilitMenuButton->setMenu(kilitMenu());
    kilitMenuButton->setPopupMode(QToolButton::InstantPopup);

    connect(kilitMenuButton, &QPushButton::clicked, [=]() {
       // slotKilitAcAll();
     });


    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);
    layout->addWidget(lockPc, 4,0,1,1,Qt::AlignCenter);

    layout->addWidget(unlockPc, 5,0,1,1,Qt::AlignCenter);
    layout->addWidget(kilitMenuButton, 6,0,1,1,Qt::AlignRight);

   /// layout->addWidget(kilitAllButton, 7,0,1,1);

  /// layout->addWidget(kilitAcAllButton, 8,0,1,1);

  return sor;
   // sor->show();

    //slotVncFlip(ekranScale->currentText());
}

QWidget* MainWindow::kilittransparanWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=e*12;
    QWidget *sor=new QWidget();
    sor->setWindowTitle("Ekran Yansıtma Seçenekleri");
    sor->setStyleSheet("font-size:"+QString::number(font.toInt())+"px;");

    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
    sor->setFixedSize(yukseklik*1.5,boy*16);
    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
   // sor->move(x, y);
    /**************************************************/

    QToolButton *transparanUnlockPc=new QToolButton();
    transparanUnlockPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    transparanUnlockPc->setIcon(QIcon(":/icons/transparanunlock.svg"));
    transparanUnlockPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    transparanUnlockPc->setFixedSize(yukseklik*1.5,boy*7);
    transparanUnlockPc->setAutoRaise(true);
   // transparanUnlockPc->setAutoFillBackground(true);
    transparanUnlockPc->setText("Şeffaf Kilit Aç");
    //transparanUnlockPc->setMenu(sessionMenu());
    //transparanUnlockPc->setPopupMode(QToolButton::MenuButtonPopup);

    connect(transparanUnlockPc, &QToolButton::clicked, [=]() {
        slotTransparanKilitAc();
    });

    /**************************************************/
    QToolButton *transparanLockPc=new QToolButton();
    transparanLockPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    transparanLockPc->setIcon(QIcon(":/icons/transparanlock.svg"));
    transparanLockPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    transparanLockPc->setFixedSize(yukseklik*1.5,boy*7);
    transparanLockPc->setAutoRaise(true);
   // transparanLockPc->setAutoFillBackground(true);
    transparanLockPc->setText("Şeffaf Kilitle");
    //transparanLockPc->setMenu(sessionMenu());
    //transparanLockPc->setPopupMode(QToolButton::MenuButtonPopup);
    connect(transparanLockPc, &QToolButton::clicked, [=]() {
        slotTransparanKilit();
  });

    QToolButton *transparanKilitMenuButton= new QToolButton();
   // transparanKilitMenuButton->setIcon(QIcon(":/icons/transparanlock.svg"));
    transparanKilitMenuButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    transparanKilitMenuButton->setFixedSize(e*5,b*2);
    transparanKilitMenuButton->setAutoRaise(true);
    //transparanKilitMenuButton->setAutoFillBackground(true);
     transparanKilitMenuButton->setText("");
    transparanKilitMenuButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    transparanKilitMenuButton->setMenu(transparanKilitMenu());
    transparanKilitMenuButton->setPopupMode(QToolButton::InstantPopup);

    connect(transparanKilitMenuButton, &QPushButton::clicked, [=]() {
       // slotKilitAcAll();
     });
    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);
    layout->addWidget(transparanLockPc, 4,1,1,1,Qt::AlignCenter);

    layout->addWidget(transparanUnlockPc, 5,1,1,1,Qt::AlignCenter);

    layout->addWidget(transparanKilitMenuButton, 6,1,1,1,Qt::AlignRight);

  return sor;
   // sor->show();

    //slotVncFlip(ekranScale->currentText());
}

QWidget* MainWindow::ekranWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=e*12;

    QWidget *sor=new QWidget();
    sor->setWindowTitle("Ekran Yansıtma Seçenekleri");
    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
    sor->setFixedSize(yukseklik*1.5,boy*16);
    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    sor->move(x, y);
    /**************************************************/
    QToolButton *screenImagePc=new QToolButton();
    screenImagePc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    screenImagePc->setIcon(QIcon(":/icons/monitor.svg"));
    screenImagePc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    screenImagePc->setFixedSize(yukseklik*1.5,boy*7);
    screenImagePc->setAutoRaise(true);
   // screenImagePc->setAutoFillBackground(true);
    screenImagePc->setText("Ekran İzle");
   // screenImagePc->setMenu(sessionMenu());
   // screenImagePc->setPopupMode(QToolButton::MenuButtonPopup);

    connect(screenImagePc, &QToolButton::clicked, [=]() {
        slotEkranIzle();
    });

    QToolButton* screenImagePcStop = new QToolButton(0);
    screenImagePcStop->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    screenImagePcStop->setIcon(QIcon(":/icons/monitorstop.svg"));
    screenImagePcStop->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    screenImagePcStop->setFixedSize(yukseklik*1.5,boy*7);
    screenImagePcStop->setAutoRaise(true);
   // screenImagePcStop->setAutoFillBackground(true);
    screenImagePcStop->setText("İzleme Durdur");
   // screenImagePcStop->setMenu(sessionMenu());
    //screenImagePcStop->setPopupMode(QToolButton::MenuButtonPopup);

    connect(screenImagePcStop, &QToolButton::clicked, [=]() {
        slotEkranIzleDurdur();
    });

    QToolButton *ekranMenuButton= new QToolButton();
   // ekranMenuButton->setIcon(QIcon(":/icons/transparanlock.svg"));
    ekranMenuButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ekranMenuButton->setFixedSize(e*5,b*2);
    ekranMenuButton->setAutoRaise(true);
    //ekranMenuButton->setAutoFillBackground(true);
     ekranMenuButton->setText("");
    ekranMenuButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    ekranMenuButton->setMenu(ekranImageMenu());
    ekranMenuButton->setPopupMode(QToolButton::InstantPopup);

    connect(ekranMenuButton, &QPushButton::clicked, [=]() {
       // slotKilitAcAll();
     });
    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);
    layout->addWidget(screenImagePc, 4,0,1,1,Qt::AlignCenter);
    layout->addWidget(screenImagePcStop, 5,0,1,1,Qt::AlignCenter);
   layout->addWidget(ekranMenuButton, 6,0,1,1,Qt::AlignRight);
  return sor;
}

QWidget* MainWindow::poweroffrebootWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=e*12;

    QWidget *sor=new QWidget();
    sor->setWindowTitle("Ekran Yansıtma Seçenekleri");
    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
    sor->setFixedSize(yukseklik*1.5,boy*16);

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    sor->move(x, y);
    /**************************************************/

    QToolButton *closePc=new QToolButton();
    closePc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    closePc->setIcon(QIcon(":/icons/close.svg"));
    closePc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    closePc->setFixedSize(yukseklik*1.5,boy*7);
    closePc->setAutoRaise(true);
    //closePc->setAutoFillBackground(true);
    closePc->setText("Kapat");
   // closePc->setMenu(sessionMenu());
   // closePc->setPopupMode(QToolButton::MenuButtonPopup);
    connect(closePc, &QToolButton::clicked, [=]() {
     slotPowerOff();
    });

    QToolButton *rebootPc=new QToolButton();
    rebootPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    rebootPc->setIcon(QIcon(":/icons/reboot.svg"));
    rebootPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    rebootPc->setFixedSize(yukseklik*1.5,boy*7);
    rebootPc->setAutoRaise(true);
    //rebootPc->setAutoFillBackground(true);
    rebootPc->setText("Yeniden Başlat");
   // rebootPc->setMenu(sessionMenu());
   // rebootPc->setPopupMode(QToolButton::MenuButtonPopup);

    connect(rebootPc, &QToolButton::clicked, [=]() {
        slotReboot();
    });

    QToolButton *poweroffRebootMenuButton= new QToolButton();
   // poweroffRebootMenuButton->setIcon(QIcon(":/icons/transparanlock.svg"));
    poweroffRebootMenuButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    poweroffRebootMenuButton->setFixedSize(e*5,b*2);
    poweroffRebootMenuButton->setAutoRaise(true);
    //poweroffRebootMenuButton->setAutoFillBackground(true);
     poweroffRebootMenuButton->setText("");
    poweroffRebootMenuButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    poweroffRebootMenuButton->setMenu(poweroffRebootMenu());
    poweroffRebootMenuButton->setPopupMode(QToolButton::InstantPopup);

    connect(poweroffRebootMenuButton, &QPushButton::clicked, [=]() {
       // slotKilitAcAll();
     });
    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);
    layout->addWidget(closePc, 4,0,1,1,Qt::AlignCenter);
  ///layout->addWidget(closePcAll, 5,0,1,1,Qt::AlignCenter);
   layout->addWidget(rebootPc, 6,0,1,1,Qt::AlignCenter);
   layout->addWidget(poweroffRebootMenuButton, 7,0,1,1,Qt::AlignRight);

  return sor;
 }

QWidget* MainWindow::logoutWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=e*12;

    QWidget *sor=new QWidget();
    sor->setWindowTitle("Ekran Yansıtma Seçenekleri");
    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
    sor->setFixedSize(yukseklik*1.5,boy*16);

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    sor->move(x, y);
    /**************************************************/
    /******************************************************/
    QToolButton *logoutPc=new QToolButton();
    logoutPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    logoutPc->setIcon(QIcon(":/icons/session.svg"));
    logoutPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  //  logoutPc->setIconSize(QSize(yukseklik,yukseklik*0.75));

    logoutPc->setFixedSize(yukseklik*1.5,boy*7);
    logoutPc->setAutoRaise(true);
   // logoutPc->setAutoFillBackground(true);
    logoutPc->setText("Oturum Kapat");
   // logoutPc->setMenu(sessionMenu());
   // logoutPc->setPopupMode(QToolButton::MenuButtonPopup);

    connect(logoutPc, &QToolButton::clicked, [=]() {
        slotLogout();
    });


    QToolButton* loginPc = new QToolButton(0);
    loginPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    loginPc->setIcon(QIcon(":/icons/login.svg"));
    loginPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
   // loginPc->setIconSize(QSize(yukseklik,yukseklik*0.75));

    loginPc->setFixedSize(yukseklik*1.5,boy*7);
    loginPc->setAutoRaise(true);
   // portKontrol->setAutoFillBackground(true);
    loginPc->setText("Oturum Aç");
    connect(loginPc, &QToolButton::clicked, [=]() {
        slotLogin();
    });
    QToolButton *sessionMenuButton= new QToolButton();
      // sessionMenuButton->setIcon(QIcon(":/icons/transparanlock.svg"));
       sessionMenuButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
       sessionMenuButton->setFixedSize(e*5,b*2);
       sessionMenuButton->setAutoRaise(true);
       //sessionMenuButton->setAutoFillBackground(true);
        sessionMenuButton->setText("");
       sessionMenuButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
       sessionMenuButton->setMenu(sessionMenu());
       sessionMenuButton->setPopupMode(QToolButton::InstantPopup);

       connect(sessionMenuButton, &QPushButton::clicked, [=]() {
          // slotKilitAcAll();
        });

    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);
    layout->addWidget(logoutPc, 4,0,1,1,Qt::AlignCenter);
  ///  layout->addWidget(closePcAll, 5,0,1,1,Qt::AlignCenter);
   layout->addWidget(loginPc, 6,0,1,1,Qt::AlignCenter);
  layout->addWidget(sessionMenuButton, 7,0,1,1,Qt::AlignRight);

  return sor;
   // sor->show();

    //slotVncFlip(ekranScale->currentText());
}

QWidget* MainWindow::pcInfo()
{
    int e=en;
    int b=boy;
    int yukseklik=e*10;
     QWidget * d = new QWidget();
   // d->setFixedSize(e*180,b*23);
   // d->setStyleSheet("background-color: #ffdced;font-size:"+QString::number(font.toInt()-2)+"px;");

    QToolButton *hostListePcButton = new QToolButton();
    hostListePcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    hostListePcButton->setIcon(QIcon(":icons/liste.svg"));
    hostListePcButton->setIconSize(QSize(yukseklik,boy*8));
    hostListePcButton->setAutoRaise(true);
    //hostListePcButton->setAutoFillBackground(true);
    hostListePcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
   hostListePcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    hostListePcButton->setText("Yenile");
    connect(hostListePcButton, &QToolButton::clicked, [=]() {
        tamReset=true;
     pcListeSlot();
});

    QToolButton *vncConnectPcButton = new QToolButton();
    vncConnectPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    vncConnectPcButton->setIcon(QIcon(":icons/vnc.svg"));
    vncConnectPcButton->setIconSize(QSize(yukseklik,boy*8));
    vncConnectPcButton->setAutoRaise(true);
   // vncConnectPcButton->setAutoFillBackground(true);
    vncConnectPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    vncConnectPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    vncConnectPcButton->setText("VNC");
    connect(vncConnectPcButton, &QToolButton::clicked, [=]() {
        slotVnc(_display);
    });

    QToolButton *xrdpConnectPcButton = new QToolButton();
    xrdpConnectPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    xrdpConnectPcButton->setIcon(QIcon(":icons/rdp.svg"));
    xrdpConnectPcButton->setIconSize(QSize(yukseklik,boy*8));
    xrdpConnectPcButton->setAutoRaise(true);
   // xrdpConnectPcButton->setAutoFillBackground(true);
    xrdpConnectPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    xrdpConnectPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    xrdpConnectPcButton->setText("RDP");
    connect(xrdpConnectPcButton, &QToolButton::clicked, [=]() {
        slotRdp();
    });

    QToolButton *terminalPcButton = new QToolButton();
    terminalPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    terminalPcButton->setIcon(QIcon(":icons/ssh.svg"));
    terminalPcButton->setIconSize(QSize(yukseklik,boy*8));
    terminalPcButton->setAutoRaise(true);
  //  terminalPcButton->setAutoFillBackground(true);
    terminalPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    terminalPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    terminalPcButton->setText("Terminal");
    connect(terminalPcButton, &QToolButton::clicked, [=]() {
        terminalSlot();
    });

    QToolButton *selectPcButton = new QToolButton();
     selectPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
     selectPcButton->setIconSize(QSize(yukseklik,boy*8));
     selectPcButton->setIcon(QIcon(":icons/select.svg"));
     selectPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
     selectPcButton->setAutoRaise(true);
    // selectPcButton->setAutoFillBackground(true);
     selectPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

      selectPcButton->setText("Pc Seç");
     connect(selectPcButton, &QToolButton::clicked, [=]() {
          selectSlot();

     });


    QToolButton *ftpPc=new QToolButton();
    ftpPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    ftpPc->setIcon(QIcon(":/icons/ftp.svg"));
    ftpPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ftpPc->setIconSize(QSize(yukseklik,boy*8));

    ftpPc->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    ftpPc->setAutoRaise(true);
   // ftpPc->setAutoFillBackground(true);
    ftpPc->setText("FTP");
    connect(ftpPc, &QToolButton::clicked, [=]() {
        ftpConnectButtonSlot();
    });

    QToolButton *wolButton=new QToolButton();
    wolButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    wolButton->setIcon(QIcon(":/icons/wol.svg"));
    wolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    wolButton->setIconSize(QSize(yukseklik,boy*8));

    wolButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    wolButton->setAutoRaise(true);
   // ftpPc->setAutoFillBackground(true);
    wolButton->setText("Pc Aç");
    connect(wolButton, &QToolButton::clicked, [=]() {
        wolSlot();
    });

    QToolButton* portKontrol = new QToolButton(0);
    portKontrol->setFixedSize(yukseklik*0.9, yukseklik*1.5);
    portKontrol->setIconSize(QSize(yukseklik,boy*8));
    portKontrol->setIcon(QIcon(":/icons/about.svg"));
    portKontrol->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    portKontrol->setAutoRaise(true);
    portKontrol->setText("Servisler");
    portKontrol->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(portKontrol, &QToolButton::clicked, [=]() {
        slotServisControl();
    });

    QToolButton *helpButton= new QToolButton;
    helpButton->setFixedSize(yukseklik*0.9, yukseklik*1.5);
    helpButton->setIconSize(QSize(yukseklik,boy*8));
    helpButton->setIcon(QIcon(":/icons/help.svg"));
    helpButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    helpButton->setText("Yardım");
    helpButton->setAutoRaise(true);

     helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(helpButton, &QToolButton::clicked, [=]() {

        QTextDocument *doc=new QTextDocument();

        doc->setHtml("<center><h2>Temel İşlemler</h2></center>"
                     "<center><img src=\":/icons/temelislem.png\" /></center> "
                     "1-Ağ üzerinde açık istemcileri listelemek için Yenile seçeneği kullanılmalıdır."
                      "<br/><br/>2-Birden fazla istemciyi seçmek için çift tıklama/sol tuşa basarak alan seçimi yapılabilir."
                      "Seçili olmayan istemcileri seçmek için Pc Seç seçeneği kullanılır."
                      "<br/><br/>3-İstemcinin canlı ekranı Vnc seçeneği ile erişilebilir."
                      "<br/><br/>4-İstemcinin kullanıcıdan bağımsız ekranına Rdp seçeneği ile erişilebilir."
                      "<br/><br/>5-İstemcinin ssh üzerinden konsoluna bağlanmak için Terminal seçeneği kullanılabilir."
                      "<br/><br/>6-İstemcinin dosyalarına dosya yöneticisi ile erişmek için Ftp seçeneği kullanılabilir."
                      "<br/><br/>7-İstemcinin uzaktan başlatmak için Pc Aç seçeneği kullanılabilir."
                      "Pc Aç seçeneği için; İstemcinin BIOS seçeneklerinden Wake On Lan seçeneği aktif edilmeli. "
                      "<br/><br/>8-İstemci simgelerinin altındaki P V S F X işaretleri servisleri ifade eder."
                     "<center><img src=\":/icons/istemci.png\" /></center>"
                     "Simgeler yeşilse servis çalışıyor. Kırmızı ise servis çalışmıyordur."
                      "<br/>P=İstemci, yeşil=istemci açık/kırmızı=istemci kapalı"
                      "<br/>V=Vnc servisi, yeşil=açık/kırmızı=kapalı"
                      "<br/>S=Ssh servisi, yeşil=açık/kırmızı=kapalı"
                      "<br/>F=Ftp servisi, yeşil=açık/kırmızı=kapalı"
                      "<br/>X=x11 ekranı, yeşil=kullanıcı login olmuş/kırmızı=kullanıcı login olmamış"
                 );
        QPrinter pdf;
            pdf.setOutputFileName("/tmp/temelislem.pdf");
            pdf.setOutputFormat(QPrinter::PdfFormat);
            doc->print(&pdf);

        QTextEdit *document = new QTextEdit();
        document->setReadOnly(true);
        //  document->show();
         document->setDocument(doc);
        QVBoxLayout * vbox = new QVBoxLayout();
         QHBoxLayout * hbox1= new QHBoxLayout();

        // hbox1->addWidget(commandFileLabel);
         hbox1->addWidget(document);

         vbox->addLayout(hbox1);
         QDialog * d1 = new QDialog();
         d1->setWindowTitle("Temel İşlemler Yardım Penceresi");
         d1->setFixedSize(QSize(boy*150,boy*120));
         auto appIcon = QIcon(":/icons/e-ag.svg");
         d1->setWindowIcon(appIcon);

         d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

         d1->setLayout(vbox);
          d1->exec();

 });
  /******************************************************/
    auto layout = new QGridLayout(d);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
  //  layout->setHorizontalSpacing(0);
    layout->addWidget(hostListePcButton, 0,0,3,1);
    layout->addWidget(selectPcButton, 0,1,3,1);

    layout->addWidget(vncConnectPcButton, 0,2,3,1);
    layout->addWidget(xrdpConnectPcButton, 0,3,3,1);

    layout->addWidget(terminalPcButton, 0,4,3,1);
    layout->addWidget(ftpPc, 0,5,3,1);
    layout->addWidget(wolButton, 0,6,3,1);

    layout->addWidget(kilitWidget(), 0,7,3,1);
    layout->addWidget(kilittransparanWidget(), 0,10,3,1);
    layout->addWidget(ekranWidget(), 0,15,3,1);
    layout->addWidget(poweroffrebootWidget(), 0,20,3,1);

    layout->addWidget(logoutWidget(), 0,25,3,1);
    layout->addWidget(portKontrol, 0,26,3,1);

    layout->addWidget(helpButton, 0,27,3,1);



     d->setLayout(layout);
    return d;
}

void MainWindow::acountButtonSlot()
{
   // qDebug()<<"ayar click";
   // if(localNetwork=="") localNetwork=(broadCastAddress);
     if(tcpPort=="") tcpPort="7879";
    QDialog * d = new QDialog();
    d->setWindowTitle("Yerel/Uzak Kullanıcı");
    d->setFixedSize(QSize(boy*70,boy*50));
    auto appIcon = QIcon(":/icons/e-ag.svg");
    d->setWindowIcon(appIcon);

    d->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    QLineEdit * remoteUserNameLE = new QLineEdit();remoteUserNameLE->setFixedSize(boy*20,en*5);
    QLineEdit * remotePasswordLE = new QLineEdit();remotePasswordLE->setFixedSize(boy*20,en*5);
    QLineEdit * localUserNameLE = new QLineEdit();localUserNameLE->setFixedSize(boy*20,en*5);
    QLineEdit * localPasswordLE = new QLineEdit();localPasswordLE->setFixedSize(boy*20,en*5);
    QLineEdit * localNetworkLE1 = new QLineEdit();localNetworkLE1->setFixedSize(boy*20,en*5);
    QLineEdit * localNetworkLE2 = new QLineEdit();localNetworkLE2->setFixedSize(boy*20,en*5);
     QLineEdit * tcpPortLE = new QLineEdit();tcpPortLE->setFixedSize(boy*20,en*5);

    QLabel *remoteUserNameLabel=new QLabel("Kontrol Edilecek İstemci Kullanıcı Adı");
    QLabel *remotePasswordLabel=new QLabel("Kontrol Edilecek İstemci Kullanıcı Parolası");
    QLabel *localUserNameLabel=new QLabel("Bu Bilgisayarın Kullanıcı Adı");
    QLabel *localPasswordLabel=new QLabel("Bu Bilgisayarın Kullanıcı Parolası");
    QLabel *localNetworkLabel1=new QLabel("Yerel Ağ Yayın Adresi 1");
    QLabel *localNetworkLabel2=new QLabel("Yerel Ağ Yayın Adresi 2");

    QLabel *tcpPortLabel=new QLabel("Port");
    remoteUserNameLE->setText(remoteUserName);
    remotePasswordLE->setText(remotePassword);
    localUserNameLE->setText(localUserName);
    localPasswordLE->setText(localPassword);
    localNetworkLE1->setText(broadCastAddress1);
    localNetworkLE2->setText(broadCastAddress2);

    tcpPortLE->setText(tcpPort);
    // messageBox.setIcon(QMessageBox::Question);

           QDialogButtonBox * buttonBox = new QDialogButtonBox();

            buttonBox->addButton("Kaydet", QDialogButtonBox::AcceptRole);
            buttonBox->addButton("Vazgeç", QDialogButtonBox::RejectRole);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    QVBoxLayout * vbox = new QVBoxLayout();
    QHBoxLayout * hbox1= new QHBoxLayout();
    QHBoxLayout * hbox2= new QHBoxLayout();
    QHBoxLayout * hbox3= new QHBoxLayout();
    QHBoxLayout * hbox4= new QHBoxLayout();
    QHBoxLayout * hbox5= new QHBoxLayout();
    QHBoxLayout * hbox6= new QHBoxLayout();
    QHBoxLayout * hbox7= new QHBoxLayout();

    hbox1->addWidget(remoteUserNameLabel);
    hbox1->addWidget(remoteUserNameLE);

    hbox2->addWidget(remotePasswordLabel);
    hbox2->addWidget(remotePasswordLE);

    hbox3->addWidget(localUserNameLabel);
    hbox3->addWidget(localUserNameLE);

    hbox4->addWidget(localPasswordLabel);
    hbox4->addWidget(localPasswordLE);

    hbox5->addWidget(localNetworkLabel1);
    hbox5->addWidget(localNetworkLE1);
    hbox6->addWidget(localNetworkLabel2);
    hbox6->addWidget(localNetworkLE2);

    hbox7->addWidget(tcpPortLabel);
    hbox7->addWidget(tcpPortLE);


    //vbox->addWidget(pcnameLabel);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox3);
    vbox->addLayout(hbox4);
    vbox->addLayout(hbox5);
    vbox->addLayout(hbox6);
    vbox->addLayout(hbox7);

    vbox->addWidget(buttonBox);

    d->setLayout(vbox);

    int result = d->exec();
    if(result == QDialog::Accepted)
    {
       // qDebug()<<"tamam";
       remoteUserName= remoteUserNameLE->text();
       remotePassword= remotePasswordLE->text();
       localUserName= localUserNameLE->text();
       localPassword= localPasswordLE->text();
       broadCastAddress1= localNetworkLE1->text();
       broadCastAddress2= localNetworkLE2->text();
        tcpPort= tcpPortLE->text();
        ayarKaydetButtonSlot();
    }

    if(result == QDialog::Rejected)
    {
        qDebug()<<"iptal";

    }

}


void MainWindow::bilgiAlButtonSlot()
{

    QTextDocument *doc=new QTextDocument();

    doc->setHtml("<center><h2>Program Hakkında</h2></center>"
                 "<center><img src=\":/icons/e-ag.svg\" width=100 height=100 /></center> "
                 "Bu uygulama yerel ağda bilgisayarlara erişim ve yönetmek için yazılmıştır."
                 "<br/> Yapılabilecek Eylemler:"
                 "<br/> Açık olan bilgisayarlara linux komutlarını aynı anda çalıştırabilirsiniz."
                 "<br/> Birden fazla bilgisayara aynı anda dosya kopyalayabilirsiniz.  "
                 "<br/> Bütün bilgisayarlara  ya da tek bilgisayarın ekranına mesaj gönderebilirsiniz."
                 "<br/> Bütün bilgisayarları ya da tek bilgisayarın ekranını kilitleyebilirsiniz."
                 "<br/> Bütün bilgisayarları ya da tek bilgisayarı kapatabilirsiniz."
                 "<br/> Bütün bilgisayarları ya da tek bilgisayarı güncellemeler yapabilirsiniz."
                 "<br/> Açık bilgisayara ftp erişimi yapılabilir."
                 "<br/> Açık bilgisayarın ekranına erişim ve kullanma. "
                 "<br/> Video yayını yapabilirsiniz."
                 "<br/> Canlı kamera yayını yapabilirsiniz."
                 "<br/> Açık olan kullanıcı masaüstüne dosya kopyalama ve geri toplayabilirsiniz."
                 "<br/> İstediğiniz bilgisayarları seçip sadece seçili olanlara işlem yapabilirsiniz."
                 "<br/> Uzak bilgisayarın yönetici hesabına script kopyalayıp server üzerinden çalıştırabilirsiniz."
                 "<br/> Server bilgisayarın ekranını yansıtma"

                 "<br/><br/>Bu uygulamayı kullanmaktan doğabilecek her türlü hukuki sorumluluğu kullanıcı kabul etmiş sayılır."
                  "<br/><br/> Copyright (C) 2022 by Bayram KARAHAN"
                 "<br/>  bayramk@gmail.com"
                 "<br/>  www.bayramkarahan.blogspot.com"

                  "<br/><br/>This program is free software; you can redistribute it and/or modify it under"
                  "the terms of the GNU General Public License as published by the Free Software"
                  "Foundation; either version 3 of the License, or (at your option) any later version."
                  "<br/>"
                  "<br/>This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;"
                  "without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."
                  "See the GNU General Public License for more details."
                  "<br/>"
                  "<br/>You should have received a copy of the GNU General Public License along with"
                  "this program; if not, write to the Free Software Foundation, Inc."
                  ",51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA ."
                  );
    QPrinter pdf;
        pdf.setOutputFileName("/tmp/hakkimda.pdf");
        pdf.setOutputFormat(QPrinter::PdfFormat);
        doc->print(&pdf);

    QTextEdit *document = new QTextEdit();
    document->setReadOnly(true);
    //  document->show();
     document->setDocument(doc);
    QVBoxLayout * vbox = new QVBoxLayout();
     QHBoxLayout * hbox1= new QHBoxLayout();

    // hbox1->addWidget(commandFileLabel);
     hbox1->addWidget(document);

     vbox->addLayout(hbox1);
     QDialog * d1 = new QDialog();
     d1->setWindowTitle("Program Hakkında");
     d1->setFixedSize(QSize(boy*120,boy*120));
     auto appIcon = QIcon(":/icons/e-ag.svg");
     d1->setWindowIcon(appIcon);

     d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

     d1->setLayout(vbox);
      d1->exec();



}


#endif // BUTONCLICK_H
