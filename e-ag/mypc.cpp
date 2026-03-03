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
#include "mypc.h"
#include<QRegularExpression>
#include<QTextStream>
#include<QDebug>
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
#include<MyCommand.h>
#include<VideoPlayer.h>

MyPc::MyPc(const QString _mac, QString _ip, QWidget *parent) : QWidget(parent)
{
    receiver=new MulticastReceiver(this);
    setObjectName("mypcobject");
    timertcpConnectControl= new QTimer(this);
    connect(timertcpConnectControl, SIGNAL(timeout()), this, SLOT(timertcpConnectControlSlot()));
    timertcpConnectControl->start(3000);

    localDir="/usr/share/e-ag/";
    #if defined(Q_OS_WIN)
        localDir="c:/e-ag/";
    #elif defined(Q_OS_LINUX)
        localDir="/usr/share/e-ag/";
    #endif
    hostnameLabel=new QLabel(this);
    select=false;
    QPalette palet;

    palet.setColor(QPalette::Window, QColor(0,0,0,0));
    setPalette(palet);
    setAutoFillBackground(true);
    sshstateLabel=new QLabel(this);
    vncstateLabel=new QLabel(this);
    userstateLabel=new QLabel(this);
    selectLabel=new QLabel(this);
    selectLabel->setObjectName("selectLabel");
    xrdpstateLabel=new QLabel(this);
    btncommand=new QToolButton(this);
    btnayar=new QToolButton(this);
    iconstateLabel=new QLabel(this);

    volumestateLabel=new QLabel(this);
    keyboardstateLabel=new QLabel(this);
    mousestateLabel=new QLabel(this);
    internetstateLabel=new QLabel(this);
    webblockstateLabel=new QLabel(this);
    youtubestateLabel=new QLabel(this);
    kilitstateLabel=new QLabel(this);
    tkilitstateLabel=new QLabel(this);

    //videoWidget=new VideoPlayer(this);
    iconstateLabel->setObjectName("iconLabel");
    iconstateLabel->setScaledContents(true);
    iconstateLabel->setStyleSheet("background-color:rgba(0,0,0,0)");
    btncommand->setText("C");
    sshstateLabel->setText("S");
    vncstateLabel->setText("V");
    xrdpstateLabel->setText("R");
    userstateLabel->setText("X");

    selectLabel->setStyleSheet("QLabel{border: 1px solid gray;border-radius: 5px;}");
   // btncommand->setAlignment(Qt::AlignCenter);
    sshstateLabel->setAlignment(Qt::AlignCenter);
    vncstateLabel->setAlignment(Qt::AlignCenter);
    xrdpstateLabel->setAlignment(Qt::AlignCenter);
    userstateLabel->setAlignment(Qt::AlignCenter);
    hostnameLabel->setAlignment(Qt::AlignTop|Qt::AlignCenter);
    hostnameLabel->raise();
    volumestateLabel->setAlignment(Qt::AlignCenter);
    keyboardstateLabel->setAlignment(Qt::AlignCenter);
    mousestateLabel->setAlignment(Qt::AlignCenter);
    internetstateLabel->setAlignment(Qt::AlignCenter);
    webblockstateLabel->setAlignment(Qt::AlignCenter);
    youtubestateLabel->setAlignment(Qt::AlignCenter);
    //kilitstateLabel->setAlignment(Qt::AlignCenter);
    //tkilitstateLabel->setAlignment(Qt::AlignCenter);

    //volumestateLabel->setText("A");

    connect(btncommand, &QToolButton::clicked, [=]() {
        /*qDebug()<<"komut:"<<command;
        qDebug()<<"komut Sonucu:"<<commandDetail;
        qDebug()<<"komut durumu:"<<commandState;*/
        MyCommand *commanddlg= new MyCommand(tr("Komut Süreci"),command,commandDetail,commandState, "", "", "", w*50, h*30,this);
        commanddlg->exec();
        //delete commanddlg;
        commanddlg = nullptr;  // Güvenlik için
    });
    connect(btnayar, &QToolButton::clicked, [=]() {
        qDebug()<<"slotPcAyar";
        slotPcAyar();

});

    btnayar->setIcon(QIcon(":icons/settings.svg"));
    btnayar->setAutoRaise(true);
    //iconLabel->setAutoFillBackground(true);
    multiSelect=false;
    auto layout = new QGridLayout(this);
    layout->setContentsMargins(2, 2, 2,2);
    layout->setVerticalSpacing(1);
    layout->addWidget(hostnameLabel, 2, 1,1,6,Qt::AlignHCenter);
    //layout->addWidget(videoWidget, 3,1,1,5,Qt::AlignHCenter);
    layout->addWidget(iconstateLabel, 3,1,1,6,Qt::AlignHCenter);
    layout->addWidget(btncommand, 4,1,1,1,Qt::AlignHCenter);
    layout->addWidget(sshstateLabel, 4, 2,1,1,Qt::AlignHCenter);
    layout->addWidget(vncstateLabel, 4, 3,1,1,Qt::AlignHCenter);
    layout->addWidget(xrdpstateLabel, 4, 4,1,1,Qt::AlignHCenter);
    layout->addWidget(userstateLabel, 4, 5,1,1,Qt::AlignHCenter);
    layout->addWidget(btnayar, 4, 6,1,1,Qt::AlignHCenter);

    layout->addWidget(volumestateLabel, 5,1,1,1,Qt::AlignHCenter);
    layout->addWidget(keyboardstateLabel, 5, 2,1,1,Qt::AlignHCenter);
    layout->addWidget(mousestateLabel, 5, 3,1,1,Qt::AlignHCenter);
    layout->addWidget(youtubestateLabel, 5, 4,1,1,Qt::AlignHCenter);

    layout->addWidget(internetstateLabel, 5, 5,1,1,Qt::AlignHCenter);
    layout->addWidget(webblockstateLabel, 5, 6,1,1,Qt::AlignHCenter);
      //layout->addWidget(kilitstateLabel, 5, 7,1,1,Qt::AlignHCenter);
    //layout->addWidget(tkilitstateLabel, 5, 8,1,1,Qt::AlignHCenter);



    this->setLayout(layout);

    this->ip=_ip;
    this->mac=_mac;


    setConnectState(false);
    setSshState("no");
    setVncState("no");
    setXrdpState("no");
    setUser("noLogin");
    setCommandButonState(false);

    DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
    QJsonArray dizi=db->Ara("mac",this->mac);
    if(dizi.count()>0)
    {
        //qDebug()<<"Kayıtlı Host.";
        QJsonObject veri=dizi.first().toObject();
        this->mac=veri.value("mac").toString();
        this->ip=veri.value("ip").toString();
        this->caption=veri.value("caption").toString();
        this->hostname=veri.value("hostname").toString();
        this->groupname=veri.value("groupname").toString();
        this->hostnameVisible =veri.value("hostnameVisible").toBool();

        //PcData::groupListe.append({true,veri.value("groupname").toString()});
        if(this->hostnameVisible)
            hostnameLabel->setText(this->hostname);
        else
        {
            hostnameLabel->setText(this->caption);
        }
        this->visibleState=veri.value("visibleState").toBool();
    }else
    {
        qDebug()<<"Yeni Host Ekleniyor.";
        QJsonObject veri;
        veri["mac"] = this->mac;
        veri["ip"] = this->ip;
        veri["caption"] = "?";
        veri["hostname"] = "";
        veri["groupname"] ="grup1";
        this->groupname="grup1";
        veri["visibleState"] = true;
        veri["hostnameVisible"] = true;

        this->visibleState=true;
        db->Ekle(veri);
    }

}
void MyPc::timertcpConnectControlSlot()
{
    tcpConnectCounter++;
    if(!iconControlState)
    {
        iconstateLabel->clear();

        //setConnectState(true);
    }
     //iconstateLabel->setText(QString::number(tcpConnectCounter));
    if(tcpConnectCounter>5)
    {
        setConnectState(false);
        setSshState("no");
        setVncState("no");
        setXrdpState("no");
        setUser("noLogin");
        tcpConnectCounter=0;
        ///emit pcCloseSignal(ip,mac);
    }

}
void MyPc::setCommandState(QString _command,QString _commandDetail,QString _commandState)
{
    command=_command;
    commandDetail=_commandDetail;
    commandState=_commandState;
    if(commandState=="0")
    {
        btncommand->setToolTip(command);
        btncommand->setStyleSheet("border: 1px solid gray; "
                                  "border-radius: 6px;"
                                  "font-size:8px;"
                                  " text-align: center;"
                                  "background-color: #00ff00;");
    }
    else
    {
        btncommand->setStyleSheet("border: 1px solid gray; "
                                  "border-radius: 6px;"
                                  "font-size:8px;"
                                  " text-align: center;"
                                  "background-color: #ff0000;");
    }
}
void MyPc::setConnectState(bool state){
    connectState=state;
    if(state)
    {

         //qDebug()<<"yeşil ayarlandı";
        iconstateLabel->setStyleSheet("background-color:rgba(0,230,0,130)");
    }
    else
    {
        //qDebug()<<"gri ayarlandı";
       iconstateLabel->setStyleSheet("background-color:rgba(127,127,127,100)");
        /*QPixmap pix(":/icons/power.png");

        // QLabel boyutuna göre ölçekle
        //iconstateLabel->setFixedSize(w*6.9, w*3.4);
        QPixmap scaled = pix.scaled(w*6.9, w*3.4,
                                    Qt::KeepAspectRatio,   // oranı korur
                                    Qt::SmoothTransformation); // yumuşak ölçekleme

        iconstateLabel->setPixmap(scaled);
        iconstateLabel->setScaledContents(false); // gereksizse kapalı kalsın
        iconstateLabel->setAlignment(Qt::AlignCenter);*/
    }
}
void MyPc::setCommandButonState(bool state){
   if(state)
    {
          btncommand->setStyleSheet("border: 1px solid gray; "
                                      "border-radius: 6px;"
                                      "font-size:8px;"
                                      " text-align: center;"
                                      "background-color: #00ff00;");
    }
    else
    {
        btncommand->setStyleSheet("border: 1px solid gray; "
                                    "border-radius: 6px;"
                                    "font-size:8px;"
                                    " text-align: center;"
                                    "background-color:rgba(0,0,0,0);");
    }
}
void MyPc::setSshState(QString state){
sshState=state;
  if(state=="o")
  {
     // sshConnectCounter=0;
      sshstateLabel->setStyleSheet("border: 1px solid gray; "
                                  "border-radius: 6px;"
                                   "font-size:8px;"
                                   " text-align: center;"
                                  "background-color: #00ff00;");

  }
  else if(state=="c")
  {
      sshstateLabel->setStyleSheet("border: 1px solid gray; "
                                  "border-radius: 6px;"
                                   "font-size:8px;"
                                   " text-align: center;"
                                  "background-color: #ff0000;");

  }
  else if(state=="no")
  {
      sshstateLabel->setStyleSheet("border: 1px solid gray; "
                                   "border-radius: 6px;"
                                   "font-size:8px;"
                                   " text-align: center;"
                                   "background-color:rgba(0,0,0,0);");

  }

}
void MyPc::setVncState(QString state){
    vncState=state;
    if(state=="o")
    {
        // sshConnectCounter=0;
        vncstateLabel->setStyleSheet("border: 1px solid gray; "
                                     "border-radius: 6px;"
                                     "font-size:8px;"
                                     " text-align: center;"
                                     "background-color: #00ff00;");

    }
    else if(state=="c")
    {
        vncstateLabel->setStyleSheet("border: 1px solid gray; "
                                     "border-radius: 6px;"
                                     "font-size:8px;"
                                     " text-align: center;"
                                     "background-color: #ff0000;");

    }
    else if(state=="no")
    {
        vncstateLabel->setStyleSheet("border: 1px solid gray; "
                                     "border-radius: 6px;"
                                     "font-size:8px;"
                                     " text-align: center;"
                                     "background-color:rgba(0,0,0,0);");

    }

}
void MyPc::setXrdpState(QString state){
    xrdpState=state;
    if(state=="o")
    {
        // sshConnectCounter=0;
        xrdpstateLabel->setStyleSheet("border: 1px solid gray; "
                                     "border-radius: 6px;"
                                     "font-size:8px;"
                                     " text-align: center;"
                                     "background-color: #00ff00;");

    }
    else if(state=="c")
    {
        xrdpstateLabel->setStyleSheet("border: 1px solid gray; "
                                     "border-radius: 6px;"
                                     "font-size:8px;"
                                     " text-align: center;"
                                     "background-color: #ff0000;");

    }
    else if(state=="no")
    {
        xrdpstateLabel->setStyleSheet("border: 1px solid gray; "
                                     "border-radius: 6px;"
                                     "font-size:8px;"
                                     " text-align: center;"
                                     "background-color:rgba(0,0,0,0);");

    }

}
void MyPc::setKilitState(bool state){
    kilitState=state;
    if(state)
    {
        //QPixmap pm = svgToPixmap(":/icons/lock.svg", QSize(w, h));  // istediğin boyut
        //kilitstateLabel->setPixmap(pm);
    }
    else
    {
        //QPixmap pm = svgToPixmap(":/icons/lock.svg", QSize(w, h));  // istediğin boyut
        //kilitstateLabel->clear();

    }

}
void MyPc::setKilitTransparanState(bool state){
    transparanKilitState=state;
    if(state)
    {
        //QPixmap pm = svgToPixmap(":/icons/transparanlock.svg", QSize(w, h));  // istediğin boyut
        //tkilitstateLabel->setPixmap(pm);
    }
    else
    {
        //QPixmap pm = svgToPixmap(":/icons/lock.svg", QSize(w, h));  // istediğin boyut
        //tkilitstateLabel->clear();

    }

}

