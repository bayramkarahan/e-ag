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
#include "pc.h"
#include<QRegularExpression>

#include<QTextStream>
#include<QDebug>
#include<filecrud.h>
#include<QLabel>
#include<QToolButton>
#include<QProcess>
#include <QMouseEvent>
#include<QApplication>
#include<QModelIndex>
#include<QMenu>
#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QVBoxLayout>
#include<QDialogButtonBox>


Pc::Pc(QWidget *parent) : QWidget(parent)
{
    setObjectName("pcobject");
   // installEventFilter(parent);
    timerPortControl= new QTimer(this);
    connect(timerPortControl, SIGNAL(timeout()), this, SLOT(timerPortControlSlot()));
   // timerPortControl->start(5000);

    timerPortControlOnline= new QTimer(this);
    connect(timerPortControlOnline, SIGNAL(timeout()), this, SLOT(timerPortControlOnlineSlot()));
    // timerPortControlOnline->start(30000);

    //pcTimerClickSlot();
    localDir="/usr/share/e-ag/";
    nameLabel=new QLabel(this);
    select=false;
    QPalette palet;

    palet.setColor(QPalette::Window, QColor(0,0,0,0));
    setPalette(palet);
    setAutoFillBackground(true);
    pcstateLabel=new QLabel(this);
    pcdrmLabel=new QLabel(this);
    sshstateLabel=new QLabel(this);
    sshdrmLabel=new QLabel(this);
    vncstateLabel=new QLabel(this);
    vncdrmLabel=new QLabel(this);
    userstateLabel=new QLabel(this);
    //connectstateLabel=new QLabel(this);
    selectLabel=new QLabel(this);
    selectLabel->setObjectName("selectLabel");
    ftpstateLabel=new QLabel(this);
    ftpdrmLabel=new QLabel(this);
    // btnctrl=new QPushButton(this);
    btnayar=new QToolButton(this);
    btnpc=new QLabel(this);
     btnpc->setObjectName("btnpc");
    iconLabel=new QLabel(this);
     iconLabel->setObjectName("iconLabel");
    iconLabel->setScaledContents(true);
    iconLabel->setStyleSheet("background-color:rgba(0,0,0,0)");
    pcstateLabel->setText("P");
    sshstateLabel->setText("S");
    vncstateLabel->setText("V");
    ftpstateLabel->setText("F");
    userstateLabel->setText("X");

    selectLabel->setStyleSheet("QLabel{border: 1px solid gray;border-radius: 5px;}");
    pcstateLabel->setAlignment(Qt::AlignCenter);
    sshstateLabel->setAlignment(Qt::AlignCenter);
    vncstateLabel->setAlignment(Qt::AlignCenter);
    ftpstateLabel->setAlignment(Qt::AlignCenter);
    userstateLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setAlignment(Qt::AlignTop|Qt::AlignCenter);
    nameLabel->raise();

    /*********************************************************/
    pcMenu();
     btnayar->setMenu(pContextMenu);
     btnayar->setPopupMode(QToolButton::InstantPopup);

   // btnayar->setStyleSheet("background-color: #dcdcdc");
    ///connect(btnayar, SIGNAL(clicked()),this, SLOT(slotPcAyar()));
    connect(btnayar, &QToolButton::clicked, [=]() {
           //   qDebug()<<"menu açılacak";
    });
    btnayar->setIcon(QIcon(":icons/settings.svg"));
    //btnayar->setAutoFillBackground(true);
    btnayar->setAutoRaise(true);
   // btnpc->setToolButtonStyle(Qt::ToolButtonIconOnly);
    iconLabel->setAutoFillBackground(true);
   // multiSelect=new QCheckBox(this);
   // multiSelect->setFont(ff);
    multiSelect=false;
    /**********************************************************/



    auto layout = new QGridLayout(this);
    layout->setContentsMargins(2, 0, 5,0);
    layout->setVerticalSpacing(0);
    //  layout->setColumnMinimumWidth(0, 37);
    //layout->addWidget(selectLabel, 2,1,1,1,Qt::AlignHCenter);
    //layout->addWidget(multiSelect, 2,1,1,1,Qt::AlignHCenter);
    layout->addWidget(nameLabel, 2, 1,1,6,Qt::AlignHCenter);
    // layout->addWidget(btnctrl, 2, 5,1,1,Qt::AlignHCenter);
    layout->addWidget(btnpc, 3,1,1,5,Qt::AlignHCenter);
    layout->addWidget(iconLabel, 3,1,1,6,Qt::AlignHCenter);
    layout->addWidget(pcstateLabel, 4,1,1,1,Qt::AlignHCenter);
    layout->addWidget(sshstateLabel, 4, 2,1,1,Qt::AlignHCenter);
    layout->addWidget(vncstateLabel, 4, 3,1,1,Qt::AlignHCenter);
    layout->addWidget(ftpstateLabel, 4, 4,1,1,Qt::AlignHCenter);
    layout->addWidget(userstateLabel, 4, 5,1,1,Qt::AlignHCenter);
    layout->addWidget(btnayar, 4, 6,1,1,Qt::AlignHCenter);
    this->setLayout(layout);


}
void Pc::setTcpConnect(bool state){

    pcdrmLabel->hide();
   /// qDebug()<<"tcpconnect:"<<tcpConnectCounter<<ip;
    if(state)
    {
        tcpConnectCounter=0;
         // pcdrmLabel->setText("on");
         //pcstateLabel->setStyleSheet("background-color: #00ff00");

        cs="online";

        btnpc->setStyleSheet("background-color:rgba(0,255,0,100)");
    }
    else
    {
        //pcdrmLabel->setText("off");
        //pcstateLabel->setStyleSheet("background-color: #00ff00");
        cs="offline";
          btnpc->setStyleSheet("background-color:rgba(125,255,125,50)");
    }
    QStringList list=fileToList("iplistname");
    list=listReplace(list, "offline", cs, 6,mac);//connectstate
    listToFile(list,"iplistname");


}
void Pc::setPcState(bool state){

      QPalette *palette=new QPalette();
    pcdrmLabel->hide();
    if(state)
    {
        pcdrmLabel->setText("on");
        // pcstateLabel->setStyleSheet("background-color: #00ff00");
          pcstateLabel->setStyleSheet("border: 1px solid gray; "
                                      "border-radius: 6px;"
                                      "font-size:8px;"
                                      " text-align: center;"
                                      "background-color: #00ff00;");

        ps="pcopen";
       // palette->setColor(QPalette::Button, QColor(255,255,125,50));
          btnpc->setStyleSheet("background-color:rgba(125,255,125,50)");
          // emit pcListeSignal();
          QStringList list=fileToList("iplistname");
          list=listReplace(list, "pcclose", ps, 2,mac);//pcstate
          listToFile(list,"iplistname");

    }
    else
    {
        pcdrmLabel->setText("off");
        // pcstateLabel->setStyleSheet("background-color: #ff0000");
        pcstateLabel->setStyleSheet("border: 1px solid gray; "
                                    "border-radius: 6px;"
                                    "font-size:8px;"
                                    " text-align: center;"
                                    "background-color: #ff0000;");

        ps="pcclose";
        btnpc->setStyleSheet("background-color:rgba(255,0,0,100)");
        setSshConnect(false);
        setVncConnect(false);
        setFtpConnect(false);
        QStringList list=fileToList("iplistname");
        list=listReplace(list, "pcclose", ps, 2,mac);//pcstate
        listToFile(list,"iplistname");

       /// emit pcListeSignal();

    }

}
void Pc::setSshConnect(bool state){

     sshdrmLabel->hide();

  if(state)
  {
      sshConnectCounter=0;
      ss="sshopen";
      sshdrmLabel->setText("on");
      //sshstateLabel->setStyleSheet("background-color: #00ff00");
      sshstateLabel->setStyleSheet("border: 1px solid gray; "
                                  "border-radius: 6px;"
                                   "font-size:8px;"
                                   " text-align: center;"
                                  "background-color: #00ff00;");

  }
  else
  {
      ss="sshclose";
      sshdrmLabel->setText("off");
       // sshstateLabel->setStyleSheet("background-color: #ff0000");
      sshstateLabel->setStyleSheet("border: 1px solid gray; "
                                  "border-radius: 6px;"
                                   "font-size:8px;"
                                   " text-align: center;"
                                  "background-color: #ff0000;");

  }
    QStringList list=fileToList("iplistname");
    list=listReplace(list, "sshclose", ss, 3,mac);//sshstate
    listToFile(list,"iplistname");

}
void Pc::setVncConnect(bool state){
//qDebug()<<"vncopen";


     vncdrmLabel->hide();

     if(state)
    {
         vncConnectCounter=0;
        vs="vncopen";
        vncdrmLabel->setText("on");
       // vncstateLabel->setStyleSheet("background-color: #00ff00");
        vncstateLabel->setStyleSheet("border: 1px solid gray; "
                                    "border-radius: 6px;"
                                    "font-size:8px;"
                                    "background-color: #00ff00;");

     //vncConnectButton->setEnabled(true);
    }
    else
    {
        vs="vncclose";
        vncdrmLabel->setText("off");
      //  vncstateLabel->setStyleSheet("background-color: #ff0000");
        vncstateLabel->setStyleSheet("border: 1px solid gray; "
                                    "border-radius: 6px;"
                                    "font-size:8px;"
                                    "background-color: #ff0000;");

       //  vncConnectButton->setEnabled(false);
    }
    QStringList list=fileToList("iplistname");
    list=listReplace(list, "vncclose", vs, 4,mac);//vncstate
    listToFile(list,"iplistname");

}
void Pc::setFtpConnect(bool state){
//qDebug()<<"ftpopen";
   ftpdrmLabel->hide();

     if(state)
    {
         ftpConnectCounter=0;
        fs="ftpopen";
        ftpdrmLabel->setText("on");
       // ftpstateLabel->setStyleSheet("background-color: #00ff00");

        ftpstateLabel->setStyleSheet("border: 1px solid gray; "
                                    "border-radius: 6px;"
                                     "font-size:8px;"
                                     " text-align: center;"

                                    "background-color: #00ff00;");

     }
    else
    {
        fs="ftpclose";
        ftpdrmLabel->setText("off");
       // ftpstateLabel->setStyleSheet("background-color: #ff0000");
        ftpstateLabel->setStyleSheet("border: 1px solid gray; "
                                    "border-radius: 6px;"
                                     "font-size:8px;"
                                     " text-align: center;"

                                    "background-color: #ff0000;");
       //  vncConnectButton->setEnabled(false);
    }
    QStringList list=fileToList("iplistname");
    list=listReplace(list, "ftpclose", fs, 5,mac);//ftpstate
    listToFile(list,"iplistname");

}
void Pc::setKilitControlState(bool state){
   // qDebug()<<"kilitstate"<<cs;
    if(state==true&&transparanKilitControlState==false&&iconControlState==false)
    {
        qDebug()<<"kilitli";
        iconLabel->setPixmap(QPixmap(":icons/lock.svg"));
         kilitControlState=true;
    }
    if(state==false&&transparanKilitControlState==false&&iconControlState==false)
    {
        iconLabel->setPixmap(QPixmap(""));
         kilitControlState=false;
    }
}
void Pc::setKilitTransparanControlState(bool state){
//qDebug()<<"transparan kilitstatecontrol"<<cs<<state;
    if(state==true&&kilitControlState==false&&iconControlState==false)
    {
        qDebug()<<"transparan kilitli";
        iconLabel->setPixmap(QPixmap(":icons/transparanlock.svg"));
        transparanKilitControlState=true;
    }
   if(state==false&&kilitControlState==false&&iconControlState==false)
   {
        iconLabel->setPixmap(QPixmap(""));
        transparanKilitControlState=false;
    }
}
void Pc::setIconControlState(bool state)
{
   if(state==true&&transparanKilitControlState==false&&kilitControlState==false)
   {
       QPixmap image =  QPixmap("/tmp/"+ip+".png");
       iconLabel->setPixmap(image);
        iconControlState=true;
   }
   if(state==false&&transparanKilitControlState==false&&kilitControlState==false)
   {
       iconLabel->setPixmap(QPixmap(""));
       iconControlState=false;
   }

}
void Pc::setAcount(QString username, QString password){
  remoteUserName=username;
  remotePassword=password;
}
void Pc::setDisplay(QString _dis)
{
    display=_dis;

}
void Pc::setUser(QString _usr)
{
    user=_usr;
    if(_usr!="noLogin")
    {
     userstateLabel->setStyleSheet("border: 1px solid gray; "
                                    "border-radius: 6px;"
                                     "font-size:8px;"
                                     " text-align: center;"
                                    "background-color: #00ff00;");
    }else
    {
     userstateLabel->setStyleSheet("border: 1px solid gray; "
                                    "border-radius: 6px;"
                                     "font-size:8px;"
                                     " text-align: center;"
                             "background-color: #ff0000;");
    }

}
void Pc::setOs(QString _os)
{
    os=_os;
}
void Pc::setCaption(QString cap)
{
    nameLabel->setText(cap);
}
void Pc::setSize(int _w, int _h, QString _font)
{
    font=_font;
    int fnt=_font.toInt();
    nameLabel->setStyleSheet("font-size:"+QString::number(fnt-2)+"px; background-color:rgba(0,255,0,0);");
    // nameLabel->setStyleSheet("background-color:rgba(200,200,0,255)");

    w=_w/6;
    setFixedSize(w*7,w*5.9);
    /**************************************/
    nameLabel->setFixedSize(w*5.2,w*1.3);

    pcstateLabel->setFixedSize(w*1,w*1);
    sshstateLabel->setFixedSize(w*1,w*1);
    vncstateLabel->setFixedSize(w*1,w*1);
    ftpstateLabel->setFixedSize(w*1,w*1);
    userstateLabel->setFixedSize(w*1,w*1);

    selectLabel->setFixedSize(w*7, w*5.9);
    btnpc->setFixedSize(w*7, w*3);
    iconLabel->setFixedSize(w*5.2, w*2.7);

    btnayar->setFixedSize(w*1, w*1);
    btnayar->setIconSize(QSize(w*0.9,w*0.9));
    userstateLabel->setStyleSheet("border: 1px solid gray; "
                                  "border-radius: 6px;"
                                  "font-size:8px;"
                                  " text-align: center;"
                                  "background-color: #ff0000;");
}

