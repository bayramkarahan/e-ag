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
#ifndef SELECTPC_H
#define SELECTPC_H
void MainWindow::selectPc()
{
    int e=en;
    int b=boy;
    auto *lineWidget1=new QWidget(this);
    lineWidget1->resize(this->width(),b*5);
    lineWidget1->move(0,b*24-1);
  //  lineWidget1->setStyleSheet("background-color: #acacac");
    lineWidget1->setStyleSheet("background-color: #dfdfdf");

  /*  auto pcSelect=new QLabel(lineWidget1);
    pcSelect->resize(e*40,b*5);
  //  pcSelect->move(e*4,b*24+2);
    pcSelect->setText("Seçili Bilgisayar: ");
*/
    pcIplbl=new QLabel(lineWidget1);
    pcIplbl->resize(e*8,b*5);
  //  pcIplbl->move(27*e,b*24+2);

    pcIp=new QLabel();
    pcIp->resize(e*40,b*5);
 //   pcIp->move(e*30,b*24+2);


    pcNamelbl=new QLabel(lineWidget1);
    pcNamelbl->resize(e*8,b*5);
    //pcNamelbl->move(e*56,b*24+2);

    pcName=new QLabel();
    pcName->resize(e*40,b*5);
   // pcName->move(e*60,b*24+2);



    pcMaclbl=new QLabel(lineWidget1);
    pcMaclbl->resize(e*8,b*5);
   // pcMaclbl->move(e*94,b*24+2);

    pcMac=new QLabel();
    pcMac->resize(e*40,b*5);
   // pcMac->move(e*100,b*24+2);


    destlabel=new QLabel(lineWidget1);
    destlabel->resize(e*60,b*6);
   // destlabel->move(e*146,b*24+2);

    socketNumberLabel=new QLabel(lineWidget1);
    socketNumberLabel->resize(e*20,b*6);
  //  socketNumberLabel->move(e*140,b*24+2);

    auto layoutsp = new QGridLayout(lineWidget1);
    layoutsp->setContentsMargins(3, 0, 3,0);
    layoutsp->setVerticalSpacing(0);
    //  layout->setColumnMinimumWidth(0, 37);
   // layoutsp->addWidget(pcSelect, 0,0,1,1);
  layoutsp->addWidget(pcNamelbl, 0,0,1,2);
 //   layoutsp->addWidget(pcName, 0,1,1,1);
    layoutsp->addWidget(pcIplbl, 0,2,1,2);
   // layoutsp->addWidget(pcIp, 0,3,1,1);
    layoutsp->addWidget(pcMaclbl, 0,4,1,2);
   // layoutsp->addWidget(pcMac, 0,5,1,1);
  layoutsp->addWidget(destlabel, 0,6,1,2);
    layoutsp->addWidget(socketNumberLabel, 0,8,1,1);

}
#endif // SELECTPC_H