void MyPc::setIconControlState(bool state)
{
    // 🔒 Her durumda sadece 1 thread çalışsın
    if (receiver && receiver->isRunning()) {
        receiver->stop();
        receiver->wait();
        receiver->deleteLater();
        receiver = nullptr;
    }

    // 🟢 İzleme açılıyor
    if (state && !transparanKilitControlState && !kilitControlState)
    {
        QStringList ipparts = ip.split(".");
        if (ipparts.size() < 4) {
            qWarning() << "❌ Geçersiz IP adresi:" << ip;
            return;
        }
        //qDebug() << "🟢"<<ip<<netProfil.serverAddress;
        //return;
        QString newIp = QString("udp://@239.0.%1.%2:1234?localaddr=%3")
                            .arg(ipparts[2])
                            .arg(ipparts[3])
                            .arg(netProfil.serverAddress);

        qDebug() << "🟢 İzleme başlatılıyor:" << newIp;

        receiver = new MulticastReceiver(this);
        receiver->urlAddress = newIp;

        // frameReady sinyali — thread’ten GUI’ye güvenli aktarım
        connect(receiver, &MulticastReceiver::frameReady, this,
                [this](const QImage &img) {
                    if (!iconstateLabel || img.isNull())
                        return;

                    QPixmap pix = QPixmap::fromImage(img)
                                      .scaled(iconstateLabel->size(),
                                              Qt::KeepAspectRatio,
                                              Qt::SmoothTransformation);
                    iconstateLabel->setPixmap(pix);
                    prevImage = img;
                },
                Qt::QueuedConnection);

        // Thread bittiğinde otomatik sil
        connect(receiver, &QThread::finished, receiver, &QObject::deleteLater);

        receiver->start();
        iconControlState = true;
    }
    // 🔴 İzleme kapatılıyor
    else if (!state && !transparanKilitControlState && !kilitControlState)
    {
        qDebug() << "🔴 İzleme durduruluyor";

        if (receiver) {
            receiver->stop();
            receiver->wait();
            receiver->deleteLater();
            receiver = nullptr;
        }

        if (iconstateLabel)
            iconstateLabel->clear();

        iconControlState = false;
    }
}
void MyPc::setVersionState(QString state)
{
    version=state;
}
void MyPc::setVolumeState(bool state)
{
    volumeState=state;
    if(state)
    {
    QPixmap pm = svgToPixmap(":/icons/volumeon.svg", QSize(w, h));  // istediğin boyut
    volumestateLabel->setPixmap(pm);
    }
    else
    {
        QPixmap pm = svgToPixmap(":/icons/volumeoff.svg", QSize(w, h));  // istediğin boyut
        volumestateLabel->setPixmap(pm);
    }
}
void MyPc::setKeyboardState(bool state)
{
    keyboardState=state;
    if(state)
    {
        QPixmap pm = svgToPixmap(":/icons/keyboardon.svg", QSize(w, h));  // istediğin boyut
        keyboardstateLabel->setPixmap(pm);
    }
    else
    {
        QPixmap pm = svgToPixmap(":/icons/keyboardoff.svg", QSize(w, h));  // istediğin boyut
        keyboardstateLabel->setPixmap(pm);
    }
}
void MyPc::setMouseState(bool state)
{
    mouseState=state;
    if(state)
    {
        QPixmap pm = svgToPixmap(":/icons/mouseon.svg", QSize(w, h));  // istediğin boyut
        mousestateLabel->setPixmap(pm);
    }
    else
    {
        QPixmap pm = svgToPixmap(":/icons/mouseoff.svg", QSize(w, h));  // istediğin boyut
        mousestateLabel->setPixmap(pm);
    }
}
void MyPc::setInternetState(bool state)
{
    internetState=state;
    if(state)
    {
        QPixmap pm = svgToPixmap(":/icons/openinternet.svg", QSize(w, h));  // istediğin boyut
        internetstateLabel->setPixmap(pm);
    }
    else
    {
        QPixmap pm = svgToPixmap(":/icons/stopinternet.svg", QSize(w, h));  // istediğin boyut
        internetstateLabel->setPixmap(pm);
    }
}
void MyPc::setWebblockState(bool state)
{
    webblockState=state;
    if(state)
    {
        QPixmap pm = svgToPixmap(":/icons/webblock.svg", QSize(w, h));  // istediğin boyut
        webblockstateLabel->setPixmap(pm);
    }
    else
    {
        QPixmap pm = svgToPixmap(":/icons/webblock.svg", QSize(w, h));  // istediğin boyut
        webblockstateLabel->setPixmap(pm);
    }
}
void MyPc::setYoutubeState(bool state)
{
    youtubeState=state;
    if(state)
    {
        QPixmap pm = svgToPixmap(":/icons/unblockyoutube.svg", QSize(w, h));  // istediğin boyut
        youtubestateLabel->setPixmap(pm);
    }
    else
    {
        QPixmap pm = svgToPixmap(":/icons/blockyoutube.svg", QSize(w, h));  // istediğin boyut
        youtubestateLabel->setPixmap(pm);
    }
}