void Pc::setMac(QString _mac, int _w, int _h, QString _font)
{
    font=_font;
    int fnt=_font.toInt();
    nameLabel->setStyleSheet("font-size:"+QString::number(fnt-2)+"px; background-color:rgba(0,255,0,0);");
   // nameLabel->setStyleSheet("background-color:rgba(200,200,0,255)");

    //qDebug()<<"pc-:"<<mac;
    mac=_mac;
    w=_w/6;
    setFixedSize(w*7,w*5.9);


        this->setToolTip("Çoklu seçim için çift tıklayınız..");
        btnpc->setToolTip(mac);
    /**************************************/
    nameLabel->setText(pcname);
        nameLabel->setFixedSize(w*5.2,w*1.3);

        pcstateLabel->setFixedSize(w*1,w*1);
        sshstateLabel->setFixedSize(w*1,w*1);
        vncstateLabel->setFixedSize(w*1,w*1);
        ftpstateLabel->setFixedSize(w*1,w*1);
        userstateLabel->setFixedSize(w*1,w*1);

        selectLabel->setFixedSize(w*7, w*5.9);
        btnpc->setFixedSize(w*7, w*3);
        iconLabel->setFixedSize(w*5.2, w*2.7);

        btnayar->setFixedSize(w*1, w*1);
        btnayar->setIconSize(QSize(w*0.9,w*0.9));
        userstateLabel->setStyleSheet("border: 1px solid gray; "
                                       "border-radius: 6px;"
                                        "font-size:8px;"
                                        " text-align: center;"
                                "background-color: #ff0000;");


}
Pc::~Pc()
{
// qDebug()<<"Pc nesnesi Silindi-----------: "<<ip<<mac;
}

