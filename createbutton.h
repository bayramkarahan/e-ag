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
#ifndef CREATEBUTTON_H
#define CREATEBUTTON_H
//#include<mybutton.h>
#include <QApplication>
#include<QToolButton>
#include<QLabel>
 void MainWindow::createButton()
 {

     int bw,bh;
     bw=en*13;
     bh=boy*10;
    auto *lineWidget=new QWidget(this);
    lineWidget->resize(this->width(),boy*11+1);
    lineWidget->move(0,boy*29+2);
    lineWidget->setStyleSheet("background-color: #acacac");


    listePcButton = new QToolButton(lineWidget);
    listePcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    listePcButton->setIcon(QIcon(":icons/liste.png"));
    listePcButton->setIconSize(QSize(bw,bh/2));
    listePcButton->setAutoRaise(true);
    listePcButton->setAutoFillBackground(true);
    listePcButton->setStyleSheet("background-color: #dcdcdc");

    listePcButton->resize(bw,bh);
   // listePcButton->move(10,150);
    listePcButton->setText("Pc Listesi");

  /* auto palette = new QPalette();
   palette->setColor(QPalette::Button, QColor(200,200,200,255));
    listePcButton->setPalette(*palette);
    listePcButton->update();
*/
    connect(listePcButton, SIGNAL(clicked()),this, SLOT(pcListeSlot()));

    vncConnectButton = new QToolButton(lineWidget);
    vncConnectButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    vncConnectButton->setIcon(QIcon(":icons/vnc.png"));
    vncConnectButton->setIconSize(QSize(bw,bh/2));
    vncConnectButton->setAutoRaise(true);
    vncConnectButton->setAutoFillBackground(true);
    vncConnectButton->setStyleSheet("background-color: #dcdcdc");

    vncConnectButton->resize(bw,bh);
   // vncConnectButton->move(85,150);
    vncConnectButton->setText("Vnc-Rdp");
    connect(vncConnectButton, SIGNAL(clicked()),this, SLOT(rdpButtonSlot()));

    ftpConnectButton = new QToolButton(lineWidget);
    ftpConnectButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ftpConnectButton->setIcon(QIcon(":icons/ftp.png"));
    ftpConnectButton->setIconSize(QSize(bw,bh/2));
    ftpConnectButton->setAutoRaise(true);
    ftpConnectButton->setAutoFillBackground(true);
    ftpConnectButton->setStyleSheet("background-color: #dcdcdc");

    ftpConnectButton->resize(bw,bh);
   // ftpConnectButton->move(160,150);
    ftpConnectButton->setText("Ftp");

    connect(ftpConnectButton, SIGNAL(clicked()),this, SLOT(ftpConnectButtonSlot()));


    macListeButton = new QToolButton(lineWidget);
    macListeButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    macListeButton->setIcon(QIcon(":icons/maclist.png"));
    macListeButton->setIconSize(QSize(bw,bh/2));
    macListeButton->setAutoRaise(true);
    macListeButton->setAutoFillBackground(true);
    macListeButton->setStyleSheet("background-color: #dcdcdc");

    macListeButton->resize(bw,bh);
   // macListeButton->move(235,150);
    macListeButton->setText("Mac Liste");

    connect(macListeButton, SIGNAL(clicked()),this, SLOT(macListButtonSlot()));


    macListSaveButton = new QToolButton(this);
    macListSaveButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    macListSaveButton->setIcon(QIcon(":icons/save.png"));
    macListSaveButton->setIconSize(QSize(bw,bh/2));
    macListSaveButton->setAutoRaise(true);
    macListSaveButton->setAutoFillBackground(true);
    macListSaveButton->setStyleSheet("background-color: #dcdcdc");

    macListSaveButton->resize(bw,bh);
    macListSaveButton->move(this->width()/2-bw/2,this->height()-boy*30.5);
    macListSaveButton->setText("Kaydet");
    connect(macListSaveButton, SIGNAL(clicked()),this, SLOT(macListSaveButtonSlot()));
    macListSaveButton->hide();

    tcpekranImageButton = new QToolButton(lineWidget);
    tcpekranImageButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tcpekranImageButton->setIcon(QIcon(":icons/screenimage.png"));
    tcpekranImageButton->setIconSize(QSize(bw,bh/2));
    tcpekranImageButton->setAutoRaise(true);
    tcpekranImageButton->setAutoFillBackground(true);
    tcpekranImageButton->setStyleSheet("background-color: #dcdcdc");

    tcpekranImageButton->resize(bw,bh);
  //  tcpekranImageButton->move(385,150);
    tcpekranImageButton->setText("Pc Ekranı");
    connect(tcpekranImageButton, SIGNAL(clicked()),this, SLOT(tcpekranImageButtonSlot()));



    tcpekranKilitButton = new QToolButton(lineWidget);
    tcpekranKilitButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tcpekranKilitButton->setIcon(QIcon(":icons/lock.png"));
    tcpekranKilitButton->setIconSize(QSize(bw,bh/2));
    tcpekranKilitButton->setAutoRaise(true);
    tcpekranKilitButton->setAutoFillBackground(true);
    tcpekranKilitButton->setStyleSheet("background-color: #dcdcdc");

    tcpekranKilitButton->resize(bw,bh);
   // tcpekranKilitButton->move(460,150);
    tcpekranKilitButton->setText("Pc Kilitle");
    connect(tcpekranKilitButton, SIGNAL(clicked()),this, SLOT(tcpekranKilitButtonSlot()));

    tcpduyuruMesajButton = new QToolButton(lineWidget);
    tcpduyuruMesajButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tcpduyuruMesajButton->setIcon(QIcon(":icons/message.png"));
    tcpduyuruMesajButton->setIconSize(QSize(bw,bh/2));
    tcpduyuruMesajButton->setAutoRaise(true);
    tcpduyuruMesajButton->setAutoFillBackground(true);
    tcpduyuruMesajButton->setStyleSheet("background-color: #dcdcdc");

    tcpduyuruMesajButton->resize(bw,bh);
    //tcpduyuruMesajButton->move(535,150);
    tcpduyuruMesajButton->setText("Duyuru");
    connect(tcpduyuruMesajButton, SIGNAL(clicked()),this, SLOT(tcpduyuruMesajButtonSlot()));

    tcppcKapatButton = new QToolButton(lineWidget);
    tcppcKapatButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tcppcKapatButton->setIcon(QIcon(":icons/close.png"));
    tcppcKapatButton->setIconSize(QSize(bw,bh/2));
    tcppcKapatButton->setAutoRaise(true);
    tcppcKapatButton->setAutoFillBackground(true);
    tcppcKapatButton->setStyleSheet("background-color: #dcdcdc");

    tcppcKapatButton->resize(bw,bh);
   // tcppcKapatButton->move(610,150);
    tcppcKapatButton->setText("Pc Kapat");
    connect(tcppcKapatButton, SIGNAL(clicked()),this, SLOT(tcppcKapatButtonSlot()));

    tcpcommandsendMessageButton = new QToolButton(lineWidget);
    tcpcommandsendMessageButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tcpcommandsendMessageButton->setIcon(QIcon(":icons/command.png"));
    tcpcommandsendMessageButton->setIconSize(QSize(bw,bh/2));
    tcpcommandsendMessageButton->setAutoRaise(true);
    tcpcommandsendMessageButton->setAutoFillBackground(true);
    tcpcommandsendMessageButton->setStyleSheet("background-color: #dcdcdc");

    tcpcommandsendMessageButton->resize(bw,bh);
   // tcpcommandsendMessageButton->move(685,150);
    tcpcommandsendMessageButton->setText("Konsol");
    connect(tcpcommandsendMessageButton, SIGNAL(clicked()),this, SLOT(tcpcommandsendMessageButtonSlot()));

    tcpPanoButton = new QToolButton(lineWidget);
    tcpPanoButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tcpPanoButton->setIcon(QIcon(":icons/pano.png"));
    tcpPanoButton->setIconSize(QSize(bw,bh/2));
    tcpPanoButton->setAutoRaise(true);
    tcpPanoButton->setAutoFillBackground(true);
    tcpPanoButton->setStyleSheet("background-color: #dcdcdc");
    tcpPanoButton->resize(bw-5,bh);
   // tcpPanoButton->move(760,150);
    tcpPanoButton->setText("Pano");
    connect(tcpPanoButton, SIGNAL(clicked()),this, SLOT(tcpPanoButtonSlot()));


   // QStyle* style = qApp->style();

    bilgiAlButton = new QToolButton(lineWidget);
    bilgiAlButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    bilgiAlButton->setIcon(QIcon(":icons/about.png"));
    bilgiAlButton->setIconSize(QSize(bw,bh/2));
    bilgiAlButton->setAutoRaise(true);
    bilgiAlButton->setAutoFillBackground(true);
    bilgiAlButton->setStyleSheet("background-color: #dcdcdc");

    bilgiAlButton->resize(bw,bh);
   // bilgiAlButton->move(830,150);
    bilgiAlButton->setText("Bilgi Al");
    connect(bilgiAlButton, SIGNAL(clicked()),this, SLOT(bilgiAlButtonSlot()));


  /*  auto *lineWidget2=new QWidget(this);
    lineWidget2->resize(this->width(),44);
    lineWidget2->move(0,this->height()-147);
    lineWidget2->setStyleSheet("background-color: #a3a3a3");
*/
    auto layoutb = new QGridLayout(lineWidget);
    layoutb->setContentsMargins(6,0, 3,0);
    layoutb->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
    layoutb->addWidget(listePcButton, 0,0,1,1);
    layoutb->addWidget(vncConnectButton, 0,1,1,1);
    layoutb->addWidget(ftpConnectButton, 0,2,1,1);
    layoutb->addWidget(macListeButton, 0,3,1,1);
  //  layoutb->addWidget(hostTableListSaveButton, 0,4,1,1);
    layoutb->addWidget(tcpekranImageButton, 0,5,1,1);
    layoutb->addWidget(tcpekranKilitButton, 0,6,1,1);
    layoutb->addWidget(tcppcKapatButton, 0,7,1,1);

    layoutb->addWidget(tcpduyuruMesajButton, 0,8,1,1);
    layoutb->addWidget(tcpcommandsendMessageButton, 0,9,1,1);
    layoutb->addWidget(tcpPanoButton, 0,10,1,1);
    layoutb->addWidget(bilgiAlButton, 0,11,1,1);

  }
#endif // CREATEBUTTON_H