void MyPc::setUser(QString _usr)
{
    user=_usr;
    if(_usr!="noLogin"&&connectState)
    {
     userstateLabel->setStyleSheet("border: 1px solid gray; "
                                    "border-radius: 6px;"
                                     "font-size:8px;"
                                     " text-align: center;"
                                    "background-color: #00ff00;");
    }else if(_usr=="noLogin"&&connectState)
    {
       /* if(pcScreenViewSignalState==false)
        {
            pcScreenViewSignalState=true;
            emit pcScreenViewSignal(mac,ip);
        }*/
     userstateLabel->setStyleSheet("border: 1px solid gray; "
                                    "border-radius: 6px;"
                                     "font-size:8px;"
                                     " text-align: center;"
                             "background-color: #ff0000;");
    }
    else if(_usr=="noLogin"&&!connectState)
    {
        userstateLabel->setStyleSheet("border: 1px solid gray; "
                                      "border-radius: 6px;"
                                      "font-size:8px;"
                                      " text-align: center;"
                                      "background-color:rgba(0,0,0,0);");
    }
    if(select){
        emit pcClickSignal(mac);//nesneler arası data transferi***
    }
}
void MyPc::setHostname(QString _hostname)
{
    //qDebug()<<"ilk hali"<<hostname<<_hostname;

    if(hostname!=_hostname)
    {
        hostname=_hostname;
        qDebug()<<"hostname güncelleniyor."<<hostname<<_hostname;
        QJsonObject veri;
        veri["mac"] = this->mac;
        veri["ip"] = this->ip;
        veri["caption"] = this->caption;
        veri["hostname"] = _hostname;
        veri["visibleState"] =this->visibleState;
        veri["groupname"]=this->groupname;
        veri["hostnameVisible"]=this->hostnameVisible;
        DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
        db->Sil("mac",this->mac);
        db->Ekle(veri);
        //qDebug()<<"hostname güncelleniyor."<<veri;

    }
    if(this->hostnameVisible)
        hostnameLabel->setText(this->hostname);
    else
    {
        hostnameLabel->setText(this->caption);
    }
    //qDebug()<<"son hali"<<hostname<<_hostname;
    if(select){
        emit pcClickSignal(mac);//nesneler arası data transferi***
    }
}
void MyPc::setSize(int _w, int _h, QString _font)
{
    font=_font;
    int fnt=_font.toInt();
    hostnameLabel->setStyleSheet("font-size:"+QString::number(fnt-2)+"px; background-color:rgba(200,200,200,255);");
    w=_w/6;
    h=_h/6;
    setFixedSize(w*7,h*8);
    /**************************************/
    hostnameLabel->setFixedSize(w*6.8,h*1.1);

    btncommand->setFixedSize(w*1,h*1);
    sshstateLabel->setFixedSize(w*1,h*1);
    vncstateLabel->setFixedSize(w*1,h*1);
    xrdpstateLabel->setFixedSize(w*1,h*1);
    userstateLabel->setFixedSize(w*1,h*1);


    volumestateLabel->setFixedSize(w*1,h*1);
    keyboardstateLabel->setFixedSize(w*1,h*1);
    mousestateLabel->setFixedSize(w*1,h*1);
    internetstateLabel->setFixedSize(w*1,h*1);
    webblockstateLabel->setFixedSize(w*1,h*1);
    youtubestateLabel->setFixedSize(w*1,h*1);

    selectLabel->setFixedSize(w*7, h*7.9);
    //btnpc->setFixedSize(w*7, h*3);
    //videoWidget->setFixedSize(w*6.9, h*4.6);
    iconstateLabel->setFixedSize(w*6.8, w*3.35);
    //layout1->SetFixedSize->setFixedSize(w*7, h*5);

    btnayar->setFixedSize(w*1, h*1);
    btnayar->setIconSize(QSize(w*1.4,h*1.4));
    setVolumeState(volumeState);
    setKeyboardState(keyboardState);
    setMouseState(mouseState);
    setInternetState(internetState);
    setWebblockState(webblockState);
    setYoutubeState(youtubeState);
    setKilitState(kilitState);
    setKilitTransparanState(transparanKilitState);
}