void Pc::slotMouseClick()
{
    if(ps=="pcopen")
    {
        QPalette palet;

      //  qDebug()<<"tıklllllandıı";
        select=true;
         emit pcClickSignal(mac);//nesneler arası data transferi***

        if(select){
            palet.setColor(QPalette::Window, QColor(0,200,200,100));
            setPalette(palet);
            setAutoFillBackground(true);

        }
        else{
            palet.setColor(QPalette::Window, QColor(0,0,0,0));
            setPalette(palet);
            setAutoFillBackground(true);

        }
    }
}
void Pc::slotPcAyar()
{
   // qDebug()<<"ayar click";
    QDialog * d = new QDialog();
    d->setWindowTitle("Host Bilgileri");
    auto appIcon = QIcon(":/icons/about.svg");
    d->setWindowIcon(appIcon);

    QSize screenSize = qApp->screens()[0]->size();
   int boy=screenSize.height()/153.6;
   int en=boy*1.1;

    d->setFixedSize(en*60,boy*60);
    QLineEdit * lineEditA = new QLineEdit();
    QLabel *pcnameLabel=new QLabel();
    QLabel *pcstate=new QLabel();
    QLabel *sshstate=new QLabel();
    QLabel *vncstate=new QLabel();
    QLabel *ftpstate=new QLabel();
    QLabel *connectstate=new QLabel();
    QLabel *displaystate=new QLabel();
    QLabel *userstate=new QLabel();
     QLabel *osstate=new QLabel();

    //QLineEdit * lineEditB = new QLineEdit();
    //QLineEdit * lineEditC = new QLineEdit();
    QCheckBox *cha=new QCheckBox("Listede Gözükmemesi için Gizle");
    //QCheckBox *chb=new QCheckBox("Girdi Değeri");
   // QCheckBox *chc=new QCheckBox("Girdi Değeri");

    QDialogButtonBox * buttonBox = new QDialogButtonBox();

    buttonBox->addButton("Kaydet", QDialogButtonBox::AcceptRole);
    buttonBox->addButton("Vazgeç", QDialogButtonBox::RejectRole);


    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    QVBoxLayout * vbox = new QVBoxLayout();
    QHBoxLayout * hbox1 = new QHBoxLayout();
    hbox1->addWidget(pcnameLabel);
    hbox1->addWidget(lineEditA);

   /* QHBoxLayout * hbox2 = new QHBoxLayout();
    hbox2->addWidget(lineEditB);
    hbox2->addWidget(chb);*/

    /*QHBoxLayout * hbox3 = new QHBoxLayout();
    hbox3->addWidget(lineEditC);
    hbox3->addWidget(chc);*/
    pcnameLabel->setText("Liste Adı:");
    //vbox->addWidget(pcnameLabel);
    vbox->addLayout(hbox1);
    vbox->addWidget(cha);
    vbox->addWidget(pcstate);
    vbox->addWidget(sshstate);
    vbox->addWidget(vncstate);
    vbox->addWidget(ftpstate);
    vbox->addWidget(connectstate);
    vbox->addWidget(userstate);
    vbox->addWidget(displaystate);
     vbox->addWidget(osstate);
  //  vbox->addLayout(hbox2);
  //  vbox->addLayout(hbox3);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);
    lineEditA->setText(pcname);
    if(ps=="pcopen")pcstate->setText("Pc: Açık");else pcstate->setText("Pc: Kapalı");
    if(ss=="sshopen")sshstate->setText("Ssh: Açık");else sshstate->setText("Ssh: Kapalı");
    if(vs=="vncopen")vncstate->setText("Vnc: Açık ("+vncport+")");else vncstate->setText("Vnc: Kapalı ("+vncport+")");
    if(fs=="ftpopen")ftpstate->setText("Ftp: Açık");else ftpstate->setText("Ftp: Kapalı");
    if(cs=="online")connectstate->setText("Tcp: Açık");else connectstate->setText("Tcp: Kapalı");
    displaystate->setText("Ekran:"+display);
    userstate->setText("Kullanıcı:"+user);
    osstate->setText("Sistem:"+os);

   // lineEditB->setText("");
   // lineEditC->setText("");

     if(lss=="e")cha->setChecked(false);else cha->setChecked(true);
   // chb->setChecked(true);
   // chc->setChecked(true);


    int result = d->exec();
    if(result == QDialog::Accepted)
    {
        if(lineEditA->text()!="") pcname=lineEditA->text(); else pcname="";
         if(cha->checkState()==Qt::Unchecked)lss="e"; else lss="h";
         QStringList list=fileToList("iplistname");
        QString line=listGetLine(list,mac);
        list=listRemove(list,mac); //değişecek satır siliniyor

        list<<ip+"|"+mac+"|" +ps+"|" +ss+"|" +vs+"|"+fs+"|"+ cs+"|"+pcname+"|"+lss;
        listToFile(list,"iplistname");


           QStringList persistlist=fileToList("persistlist");
        persistlist=listRemove(persistlist,mac); //değişecek satır siliniyor
        persistlist<<ip+"|"+mac+"|" +ps+"|" +ss+"|" +vs+"|"+fs+"|"+ cs+"|"+pcname+"|"+lss;

        listToFile(persistlist,"persistlist");

   // emit pcListeSignal();
        nameLabel->setText(pcname);

    }

    ///label.setText("");

}
void Pc::slotServisControl()
{
    F="e";
    S="e";
    V="e";
    C="e";

    if (getIpPortStatus(ip,"5900")=="open"){ setVncConnect(true);vs="vncopen";}
    else {setVncConnect(false);vs="vncclose";V="h";}

    if (getIpPortStatus(ip,"22")=="open"){setSshConnect(true); ss="sshopen";}
    else {setSshConnect(false);ss="sshclose";S="h";}

    if (getIpPortStatus(ip,"21")=="open") {setFtpConnect(true);fs="ftpopen";}
    else {setFtpConnect(false);fs="ftpclose";F="h";}

   /// servisStateUpdate();

    QStringList list=fileToList("iplistname");
    QString line=listGetLine(list,mac);
    list=listRemove(list,mac); //değişecek satır siliniyor

    list<<ip+"|"+mac+"|" +ps+"|" +ss+"|" +vs+"|"+fs+"|"+ cs+"|"+nameLabel->text()+"|"+line.split("|")[8];
    listToFile(list,"iplistname");
}
void Pc::slotVnc0(){
    // emit pcClickSignal(mac);//nesneler arası data transferi***
    emit pcMenuSignal(mac,ip,"slotVnc0");
  }
