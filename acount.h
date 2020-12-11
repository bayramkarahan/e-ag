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
#ifndef ACOUNT_H
#define ACOUNT_H
void MainWindow::acount()
{
    int e=en;
    int b=boy;
    auto *acountWidget=new QWidget(this);
    acountWidget->resize(this->width(),b*9);
    acountWidget->move(0,0);
    //acountWidget->setStyleSheet("background-color: #9999aa;");

    auto *acountWidgetbc=new QWidget(acountWidget);
       acountWidgetbc->resize(this->width(),b*9);
       acountWidgetbc->move(0,0);
       acountWidgetbc->setStyleSheet("background-color: #dfdfdf");

/************************uzak kullanıcı adı şifre*********************************/
  /*  auto *remoteWidget=new QWidget();
    remoteWidget->resize(238,30);
   // remoteWidget->move(0,10);
    remoteWidget->setStyleSheet("background-color: #acffac");
*/
    QLabel *remoteuserLabel=new QLabel(acountWidget);
   // remoteuserLabel->resize(90,30);
   // remoteuserLabel->move(2,10);
    remoteuserLabel->setText("Uzak Ad");

    remoteUsername=new QLineEdit(acountWidget);
    remoteUsername->setFixedSize(e*15,b*6);
   // remoteUsername->move(52,10);
    connect(remoteUsername, &QLineEdit::textChanged,this, &MainWindow::enableButton);

    QLabel *remotepasswordLabel=new QLabel(acountWidget);
   // remotepasswordLabel->resize(60,30);
   // remotepasswordLabel->move(130,10);
    remotepasswordLabel->setText("Şifre");

    remotePassword=new QLineEdit(acountWidget);
    remotePassword->setFixedSize(e*15,b*6);
   // remotePassword->move(160,10);
    remotePassword->setEchoMode(QLineEdit::Password);
    connect(remotePassword, &QLineEdit::textChanged,this, &MainWindow::enableButton);


    /****************Yerel Kullanıcı****************************************************/
   /* auto *localWidget=new QWidget(acountWidget);
    localWidget->resize(236,30);
    localWidget->move(239,10);
    localWidget->setStyleSheet("background-color: #ffacac");
*/
    QLabel *localuserLabel=new QLabel(acountWidget);
  //  localuserLabel->resize(90,30);
    //localeuserLabel->move(241,10);
    localuserLabel->setText("Yerel Ad");

    localUsername=new QLineEdit(acountWidget);
    localUsername->setFixedSize(e*15,b*6);
    //localUsername->move(293,10);
    connect(localUsername, &QLineEdit::textChanged,this, &MainWindow::enableButton);

    QLabel *localpasswordLabel=new QLabel(acountWidget);
    //localpasswordLabel->resize(70,30);
   // localpasswordLabel->move(369,10);
    localpasswordLabel->setText("Şifre");

    localPassword=new QLineEdit(acountWidget);
    localPassword->setFixedSize(e*15,b*6);
   // localPassword->move(398,10);
    localPassword->setEchoMode(QLineEdit::Password);
    connect(localPassword, &QLineEdit::textChanged,this, &MainWindow::enableButton);
/***********************broadcas adress* and port*******************/
    /*  auto *taraWidget=new QWidget(acountWidget);
      taraWidget->resize(370,34);
      taraWidget->move(535,5);
      taraWidget->setStyleSheet("background-color: #ffffac");
*/
      QLabel *localNetworkLabel=new QLabel(acountWidget);
     // localNetworkLabel->resize(160,30);
     // leLabel->move(478,10);
      localNetworkLabel->setText("Yerel Ağ");//("+broadCastAddress+")");
      //leLabel->setStyleSheet("background-color: #a30000");
      localNetwork=new QLineEdit(acountWidget);
      localNetwork->setFixedSize(e*22,b*6);
    //  localNetwork->move(530,10);

      QLabel *tcpPortLabel=new QLabel(acountWidget);
      //tcpPortLabel->resize(90,30);
     // tcpPortLabel->move(655,10);
      tcpPortLabel->setText("Tcp Port");

      tcpPort=new QLineEdit(acountWidget);
      tcpPort->setFixedSize(e*8,b*6);
      //tcpPort->move(710,10);

    /*************************************/
      taramaButton=new QPushButton(acountWidget);
      taramaButton->setFixedSize(e*10,b*6);

      //taramaButton->move(840,10);
      taramaButton->setText("Araçlar");
      connect(taramaButton, SIGNAL(clicked()),this, SLOT(taramaButtonSlot()));

      ayarKaydetButton=new QPushButton(acountWidget);
      ayarKaydetButton->setFixedSize(e*4,b*6);
    //  ayarKaydetButton->move(810,10);
      ayarKaydetButton->setText("+");
      connect(ayarKaydetButton, SIGNAL(clicked()),this, SLOT(ayarKaydetButtonSlot()));

/*****************************************/
    auto layoutk = new QGridLayout(acountWidget);
    layoutk->setContentsMargins(3, 0, 3,0);
    layoutk->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
    layoutk->addWidget(remoteuserLabel, 0,0,1,1);
    layoutk->addWidget(remoteUsername, 0,1,1,1);
    layoutk->addWidget(remotepasswordLabel, 0,2,1,1);
    layoutk->addWidget(remotePassword, 0,3,1,1);

    layoutk->addWidget(localuserLabel, 0,4,1,1);
    layoutk->addWidget(localUsername, 0,5,1,1);
    layoutk->addWidget(localpasswordLabel, 0,6,1,1);
    layoutk->addWidget(localPassword, 0,7,1,1);

    layoutk->addWidget(localNetworkLabel, 0,8,1,1);
    layoutk->addWidget(localNetwork, 0,9,1,1);
    layoutk->addWidget(tcpPortLabel, 0,10,1,1);
    layoutk->addWidget(tcpPort, 0,11,1,1);

    layoutk->addWidget(ayarKaydetButton, 0,20,1,1);
    layoutk->addWidget(taramaButton, 0,21,1,1);


}
#endif // ACOUNT_H