MyPc::~MyPc()
{
    if (receiver) {
        // Tüm bağlantıları kes (frameReady vs.)
        receiver->disconnect(this);

        // Thread’i düzgün sonlandır
        receiver->stop();
        receiver->wait();

        // Qt event loop üzerinden güvenli silme
        receiver->deleteLater();
        receiver = nullptr;
    }
}


void MyPc::slotMouseClick()
{

    ///if(connectState)
    ///{
        QPalette palet;

        //qDebug()<<"tıklllllandıı";
        select=true;
         emit pcClickSignal(mac);//nesneler arası data transferi***

        if(select){
            palet.setColor(QPalette::Window, QColor(0,200,250,150));
            setPalette(palet);
            setAutoFillBackground(true);
           //selectLabel->setStyleSheet("QLabel{border: 1px solid gray;background-color: rgba(0, 200, 250, 150); border-radius: 5px;}");

        }
        else{
            palet.setColor(QPalette::Window, QColor(0,0,0,0));
            setPalette(palet);
            setAutoFillBackground(true);
           //selectLabel->setStyleSheet("QLabel{border: 1px solid gray;background-color: rgba(0, 0, 0, 0); border-radius: 5px;}");

        }
    ///}

}
void MyPc::slotPcAyar()
{
   // qDebug()<<"ayar click";
    QDialog * d = new QDialog();
    d->setWindowTitle("Host Bilgileri");
    auto appIcon = QIcon(":/icons/about.svg");
    d->setWindowIcon(appIcon);

    QSize screenSize = qApp->screens()[0]->size();
   int boy=screenSize.height()/153.6;
   int en=boy*1.1;

    d->setFixedSize(en*60,boy*80);
    QLineEdit * lineEditA = new QLineEdit();
    QLineEdit * groupNameEdit = new QLineEdit();
    QLabel *pcnameLabel=new QLabel();
    QLabel *pcgroupLabel=new QLabel();
    QLabel *pcstate=new QLabel();
    QLabel *sshstate=new QLabel();
    QLabel *vncstate=new QLabel();
    QLabel *xrdpstate=new QLabel();
    QLabel *connectstate=new QLabel();
    QLabel *displaystate=new QLabel();
    QLabel *userstate=new QLabel();
    QLabel *osstate=new QLabel();
    QLabel *volumestate=new QLabel();
    QLabel *keyboardstate=new QLabel();
    QLabel *mousestate=new QLabel();
    QLabel *internetstate=new QLabel();
    QLabel *webblockstate=new QLabel();
    QLabel *youtubewebblockstate=new QLabel();

    //QLineEdit * lineEditB = new QLineEdit();
    //QLineEdit * lineEditC = new QLineEdit();
    QCheckBox *cha=new QCheckBox("Listede Gözükmemesi için Gizle");
    QCheckBox *hostnamechb=new QCheckBox("İsim Olarak Hostname Gözüksün");
    //QCheckBox *chb=new QCheckBox("Girdi Değeri");
   // QCheckBox *chc=new QCheckBox("Girdi Değeri");

    QDialogButtonBox * buttonBox = new QDialogButtonBox();

    buttonBox->addButton("Kaydet", QDialogButtonBox::AcceptRole);
    buttonBox->addButton("Vazgeç", QDialogButtonBox::RejectRole);


    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    QVBoxLayout * vbox = new QVBoxLayout();
    QHBoxLayout * hbox1 = new QHBoxLayout();
    pcnameLabel->setText("Liste Adı:");
    pcnameLabel->setFixedWidth(en*20);
    hbox1->addWidget(pcnameLabel);
    hbox1->addWidget(lineEditA);



    QHBoxLayout * hbox2 = new QHBoxLayout();
    pcgroupLabel->setText("Bulunduğu Grup:");
    pcgroupLabel->setFixedWidth(en*20);
    hbox2->addWidget(pcgroupLabel);
    hbox2->addWidget(groupNameEdit);

    /*QHBoxLayout * hbox3 = new QHBoxLayout();
    hbox3->addWidget(lineEditC);
    hbox3->addWidget(chc);*/
    vbox->addLayout(hbox1);
    vbox->addWidget(hostnamechb);
    vbox->addLayout(hbox2);
    vbox->addWidget(cha);

    vbox->addWidget(pcstate);
    vbox->addWidget(sshstate);
    vbox->addWidget(vncstate);
    vbox->addWidget(xrdpstate);
    vbox->addWidget(connectstate);
    vbox->addWidget(userstate);
    vbox->addWidget(displaystate);
    vbox->addWidget(osstate);

    vbox->addWidget(volumestate);
    vbox->addWidget(keyboardstate);
    vbox->addWidget(mousestate);

    vbox->addWidget(internetstate);
    vbox->addWidget(webblockstate);
    vbox->addWidget(youtubewebblockstate);

  //  vbox->addLayout(hbox3);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);
    lineEditA->setText(caption);
    groupNameEdit->setText(groupname);
    if(volumeState) volumestate->setText("Ses: Açık");else volumestate->setText("Ses: Kapalı");
    if(keyboardState) keyboardstate->setText("Klavye: Açık");else keyboardstate->setText("Klavye: Kapalı");
    if(mouseState) mousestate->setText("Fare: Açık");else mousestate->setText("Fare: Kapalı");
    if(internetState) internetstate->setText("İnternet: Açık");else internetstate->setText("İnternet: Kapalı");
    if(webblockState) webblockstate->setText("Web Filtresi: Açık");else webblockstate->setText("Web Filtresi: Kapalı");
    if(youtubeState) youtubewebblockstate->setText("Youtube : Açık");else youtubewebblockstate->setText("Tek Web Sitesi: Kapalı");

    if(connectState)connectstate->setText("Pc: Açık");else connectstate->setText("Pc: Kapalı");
    if(sshState=="o")
    sshstate->setText("Ssh: Açık");
    else if (sshState=="c")
        sshstate->setText("Ssh: Kapalı");
    else if (sshState=="no")
        sshstate->setText("Ssh: ...");

    if(vncState=="o")
        vncstate->setText("Vnc: Açık ("+vncport+")");
    else if(vncState=="c")
        vncstate->setText("Vnc: Kapalı ("+vncport+")");
    else if(vncState=="no")
        vncstate->setText("Vnc: ...");

    if(xrdpState=="o")
        xrdpstate->setText("Xrdp: Açık");
    else if(xrdpState=="c")
        xrdpstate->setText("Xrdp: Kapalı");
    else if(xrdpState=="no")
        xrdpstate->setText("Xrdp: ...");

    if(connectstate)connectstate->setText("Tcp: Açık");else connectstate->setText("Tcp: Kapalı");
    //displaystate->setText("Ekran:"+display);
    userstate->setText("Kullanıcı:"+user);
    osstate->setText("Sunucu:"+hostname);

   // lineEditB->setText("");
   // lineEditC->setText("");

     if(visibleState)cha->setChecked(false);else cha->setChecked(true);
     if(hostnameVisible)hostnamechb->setChecked(true);else hostnamechb->setChecked(false);

   // chb->setChecked(true);
   // chc->setChecked(true);


    int result = d->exec();
    if(result == QDialog::Accepted)
    {
        if(lineEditA->text()!="") caption=lineEditA->text(); else caption="";
        //if(groupNameEdit->text()!="") groupname=groupNameEdit->text(); else groupname="";
        groupname=groupNameEdit->text();
        if(cha->checkState()==Qt::Checked)visibleState=false; else visibleState=true;
        if(hostnamechb->checkState()==Qt::Checked) hostnameVisible=true; else hostnameVisible=false;

            //qDebug()<<"Yeni Host Ekleniyor.";
            QJsonObject veri;
            veri["mac"] = this->mac;
            veri["ip"] = this->ip;
            veri["caption"] = this->caption;
            veri["hostname"] = this->hostname;
            veri["groupname"] = this->groupname;
            veri["visibleState"] =this->visibleState;
            veri["hostnameVisible"] =this->hostnameVisible;
            if(this->hostnameVisible)
                hostnameLabel->setText(this->hostname);
            else
                hostnameLabel->setText(this->caption);

            DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
            db->Sil("mac",this->mac);
            db->Ekle(veri);
            //qDebug()<<"mypc gizleniyor"<<mac<<visibleState;
            //if(!visibleState) { emit pcHideSignal(this->mac);}

            emit pcSettingUpdateSignal(this->mac,"pc Güncellendi");
    }
}
void MyPc::mousePressEvent(QMouseEvent *event)
{
slotMouseClick();
    if (event->button()==Qt::RightButton)
    {
    if(!multiSelect){
        //pcselectMenu();
        //pContextSelectMenu->exec(mapToGlobal(event->pos()),nullptr);
        //qDebug()<<"burası pc içi";
        emit pcRightClickSignal();
        QWidget::mousePressEvent(event);
    }
    else
    {
        //qDebug()<<"burası pc içi";
        emit pcRightClickSignal();
        QWidget::mousePressEvent(event);
    }
    }
}
void MyPc::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        slotMouseDoubleClick();
    }else if(connectState)
    {
        emit pcDoubleClickSignal(mac);
    }
    // (isteğe bağlı) aksi halde normal davranış istiyorsan:
    QWidget::mouseDoubleClickEvent(event);

}