void Pc::slotVnc1(){
     //emit pcClickSignal(mac);//nesneler arası data transferi***
    emit pcMenuSignal(mac,ip,"slotVnc1");
  }
void Pc::slotVnc2(){
    // emit pcClickSignal(mac);//nesneler arası data transferi***
    emit pcMenuSignal(mac,ip,"slotVnc2");
  }
void Pc::slotVncFlip(){
    // emit pcClickSignal(mac);//nesneler arası data transferi***
    emit pcMenuSignal(mac,ip,"slotVncFlip");
}
void Pc::slotVncFlipStop(){
    // emit pcClickSignal(mac);//nesneler arası data transferi***
    emit pcMenuSignal(mac,ip,"slotFlipStop");
}
void Pc::slotRdp(){
    // emit pcClickSignal(mac);//nesneler arası data transferi***
       emit pcMenuSignal(mac,ip,"slotRdp");
  }
void Pc::slotFtp(){
    // emit pcClickSignal(mac);//nesneler arası data transferi***
    emit pcMenuSignal(mac,ip,"slotFtp");
}
void Pc::slotKilit(){
     //emit pcClickSignal(mac);//nesneler arası data transferi***
      emit pcMenuSignal(mac,ip,"slotKilit");
}
void Pc::slotKilitAc(){
    // emit pcClickSignal(mac);//nesneler arası data transferi***
      emit pcMenuSignal(mac,ip,"slotKilitAc");
}
void Pc::slotLogin(){
    // emit pcClickSignal(mac);//nesneler arası data transferi***
      emit pcMenuSignal(mac,ip,"slotLogin");
 }
