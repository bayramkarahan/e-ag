#ifndef FILECOPYWIDGET_H
#define FILECOPYWIDGET_H
#include<scdimgclient.h>
#include <QDir>
#include <QTextStream>
#define  echo QTextStream(stderr) <<


QWidget*  MainWindow::fileWidget()
{
    int e=en;
    int b=boy;
    // qDebug()<<"ayar click";
    QFont ff( "Arial", 20, 0);
    int yukseklik=b*7.5;
    QWidget * d = new QWidget();
    d->setWindowTitle(tr("Dosya Kopyalama Penceresi"));
    QLineEdit *le = new QLineEdit();
    le->setFixedSize(e*75,boy*15);
    le->setStyleSheet("font-size:"+QString::number(font.toInt()+2)+"px;");

    // le->setFont(ff);
    /*QLineEdit * ple = new QLineEdit();
    ple->setFixedSize(e*61,boy*7);
    ple->setStyleSheet("font-size:"+QString::number(font.toInt()+2)+"px;");
*/
    QLabel *commandFileLabel=new QLabel("Dosya");
    commandFileLabel->setFixedSize(e*7,yukseklik);
    commandFileLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
/*
    QLabel *pathLabel=new QLabel("Hedef Konum\n/home/user/\n/tmp/");
    pathLabel->setFixedSize(e*12,yukseklik);
    pathLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
*/


    fileSelectButton=new QToolButton();
    fileSelectButton->setFixedSize(e*13,yukseklik*2);
    fileSelectButton->setAutoRaise(true);
    //fileSelectButton->setAutoFillBackground(true);
    fileSelectButton->setText(tr("Dosya\nSeç"));
    fileSelectButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    fileSelectButton->setIcon(QIcon(":/icons/openfile.svg"));
    fileSelectButton->setIconSize(QSize(b*6,yukseklik*0.9));
    fileSelectButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(fileSelectButton, &QToolButton::clicked, [=]() {
        //pcClickSlot(pcMac->text());
        QString seatUser=getSessionInfo(getSeatId(),"USER=");
        QStringRef _sessionUser=seatUser.rightRef(seatUser.length()-5);
        seatUser=_sessionUser.toString();
        //qDebug()<<"Kullanıcı: "<<sessionUser;
        QString fileName = QFileDialog::getOpenFileName(this,tr("Dosya Seç"),"/home/"+seatUser, tr("Files (*)"));
        le->setText(fileName);

        QFileInfo fi(le->text());

        mesajSlot(tr("Dosya Seçildi."));

    });


    fileCopyButton=new QToolButton();
    fileCopyButton->setFixedSize(e*13,yukseklik*2);
    fileCopyButton->setAutoRaise(true);
    fileCopyButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    fileCopyButton->setText(tr("Ev Dizinine\nGönder"));
    fileCopyButton->setIcon(QIcon(":/icons/selectcopyfile.svg"));
    fileCopyButton->setIconSize(QSize(b*8,yukseklik*0.9));
    fileCopyButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(fileCopyButton, &QToolButton::clicked, [=]() {
        QString name1 = QUrl::fromLocalFile(le->text()).path(QUrl::FullyEncoded);
        name1.replace("%20","%5C%20");
        QUrl pth;

        QFileInfo fi(le->text());
        //QString name = fi.fileName();

        QString uzanti = fi.completeSuffix();
        QString ad = fi.baseName().replace(" ","");
        if(uzanti=="")
            selectFileCopySlot("homesendfile",pth.fromPercentEncoding(name1.toUtf8()),ad);
         else
            selectFileCopySlot("homesendfile",pth.fromPercentEncoding(name1.toUtf8()),ad+"."+uzanti);


        mesajSlot("Dosya Seçili Pc'ye Kopyalandı.");
    });

    fileCopyInstallButton=new QToolButton();
    fileCopyInstallButton->setFixedSize(e*13,yukseklik*2);
    fileCopyInstallButton->setAutoRaise(true);
    fileCopyInstallButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    fileCopyInstallButton->setText(tr("Paketi\nKur"));
    fileCopyInstallButton->setIcon(QIcon(":/icons/install.svg"));
    fileCopyInstallButton->setIconSize(QSize(b*8,yukseklik*0.9));
    fileCopyInstallButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(fileCopyInstallButton, &QToolButton::clicked, [=]() {
        QString name1 = QUrl::fromLocalFile(le->text()).path(QUrl::FullyEncoded);
        name1.replace("%20","%5C%20");
        QUrl pth;

        QFileInfo fi(le->text());
        QString name = fi.fileName();

        QString uzanti = fi.completeSuffix();
        QString ad = fi.baseName().replace(" ","");
        QString dosya=QString("cat >/tmp/debeagscript << EOF"
                                "\n#!/bin/bash"
                                "\nexport DEBIAN_FRONTEND=noninteractive"
                                "\napt-get --fix-broken install -y"
                                "\napt-get install -f -y"
                                "\napt-get autoremove -y"
                                "\napt-get update"
                                "\napt-get install /tmp/%1 -y"
                                "\napt-get install -f -y"
                                "\nEOF").arg(name);

        system(dosya.toStdString().c_str());
        /*****************************************************************************/

        selectFileCopySlot("realdebsendfile",pth.fromPercentEncoding(name1.toUtf8()),name);
        //system("sleep 0.1");
        selectFileCopySlot("debscriptsendfile", "/tmp/debeagscript","debeagscript");
        for(int i=0;i<onlinePcList.count();i++)
        {
            if((onlinePcList[i]->select||onlinePcList[i]->multiSelect))
            {
                onlinePcList[i]->setCommandButonState(false);
            }
        }
       mesajSlot("Dosya Seçili Pc'ye Kopyalandı ve Kuruldu.");
    });

    fileCopyInstallScriptButton=new QToolButton();
    fileCopyInstallScriptButton->setFixedSize(e*13,yukseklik*2);
    fileCopyInstallScriptButton->setAutoRaise(true);
    fileCopyInstallScriptButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    fileCopyInstallScriptButton->setText(tr("Scripti\nÇalıştır"));
    fileCopyInstallScriptButton->setIcon(QIcon(":/icons/bash.svg"));
    fileCopyInstallScriptButton->setIconSize(QSize(b*8,yukseklik*0.9));
    fileCopyInstallScriptButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(fileCopyInstallScriptButton, &QToolButton::clicked, [=]() {
        QString name1 = QUrl::fromLocalFile(le->text()).path(QUrl::FullyEncoded);
        name1.replace("%20","%5C%20");
        QUrl pth;

        QFileInfo fi(le->text());
        QString name = fi.fileName();

        QString uzanti = fi.completeSuffix();
        QString ad = fi.baseName().replace(" ","");
        QString dosya=QString("cat >/tmp/eagscript << EOF"
                                "\n#!/bin/bash"
                                "\nexport DEBIAN_FRONTEND=noninteractive"
                                "\napt-get --fix-broken install -y"
                                "\napt-get install -f -y"
                                "\napt-get autoremove -y"
                                "\napt-get update"
                                "\nbash /tmp/%1"
                                "\nEOF").arg(name);

        system(dosya.toStdString().c_str());
        /*****************************************************************************/

        selectFileCopySlot("realscriptsendfile",pth.fromPercentEncoding(name1.toUtf8()),name);
        //system("sleep 0.1");
        selectFileCopySlot("scriptsendfile", "/tmp/eagscript","eagscript");

    for(int i=0;i<onlinePcList.count();i++)
    {
     if((onlinePcList[i]->select||onlinePcList[i]->multiSelect))
     {
            onlinePcList[i]->setCommandButonState(false);
     }
    }
        mesajSlot("Script Dosya Seçili Pc'ye Kopyalandı ve Kuruldu.");
    });


    QToolButton *fileCopyDesktopNotGetSendButton=new QToolButton();
    fileCopyDesktopNotGetSendButton->setFixedSize(e*13,yukseklik*2);
    fileCopyDesktopNotGetSendButton->setAutoRaise(true);
    fileCopyDesktopNotGetSendButton->setText(tr("Masaüstüne\nGönder"));
    fileCopyDesktopNotGetSendButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    fileCopyDesktopNotGetSendButton->setIcon(QIcon(":/icons/senddesktopfile.svg"));
    fileCopyDesktopNotGetSendButton->setIconSize(QSize(b*8,yukseklik*0.9));
    fileCopyDesktopNotGetSendButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(fileCopyDesktopNotGetSendButton, &QToolButton::clicked, [=]() {
        QString name1 = QUrl::fromLocalFile(le->text()).path(QUrl::FullyEncoded);
        name1.replace("%20","%5C%20");
        QUrl pth;

        QFileInfo fi(le->text());
        QString name = fi.fileName();

        QString uzanti = fi.completeSuffix();
        QString ad = fi.baseName().replace(" ","");
        if(uzanti=="")
            selectFileCopySlot("desktopsendfile", pth.fromPercentEncoding(name1.toUtf8()),ad);
        else
            selectFileCopySlot("desktopsendfile", pth.fromPercentEncoding(name1.toUtf8()),ad+"."+uzanti);

        mesajSlot("Dosya Masaüstlerine Gönderildi.");
    });

    QToolButton *fileCopyDesktopSendButton=new QToolButton();
    fileCopyDesktopSendButton->setFixedSize(e*13,yukseklik*2);
    fileCopyDesktopSendButton->setAutoRaise(true);
    fileCopyDesktopSendButton->setText(tr("Çalışma\n Dağıt"));
    fileCopyDesktopSendButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    fileCopyDesktopSendButton->setIcon(QIcon(":/icons/senddesktopquiz.svg"));
    fileCopyDesktopSendButton->setIconSize(QSize(b*8,yukseklik*0.9));
    fileCopyDesktopSendButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(fileCopyDesktopSendButton, &QToolButton::clicked, [=]() {
        QString name1 = QUrl::fromLocalFile(le->text()).path(QUrl::FullyEncoded);
        name1.replace("%20","%5C%20");
        QUrl pth;

        QFileInfo fi(le->text());
        QString name = fi.fileName();
        QString uzanti = fi.completeSuffix();
        QString onlypath=fi.canonicalPath();

        /*qDebug()<<"dosya adı-uzantısı:"<<name;
        qDebug()<<"dosya sadece adı:"<<fi.baseName();
        qDebug()<<"dosya sadece uzantı:"<<uzanti;
        qDebug()<<"dosya sadece yol:"<<onlypath;
        qDebug()<<"dosya ve yolu:"<<pth.fromPercentEncoding(name1.toUtf8());
*/
        //return;
          if(uzanti=="")
            selectFileCopySlot("desktopsendworkfile",pth.fromPercentEncoding(name1.toUtf8()),"e-ag-server-"+fi.baseName());
         else
             selectFileCopySlot("desktopsendworkfile",pth.fromPercentEncoding(name1.toUtf8()),"e-ag-server-"+name);
         mesajSlot("Dosya Masaüstlerine Gönderildi.");
    });

    QToolButton *fileCopyDesktopGetButton=new QToolButton();
    fileCopyDesktopGetButton->setFixedSize(e*13,yukseklik*2);
    fileCopyDesktopGetButton->setAutoRaise(true);
    //fileCopyDesktopGetButton->setAutoFillBackground(true);
    fileCopyDesktopGetButton->setText(tr("Çalışma\n Topla"));
    fileCopyDesktopGetButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    fileCopyDesktopGetButton->setIcon(QIcon(":/icons/getdesktopquiz.svg"));
    fileCopyDesktopGetButton->setIconSize(QSize(b*8,yukseklik*0.9));
    fileCopyDesktopGetButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(fileCopyDesktopGetButton, &QToolButton::clicked, [=]() {
        /*for(int i=0;i<onlinePcList.count();i++)
        {
            if(onlinePcList[i]->sshState)
            {
                udpSendData("x11command","dosyatopla",onlinePcList[i]->ip);


            }
        }*/
        udpSendData("dosyatopla","","","Dosya Masaüstlerinden Alındı",false);


        mesajSlot("Dosya Masaüstlerinden Alındı.");
    });

    QToolButton *helpButton= new QToolButton;
    helpButton->setFixedSize(e*13,yukseklik*2);
    helpButton->setAutoRaise(true);
    // bilgiButton->setAutoFillBackground(true);
    helpButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    helpButton->setText(tr("Yardım"));
    helpButton->setIcon(QIcon(":/icons/help.svg"));
    helpButton->setIconSize(QSize(b*8,yukseklik*0.9));
    helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(helpButton, &QToolButton::clicked, [=]() {
        QTextDocument *doc=new QTextDocument();

        doc->setHtml(tr("<center><h2>Dosya Kopyalama</h2></center>"
                     "<center><img src=\":/icons/dosyakopyalama.png\" /></center> "
                     "<center><img src=\":/icons/istemci.png\" /></center>"
                     "<br/><br/>1-Klasör içeriğinin tamamını kopyalamak için dosya ismi yerine * konulması gerekir;"
                     "<br/> Örneğin: /home/user/* şeklinde klasör içeriğini kopyalar."
                     "<br/><br/>2-İstemcide açık kullanıcı masaüstüne dosya kopyalama için Masaüstlerine Dağıt seçeneğini kullanabilirsiniz."
                     "<br/><br/>3-İstemcide açık kullanıcı masaüstüne çalışma dosyası göndermek için Çalışmaları Dağıt seçeneğini kullanabilirsiniz."
                     "<br/><br/>4-İstemcide açık kullanıcı masaüstündeki çalışma dosyasını Sunucuya toplamak için Çalışmaları Topla seçeneğini kullanabilirsiniz."
                     "<br/><br/>5-<b>Pc'lere Kopyala</b> seçeneği Client'de açık kullanıcının ev dizinine kopyalanacaktır."
                     "<br/><br/>6-Birden fazla istemciye kopyalama için istemcileri seçerek kopyalanabilir."
                     "<br/><br/>7-<b>Paketi Kur</b> seçeneği ile deb uzantılı paketi istemciye kururulumu yapılır."
                     "<br/><br/>8-<b>Scripti Çalıştır</b> seçeneği ile scripti istemci üzerinde çalıştırır."
                        ));
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
        d1->setWindowTitle(tr("Dosya Kopyalama Yardım Penceresi"));
        d1->setFixedSize(QSize(boy*215,boy*110));
        auto appIcon = QIcon(":/icons/e-ag.svg");
        d1->setWindowIcon(appIcon);

        d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

        d1->setLayout(vbox);
        d1->exec();
    });
    QGridLayout * vbox = new QGridLayout();
    vbox->setContentsMargins(0, 0, 0,0);
    vbox->setVerticalSpacing(0);
    //vbox->addWidget(pathLabel,2,1,1,1);
    //vbox->addWidget(ple,2,2,1,1);
    vbox->addWidget(commandFileLabel,1,1,1,1);
    vbox->addWidget(le,1,2,1,1);
    vbox->addWidget(fileSelectButton,1,3,2,1);
    vbox->addWidget(fileCopyInstallButton,1,4,2,1);
    vbox->addWidget(fileCopyInstallScriptButton,1,5,2,1);
    vbox->addWidget(fileCopyButton,1,6,2,1);
    //vbox->addWidget(fileCopyAllButton,1,7,2,1);

    vbox->addWidget(fileCopyDesktopNotGetSendButton,1,8,2,1);

    vbox->addWidget(fileCopyDesktopSendButton,1,9,2,1);
    vbox->addWidget(fileCopyDesktopGetButton,1,10,2,1);


    vbox->addWidget(helpButton,1,11,2,1);

    d->setLayout(vbox);
    return d;
}

