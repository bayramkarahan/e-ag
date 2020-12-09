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
Pc::Pc(QWidget *parent) : QWidget(parent)
{
    localDir="/usr/share/E-Ag/";
    nameLabel=new QLabel(this);
    btnpc=new QToolButton(this);
    pcstateLabel=new QLabel(this);
    pcdrmLabel=new QLabel(this);
    sshstateLabel=new QLabel(this);
    sshdrmLabel=new QLabel(this);
    vncstateLabel=new QLabel(this);
    vncdrmLabel=new QLabel(this);
   // connectstateLabel=new QLabel(this);
    //connectdrmLabel=new QLabel(this);
    ftpstateLabel=new QLabel(this);
    ftpdrmLabel=new QLabel(this);
    btnctrl=new QPushButton(this);
}
void Pc::setCaption(QString cap)
{
    nameLabel->setText(cap);
}
void Pc::setIcon(QString file)
{
     QPixmap image =  QPixmap(file);
     btnpc->setIcon(QIcon(image));
       //        qDebug()<<"toooltiip"<<this->toolTip();
}
void Pc::setUpdate(QString mac,bool upd)
{
   // qDebug()<<"Pc güncelleniyor";
    QStringList list=fileToList("iplistname");
    QString line=listGetLine(list,mac);

    if (line!="")
    {
        QStringList ls=line.split("|");
       // qDebug()<<ls;
        ip=ls[0];
        ps=ls[2];
        ss=ls[3];
        vs=ls[4];
        fs=ls[5];;
        cs=ls[6];
        pcname=ls[7];
        lss=ls[8];
        ts=ls[9];
        lns=ls[10];
        S=ls[11];
        V=ls[12];
        F=ls[13];
    }
  //  bool proces=true;
    bool update=true;
    bool control=true;
    bool rcontrol=true;
    QPalette *palette=new QPalette();
    if (vs=="vncclose"||ss=="sshclose"||fs=="ftpclose")rcontrol=false;

    if(ts=="disconnect")
    {
       // qDebug()<<ip<<"Pc disconnect";
    }
    if(ts=="arpscan")
    {
       // qDebug()<<ip<<"Pc arpscan";
    }
    if(ts=="nmapscan")
    {
        ///qDebug()<<ip<<"Pc nmapscan";
    }
    if(ts!="disconnect"&&ts!="arpscan"&&ts!="nmapscan"&&lss=="e"&&rcontrol==false)
    {
      //  proces=false;
        qDebug()<<ip<<"Pc online";
        upd=true;
       /* if(vs=="vncclose"&&control)
        {//qDebug()<<"vnc";
            if (getIpVncStatus(ip)=="open") vs="vncopen"; else vs="vncclose";
        }
        if(ss=="sshclose"&&control)
        {//qDebug()<<"ssh";
            if (getIpSshStatus(ip)=="open") ss="sshopen"; else ss="sshclose";}
        if(fs=="ftpclose"&&control)
        {//qDebug()<<"ftp";
            if (getIpFtpStatus(ip)=="open") fs="ftpopen"; else fs="ftpclose";}
    */
}

    if(ts=="disconnect"||ts=="arpscan"||ts=="nmapscan") update=false;
    if(cs=="offline"&&ps=="pcopen") {palette->setColor(QPalette::Button, QColor(125,255,125,50));}
    if(cs=="online"&&ps=="pcopen")  palette->setColor(QPalette::Button, QColor(0,255,0,100));
    if(cs=="offline"&&ps=="pcclose") {palette->setColor(QPalette::Button, QColor(255,0,0,100));}

    btnpc->setPalette(*palette);
    btnpc->update();

   // qDebug()<<"vnc:"<<vs<<"ssh:"<<ss<<"ftp:"<<fs<<"pc:"<<ps<<"link"<<cs;

    if(upd)//&&control)
    {


        if(V=="e"&&vs=="vncclose")
        {
            if (getIpVncStatus(ip)=="open") vs="vncopen"; else{ vs="vncclose";
            V="h";}
        }
        if(S=="e"&&ss=="sshclose")
        {
            if (getIpSshStatus(ip)=="open") ss="sshopen"; else {ss="sshclose";
            S="h";}
        }
        if(F=="e"&&fs=="ftpclose")
        {
            if (getIpFtpStatus(ip)=="open") fs="ftpopen"; else {fs="ftpclose";
            F="h";}
        }


    }
    servisStateUpdate();// çok önemli bir yer....

    list=listRemove(list,mac); //değişecek satır siliniyor
    list<<ip+"|"+mac+"|" +ps+"|" +ss+"|" +vs+"|"+fs+"|"+ cs+"|"+nameLabel->text()+"|"+line.split("|")[8]+"|" +line.split("|")[9]+"|"+line.split("|")[10]+"|"+S+"|"+V+"|"+F;
    listToFile(list,"iplistname");

}