void Pc::slotLogout(){
     //emit pcClickSignal(mac);//nesneler arası data transferi***
     emit pcMenuSignal(mac,ip,"slotLogout");
  }
void Pc::slotReboot(){
   //  emit pcClickSignal(mac);//nesneler arası data transferi***
    emit pcMenuSignal(mac,ip,"slotReboot");
 }
void Pc::slotKapat(){
   //  emit pcClickSignal(mac);//nesneler arası data transferi***
    emit pcMenuSignal(mac,ip,"slotPowerOff");
 }
void Pc::slotMesaj(){
    // emit pcClickSignal(mac);//nesneler arası data transferi***
    emit pcMenuSignal(mac,ip,"slotMesaj");
 }
void Pc::slotEkranIzle(){
// emit pcClickSignal(mac);//nesneler arası data transferi***
    emit pcMenuSignal(mac,ip,"slotEkranIzle");
 }
void Pc::slotEkranIzleDurdur(){
    // emit pcClickSignal(mac);//nesneler arası data transferi***
    emit pcMenuSignal(mac,ip,"slotEkranIzleDurdur");
  }
void Pc::slotCommand(){
   //  emit pcClickSignal(mac);//nesneler arası data transferi***
    emit pcMenuSignal(mac,ip,"slotCommand");
 }
void Pc::mousePressEvent(QMouseEvent *event)
{
slotMouseClick();
}
void Pc::mouseDoubleClickEvent(QMouseEvent *event)
{
slotMouseDoubleClick();
}

/*void Pc::mouseMoveEvent(QMouseEvent *event)
{
  // slotMouseDoubleClick();
    //slotMouseDoubleClick();
    qDebug()<<"dclick";
}
void Pc::mouseReleaseEvent(QMouseEvent *event)
{
  // slotMouseDoubleClick();
}*/

void Pc::slotMouseDoubleClick(){
    if(ps=="pcopen")
    {
        if(!multiSelect){
         //   qDebug()<<"double click";
            multiSelect=(!multiSelect);
            selectLabel->setStyleSheet("QLabel{border: 2px solid blue;border-radius: 5px;}");
        }
        else
        {
            //qDebug()<<"double click";
            multiSelect=(!multiSelect);
            selectLabel->setStyleSheet("QLabel{border: 1px solid gray;border-radius: 5px;}");
        }
    }
}
void Pc::slotSelectPc(){
    if(ps=="pcopen")
    {
        multiSelect=true;
        selectLabel->setStyleSheet("QLabel{border: 2px solid blue;border-radius: 5px;}");
    }
}
void Pc::slotUnselectPc(){
    if(ps=="pcopen")
    {
        multiSelect=false;
        selectLabel->setStyleSheet("QLabel{border: 1px solid gray;border-radius: 5px;}");
    }
}
QString Pc::getIpPortNmapStatus(QString ip_,QString port)
{
    QString result="";
    QStringList arguments;
    arguments << "-c" << QString("nmap  -n -p %2 %1 | awk '/%2\\/tcp/{print $2;}'").arg(ip_,port);
    QProcess process;
    process.start("/bin/bash",arguments);
    if(process.waitForFinished())
    {
        result = process.readAll();
        result.chop(1);
    }
    qDebug()<<"Port Sorgulama(Nmap):"<<ip_<<result<<port;
    if(result.toInt()>0){ return "open";}
    else {return "close";}
}

QString  Pc::sshCommandSlot(QString ip_,QString port)
{
   /// QString komut="sshpass -p 1 ssh -o StrictHostKeyChecking=no -n etapadmin@192.168.1.110 'echo 1 | sudo -S' lsof -i:22|wc -l";

    QString komut="sshpass -p "+remotePassword+" ssh -o StrictHostKeyChecking=no -n "+
            remoteUserName+"@"+ip_+" 'echo "+remotePassword+" | sudo -S' lsof -i:"+port+"|wc -l";

///    mesajSlot(komut);
   /// qDebug()<<komut;
    QStringList arguments;
    //QString  komut;
    //komut.append("vncviewer ").append(pcIp->text()).append(" \-passwd \/usr\/bin\/x11vncpasswd");
    arguments << "-c" << komut;
    QString result;
    QProcess process;
    process.start("/bin/bash",arguments);
    if(process.waitForFinished())
    {
        result = process.readAll();
        result.chop(1);
    }

    if(result.toInt()>0){ return "open";}
    else {return "close";}
}