void MainWindow::selectFileCopySlot(QString _mesajtype,QString _sourcePath,QString _targetPath)
{
       for(int i=0;i<onlinePcList.count();i++)
    {
     if((onlinePcList[i]->select||onlinePcList[i]->multiSelect))
     {
     if((_mesajtype=="desktopsendworkfile"||
         _mesajtype=="desktopsendfile")
        &&onlinePcList[i]->user=="noLogin")
        continue;
        qDebug()<<"kopyalanacak dosya: "<<_sourcePath<<_targetPath<<onlinePcList[i]->ip;
        ///QString komut="/usr/bin/scd-client "+onlinePcList[i]->ip+" "+onlinePcList[i]->netProfil.ftpPort+" PUT "+_sourcePath+" /"+_targetPath;
        //system(komut.toStdString().c_str());
        fileCopyTasks.enqueue({_mesajtype,onlinePcList[i]->ip,onlinePcList[i]->netProfil.ftpPort,_sourcePath,_targetPath});

     }
    }
    listeyiKopyala();
    mesajSlot("Dosya Seçili Pc'lere Kopyalandı");
}
void MainWindow::listeyiKopyala() {
    if (fileCopyTasks.isEmpty()) {
        qDebug() << "Tüm bilgisayarlara dosya gönderildi.";
        return;
    }
    fileCopyTask current = fileCopyTasks.dequeue();
    QString komut="/usr/bin/scd-client "+current.ip+" "+current.port+" PUT "+current.sourcePath+" /"+current.targetPath;
    /*********************QProcess***********************************/
    /*********************QProcess***********************************/
    QStringList arguments;
    QProcess *process = new QProcess(this);
    connect(process,
               QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
               [=](int exitCode, QProcess::ExitStatus exitStatus) {
                   this->onProcessFinished(exitCode, exitStatus, current);
                   process->deleteLater();
                   listeyiKopyala();
               });
    arguments << "-c" << komut<<" &";
    process->start("/bin/bash",arguments);
}

void MainWindow::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus, fileCopyTask task) {
    if (exitStatus == QProcess::NormalExit && exitCode == 0) {
        qDebug() << "Dosya Kopyalama Başarılı:" << task.mesajtype << "->" << task.ip<<task.targetPath;
        udpSendData(task.mesajtype,task.targetPath,"","",false);
    } else {
        qDebug() << "Dosya Kopyalama Hata oluştu:" << task.mesajtype << "->" << task.ip;
    }
    udpSendData(task.mesajtype,task.targetPath,"","",false);
}



#endif // FILECOPYWIDGET_H