void Pc::servisStateUpdate()
{
    //QPalette *yesil=new QPalette();
    //QPalette *kirmizi=new QPalette();

    //yesil->setColor(QPalette::Button, QColor(0,255,0,255));
    //kirmizi->setColor(QPalette::Button, QColor(255,0,0,255));


    QFont fn( "Arial", 7, QFont::Normal);
    pcstateLabel->setFont(fn);

    pcdrmLabel->hide();
    if(ps=="pcopen")
    {
         pcdrmLabel->setText("on");
        pcstateLabel->setText("PC");
        pcstateLabel->setStyleSheet("background-color: #00ff00");
    }
    else
    { pcdrmLabel->setText("off");
        pcstateLabel->setText("PC");

        pcstateLabel->setStyleSheet("background-color: #ff0000");
    }
      sshstateLabel->setFont(fn);
      sshdrmLabel->hide();

    if(ss=="sshopen")
    {sshdrmLabel->setText("on");
        sshstateLabel->setText("SSH");
        sshstateLabel->setStyleSheet("background-color: #00ff00");
    }
    else
    {sshdrmLabel->setText("off");
        sshstateLabel->setText("SSH");

        sshstateLabel->setStyleSheet("background-color: #ff0000");
    }


    vncdrmLabel->hide();

     vncstateLabel->setFont(fn);
    if(vs=="vncopen")
    { vncdrmLabel->setText("on");
        vncstateLabel->setText("VNC");
        vncstateLabel->setStyleSheet("background-color: #00ff00");
     //vncConnectButton->setEnabled(true);
    }
    else
    { vncdrmLabel->setText("off");
        vncstateLabel->setText("VNC");

        vncstateLabel->setStyleSheet("background-color: #ff0000");
       //  vncConnectButton->setEnabled(false);
    }
/*************************************************************/
    ftpdrmLabel->hide();

     ftpstateLabel->setFont(fn);
    if(fs=="ftpopen")
    { ftpdrmLabel->setText("on");
        ftpstateLabel->setText("FTP");
        ftpstateLabel->setStyleSheet("background-color: #00ff00");
     }
    else
    { ftpdrmLabel->setText("off");
        ftpstateLabel->setText("FTP");

        ftpstateLabel->setStyleSheet("background-color: #ff0000");
       //  vncConnectButton->setEnabled(false);
    }
    /*************************************************************/
 //   qDebug()<<"pcname:"<<nameLabel->text();
}
void Pc::setMac(QString _mac,int _w,int _h)
{
    mac=_mac;

    /******************************************/
   // palette = new QPalette();
   //QWidget *cpc=new QWidget();


    QStringList list=fileToList("iplistname");
    QString line=listGetLine(list,mac);
    if (line!="")
    {
        QStringList ls=line.split("|");
        ip=ls[0];
        ps=ls[2];
        ss=ls[3];
        vs=ls[4];
        fs=ls[5];;
        cs=ls[6];
  /******************kalıcı dosyadan host isimleri çekiliyor***************/
        QStringList persistlist=fileToList("persistlist");
        QString persistline=listGetLine(persistlist,mac);
        if (persistline!="")
        {
             QStringList persistls=persistline.split("|");
             pcname=persistls[7];
        }
    /**************************************/
        w=_w;
        h=_h;
        this->resize(w,h/8*9);
       // bool setImage;
        //QString iconname;
        this->setToolTip(mac);
        nameLabel->setFixedWidth(w);
        nameLabel->setText(pcname); //pcname
        QFont ff( "Arial", 8, QFont::Normal);
        nameLabel->setFont(ff);
        nameLabel->setAlignment(Qt::AlignCenter);
        nameLabel->move(0,0);



        //btnpc->setFixedSize(20, 20);
        btnctrl->setFixedSize(w/8, h/6);
      //  btnctrl->setToolButtonStyle(Qt::ToolButtonIconOnly);
       // btnctrl->setAutoFillBackground(true);
        btnctrl->setIconSize(QSize(w,h/8*5));
        btnctrl->move(w/8*7,0);
        btnctrl->setText("?");
        QFont bf( "Arial", 8, QFont::Normal);
        btnctrl->setFont(bf);
        btnctrl->setFlat(true);
         btnctrl->setStyleSheet("color: #2299aa");

        //btnpc->setFixedSize(20, 20);
        btnpc->setFixedSize(w, h/8*6);
        btnpc->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnpc->setAutoFillBackground(true);
        btnpc->setIconSize(QSize(w,h/8*5));
        btnpc->move(0,h/8+2);
        btnpc->setToolTip(mac);

        setUpdate(mac,false);//very imported labelleri düzenliyor
        pcstateLabel->move(1,h/8*7.4);
        sshstateLabel->move(17,h/8*7.4);
        vncstateLabel->move(39,h/8*7.4);
        ftpstateLabel->move(62,h/8*7.4);
        //connectstateLabel->move(70,h/8*7.4);

   //  this->setStyleSheet("background-color: #ef00ef");

     //cpc->resize(w,h);
        connect(btnpc, &QToolButton::clicked, [=]() {
            FileCrud *fc=new FileCrud();
            fc->dosya=localDir+"click";
            if(fc->fileExists()) fc->fileRemove();
            fc->fileWrite("mac="+mac);


        });

        connect(btnctrl, &QPushButton::clicked, [=]() {
            //qDebug()<<"tıkladınnnn";
            F="e";
            S="e";
            V="e";
            if(V=="e")
            {
                if (getIpVncStatus(ip)=="open") vs="vncopen"; else {vs="vncclose";
                V="h";}
            }
            if(S=="e")
            {
                if (getIpSshStatus(ip)=="open") ss="sshopen"; else {ss="sshclose";
                S="h";}
            }
            if(F=="e")
            {
                if (getIpFtpStatus(ip)=="open") fs="ftpopen"; else {fs="ftpclose";
                F="h";}
            }
            servisStateUpdate();
            QStringList list=fileToList("iplistname");
            QString line=listGetLine(list,mac);
            list=listRemove(list,mac); //değişecek satır siliniyor

            list<<ip+"|"+mac+"|" +ps+"|" +ss+"|" +vs+"|"+fs+"|"+ cs+"|"+nameLabel->text()+"|"+line.split("|")[8]+"|" +line.split("|")[9]+"|"+line.split("|")[10]+"|"+S+"|"+V+"|"+F;
            listToFile(list,"iplistname");
           // qDebug()<<"deneme|"+S+"|"+V+"|"+F<<pcname;
            //qDebug()<<"pcname:"<<nameLabel->text();
            //setUpdate(mac,true);

            });


//qDebug()<<"pc oluşturuldu..";
    }




}