QString Pc::getIpPortStatus(QString ip_,QString port)
{
    QString result="";
    QStringList arguments;
    arguments << "-c" << QString("nc -zv -w1 %1 %2 2>&1|grep 'open'|wc -l").arg(ip_,port);
    QProcess process;
    process.start("/bin/bash",arguments);
    if(process.waitForFinished(-1))
    {
        result = process.readAll();
        result.chop(1);
    }
    qDebug()<<"Port sorgulama:"<<ip_<<result<<port;
    if(result.toInt()>0){ return "open";}
    else {return "close";}
}

void Pc::timerPortControlSlot()
{
    qDebug()<<"*************port kontrol*******************";
     QStringList list=fileToList("iplistname");
     if(iconControlState&&ps=="pcopen") {
         //setIcon(false);
         setIconControlState(true);
         emit pcIconStateControlSignal(this->mac,this->ip,true);
     }
     if(kilitControlState&&ps=="pcopen")  {
         setKilitControlState(true);
         emit pcKilitStateControlSignal(this->mac,this->ip,true);//kilitle

     }
     if(transparanKilitControlState&&ps=="pcopen")  {
         setKilitTransparanControlState(true);
         emit pcKilitTransparanStateControlSignal(this->mac,this->ip,true);
     }

    //if(cs=="offline"&&ps=="pcopen")
    ///if(ps=="pcopen")  emit pcTcpPortControlSignal(this->mac,this->ip);
    ///if(ss=="sshclose"&&ps=="pcopen")   emit pcSshPortControlSignal(this->mac,this->ip);
    ///if(vs=="vncclose"&&ps=="pcopen")   emit pcVncPortControlSignal(this->mac,this->ip);
    ///if(fs=="ftpclose"&&ps=="pcopen")   emit pcFtpPortControlSignal(this->mac,this->ip);
     if(refreshContinueState==false) //4 defa kontrol ediyor servisleri
     {
         if(tcpConnectCounter>2){
             setTcpConnect(false);
             setPcState(true);
             tcpConnectCounter=0;
             refreshContinueState=true;
           /*  qDebug()<<"host kapatıldı*********************************444444444444444444"<<ip<<mac;
*/
             system("cat /proc/net/arp |awk '$3==\"0x2\" {print $1\"|\"$4}'>/usr/share/e-ag/pcitemarplist");
             QStringList arpList=fileToList("pcitemarplist");
             //if(listGetLine(arpList,mac).count()>0&&ps=="pcclose") setPcState(true);
             if(listGetLine(arpList,mac).count()==0&&ps=="pcopen")
             {
                 qDebug()<<"host kapatıldı"<<ip<<mac;
                 setPcState(false);

                 emit pcListeStateSignal();
             }
         }
      if(sshConnectCounter>2){setSshConnect(false);sshConnectCounter=0;refreshContinueState=true;}
     if(vncConnectCounter>2){setVncConnect(false);vncConnectCounter=0;refreshContinueState=true;}
     if(ftpConnectCounter>2){setFtpConnect(false);ftpConnectCounter=0;refreshContinueState=true;}



     tcpConnectCounter++;
    sshConnectCounter++;
    vncConnectCounter++;
    ftpConnectCounter++;

 }
     /********************************************************/

   /* system("cat /proc/net/arp |awk '$3==\"0x2\" {print $1\"|\"$4}'>/usr/share/e-ag/pcitemarplist");
    QStringList arpList=fileToList("pcitemarplist");
    //if(listGetLine(arpList,mac).count()>0&&ps=="pcclose") setPcState(true);
    if(listGetLine(arpList,mac).count()==0&&ps=="pcopen")
    {
        qDebug()<<"host kapatıldı"<<ip<<mac;
        setPcState(false);

        emit pcListeStateSignal();
    }

*/
   }
void Pc::timerPortControlOnlineSlot()
{
   // if(cs=="online"&&ps=="pcopen")    emit pcTcpPortControlSignal(this->mac,this->ip);
   /// if(ss=="sshopen"&&ps=="pcopen")    emit pcSshPortControlSignal(this->mac,this->ip);
   /// if(vs=="vncopen"&&ps=="pcopen")    emit pcVncPortControlSignal(this->mac,this->ip);
   /// if(fs=="ftpopen"&&ps=="pcopen")     emit pcFtpPortControlSignal(this->mac,this->ip);
    //if(!kilitState) emit pcKilitStateControlSignal(this->mac,this->ip);

}
QStringList Pc::listRemove(QStringList list,QString data)
 {
    // qDebug()<<"deneme-ddd"<<data;
    // QStringList list;
     //  qDebug()<<list;
      QRegularExpression re(data);
     for(int i=0;i<list.count();i++)if(list[i].contains(re)) list.removeAt(i);
    // qDebug()<<list;
     return list;
 }
QString Pc::listGetLine(QStringList list,QString data)
 {
     //QStringList list;
     QRegularExpression re(data);
     for(int i=0;i<list.count();i++) if(list[i].contains(re)) return list[i];
     //qDebug()<<list;
     return "";
 }
