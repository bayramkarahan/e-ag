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
#include<selectpc.h>
void MainWindow::acountLoad()
{
    /***********************ayar load************************/
    FileCrud *fcc=new FileCrud();
    fcc->dosya=localDir+"e-ag.conf";

    if(!fcc->fileExists())
    {
     bilgiAlButtonSlot();
     ayarKaydetButtonSlot();
}

    QStringList ayarlst=fileToList("e-ag.conf");
    QString lu=listGetLine(ayarlst,"localUser");
    if(lu!="") {
     //   qDebug()<<"local:"<<lu;
        if(lu.split("|")[1]!="")localUserName=(lu.split("|")[1]);
        if(lu.split("|")[2]!="")localPassword=(lu.split("|")[2]);
    }
    QString ru=listGetLine(ayarlst,"remoteUser");
    if(ru!="") {
        if(ru.split("|")[1]!="")remoteUserName=(ru.split("|")[1]);
        if(ru.split("|")[1]!="")remotePassword=(ru.split("|")[2]);
    }
    QString bc1=listGetLine(ayarlst,"broadCastAddress1");
    if(bc1!="") {
        if(bc1.split("|")[1]!="")broadCastAddress1=(bc1.split("|")[1]);
     }
    QString bc2=listGetLine(ayarlst,"broadCastAddress2");
    if(bc2!="") {
        if(bc2.split("|")[1]!="")broadCastAddress2=(bc2.split("|")[1]);
     }
    QString tp=listGetLine(ayarlst,"tcpPort");
    if(tp!="") {
        if(tp.split("|")[1]!="")tcpPort=(tp.split("|")[1]);
     }
    QString wbs=listGetLine(ayarlst,"webblockstate");
    if(wbs!="") {
        if(wbs.split("|")[1]!="")webblockstate=(wbs.split("|")[1]).toInt();
        }

    /********************************************************/
    if(broadCastAddress1==""||(broadCastAddress2==""&&ipmaclist.count()>1))
    {
        hostAddressMacButtonSlot();
        for(int i=0;i<ipmaclist.count();i++)
        {
            qDebug()<<"broadcast address:"<<ipmaclist[i].broadcast;
            if (i==0)broadCastAddress1=ipmaclist[i].broadcast;
            if (i==1)broadCastAddress2=ipmaclist[i].broadcast;
        }
    }

        if(remoteUserName==""||remotePassword==""||
                localUserName==""||localPassword=="")
        {
              acountButtonSlot();
        }

}
void MainWindow::init(){




}


#endif // INIT_H
