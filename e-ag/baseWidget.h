#ifndef BASEWIDGET_H
#define BASEWIDGET_H
#include<MyDialog.h>
#include<userprivilegehelper.h>
#include<QLocalSocket>
QWidget* MainWindow::baseWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=e*10;
    QWidget * d = new QWidget();
    // d->setFixedSize(e*180,b*23);
    // d->setStyleSheet("background-color: #ffdced;font-size:"+QString::number(font.toInt()-2)+"px;");
    // 🔲 Container (kutu)
    QFrame *vncbox = new QFrame(d);
    vncbox->setFrameShape(QFrame::Box);
    //vncbox->setLineWidth(1);
    vncbox->setStyleSheet("QFrame { border: 1px solid #ccc; border-radius: 2px; }");

    // 📦 Layout
    QHBoxLayout *layoutvnc = new QHBoxLayout(vncbox);
    layoutvnc->setSpacing(2);
    layoutvnc->setContentsMargins(1,1,1,1);

    // 🔘 Buton
    QToolButton *vncConnectPcButton = new QToolButton();
    vncConnectPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    vncConnectPcButton->setIcon(QIcon(":icons/vnc.svg"));
    vncConnectPcButton->setIconSize(QSize(yukseklik,boy*8));
    vncConnectPcButton->setAutoRaise(true);
    // vncConnectPcButton->setAutoFillBackground(true);
    vncConnectPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    vncConnectPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.4);
    vncConnectPcButton->setText(tr("VNC"));
    connect(vncConnectPcButton, &QToolButton::clicked, [=]() {
        pcDoubleClickSignalSlot(pcMac->text(),"");
    });

    // Slider buton boyutunun yarısı kadar olacak
    vncEkranSlider = new QSlider(Qt::Vertical);
    vncEkranSlider->setFixedSize(yukseklik*0.3, yukseklik*1.4);
    vncEkranSlider->setMinimum(0);
    vncEkranSlider->setMaximum(200);
    vncEkranSlider->setValue(80); // varsayılan değer
    CustomInputDialog *cid0=new CustomInputDialog(tr("İstemci Kullanıcısı"),tr(" İstemcideki Kullanıcının Adını Giriniz :"),"",300,100,this);
    cid0->readMetaData("vncEkranSlider", [this](QString _data){
           if(_data!=""){
            //qDebug() << "vncEkranSlider geldi:" << _data;
           int value = _data.toInt();
           vncEkranSlider->setValue(value);
           }
           else
           {
             vncEkranSlider->setValue(80);
             qDebug() << "vncEkranSlider 80 ayarlandı";
           }
    });
    vncEkranSlider->setTracking(false);
    connect(vncEkranSlider, &QSlider::valueChanged, this, [=](int value){
        QString vncEkranSliderValue=QString::number(value);
        cid0->saveMetaData("vncEkranSlider", vncEkranSliderValue);
    });

    // 📌 Layout’a ekle
    layoutvnc->addWidget(vncConnectPcButton, 0, Qt::AlignCenter);
    layoutvnc->addWidget(vncEkranSlider, 0, Qt::AlignCenter);
    // 📌 Kutunun boyutu (opsiyonel)
    vncbox->setFixedSize(yukseklik*1.25,yukseklik*1.5);


    QToolButton *novncConnectPcButton = new QToolButton();
    novncConnectPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    novncConnectPcButton->setIcon(QIcon(":icons/novnc.svg"));
    novncConnectPcButton->setIconSize(QSize(yukseklik,boy*8));
    novncConnectPcButton->setAutoRaise(true);
    // vncConnectPcButton->setAutoFillBackground(true);
    novncConnectPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    novncConnectPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    novncConnectPcButton->setText(tr("noVNC"));
    connect(novncConnectPcButton, &QToolButton::clicked, [=]() {
        QString kmt26="env MOZ_USE_XINPUT2=1 /usr/lib/firefox/firefox "+pcIp->text()+":6085/vnc.html";
        system(kmt26.toStdString().c_str());

        // QDesktopServices::openUrl(QUrl("192.168.1.101:6085"));
    });

    // 🔲 Container (kutu)
    QFrame *rdpbox = new QFrame(d);
    rdpbox->setFrameShape(QFrame::Box);
    //rdpbox->setLineWidth(1);
    rdpbox->setStyleSheet("QFrame { border: 1px solid #ccc; border-radius: 2px; }");

    // 📦 Layout
    QHBoxLayout *layoutrdp = new QHBoxLayout(rdpbox);
    layoutrdp->setSpacing(2);
    layoutrdp->setContentsMargins(1,1,1,1);

    // 🔘 Buton
     QToolButton *xrdpConnectPcButton = new QToolButton();
    xrdpConnectPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    xrdpConnectPcButton->setIcon(QIcon(":icons/rdp.svg"));
    xrdpConnectPcButton->setIconSize(QSize(yukseklik,boy*8));
    xrdpConnectPcButton->setAutoRaise(true);
   // xrdpConnectPcButton->setAutoFillBackground(true);
    xrdpConnectPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    xrdpConnectPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.4);
    xrdpConnectPcButton->setText(tr("RDP"));
    connect(xrdpConnectPcButton, &QToolButton::clicked, [=]() {
        slotRdp();
    });

    // Slider buton boyutunun yarısı kadar olacak
    rdpEkranSlider = new QSlider(Qt::Vertical,d);
    rdpEkranSlider->setFixedSize(yukseklik*0.3, yukseklik*1.4);
    rdpEkranSlider->setMinimum(0);
    rdpEkranSlider->setMaximum(200);
    rdpEkranSlider->setValue(80); // varsayılan değer
    CustomInputDialog *cidrdp=new CustomInputDialog(tr("İstemci Kullanıcısı"),tr(" İstemcideki Kullanıcının Adını Giriniz :"),"",300,100,this);
    cidrdp->readMetaData("rdpEkranSlider", [this](QString _data){
           if(_data!=""){
            //qDebug() << "rdpEkranSlider geldi:" << _data;
           int value = _data.toInt();
           rdpEkranSlider->setValue(value);
           }
           else
           {
             vncEkranSlider->setValue(75);
             qDebug() << "rdpEkranSlider 75 ayarlandı";
           }
    });
    rdpEkranSlider->setTracking(false);
    connect(rdpEkranSlider, &QSlider::valueChanged, this, [=](int value){
        QString rdpEkranSliderValue=QString::number(value);
        cidrdp->saveMetaData("rdpEkranSlider", rdpEkranSliderValue);
        //qDebug() << "rdpEkranSlider"<<rdpEkranSliderValue;
    });
    // 📌 Layout’a ekle
    layoutrdp->addWidget(xrdpConnectPcButton, 0, Qt::AlignCenter);
    layoutrdp->addWidget(rdpEkranSlider, 0, Qt::AlignCenter);
    // 📌 Kutunun boyutu (opsiyonel)
    rdpbox->setFixedSize(yukseklik*1.25,yukseklik*1.5);


    QToolButton *terminalPcButton = new QToolButton();
    terminalPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    terminalPcButton->setIcon(QIcon(":icons/ssh.svg"));
    terminalPcButton->setIconSize(QSize(yukseklik,boy*8));
    terminalPcButton->setAutoRaise(true);
    //  terminalPcButton->setAutoFillBackground(true);
    terminalPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    terminalPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    terminalPcButton->setText(tr("Terminal"));
    connect(terminalPcButton, &QToolButton::clicked, [=]() {

        UserPrivilegeHelper helper;
        QString seatUser = helper.detectActiveUser();// 1) Aktif kullanıcıyı bul

        CustomInputDialog *cid0=new CustomInputDialog(tr("İstemci Kullanıcısı"),tr(" İstemcideki ssh Kullanıcının Adını Giriniz :"),"",300,100);
        cid0->setData("sshuser",seatUser,"text");
        int result0=cid0->exec();
        seatUser = cid0->getText();
        //qDebug() << "User geldi:"<<result0 << seatUser;
            if(seatUser!=""&&result0==1)
            {
            // Kullanıcı + parola kaydediliyor
            cid0->saveMetaData("sshuser", seatUser);
            QString kmt10="xterm -fa \"Monospace\" -fs 14 -e \"ssh "+seatUser+"@"+pcIp->text()+"\" &";
            system(kmt10.toStdString().c_str());
        }
    // QString kmt10="x-terminal-emulator -e \"ssh "+remoteUserName+"@"+pcIp->text()+"\"";
        //QString kmt9="ssh etapadmin@"+pcIp->text()+"\" &";
    // SSH bağlantısını başlat
        //QTermWidget *terminal=new QTermWidget();
        //qterm->show();
        //qterm->sendText(kmt10);
        //qterm->sendData(kmt9.c_str());
       // return;
       /* QStringList komut;
        komut << "grep" << "-i" << "aranacak_kelime" << "dosya_adi.txt";
        terminal->startShellProgram(komut);*/

        mesajSlot("Seçili Hostda Terminal Başlatıldı.");

    });

    QToolButton *selectPcButton = new QToolButton();
    selectPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    selectPcButton->setIconSize(QSize(yukseklik,boy*8));
    selectPcButton->setIcon(QIcon(":icons/select.svg"));
    selectPcButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    selectPcButton->setAutoRaise(true);
    // selectPcButton->setAutoFillBackground(true);
    selectPcButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    selectPcButton->setText(tr("Pc Seç"));
    connect(selectPcButton, &QToolButton::clicked, [=]() {
        selectSlot();

    });


    QToolButton *ftpPc=new QToolButton();
    ftpPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    ftpPc->setIcon(QIcon(":/icons/ftp.svg"));
    ftpPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ftpPc->setIconSize(QSize(yukseklik,boy*8));

    ftpPc->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    ftpPc->setAutoRaise(true);
    // ftpPc->setAutoFillBackground(true);
    ftpPc->setText("FTP");
    connect(ftpPc, &QToolButton::clicked, [=]() {

        UserPrivilegeHelper helper;
        QString seatUser = helper.detectActiveUser();// 1) Aktif kullanıcıyı bul

        CustomInputDialog *cid0=new CustomInputDialog(tr("İstemci Kullanıcısı"),tr(" İstemcideki Kullanıcının Adını Giriniz :"),"",300,100);
        cid0->setData("lastuser",seatUser,"text");
        int result0=cid0->exec();
        seatUser = cid0->getText();
        //qDebug() << "User geldi:"<<result0 << seatUser;

        CustomInputDialog  *cid1=new CustomInputDialog(tr("İstemci Parolası"),tr(" İstemcideki Kullanıcının Parolasını Giriniz :"),"",300,100);
        cid1->setData("lastpasswd","","passwd");
        int result1=cid1->exec();
        QString seatUserPasswd=cid1->getText();
        //qDebug() << "password geldi:"<<result1 << seatUserPasswd;

            if(seatUser!=""&&seatUserPasswd!=""&&result0==1&&result1==1)
            {

            // Kullanıcı + parola kaydediliyor
            cid0->saveMetaData("lastuser", seatUser);
            cid1->saveMetaData("lastpasswd", seatUserPasswd);
            QString ftpapp="nemo";
            if(QFile::exists("/usr/bin/nemo")) ftpapp="nemo";
            else if(QFile::exists("/usr/bin/thunar")) ftpapp="thunar";
            else if(QFile::exists("/usr/bin/nautilus"))ftpapp="nautilus";
            else if(QFile::exists("/usr/bin/dolphin")) ftpapp="dolphin";
            else if(QFile::exists("/usr/bin/pcmanfm")) ftpapp="pcmanfm";
            else{
                MyDialog(tr("Uyarı"),tr("ftp için nemo, thunar, nautilus, dolphi, pcmanfm vb. uygulama bulunamadı.\n"
                              "Bu uygulamalardan birini kururarak ftp işlemi yapabilirsiniz.."),"","","tamam",500,100).exec();
            }
            textBrowser_receivedMessages->clear();
            QString  komut;
            komut.append(ftpapp).append(" sftp://").append(seatUser+":").append(seatUserPasswd).append("@"+pcIp->text());
            eagtraySendDataDetached(komut);

 }
    });

    QToolButton *wolButton=new QToolButton();
    wolButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    wolButton->setIcon(QIcon(":/icons/wol.svg"));
    wolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    wolButton->setIconSize(QSize(yukseklik,boy*8));

    wolButton->setFixedSize(yukseklik*0.95,yukseklik*1.5);
    wolButton->setAutoRaise(true);
    // ftpPc->setAutoFillBackground(true);
    wolButton->setText(tr("Pc Aç"));
    QMenu *wolMenu = new QMenu();

    QWidgetAction *action = new QWidgetAction(wolMenu);
    QWidget *w = wolWidget(); // yukarıdaki fonksiyonla
    QRect screen = QApplication::primaryScreen()->geometry();
    int x = (screen.width() - w->sizeHint().width()) / 2;
    int y = (screen.height() - w->sizeHint().height()) / 2;
    //w->show();
    //w->move(x, y);  // tam ekran ortasına al
    //w->close();

    action->setDefaultWidget(w);
     wolMenu->addAction(action);
    wolButton->setMenu(wolMenu);
    wolButton->setPopupMode(QToolButton::MenuButtonPopup);

    connect(wolButton, &QToolButton::clicked, [=]() {

        for(int i=0;i<onlinePcList.count();i++)
        {
            if(onlinePcList[i]->connectState==false&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect))
            {
                ///qDebug()<<onlinePcList[i]->ip<<onlinePcList[i]->mac;
                //slotWakeOnLan(onlinePcList[i]->ip,onlinePcList[i]->mac);
                QString kmt29="wakeonlan "+onlinePcList[i]->mac+" &";
                system(kmt29.toStdString().c_str());
                qDebug()<<"Açılana Pc: "<<kmt29;
            }
        }

    });

    QToolButton *cleanDesktopButton=new QToolButton();
    cleanDesktopButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    cleanDesktopButton->setIcon(QIcon(":/icons/cleandesktop.svg"));
    cleanDesktopButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    cleanDesktopButton->setIconSize(QSize(yukseklik,boy*5));

    cleanDesktopButton->setFixedSize(yukseklik*1.4,yukseklik*1.5);
    cleanDesktopButton->setAutoRaise(true);
    // ftpPc->setAutoFillBackground(true);
    cleanDesktopButton->setText(tr("Açık\nUygulamaları\nKapat"));
    connect(cleanDesktopButton, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}
        //udpSendData("consolecommand","consolecommand","bash /usr/bin/clean-desktop","clean-desktop",true);
        udpSendData("x11command","windowclose","","window-close",true);

    });

    QToolButton *helpButton= new QToolButton;
    helpButton->setFixedSize(yukseklik*0.9, yukseklik*1.5);
    helpButton->setIconSize(QSize(yukseklik,boy*8));
    helpButton->setIcon(QIcon(":/icons/help.svg"));
    helpButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    helpButton->setText(tr("Yardım"));
    helpButton->setAutoRaise(true);

    helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(helpButton, &QToolButton::clicked, [=]() {

        QTextDocument *doc=new QTextDocument();

        doc->setHtml(tr("<center><h2>Temel İşlemler</h2></center>"
                     "<center><img src=\":/icons/temelislem.png\" /></center> "
                     "<br/><br/>1-Vnc seçeneği istemcide açık olan masaüstüne erişilir."
                     "<br/><br/>2-noVnc seçeneği istemcide açık olan masaüstüne web tarayısıyla erişilir."
                     "<br/><br/>3-Rdp ile istemci üzerinde açık olmayan bir kullanıcı ile masaüstüne erişilir."
                     "<br/><br/>4-Terminal ile  ssh üzerinden konsoluna bağlanmak kullanılır."
                     "<br/><br/>5-FTP ile dosya yöneticisini kullanarak istemciye bağlanıp dosya transferi için kullanılır."
                     "<br/><br/>6-İstemcinin uzaktan başlatmak için Pc Aç seçeneği kullanılabilir."
                     "Pc Aç seçeneği için; İstemcinin BIOS seçeneklerinden Wake On Lan seçeneği aktif edilmeli. "
                     "<br/><br/>7-İstemci simgelerinin altındaki C V S R X işaretleri servisleri ifade eder."
                     "<center><img src=\":/icons/istemci.png\" /></center>"
                     "Simgeler yeşilse servis çalışıyor. Kırmızı ise servis çalışmıyordur."
                     "<br/>C=İstemcide açlışan komutun sonucunu izleyebileceğimiz bir seçenek. C üzerine tıklayarak detaylarına bakabilirsiniz. C yeşilse komut başarılı, kırmızı ise bir hata olmuştur."
                     "<br/>V=Vnc servisi, yeşil=Aktif masaüsütü kontrolü açık/Aktif masaüsütü kontrolü kırmızı=kapalı"
                     "<br/>S=Ssh servisi, yeşil=Uzak terminal açık/kırmızı=Uzak terminal kapalı"
                     "<br/>R=Xrdp servisi, yeşil=Uzak masaüstü kontrolü açık/kırmızı=uzak masaüstü kontrolü kapalı"
                     "<br/>X=x11 ekranı, yeşil=Kullanıcı login olmuş/kırmızı=kullanıcı login olmamış"
                        ));
        QPrinter pdf;
        pdf.setOutputFileName("/tmp/temelislem.pdf");
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
        d1->setWindowTitle(tr("Temel İşlemler Yardım Penceresi"));
        d1->setFixedSize(QSize(boy*215,boy*120));
        auto appIcon = QIcon(":/icons/e-ag.svg");
        d1->setWindowIcon(appIcon);

        d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

        d1->setLayout(vbox);
        d1->exec();

    });
    /******************************************************/
    auto layout = new QGridLayout(d);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    //  layout->setHorizontalSpacing(0);
    // layout->addWidget(hostListePcButton, 0,0,3,1);
    //layout->addWidget(selectPcButton, 0,1,3,1);

    layout->addWidget(vncbox, 0,2,3,1);
   // layout->addWidget(vncEkranSlider, 0,2,3,1);
    //layout->addWidget(vncConnectPcButton, 0,3,3,1);

    layout->addWidget(novncConnectPcButton, 0,4,3,1);
    layout->addWidget(rdpbox, 0,5,3,1);

   // layout->addWidget(rdpEkranSlider, 0,5,3,1);
   // layout->addWidget(xrdpConnectPcButton, 0,6,3,1);

    layout->addWidget(terminalPcButton, 0,7,3,1);
    layout->addWidget(ftpPc, 0,8,3,1);
    layout->addWidget(wolButton, 0,9,3,1);
    layout->addWidget(cleanDesktopButton, 0,10,3,1);

    layout->addWidget(kilitWidget(), 0,12,3,1);
    layout->addWidget(ekranWidget(), 0,13,3,1);
    layout->addWidget(poweroffrebootWidget(), 0,20,3,1);
    //layout->addWidget(keyboardmouseWidget(), 0,21,3,1);
    //layout->addWidget(volumeWidget(), 0,23,3,1);
    groupwidget1=groupWidget(nullptr);
    groupwidget1=groupWidget(groupwidget1);
    layout->addWidget(logoutWidget(), 0,25,3,1);
    layout->addWidget(groupwidget1, 0,26,3,1);
    layout->addWidget(languageWidget(), 0,28,3,1);

    layout->addWidget(helpButton, 0,30,3,1);
    d->setLayout(layout);
    return d;
}


#endif // BASEWIDGET_H
