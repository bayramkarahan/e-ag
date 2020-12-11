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
#ifndef INIT_H
#define INIT_H
#include <QApplication>
#include<QToolButton>
#include<acount.h>
#include<ssh.h>
#include<selectpc.h>

void MainWindow::init(){

    QSize screenSize = qApp->screens()[0]->size();
     //qDebug()<<"screenSize"<<screenSize.height()/153.6;
boy=screenSize.height()/153.6;
     //boy=5;
en=boy*1.1;
int e=en;
int b=boy;

setWindowTitle("E-Ag 4.0");
        this->resize(en*180,boy*130);
        setFixedHeight(boy*130);
        setFixedWidth(en*180);
        /****************************************************************/
        QRect screenGeometry = QApplication::desktop()->screenGeometry();
        int x = (screenGeometry.width() - this->width())/2;
        int y = (screenGeometry.height() - this->height()) / 2;
        this->move(x, y);
        /*****************************************************************/

             /******************************************************************/
          //   this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        lst=new QWidget(this);
        lst->resize(e*180,e*180);
        auto *scrollArea=new QScrollArea(this);
        scrollArea->setWidget(lst);
        scrollArea->resize(e*180,this->height()-b*61);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        lst->move(0,b*41);
        scrollArea->move(0,b*41);
        lst->hide();
        //lst->setStyleSheet("background-color: #a3a3a3");
        //auto
        layout = new QGridLayout();
       // layout->setContentsMargins(0, 0, 0,0);
        layout->setSpacing(2);
        lst->setLayout(layout);
        hostAddressButtonSlot();
        /*********************************************************************/
        selectPc();
        acount();
        ssh();
        createButton();
        createTable();
        /********************************************************************/
        tw->hide();
        //lst->show();
        textBrowser_receivedMessages=new QPlainTextEdit(this);
        textBrowser_receivedMessages->resize(this->width(),b*20-2);
        textBrowser_receivedMessages->move(0,this->height()-b*20);
        textBrowser_receivedMessages->setStyleSheet("background-color: #a3a3a3");

        /***********************ayar load************************/
        FileCrud *fcc=new FileCrud();
        fcc->dosya=localDir+"E-Ag.conf";
        if(!fcc->fileExists())
        {
         bilgiAlButtonSlot();
         ayarKaydetButtonSlot();

        }
        QStringList ayarlst=fileToList("E-Ag.conf");
        QString lu=listGetLine(ayarlst,"localUser");
        if(lu!="") {
         //   qDebug()<<"local:"<<lu;
            if(lu.split("|")[1]!="")localUsername->setText(lu.split("|")[1]);
            if(lu.split("|")[2]!="")localPassword->setText(lu.split("|")[2]);
        }
        QString ru=listGetLine(ayarlst,"remoteUser");
        if(ru!="") {
            if(ru.split("|")[1]!="")remoteUsername->setText(ru.split("|")[1]);
            if(ru.split("|")[1]!="")remotePassword->setText(ru.split("|")[2]);
        }
        QString ln=listGetLine(ayarlst,"localNetwork");
        if(ln!="") {
            if(ln.split("|")[1]!="")localNetwork->setText(ln.split("|")[1]);
         }
        QString tp=listGetLine(ayarlst,"tcpPort");
        if(tp!="") {
            if(tp.split("|")[1]!="")tcpPort->setText(tp.split("|")[1]);
         }

        /********************************************************/

            if(localNetwork->text()=="")
            {

               // QLabel* lnetwork=new QLabel(this);
            localNetwork->setText(broadCastAddress);
            //lnetwork->move(535,10);
            }


        /***********************Ekran Fotosu Alma*****************************/
     /*   ekranImages = 0;
        ekranSocketServer = new QUdpSocket( this );
        ekranSocketServer->bind( 9988 );
        connect( ekranSocketServer, SIGNAL(readyRead()), this, SLOT(ekranImageRead()) );

        /***********************************************************/
        timerEkranImageAll= new QTimer(this);
        connect(timerEkranImageAll, SIGNAL(timeout()), this, SLOT(ekranImageAll()));
        //timerEkranImageAll->start(5000);

        timerEkranImage= new QTimer(this);
        connect(timerEkranImage, SIGNAL(timeout()), this, SLOT(ekranImage()));
        //timerEkranImage->start(5000);


}


#endif // INIT_H