QStringList Pc::fileToList(QString filename)
 {
    FileCrud *fcc=new FileCrud();
    fcc->dosya=localDir+filename;
    QStringList list;
    for(int i=1;i<=fcc->fileCount();i++)
    {
         QString line=fcc->fileGetLine(i);
         if(line!="")
         {
             line.chop(1);
             QStringList lst=line.split("|");
             QString ln="";
             if(lst.count()>0)ln.append(lst[0]);
             if(lst.count()>1)ln.append("|").append(lst[1]);
             if(lst.count()>2)ln.append("|").append(lst[2]);
             if(lst.count()>3)ln.append("|").append(lst[3]);
             if(lst.count()>4)ln.append("|").append(lst[4]);
             if(lst.count()>5)ln.append("|").append(lst[5]);
             if(lst.count()>6)ln.append("|").append(lst[6]);
             if(lst.count()>7)ln.append("|").append(lst[7]);
             if(lst.count()>8)ln.append("|").append(lst[8]);
             if(lst.count()>9)ln.append("|").append(lst[9]);
             if(lst.count()>10)ln.append("|").append(lst[10]);
             if(lst.count()>11)ln.append("|").append(lst[11]);
             if(lst.count()>12)ln.append("|").append(lst[12]);
             if(lst.count()>13)ln.append("|").append(lst[13]);

             list <<ln;
            // qDebug()<<ln;
             // list <<lst[0]+"|"+lst[1]+"|"+lst[2]+"|"+lst[3]+"|"+lst[4]+"|"+lst[5];

         }
    }
       return list;
 }
void Pc::listToFile(QStringList list, QString filename)
 {
    FileCrud *fcc=new FileCrud();
    fcc->dosya=localDir+filename;
    fcc->fileRemove();
    for(int i=0;i<list.count();i++)
    {
         QString line=list[i];
         if(line!="")
         {
             //line.chop(1);
             QStringList lst=line.split("|");
             //qDebug()<<line;
             QString ln="";
             if(lst.count()>0)ln.append(lst[0]);
             if(lst.count()>1)ln.append("|").append(lst[1]);
             if(lst.count()>2)ln.append("|").append(lst[2]);
             if(lst.count()>3)ln.append("|").append(lst[3]);
             if(lst.count()>4)ln.append("|").append(lst[4]);
             if(lst.count()>5)ln.append("|").append(lst[5]);
             if(lst.count()>6)ln.append("|").append(lst[6]);
             if(lst.count()>7)ln.append("|").append(lst[7]);
             if(lst.count()>8)ln.append("|").append(lst[8]);
             if(lst.count()>9)ln.append("|").append(lst[9]);
             if(lst.count()>10)ln.append("|").append(lst[10]);
             if(lst.count()>11)ln.append("|").append(lst[11]);
             if(lst.count()>12)ln.append("|").append(lst[12]);
             if(lst.count()>13)ln.append("|").append(lst[13]);

             //qDebug()<<ln;
             fcc->fileWrite(ln);

         }

    }
 }
QStringList Pc::listReplace(QStringList list, QString oldData, QString newData, int index,QString _mac)
 {
    QStringList liste;
         QRegularExpression re(oldData);
        QRegularExpression mc(_mac);
     for(int i=0;i<list.count();i++)
     {
         if(list[i].contains(re)&&list[i].contains(mc))
         {
             QStringList lst=list[i].split("|");
             lst[index].replace(oldData, newData);
            // qDebug()<<lst;

             QString ln="";
             if(lst.count()>0)ln.append(lst[0]);
             if(lst.count()>1)ln.append("|").append(lst[1]);
             if(lst.count()>2)ln.append("|").append(lst[2]);
             if(lst.count()>3)ln.append("|").append(lst[3]);
             if(lst.count()>4)ln.append("|").append(lst[4]);
             if(lst.count()>5)ln.append("|").append(lst[5]);
             if(lst.count()>6)ln.append("|").append(lst[6]);
             if(lst.count()>7)ln.append("|").append(lst[7]);
             if(lst.count()>8)ln.append("|").append(lst[8]);
             if(lst.count()>9)ln.append("|").append(lst[9]);
             if(lst.count()>10)ln.append("|").append(lst[10]);
             if(lst.count()>11)ln.append("|").append(lst[11]);
             if(lst.count()>12)ln.append("|").append(lst[12]);
             if(lst.count()>13)ln.append("|").append(lst[13]);

            // list.removeAt(i);
             liste.append(ln);
         }else
         {
             liste.append(list[i]);
         }
     }
    // qDebug()<<list;
     return liste;
 }