void Pc::mousePressEvent(QMouseEvent *event)
{

}
QString Pc::getIpSshStatus(QString ip_)
{
    QString ipp="";
    QStringList arguments;
    arguments << "-c" << QString("nmap  -n -p 22 %1 | awk '/22\\/tcp/{print $2;}'").arg(ip_);
             QProcess process;
            process.start("/bin/bash",arguments);
             if(process.waitForFinished())
    {
        ipp = process.readAll();
          ipp.chop(1);
    }
    qDebug()<<"ssh sorgulama:"<<ip_<<ipp;
    return ipp;
}

QString Pc::getIpVncStatus(QString ip_)
{
    QString ipp="";
    QStringList arguments;
            arguments << "-c" << QString("nmap  -n -p 5900 %1 | awk '/5900\\/tcp/{print $2;}'").arg(ip_);
            QProcess process;
            process.start("/bin/bash",arguments);
             if(process.waitForFinished())
    {
        ipp = process.readAll();
          ipp.chop(1);
    }
    qDebug()<<"vnc sorgulama:"<<ip_<<ipp;
    return ipp;
}

QString Pc::getIpFtpStatus(QString ip_)
{
    QString ipp="";
    QStringList arguments;
            arguments << "-c" << QString("nmap  -n -p 21 %1 | awk '/21\\/tcp/{print $2;}'").arg(ip_);
            QProcess process;
            process.start("/bin/bash",arguments);
             if(process.waitForFinished())
    {
        ipp = process.readAll();
          ipp.chop(1);
    }
    qDebug()<<"ftp sorgulama:"<<ip_<<ipp;
    return ipp;
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
