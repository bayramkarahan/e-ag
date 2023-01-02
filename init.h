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

    QStringList ayarlst=fileToList("e-ag.conf",localDir);
    QString ap1=listGetLine(ayarlst,"agProfil1");
    if(ap1!="") {
     //   qDebug()<<"local:"<<lu;
        if(ap1.split("|")[1]!="")agProfil1=(ap1.split("|")[1]);

    }
    QString ap2=listGetLine(ayarlst,"agProfil2");
    if(ap2!="") {
     //   qDebug()<<"local:"<<lu;
        if(ap2.split("|")[1]!="")agProfil2=(ap2.split("|")[1]);

    }
    /************************************************************************/
    QString lu1=listGetLine(ayarlst,"localUser1");
    if(lu1!="") {
     //   qDebug()<<"local:"<<lu;
        if(lu1.split("|")[1]!="")localUserName1=(lu1.split("|")[1]);
        if(lu1.split("|")[2]!="")localPassword1=(lu1.split("|")[2]);
    }

    QString ru1=listGetLine(ayarlst,"remoteUser1");
    if(ru1!="") {
        if(ru1.split("|")[1]!="")remoteUserName1=(ru1.split("|")[1]);
        if(ru1.split("|")[1]!="")remotePassword1=(ru1.split("|")[2]);
    }

    QString lu2=listGetLine(ayarlst,"localUser2");
    if(lu2!="") {
     //   qDebug()<<"local:"<<lu;
        if(lu2.split("|")[1]!="")localUserName2=(lu2.split("|")[1]);
        if(lu2.split("|")[2]!="")localPassword2=(lu2.split("|")[2]);
    }

    QString ru2=listGetLine(ayarlst,"remoteUser2");
    if(ru2!="") {
        if(ru2.split("|")[1]!="")remoteUserName2=(ru2.split("|")[1]);
        if(ru2.split("|")[1]!="")remotePassword2=(ru2.split("|")[2]);
    }
    /************************************************************************/
    QString bc11=listGetLine(ayarlst,"broadCastAddress11");
    if(bc11!="") {
        if(bc11.split("|")[1]!="")broadCastAddress11=(bc11.split("|")[1]);
     }
    QString bc12=listGetLine(ayarlst,"broadCastAddress12");
    if(bc12!="") {
        if(bc12.split("|")[1]!="")broadCastAddress12=(bc12.split("|")[1]);
     }
    QString bc21=listGetLine(ayarlst,"broadCastAddress21");
    if(bc21!="") {
        if(bc21.split("|")[1]!="")broadCastAddress21=(bc21.split("|")[1]);
     }
    QString bc22=listGetLine(ayarlst,"broadCastAddress22");
    if(bc22!="") {
        if(bc22.split("|")[1]!="")broadCastAddress22=(bc22.split("|")[1]);
     }

     /************************************************************************/
    QString tp1=listGetLine(ayarlst,"tcpPort1");
    if(tp1!="") {
        if(tp1.split("|")[1]!="")tcpPort1=(tp1.split("|")[1]);
     }
    QString wbs1=listGetLine(ayarlst,"webblockstate1");
    if(wbs1!="") {
        if(wbs1.split("|")[1]!="")webblockstate1=(wbs1.split("|")[1]).toInt();
        }
    QString tp2=listGetLine(ayarlst,"tcpPort2");
    if(tp2!="") {
        if(tp2.split("|")[1]!="")tcpPort2=(tp2.split("|")[1]);
     }
    QString wbs2=listGetLine(ayarlst,"webblockstate2");
    if(wbs2!="") {
        if(wbs2.split("|")[1]!="")webblockstate2=(wbs2.split("|")[1]).toInt();
        }

    /*******************************************************************************/
    if(broadCastAddress11==""||(broadCastAddress12==""&&ipmaclist.count()>1))
    {
        hostAddressMacButtonSlot();
        for(int i=0;i<ipmaclist.count();i++)
        {
            qDebug()<<"broadcast address:"<<ipmaclist[i].broadcast;
            if (i==0)broadCastAddress11=ipmaclist[i].broadcast;
            if (i==1)broadCastAddress12=ipmaclist[i].broadcast;
        }
    }

    if(broadCastAddress21==""||(broadCastAddress22==""&&ipmaclist.count()>1))
    {
        hostAddressMacButtonSlot();
        for(int i=0;i<ipmaclist.count();i++)
        {
            qDebug()<<"broadcast address:"<<ipmaclist[i].broadcast;
            if (i==0)broadCastAddress21=ipmaclist[i].broadcast;
            if (i==1)broadCastAddress22=ipmaclist[i].broadcast;
        }
    }
    /*****************************************************************************/
    agProfil=agProfil1;
    localUserName=localUserName1;
    localPassword=localPassword1;
    remoteUserName=remoteUserName1;
    remotePassword=remotePassword1;
    broadCastAddress1=broadCastAddress11;
    broadCastAddress2=broadCastAddress12;
    webblockstate=webblockstate1;
    tcpPort= tcpPort1;


        if(remoteUserName==""||remotePassword==""||
                localUserName==""||localPassword=="")
        {
              acountButtonSlot();
        }

}



#endif // INIT_H