void MyPc::slotMouseDoubleClick(){
    //if(connectState)
   // {
        //qDebug()<<"--------"<<multiSelect;
        if(multiSelect)
            slotUnselectPc();
        else
            slotSelectPc();
   // }
}
void MyPc::slotSelectPc(){
    //if(connectState)
   // {
        multiSelect=true;
        selectLabel->setStyleSheet("QLabel{border: 2px solid blue;border-radius: 5px;}");
    //}
}
void MyPc::slotUnselectPc(){
    //if(connectState)
    //{
        multiSelect=false;
        selectLabel->setStyleSheet("QLabel{border: 1px solid gray;border-radius: 5px;}");
    //}
}
QString MyPc::getIpPortStatus(QString ip_,QString port)
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

void MyPc::slothidePc()
{
    qDebug()<<"slothidePc: Host Gizlenecek...";
    QJsonObject veri;
    veri["mac"] = this->mac;
    veri["ip"] = this->ip;
    veri["caption"] = this->caption;
    veri["hostname"] = this->hostname;
    veri["groupname"] = this->groupname;

    veri["visibleState"] =false;
    visibleState=false;
    if(this->caption!="?")
        hostnameLabel->setText(this->caption);
    else
        hostnameLabel->setText(this->hostname);

    veri["hostnameVisible"] =this->hostnameVisible;
    DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
    db->Sil("mac",this->mac);
    db->Ekle(veri);
    //qDebug()<<"mypc gizleniyor"<<mac<<visibleState;
    //if(!visibleState) { emit pcHideSignal(this->mac);}

}

QPixmap MyPc::svgToPixmap(const QString &svgPath, const QSize &size)
{
    QSvgRenderer r(svgPath);
    QSize defaultSize = r.defaultSize();

    QPixmap pixmap(size);
    pixmap.fill(Qt::transparent);

    QPainter p(&pixmap);
    QRectF target(QPointF(0,0), size);
    QRectF source(QPointF(0,0), defaultSize);

    // oran koru
    QSizeF scaled = source.size();
    scaled.scale(target.size(), Qt::KeepAspectRatio);
    QRectF rect((size.width() - scaled.width())/2,
                (size.height() - scaled.height())/2,
                scaled.width(),
                scaled.height());

    r.render(&p, rect);
    return pixmap;
}