void Pc::pcMenu()
{
QAction *pVncAction0 = new QAction("Vnc Bağlan",this);
pVncAction0->setIcon(QIcon(":/icons/vnc.svg"));
pVncAction0->setIconVisibleInMenu(true);
connect(pVncAction0 ,SIGNAL(triggered()),this,SLOT(slotVnc0()));

QAction *pVncAction1 = new QAction("Vnc Bağlan:1",this);
pVncAction1->setIcon(QIcon(":/icons/vnc.svg"));
pVncAction1->setIconVisibleInMenu(true);
connect(pVncAction1 ,SIGNAL(triggered()),this,SLOT(slotVnc1()));


QAction *pVncAction2 = new QAction("Vnc Bağlan:2",this);
pVncAction2->setIcon(QIcon(":/icons/vnc.svg"));
pVncAction2->setIconVisibleInMenu(true);
connect(pVncAction2 ,SIGNAL(triggered()),this,SLOT(slotVnc2()));


QAction *pVncFlipAction = new QAction("Ekranı Yansıt",this);
pVncFlipAction->setIcon(QIcon(":/icons/vnc.svg"));
pVncFlipAction->setIconVisibleInMenu(true);
connect(pVncFlipAction ,SIGNAL(triggered()),this,SLOT(slotVncFlip()));

QAction *pVncFlipStopAction = new QAction("Ekranı Yansıtmayı Durdur",this);
pVncFlipStopAction->setIcon(QIcon(":/icons/vnc.svg"));
pVncFlipStopAction->setIconVisibleInMenu(true);
connect(pVncFlipStopAction ,SIGNAL(triggered()),this,SLOT(slotVncFlipStop()));

QAction *pRdpAction = new QAction("Rdp Bağlan",this);
pRdpAction->setIcon(QIcon(":/icons/rdp.svg"));
pRdpAction->setIconVisibleInMenu(true);
connect(pRdpAction ,SIGNAL(triggered()),this,SLOT(slotRdp()));

QAction *pFtpAction = new QAction("Ftp",this);
pFtpAction->setIcon(QIcon(":/icons/ftp.svg"));
pFtpAction->setIconVisibleInMenu(true);
connect(pFtpAction ,SIGNAL(triggered()),this,SLOT(slotFtp()));


QAction *pKilitAction = new QAction("Kilitle",this);
pKilitAction->setIcon(QIcon(":/icons/lock.svg"));
pKilitAction->setIconVisibleInMenu(true);
connect(pKilitAction ,SIGNAL(triggered()),this,SLOT(slotKilit()));

QAction *pKilitAcAction = new QAction("Kilit Aç",this);
pKilitAcAction->setIcon(QIcon(":/icons/unlock.svg"));
pKilitAcAction->setIconVisibleInMenu(true);
connect(pKilitAcAction ,SIGNAL(triggered()),this,SLOT(slotKilitAc()));

QAction *pRebootAction = new QAction("Yeniden Başlat",this);
pRebootAction->setIcon(QIcon(":/icons/reboot.svg"));
pRebootAction->setIconVisibleInMenu(true);
connect(pRebootAction ,SIGNAL(triggered()),this,SLOT(slotReboot()));

QAction *pKapatAction = new QAction("Kapat",this);
pKapatAction->setIcon(QIcon(":/icons/close.svg"));
pKapatAction->setIconVisibleInMenu(true);
connect(pKapatAction ,SIGNAL(triggered()),this,SLOT(slotKapat()));

QAction *pLoginAction = new QAction("Oturum Aç",this);
pLoginAction->setIcon(QIcon(":/icons/login.svg"));
pLoginAction->setIconVisibleInMenu(true);
connect(pLoginAction ,SIGNAL(triggered()),this,SLOT(slotLogin()));

QAction *pLogoutAction = new QAction("Oturum Kapat",this);
pLogoutAction->setIcon(QIcon(":/icons/session.svg"));
pLogoutAction->setIconVisibleInMenu(true);
connect(pLogoutAction ,SIGNAL(triggered()),this,SLOT(slotLogout()));

QAction *pMesajAction = new QAction("Duyuru İlet",this);
pMesajAction->setIcon(QIcon(":/icons/message.svg"));
pMesajAction->setIconVisibleInMenu(true);
connect(pMesajAction ,SIGNAL(triggered()),this,SLOT(slotMesaj()));

QAction *pEkranIzleAction = new QAction("Ekran İzle",this);
pEkranIzleAction->setIcon(QIcon(":/icons/command.svg"));
pEkranIzleAction->setIconVisibleInMenu(true);
connect(pEkranIzleAction ,SIGNAL(triggered()),this,SLOT(slotEkranIzle()));

QAction *pEkranIzleDurdurAction = new QAction("Ekran İzlemeyi Durdur",this);
pEkranIzleDurdurAction->setIcon(QIcon(":/icons/command.svg"));
pEkranIzleDurdurAction->setIconVisibleInMenu(true);
connect(pEkranIzleDurdurAction ,SIGNAL(triggered()),this,SLOT(slotEkranIzleDurdur()));

QAction *pCommandAction = new QAction("Komut Çalıştır",this);
pCommandAction->setIcon(QIcon(":/icons/command.svg"));
pCommandAction->setIconVisibleInMenu(true);
connect(pCommandAction ,SIGNAL(triggered()),this,SLOT(slotCommand()));

QAction *pserviceAction = new QAction("Servisleri Sorgula",this);
pserviceAction->setIcon(QIcon(":/icons/about.svg"));
pserviceAction->setIconVisibleInMenu(true);
connect(pserviceAction ,SIGNAL(triggered()),this,SLOT(slotServisControl()));

QAction *psettingAction = new QAction("Host Bilgileri",this);
psettingAction->setIcon(QIcon(":/icons/settings.svg"));
psettingAction->setIconVisibleInMenu(true);

connect(psettingAction ,SIGNAL(triggered()),this,SLOT(slotPcAyar()));


pContextMenu = new QMenu( this);
pContextMenu->setStyleSheet("width:165px;  font-size:"+font+"px;");

pContextMenu->addAction(pVncAction0 );
//pContextMenu->addAction(pVncAction1 );
// pContextMenu->addAction(pVncAction2 );
//pContextMenu->addAction(pVncFlipAction );
//pContextMenu->addAction(pVncFlipStopAction );
// pContextMenu->addAction(pRdpAction );
//pContextMenu->addAction(pFtpAction );
pContextMenu->addAction(pKilitAction);
pContextMenu->addAction(pKilitAcAction );
//pContextMenu->addAction(pEkranIzleAction );
//pContextMenu->addAction(pEkranIzleDurdurAction );

pContextMenu->addAction(pRebootAction );
pContextMenu->addAction(pKapatAction );
// pContextMenu->addAction(pLoginAction );
pContextMenu->addAction(pLogoutAction );
//pContextMenu->addAction(pMesajAction );
//pContextMenu->addAction(pCommandAction );
pContextMenu->addAction(pserviceAction );
pContextMenu->addAction(psettingAction );

//btnpc->setMenu(pContextMenu);
//btnpc->setPopupMode(QToolButton::MenuButtonPopup);
 btnayar->setMenu(pContextMenu);
 btnayar->setPopupMode(QToolButton::InstantPopup);

 /***************************************************************/
//pContextMenu->exec();


}

