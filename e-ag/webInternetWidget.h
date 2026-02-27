#ifndef WEBINTERNETWIDGET_H
#define WEBINTERNETWIDGET_H

QWidget* MainWindow::webInternetWidget()
{
    int e=en;
    int b=boy;
    // qDebug()<<"ayar click";
    QFont ff( "Arial", 20, 0);
    int yukseklik=b*7.5;
    QWidget * d = new QWidget();
    d->setWindowTitle("web/internet Çalıştırma Penceresi");


    QToolButton *webOpenButton=new QToolButton();
    webOpenButton->setFixedSize(e*12,yukseklik*2);
    webOpenButton->setAutoRaise(true);
    // webOpenButton->setAutoFillBackground(true);
    webOpenButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    webOpenButton->setIcon(QIcon(":/icons/openweb.svg"));
    webOpenButton->setIconSize(QSize(b*10,yukseklik*1.2));
    webOpenButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    webOpenButton->setText(tr("Sayfa Aç"));
    connect(webOpenButton, &QToolButton::clicked, [=]() {

        if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}

        CustomInputDialog  cid(tr("Adres Girişi"),tr(" İstemcilerde Açılacak Web Adresini Giriniz."),"google.com",300,100);
        QString urlString = cid.getText().trimmed();
          if(urlString!="")
        {
            // Eğer http:// veya https:// ile başlamıyorsa başına https:// ekle
            if (!urlString.startsWith("http://") && !urlString.startsWith("https://")) {
                urlString.prepend("https://");
            }

            QUrl url(urlString, QUrl::TolerantMode);

            QString kmt="xdg-open "+url.toString();
            qDebug()<<kmt;
            udpSendData("x11command","x11command",kmt,"",false);
            for(int i=0;i<onlinePcList.count();i++)
            {
                if((onlinePcList[i]->select||onlinePcList[i]->multiSelect))
                {
                    onlinePcList[i]->setCommandButonState(false);
                }
            }
        }


    });

    QToolButton *blockYoutubeButton=new QToolButton();
    blockYoutubeButton->setFixedSize(e*12,yukseklik*2);
    blockYoutubeButton->setAutoRaise(true);
    //blockYoutubeButton->setAutoFillBackground(true);
    blockYoutubeButton->setText(tr("Engelle"));
    blockYoutubeButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    blockYoutubeButton->setIcon(QIcon(":/icons/blockyoutube.svg"));
    blockYoutubeButton->setIconSize(QSize(b*10,yukseklik*1.2));
    blockYoutubeButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(blockYoutubeButton, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}
        //udpSendData("x11command","x11command",webEdit->text());
        udpSendData("consolecommand","consolecommand","/usr/share/webblock/script/domainblock add youtube.com","youtube-off",true);
    });

    QToolButton *unblockYoutubeButton=new QToolButton();
    unblockYoutubeButton->setFixedSize(e*12,yukseklik*2);
    unblockYoutubeButton->setAutoRaise(true);
    //unblockYoutubeButton->setAutoFillBackground(true);
    unblockYoutubeButton->setText(tr("Engel Kaldır"));
    unblockYoutubeButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    unblockYoutubeButton->setIcon(QIcon(":/icons/unblockyoutube.svg"));
    unblockYoutubeButton->setIconSize(QSize(b*10,yukseklik*1.2));
    unblockYoutubeButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(unblockYoutubeButton, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}
        //udpSendData("x11command","x11command",webEdit->text());
        udpSendData("consolecommand","consolecommand","/usr/share/webblock/script/domainblock remove youtube.com","youtube-on",true);
    });

    QToolButton *blockDomainButton=new QToolButton();
    blockDomainButton->setFixedSize(e*12,yukseklik*2);
    blockDomainButton->setAutoRaise(true);
    //blockDomainButton->setAutoFillBackground(true);
    blockDomainButton->setText(tr("Site Engelle"));
    blockDomainButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    blockDomainButton->setIcon(QIcon(":/icons/domainblock.svg"));
    blockDomainButton->setIconSize(QSize(b*10,yukseklik*1.2));
    blockDomainButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(blockDomainButton, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}
        //udpSendData("x11command","x11command",webEdit->text());
        CustomInputDialog  cid(tr("Adres Girişi"),tr(" Engellenecek Web Adresini Giriniz.\n"
                                                     "Bu web sitesine girilemez. "),"",300,150);
        QString raw = cid.getText().trimmed();

        if (!raw.startsWith("http://") && !raw.startsWith("https://"))
            raw.prepend("http://");  // QUrl doğru parse etsin

        QUrl url(raw);
        QString hostname = url.host();  // sadece domain gelir

        qDebug() << hostname;
        udpSendData("consolecommand","consolecommand","/usr/share/webblock/script/domainblock add "+hostname,"",true);

});

    QToolButton *unblockDomainButton=new QToolButton();
    unblockDomainButton->setFixedSize(e*12,yukseklik*2);
    unblockDomainButton->setAutoRaise(true);
    //unblockDomainButton->setAutoFillBackground(true);
    unblockDomainButton->setText(tr("Site Engel\nKaldır"));
    unblockDomainButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    unblockDomainButton->setIcon(QIcon(":/icons/domainunblock.svg"));
    unblockDomainButton->setIconSize(QSize(b*10,yukseklik*1.2));
    unblockDomainButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(unblockDomainButton, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}
        CustomInputDialog  cid(tr("Adres Girişi"),tr(" Engel Kaldırılacak Web Adresini Giriniz.\n"
                                                     "Bu adrese engelsiz girebilirsiniz. "),"",300,150);
        QString raw = cid.getText().trimmed();

        if (!raw.startsWith("http://") && !raw.startsWith("https://"))
            raw.prepend("http://");  // QUrl doğru parse etsin
        QUrl url(raw);
        QString hostname = url.host();  // sadece domain gelir
        udpSendData("consolecommand","consolecommand","/usr/share/webblock/script/domainblock remove "+hostname,"",true);
    });

    QToolButton *onlyAllowStopWebButton=new QToolButton();
    onlyAllowStopWebButton->setFixedSize(e*12,yukseklik*2);
    onlyAllowStopWebButton->setAutoRaise(true);
    //onlyAllowStopWebButton->setAutoFillBackground(true);
    onlyAllowStopWebButton->setText(tr("Tek Adresi\n İptal Et"));
    onlyAllowStopWebButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    onlyAllowStopWebButton->setIcon(QIcon(":/icons/denyweb.svg"));
    onlyAllowStopWebButton->setIconSize(QSize(b*10,yukseklik*1.2));
    onlyAllowStopWebButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(onlyAllowStopWebButton, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}
        udpSendData("consolecommand","consolecommand","/usr/share/webblock/script/only-webblock stop","only-web-allow-stop",true);

     });

    QToolButton *onlyAllowStartWebButton=new QToolButton();
    onlyAllowStartWebButton->setFixedSize(e*12,yukseklik*2);
    onlyAllowStartWebButton->setAutoRaise(true);
    //onlyAllowStartWebButton->setAutoFillBackground(true);
    onlyAllowStartWebButton->setText(tr("Tek Adrese\nİzin Ver"));
    onlyAllowStartWebButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    onlyAllowStartWebButton->setIcon(QIcon(":/icons/allowweb.svg"));
    onlyAllowStartWebButton->setIconSize(QSize(b*10,yukseklik*1.2));
    onlyAllowStartWebButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(onlyAllowStartWebButton, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}

        CustomInputDialog  cid(tr("Adres Girişi"),tr(" Sadece İzin Verilecek Web Adresini Giriniz.\n"
                                                     "Bu adres dışında başka web sitesine girilemez. "),"",300,150);
        QString urlString = cid.getText().trimmed();

            udpSendData("consolecommand","consolecommand","/usr/share/webblock/script/only-webblock start "+urlString,"only-web-allow-on",true);


        });

    QToolButton *stopInternetButton=new QToolButton();
    stopInternetButton->setFixedSize(e*12,yukseklik*2);
    stopInternetButton->setAutoRaise(true);
    //stopInternetButton->setAutoFillBackground(true);
    stopInternetButton->setText(tr("İnterneti\nDurdur"));
    stopInternetButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    stopInternetButton->setIcon(QIcon(":/icons/stopinternet.svg"));
    stopInternetButton->setIconSize(QSize(b*10,yukseklik*1.2));
    stopInternetButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(stopInternetButton, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}
           udpSendData("consolecommand","consolecommand","/usr/share/webblock/script/internet-off","internet-off",true);
                      });

    QToolButton *openInternetButton=new QToolButton();
    openInternetButton->setFixedSize(e*12,yukseklik*2);
    openInternetButton->setAutoRaise(true);
    //openInternetButton->setAutoFillBackground(true);
    openInternetButton->setText(tr("İnterneti Aç"));
    openInternetButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    openInternetButton->setIcon(QIcon(":/icons/openinternet.svg"));
    openInternetButton->setIconSize(QSize(b*10,yukseklik*1.2));
    openInternetButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(openInternetButton, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}
        //udpSendData("x11command","x11command",webEdit->text());
        udpSendData("consolecommand","consolecommand","/usr/share/webblock/script/internet-on","internet-on",true);
    });
    QToolButton *webblockButton= new QToolButton;
    webblockButton->setFixedSize(e*12,yukseklik*2);
    webblockButton->setAutoRaise(true);
    // webblockButton->setAutoFillBackground(true);
    webblockButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    webblockButton->setText(tr("Web Filtresi"));
    webblockButton->setIcon(QIcon(":/icons/webblock.svg"));
    webblockButton->setIconSize(QSize(b*10,yukseklik*1.2));
    webblockButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    connect(webblockButton, &QToolButton::clicked, [=]() {
        webBlockWidget();

    });

    QToolButton *helpButton= new QToolButton;
    helpButton->setFixedSize(e*12,yukseklik*2);
    helpButton->setAutoRaise(true);
    // bilgiButton->setAutoFillBackground(true);
    helpButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    helpButton->setText(tr("Yardım"));
    helpButton->setIcon(QIcon(":/icons/help.svg"));
    helpButton->setIconSize(QSize(b*10,yukseklik*1.3));
    helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(helpButton, &QToolButton::clicked, [=]() {
        QTextDocument *doc=new QTextDocument();

        doc->setHtml(tr("<center><h2>Web/Internet İşlemleri</h2></center>"
                     "<center><img src=\":/icons/web-internet.png\" /></center> "
                     "<center><img src=\":/icons/istemci.png\" /></center>"
                     "<br/>1-Açmak instenilen Web sayfasının adresini yazıp client de açabilirsiniz."
                     "<br/>2-Youtube girişini aktif-pasif yapabilirsiniz."
                        "<br/>3-İstenilen bir adresi İstemcide engelleyebilir veya engel kaldırabiliriz."
                        "<br/>4-Tüm interneti client de aktif-pasif yapabilirsiniz."
                                           ));
        QPrinter pdf;
        pdf.setOutputFileName("/tmp/web-internet.pdf");
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
        d1->setWindowTitle(tr("Web/İnternet Yardım Penceresi"));
        d1->setFixedSize(QSize(boy*215,boy*90));
        auto appIcon = QIcon(":/icons/e-ag.svg");
        d1->setWindowIcon(appIcon);

        d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

        d1->setLayout(vbox);
        d1->exec();
    });


    QGridLayout * vbox = new QGridLayout();
    vbox->setContentsMargins(0, 0, 0,0);
    vbox->setVerticalSpacing(0);

    vbox->addWidget(webOpenButton,1,4,2,1);
    vbox->addWidget(blockYoutubeButton,1,5,2,1);
    vbox->addWidget(unblockYoutubeButton,1,6,2,1);
    vbox->addWidget(blockDomainButton,1,7,2,1);
    vbox->addWidget(unblockDomainButton,1,8,2,1);

    //vbox->addWidget(onlyAllowStartWebButton,1,10,2,1);
    //vbox->addWidget(onlyAllowStopWebButton,1,11,2,1);

    vbox->addWidget(stopInternetButton,1,12,2,1);
    vbox->addWidget(openInternetButton,1,13,2,1);

    ///vbox->addWidget(webblockButton,1,14,2,1);

    vbox->addWidget(helpButton,1,15,2,1);


    d->setLayout(vbox);

    return d;

}


void MainWindow::webBlockWidget()
{
    // qDebug()<<"ayar click";
    QDialog * d = new QDialog();
    d->setWindowTitle(tr("Web Filtresi"));
    d->setFixedSize(QSize(boy*95,boy*50));
    d->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    auto appIcon = QIcon(":/icons/e-ag.svg");
    d->setWindowIcon(appIcon);
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - d->width())/2;
    int y = (screenGeometry.height() - d->height()) / 2;
    d->move(x, y);
    /***********************************************************************/
    QTableWidget *twlh=new QTableWidget;

    twlh->setFixedSize(QSize(boy*90,boy*35));
    twlh->setColumnCount(5);
    //twlh->setRowCount(0);
    twlh->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Seç")));
    twlh->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Index")));
    twlh->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Engelenen Kelime")));
    twlh->setHorizontalHeaderItem(3, new QTableWidgetItem(""));
    twlh->setHorizontalHeaderItem(4, new QTableWidgetItem(""));

    twlh->setSelectionBehavior(QAbstractItemView::SelectRows);
    twlh->setSelectionMode(QAbstractItemView::SingleSelection);
    //connect(tw, &QTableWidget::cellClicked, this, cellClicked());
    twlh->setRowCount(0);
    twlh->setColumnWidth(0, boy*10);
    twlh->setColumnWidth(1, boy*7);
    twlh->setColumnWidth(2,boy*35);
    twlh->setColumnWidth(3,boy*17);
    twlh->setColumnWidth(4,boy*12);

    DatabaseHelper *db=new DatabaseHelper(localDir+"webblockserver.json");
    QJsonArray dizi=db->Oku();
    int sr=0;

    for (const QJsonValue &item : dizi) {
        QJsonObject veri=item.toObject();

        twlh->setRowCount(twlh->rowCount()+1);
        QCheckBox *mCheck = new QCheckBox();
        mCheck->setFixedWidth(boy*15);
        mCheck->setChecked(false);
        QLineEdit * index = new QLineEdit();
        QLineEdit * word = new QLineEdit();
        QToolButton *saveButton= new QToolButton;
        saveButton->setText(tr("Kelimeyi Kaydet"));
        saveButton->setFixedWidth(boy*17);
        connect(saveButton, &QPushButton::clicked, [=]() {
            //qDebug()<<"Değişiklikler Kaydedildi.."<<insertButton->toolTip();
            int numRows = twlh->rowCount();
            for ( int i = 0 ; i < numRows ; i++)
            {
                QCheckBox* mBox = static_cast<QCheckBox*> (twlh->cellWidget(i,0));
                QLineEdit * index = static_cast<QLineEdit*> (twlh->cellWidget(i,1));
                QLineEdit * word = static_cast<QLineEdit*> (twlh->cellWidget(i,2));
                if (index->text()==saveButton->toolTip())
                {
                    QJsonArray dizi=db->Ara("index",saveButton->toolTip());
                    if(dizi.count()>0)
                    {
                        qDebug()<<"Kelime Değiştirilecek."<<saveButton->toolTip();
                        QJsonObject veri;
                        if (mBox->isChecked()) veri["selectedWord"] =true;
                        else veri["selectedWord"] =false;
                        veri["index"] = index->text();
                        veri["word"] = word->text();
                        //qDebug()<<"kelime kayıt"<<veri;
                        db->Sil("index",index->text());
                        db->Ekle(veri);
                    }
                }
            }
            d->close();
            webBlockWidget();
        });
        QToolButton *removeButton= new QToolButton;
        removeButton->setText(tr("Kelime Sil"));
        removeButton->setFixedWidth(boy*12);
        connect(removeButton, &QPushButton::clicked, [=]() {
            //qDebug()<<"Profil Silindi.."<<networkRemoveButton->toolTip();
            QJsonArray dizi=db->Ara("networkIndex",removeButton->toolTip());
            qDebug()<<"Web Kelime Silinecek."<<removeButton->toolTip();
            db->Sil("index",index->text());
            d->close();
            webBlockWidget();
        });



        index->setText(veri.value("index").toString());
        index->setReadOnly(true);
        word->setText(veri.value("word").toString());
        saveButton->setToolTip(index->text());
        twlh->setCellWidget(sr,0,mCheck);
        twlh->setCellWidget(sr,1,index);
        twlh->setCellWidget(sr,2,word);
        twlh->setCellWidget(sr,3,saveButton);
        twlh->setCellWidget(sr,4,removeButton);

        //qDebug()<<"Kayıtlı Host.";
        if(veri.value("selectedWord").toBool())
            mCheck->setChecked(true);
        else
            mCheck->setChecked(false);
        sr++;
    }

    /********************************************************************/
    QToolButton *insertWordButton= new QToolButton;
    insertWordButton->setFixedSize(QSize(boy*40,boy*10));
    insertWordButton->setIconSize(QSize(boy*40,boy*5));
    insertWordButton->setStyleSheet("Text-align:center");
    insertWordButton->setIcon(QIcon(":/icons/boot.svg"));
    insertWordButton->setAutoRaise(true);
    insertWordButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    // newNetworkButton->setFont(f2);
    insertWordButton->setText(tr("Yeni Profil Ekle"));

    connect(insertWordButton, &QPushButton::clicked, [=]() {
        DatabaseHelper *db=new DatabaseHelper(localDir+"webblockserver.json");
        QJsonObject veri;
        veri["index"] =QString::number(db->getIndex("index"));
        if(db->Oku().size()==0) veri["selectedWord"] =true;
        else veri["selectedWord"] =false;
        veri["word"] = "sample";
        db->Ekle(veri);
        d->close();
        webBlockWidget();
    });

    QToolButton *webAyarGuncelleButton= new QToolButton;
    webAyarGuncelleButton->setFixedSize(QSize(en*40,en*10));
    webAyarGuncelleButton->setIconSize(QSize(en*40,en*5));
    webAyarGuncelleButton->setStyleSheet("Text-align:center");
    webAyarGuncelleButton->setIcon(QIcon(":/icons/clientrefresh.svg"));
    webAyarGuncelleButton->setAutoRaise(true);
    webAyarGuncelleButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    // webAyarGuncelleButton->setFont(f2);
    webAyarGuncelleButton->setText(tr("Açık Pc'lerin Web Filtre Listesini Güncelle"));

    connect(webAyarGuncelleButton, &QPushButton::clicked, [=]() {

        /*for(int i=0;i<onlinePcList.count();i++)
        {
            if((onlinePcList[i]->select||onlinePcList[i]->multiSelect)&&
                onlinePcList[i]->user!="noLogin")
            {
                //qDebug()<<"giden pc"<<onlinePcList[i]->ip;
                selectFileCopySlot("webblockserversendfile",onlinePcList[i]->ip,onlinePcList[i]->netProfil.ftpPort, "/usr/share/e-ag/webblockserver.json","webblockserver.json");
                system("sleep 0.1");
             }
        }*/
        ///selectFileCopySlot("webblockserversendfile", "/usr/share/e-ag/webblockserver.json","webblockserver.json");

        ////return;
        ///
        ///if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}
        ///udpSendData("consolecommand","consolecommand","/usr/share/webblock/script/internet-off","internet-off",true);

       /* hostAddressMacButtonSlot();
        for(int k=0;k<interfaceList.count();k++)
        {
            for(int i=0;i<onlinePcList.count();i++)
            {
                if(onlinePcList[i]->connectState&&
                    (onlinePcList[i]->select||onlinePcList[i]->multiSelect)&&
                    interfaceList[k].ip.section(".",0,1)==onlinePcList[i]->ip.section(".",0,1))
                {
                    udpSendData("webblock",QString::number(webblockstate),onlinePcList[i]->ip,"Web Filtresi Güncellendi",true);

                }
            }
            system("sleep 0.1");
        }
*/
    });
    /*********************************************************************/

    QVBoxLayout * vbox = new QVBoxLayout();
    vbox->addWidget(twlh);
    QHBoxLayout * hbox = new QHBoxLayout();
    hbox->addWidget(insertWordButton);
    hbox->addWidget(webAyarGuncelleButton);

    vbox->addLayout(hbox);

    d->setLayout(vbox);
    d->exec();


}



#endif // WEBINTERNETWIDGET_H
