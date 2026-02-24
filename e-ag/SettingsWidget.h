#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H
QWidget* MainWindow::settingsWidget()
{
    int e=en;
    int b=boy;
    // qDebug()<<"ayar click";
    QFont ff( "Arial", 20, 0);
    int yukseklik=b*14;
    QWidget * d = new QWidget();
    //d->setFixedSize(this->width(),boy*16);

    d->setWindowTitle(tr("Ayarlar Penceresi"));

    QToolButton *acountButton=new QToolButton();
    acountButton->setFixedSize(e*27,yukseklik);
    acountButton->setAutoRaise(true);
    // duyuruButton->setAutoFillBackground(true);
    acountButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    acountButton->setText(tr("Ağ Profilleri"));
    acountButton->setIcon(QIcon(":/icons/session.svg"));
    acountButton->setIconSize(QSize(b*8,b*8));
    acountButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(acountButton, &QToolButton::clicked, [=]() {
        networkProfil();
    });



    QToolButton *macListe1Button=new QToolButton();
    macListe1Button->setFixedSize(e*27,yukseklik);
    macListe1Button->setAutoRaise(true);
    // macListe1Button->setAutoFillBackground(true);
    macListe1Button->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    macListe1Button->setText(tr("İstemci Liste"));
    macListe1Button->setIcon(QIcon(":/icons/maclist.svg"));
    macListe1Button->setIconSize(QSize(b*8,yukseklik/2));
    macListe1Button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(macListe1Button, &QToolButton::clicked, [=]() {

        HostListWidget()->show();
    });



   QToolButton *clientShowButton= new QToolButton;
    clientShowButton->setFixedSize(e*27,yukseklik);
    clientShowButton->setAutoRaise(true);
    // clientShowButton->setAutoFillBackground(true);
    clientShowButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    clientShowButton->setText(tr("Gizli Bilgisayarlar"));
    clientShowButton->setIcon(QIcon(":/icons/showhost.svg"));
    clientShowButton->setIconSize(QSize(b*8,yukseklik/2));
    clientShowButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(clientShowButton, &QToolButton::clicked, [=]() {
        hideShowPcSlot();
    });

    QToolButton *bilgiButton= new QToolButton;
    bilgiButton->setFixedSize(e*20,yukseklik);
    bilgiButton->setAutoRaise(true);
    // bilgiButton->setAutoFillBackground(true);
    bilgiButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    bilgiButton->setText(tr("Hakkında"));
    bilgiButton->setIcon(QIcon(":/icons/about.svg"));
    bilgiButton->setIconSize(QSize(b*8,yukseklik/2));
    bilgiButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(bilgiButton, &QToolButton::clicked, [=]() {
        bilgiAlButtonSlot();

    });

    QToolButton *helpButton= new QToolButton;
    helpButton->setFixedSize(e*20,yukseklik);
    helpButton->setAutoRaise(true);
    // bilgiButton->setAutoFillBackground(true);
    helpButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    helpButton->setText(tr("Yardım"));
    helpButton->setIcon(QIcon(":/icons/help.svg"));
    helpButton->setIconSize(QSize(b*8,yukseklik/2));
    helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(helpButton, &QToolButton::clicked, [=]() {
        QTextDocument *doc=new QTextDocument();

        doc->setHtml(tr("<center><h2>Ayarlar</h2></center>"
                     "<center><img src=\":/icons/ayar.png\"></center> "
                     "<br/><center><img src=\":/icons/userayar.png\"/></center>"
                     "<br/>1-Uygulamadaki Yerel Ağ: bulunduğumuz ağ örn:192.168.1.255 şeklinde girilmeli."
                     "<br/><br/>2-Uygulamadaki Tcp Port: yazılımın kullandığı port boş bırakılırsa 7879 olarak ayarlar."
                     "<br/><br/>3-İstemcilerin listesini İstemci Listele seçeneği ile yapabilir ve listeyi yazdırabiliriz."
                     "<br/><br/>4-Gizlenmiş istemcileri tekrar listede görünmesi için Gizli Bilgisayarlar Göster seçeneğini kullanabilirsiniz."
                          ));
        QPrinter pdf;
        pdf.setOutputFileName("/tmp/ayar.pdf");
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
        d1->setWindowTitle(tr("Ayarlar Yardım Penceresi"));
        d1->setFixedSize(QSize(boy*215,boy*127));
        auto appIcon = QIcon(":/icons/e-ag.svg");
        d1->setWindowIcon(appIcon);

        d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

        d1->setLayout(vbox);
        d1->exec();


    });

    auto layout = new QGridLayout(d);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    layout->addWidget(acountButton, 0,0,1,1,Qt::AlignCenter);
    //layout->addWidget(clientUpdateButton, 0,1,1,1,Qt::AlignCenter);
    layout->addWidget(macListe1Button, 0,2,1,1,Qt::AlignCenter);
  //  layout->addWidget(webblockButton, 0,3,1,1,Qt::AlignCenter);
    layout->addWidget(clientShowButton, 0,4,1,1,Qt::AlignCenter);
    layout->addWidget(helpButton, 0,5,1,1,Qt::AlignCenter);
    layout->addWidget(bilgiButton, 0,6,1,1,Qt::AlignCenter);

    d->setLayout(layout);

    return d;

}

void MainWindow::hideShowPcSlot()
{
    // qDebug()<<"ayar click";
    QDialog * d = new QDialog();
    d->setWindowTitle("Gizli Bilgisayar Listesi");
    d->setFixedSize(QSize(boy*100,boy*65));
    d->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    auto appIcon = QIcon(":/icons/e-ag.svg");
    d->setWindowIcon(appIcon);
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - d->width())/2;
    int y = (screenGeometry.height() - d->height()) / 2;
    d->move(x, y);
    /***********************************************************************/
    QTableWidget *twlh=new QTableWidget;

    twlh->setFixedSize(QSize(boy*95,boy*50));
    twlh->setColumnCount(5);
    //twlh->setRowCount(0);

    twlh->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Seç")));
    twlh->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Ip")));
    twlh->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Mac")));
    twlh->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Adı")));
    twlh->setHorizontalHeaderItem(4, new QTableWidgetItem(tr("Host")));

    twlh->setSelectionBehavior(QAbstractItemView::SelectRows);
    twlh->setSelectionMode(QAbstractItemView::SingleSelection);
    //connect(tw, &QTableWidget::cellClicked, this, cellClicked());
    twlh->setRowCount(0);
    twlh->setColumnWidth(0, boy*5);
    twlh->setColumnWidth(1, boy*20);
    twlh->setColumnWidth(2,boy*15);
    twlh->setColumnWidth(3,boy*24);
    twlh->setColumnWidth(4,boy*24);
    DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
    QJsonArray dizi=db->Oku();
    int sr=0;

    for (const QJsonValue &item : dizi) {
        QJsonObject veri=item.toObject();
        if (!veri.value("visibleState").toBool())
        {
            twlh->setRowCount(twlh->rowCount()+1);
            QCheckBox *mCheck = new QCheckBox();
            mCheck->setChecked(false);
            twlh->setCellWidget(sr,0,mCheck);
            //qDebug()<<"Kayıtlı Host.";
            twlh->setItem(sr, 1, new QTableWidgetItem(veri.value("mac").toString()));//ip
            twlh->setItem(sr, 2, new QTableWidgetItem(veri.value("ip").toString()));//mac
            twlh->setItem(sr, 3, new QTableWidgetItem(veri.value("caption").toString()));//caption
            twlh->setItem(sr, 4, new QTableWidgetItem(veri.value("hostname").toString()));//name
            sr++;
        }

    }

    /********************************************************************/
    QToolButton *showPcButton= new QToolButton;
    showPcButton->setFixedSize(QSize(boy*40,boy*10));
    showPcButton->setIconSize(QSize(boy*40,boy*5));
    showPcButton->setStyleSheet("Text-align:center");
    showPcButton->setIcon(QIcon(":/icons/boot.svg"));
    showPcButton->setAutoRaise(true);
    showPcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    // showPcButton->setFont(f2);
    showPcButton->setText(tr("Seçili Bilgisayarı Göster"));

    connect(showPcButton, &QPushButton::clicked, [=]() {
        int numRows = twlh->rowCount();
        bool updateState=false;
        DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
        for ( int i = 0 ; i < numRows ; i++)
        {
            QCheckBox* mBox = static_cast<QCheckBox*> (twlh->cellWidget(i,0));
            if (mBox->isChecked())
            {
                QString _mac = twlh->model()->data(twlh->model()->index(i, 1)).toString().simplified();
                QJsonArray dizi=db->Ara("mac",_mac);
                if(dizi.count()>0)
                {
                    qDebug()<<"Host Görünürlüğü Değiştirilecek."<<_mac;
                    QJsonObject veri=dizi.first().toObject();
                    veri["visibleState"] =true;
                    db->Sil("mac",_mac);
                    db->Ekle(veri);
                    for(int i=0;i<onlinePcList.count();i++)
                    {
                        if(onlinePcList[i]->mac==_mac)
                            onlinePcList[i]->visibleState=true;

                    }
                    updateState=true;
                }
            }
        }
        if(updateState)
        {
            pcListeGuncelleSlot("visibleStateUpdate");
            d->close();
        }
    });
    /*********************************************************************/
    /*********************************************************************/

    QVBoxLayout * vbox = new QVBoxLayout();
    vbox->addWidget(twlh);
    QHBoxLayout * hbox = new QHBoxLayout();
    hbox->addWidget(showPcButton);
    vbox->addLayout(hbox);

    d->setLayout(vbox);
    d->exec();


}

QWidget* MainWindow::HostListWidget()
{
    int bw,bh;
    bw=en*10;
    bh=boy*10;
    QDialog *wd=new QDialog();
    wd->setWindowTitle(tr("İstemci Listesi"));
    auto appIcon = QIcon(":/icons/e-ag.svg");
    wd->setWindowIcon(appIcon);
    wd->setFixedSize(en*100,boy*65);
    wd->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - wd->width())/2;
    int y = (screenGeometry.height() - wd->height()) / 2;
    wd->move(x, y);
    /***************************************************************/
    QTableWidget *twlh=new QTableWidget(wd);

    twlh->setFixedSize(QSize(boy*95,boy*50));
    twlh->setColumnCount(6);
    //twlh->setRowCount(0);
    twlh->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Seç")));
    twlh->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Mac")));
    twlh->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Ip")));
    twlh->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Adı")));
    twlh->setHorizontalHeaderItem(4, new QTableWidgetItem(tr("Host")));
    twlh->setHorizontalHeaderItem(5, new QTableWidgetItem(tr("Listele")));

    twlh->setSelectionBehavior(QAbstractItemView::SelectRows);
    twlh->setSelectionMode(QAbstractItemView::SingleSelection);
    //connect(tw, &QTableWidget::cellClicked, this, cellClicked());
    twlh->setRowCount(0);
    twlh->setColumnWidth(0, boy*5);
    twlh->setColumnWidth(1, boy*20);
    twlh->setColumnWidth(2,boy*15);
    twlh->setColumnWidth(3,boy*20);
    twlh->setColumnWidth(4,boy*20);
    twlh->setColumnWidth(5,boy*10);
    DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
    QJsonArray dizi=db->Oku();
    int sr=0;

    for (const QJsonValue &item : dizi) {
        QJsonObject veri=item.toObject();
        //if (!veri.value("visibleState").toBool())
        //{
        twlh->setRowCount(twlh->rowCount()+1);
        QCheckBox *mCheck = new QCheckBox();
        mCheck->setChecked(false);
        twlh->setCellWidget(sr,0,mCheck);
        //qDebug()<<"Kayıtlı Host.";
        twlh->setItem(sr, 1, new QTableWidgetItem(veri.value("mac").toString()));//ip
        twlh->setItem(sr, 2, new QTableWidgetItem(veri.value("ip").toString()));//mac
        twlh->setItem(sr, 3, new QTableWidgetItem(veri.value("caption").toString()));//caption
        twlh->setItem(sr, 4, new QTableWidgetItem(veri.value("hostname").toString()));//name
        twlh->setItem(sr, 5, new QTableWidgetItem(veri.value("visibleState").toString()));//name
        sr++;
        //}
    }
    /***************************************************************/
    QToolButton *printButton = new QToolButton(wd);
    printButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    printButton->setIcon(QIcon(":icons/print.svg"));
    printButton->setIconSize(QSize(bw,bh/2));
    printButton->setAutoRaise(true);
    printButton->setAutoFillBackground(true);
    printButton->setStyleSheet(" font-size:"+QString::number(font.toInt()-2)+"px;");
    printButton->resize(bw,bh);
   // printButton->move(wd->width()/2-bw/2,wd->height()-bh);
    printButton->setText(tr("Yazdır"));
    //connect(printButton, SIGNAL(clicked()),this, SLOT(printButtonSlot()));
    connect(printButton, &QPushButton::clicked, [=]() {
        QString strStream;
        QTextStream out(&strStream);

        const int rowCount =twlh->model()->rowCount();
        const int columnCount = twlh->model()->columnCount();
        out <<  "<html>\n"
               "<head>\n"
               "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg(QString(tr("Ağ IP ve Mac Adres Listesi")))
            <<  "</head>\n"
               "<body bgcolor=#ffffff link=#5000A0>\n"
               "<table border=1 width=600 cellspacing=0 cellpadding=2>\n";

        // headers
        out << "<thead>";
        out << QString("<tr><th colspan=5>%1</th></tr>").arg(QString(tr("Ağ IP ve Mac Adres Listesi")));

        out<<"<tr bgcolor=#f0f0f0>";

        for (int column = 0; column < columnCount; column++)
            if (!twlh->isColumnHidden(column))
                out << QString("<th>%1</th>").arg(twlh->model()->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++) {
            out << "<tr>";
            for (int column =0; column < columnCount; column++) {

                if (!twlh->isColumnHidden(column)) {
                    QString data = twlh->model()->data(twlh->model()->index(row, column)).toString().simplified();
                    QString bilgi=(!data.isEmpty()) ? data : QString("&nbsp;");
                    if(column==0)
                        out << QString("<td bkcolor=0 style='font-size:12px;'>%1-%2</td>").arg(QString::number(row+1),bilgi);
                    else
                        out << QString("<td bkcolor=0 style='font-size:12px;'>%1</td>").arg(bilgi);
                }
            }
            out << "</tr>\n";
        }
        out <<  "</table>\n"
               "</body>\n"
               "</html>\n";

        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);

        QPrinter printer;
        QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
        printer.setOutputFileName(QDir::homePath()+"macliste.pdf");
        if (dialog->exec() == QDialog::Accepted) {
            document->print(&printer);
        }

        delete document;


    });

    QToolButton *deletePcButton= new QToolButton;
    deletePcButton->setFixedSize(QSize(boy*25,boy*10));
    deletePcButton->setIconSize(QSize(boy*40,boy*5));
    deletePcButton->setStyleSheet("Text-align:center");
    deletePcButton->setIcon(QIcon(":/icons/boot.svg"));
    deletePcButton->setAutoRaise(true);
    deletePcButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    // showPcButton->setFont(f2);
    deletePcButton->setText(tr("Seçili Bilgisayarı Sil"));

    connect(deletePcButton, &QPushButton::clicked, [=]() {
        int numRows = twlh->rowCount();
        bool updateState=false;
        QList<int> toDelete;
        DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
        for ( int i = 0 ; i < numRows ; i++)
        {
            QCheckBox* mBox = static_cast<QCheckBox*> (twlh->cellWidget(i,0));
            if (mBox->isChecked())
            {
                QString _mac = twlh->model()->data(twlh->model()->index(i, 1)).toString().simplified();
                QString _ip = twlh->model()->data(twlh->model()->index(i, 2)).toString().simplified();
                db->Sil("mac",_mac);
                pcCloseSignalSlot(_ip,_mac);
                   toDelete << i;
                updateState=true;
            }
        }
        if(updateState)
        {
            // Tersten sil
            for (int i = toDelete.count() - 1; i >= 0; i--) {
                twlh->removeRow(toDelete[i]);
            }
            pcListeGuncelleSlot("delete host");
           // wd->close();
        }
    });
    QVBoxLayout * vbox = new QVBoxLayout();
    vbox->addWidget(twlh);
    QHBoxLayout * hbox = new QHBoxLayout();
    hbox->addWidget(deletePcButton);
    hbox->addWidget(printButton);
    vbox->addLayout(hbox);

    wd->setLayout(vbox);
   // wd->exec();
    return wd;
}


void MainWindow::networkProfil()
{
    // qDebug()<<"ayar click";
    QDialog * d = new QDialog();
    d->setWindowTitle(tr("Ağ Profil Listesi"));
    d->setFixedSize(QSize(boy*200,boy*50));
    d->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    auto appIcon = QIcon(":/icons/e-ag.svg");
    d->setWindowIcon(appIcon);
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - d->width())/2;
    int y = (screenGeometry.height() - d->height()) / 2;
    d->move(x, y);
    /***********************************************************************/
    QTableWidget *twlh=new QTableWidget;

    twlh->setFixedSize(QSize(boy*195,boy*35));
    twlh->setColumnCount(14);
    //twlh->setRowCount(0);
    twlh->setHorizontalHeaderItem(0, new QTableWidgetItem("Seçili Ağ"));
    twlh->setHorizontalHeaderItem(1, new QTableWidgetItem("Ağ No"));
    twlh->setHorizontalHeaderItem(2, new QTableWidgetItem("Ağ Adı"));
    twlh->setHorizontalHeaderItem(3, new QTableWidgetItem("Ip'si"));
    twlh->setHorizontalHeaderItem(4, new QTableWidgetItem("Yayın Adresi"));
    twlh->setHorizontalHeaderItem(5, new QTableWidgetItem("Port"));
    twlh->setHorizontalHeaderItem(6, new QTableWidgetItem("ftpPort"));
    twlh->setHorizontalHeaderItem(7, new QTableWidgetItem("rootpath"));
    twlh->setHorizontalHeaderItem(8, new QTableWidgetItem("language"));
    twlh->setHorizontalHeaderItem(9, new QTableWidgetItem("ClientKilidi"));
    twlh->setHorizontalHeaderItem(10, new QTableWidgetItem("ClientWebFilter"));
    twlh->setHorizontalHeaderItem(11, new QTableWidgetItem("MuticastAdresi"));
    twlh->setHorizontalHeaderItem(12, new QTableWidgetItem(""));
    twlh->setHorizontalHeaderItem(13, new QTableWidgetItem(""));


    twlh->setSelectionBehavior(QAbstractItemView::SelectRows);
    twlh->setSelectionMode(QAbstractItemView::SingleSelection);
    //connect(tw, &QTableWidget::cellClicked, this, cellClicked());
    twlh->setRowCount(0);
    twlh->setColumnWidth(0, boy*10);
    twlh->setColumnWidth(1, boy*10);
    twlh->setColumnWidth(2,boy*20);
    twlh->setColumnWidth(3,boy*15);
    twlh->setColumnWidth(4,boy*15);
    twlh->setColumnWidth(5,boy*10);
    twlh->setColumnWidth(6,boy*10);
    twlh->setColumnWidth(7,boy*10);
    twlh->setColumnWidth(8,boy*10);
    twlh->setColumnWidth(9,boy*20);
    twlh->setColumnWidth(10,boy*20);
    twlh->setColumnWidth(11,boy*20);
    twlh->setColumnWidth(12,boy*10);
    twlh->setColumnWidth(13,boy*10);


    DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag.json");
    QJsonArray dizi=db->Oku();
    int sr=0;

    for (const QJsonValue &item : dizi) {
        QJsonObject veri=item.toObject();

        twlh->setRowCount(twlh->rowCount()+1);
        QCheckBox *mCheck = new QCheckBox();
        mCheck->setFixedWidth(boy*15);
        mCheck->setChecked(false);
        QLineEdit * networkIndex = new QLineEdit();
        QLineEdit * networkName = new QLineEdit();
        QLineEdit * serverAddress = new QLineEdit();
        QLineEdit * networkBroadCastAddress = new QLineEdit();
        QLineEdit * networkTcpPort = new QLineEdit();
        QLineEdit * ftpPort = new QLineEdit();
        QLineEdit * rootPath= new QLineEdit();
        QLineEdit * language = new QLineEdit();
        QLineEdit * multicastAddress = new QLineEdit();
        QCheckBox * lockScreenState = new QCheckBox();
        QCheckBox * webblockState = new QCheckBox();


        QToolButton *savetButton= new QToolButton;
        savetButton->setText(tr("Kaydet"));
        savetButton->setFixedWidth(boy*10);
        connect(savetButton, &QPushButton::clicked, [=]() {
            //qDebug()<<"Değişiklikler Kaydedildi.."<<networkInsertButton->toolTip();
            int numRows = twlh->rowCount();
            for ( int i = 0 ; i < numRows ; i++)
            {

                if (networkIndex->text()==savetButton->toolTip())
                {
                    QJsonArray dizi=db->Ara("networkIndex",savetButton->toolTip());
                    if(dizi.count()>0)
                    {
                        QCheckBox* mBox1 = static_cast<QCheckBox*> (twlh->cellWidget(i,0));
                        QLineEdit * networkIndex1 = static_cast<QLineEdit*> (twlh->cellWidget(i,1));
                        QLineEdit * networkName1 = static_cast<QLineEdit*> (twlh->cellWidget(i,2));
                        QLineEdit * serverAddress1 =static_cast<QLineEdit*> (twlh->cellWidget(i,3));
                        QLineEdit * networkBroadCastAddress1 =static_cast<QLineEdit*> (twlh->cellWidget(i,4));
                        QLineEdit * networkTcpPort1 = static_cast<QLineEdit*> (twlh->cellWidget(i,5));
                        QLineEdit * ftpPort1 = static_cast<QLineEdit*> (twlh->cellWidget(i,6));
                        QLineEdit * rootPath1 = static_cast<QLineEdit*> (twlh->cellWidget(i,7));
                        QLineEdit * language1 = static_cast<QLineEdit*> (twlh->cellWidget(i,8));

                        QCheckBox * lockScreenState1 = static_cast<QCheckBox*> (twlh->cellWidget(i,10));
                        QCheckBox * webblockState1 = static_cast<QCheckBox*> (twlh->cellWidget(i,11));
                        QLineEdit * multicastAddress1 = static_cast<QLineEdit*> (twlh->cellWidget(i,9));

                        qDebug()<<"Ağ Profili Değiştirilecek."<<savetButton->toolTip();
                        QJsonObject veri;
                        if (mBox1->isChecked()) veri["selectedNetworkProfil"] =true;
                        else veri["selectedNetworkProfil"] =false;
                        veri["networkIndex"] = networkIndex1->text();
                        veri["networkName"] = networkName1->text();
                        veri["networkTcpPort"] = networkTcpPort1->text();
                        veri["networkBroadCastAddress"]=networkBroadCastAddress1->text();//dikkat
                        veri["subnet"]=networkBroadCastAddress1->toolTip();//dikkat
                        veri["serverAddress"]=serverAddress1->text();
                        veri["ftpPort"]=ftpPort1->text();
                        veri["rootPath"]=rootPath1->text();
                        veri["language"]=language1->text();
                        veri["multicastAddress"]=multicastAddress->text();
                        //veri["webblockState"]=webblockState->text();
                        if (lockScreenState1->isChecked()) veri["lockScreenState"] =true;
                        else veri["lockScreenState"] =false;
                        if (webblockState1->isChecked()) veri["webblockState"] =true;
                        else veri["webblockState"] =false;
                        //qDebug()<<"network kayıt"<<veri;
                        db->Sil("networkIndex",networkIndex1->text());
                        db->Ekle(veri);
                    }
                }
            }
            d->close();
            networkProfil();
            networkProfilLoad();
        });
        QToolButton *networkRemoveButton= new QToolButton;
        networkRemoveButton->setText("Sil");
        networkRemoveButton->setFixedWidth(boy*10);
        connect(networkRemoveButton, &QPushButton::clicked, [=]() {
            //qDebug()<<"Profil Silindi.."<<networkRemoveButton->toolTip();
            QJsonArray dizi=db->Ara("networkIndex",networkRemoveButton->toolTip());
            qDebug()<<"Ağ Profili Silinecek."<<networkRemoveButton->toolTip();
            db->Sil("networkIndex",networkIndex->text());
            d->close();
            networkProfil();
            //networkProfilLoad();
        });

        networkIndex->setText(veri.value("networkIndex").toString());
        networkIndex->setReadOnly(true);
        networkName->setText(veri.value("networkName").toString());
        networkBroadCastAddress->setText(veri.value("networkBroadCastAddress").toString());
        networkBroadCastAddress->setToolTip(veri.value("subnet").toString());

        serverAddress->setText(veri.value("serverAddress").toString());
        networkTcpPort->setText(veri.value("networkTcpPort").toString());
        ftpPort->setText(veri.value("ftpPort").toString());
        rootPath->setText(veri.value("rootPath").toString());
        language->setText(veri.value("language").toString());
        multicastAddress->setText(veri.value("multicastAddress").toString());

        savetButton->setToolTip(networkIndex->text());
        twlh->setCellWidget(sr,0,mCheck);
        twlh->setCellWidget(sr,1,networkIndex);
        twlh->setCellWidget(sr,2,networkName);
        twlh->setCellWidget(sr,3,serverAddress);
        twlh->setCellWidget(sr,4,networkBroadCastAddress);
        twlh->setCellWidget(sr,5,networkTcpPort);
        twlh->setCellWidget(sr,6,ftpPort);
        twlh->setCellWidget(sr,7,rootPath);
        twlh->setCellWidget(sr,8,language);
        twlh->setCellWidget(sr,9,lockScreenState);
        twlh->setCellWidget(sr,10,webblockState);
        twlh->setCellWidget(sr,11,multicastAddress);

        twlh->setCellWidget(sr,12,savetButton);
        twlh->setCellWidget(sr,13,networkRemoveButton);
        if(veri.value("selectedNetworkProfil").toBool()) mCheck->setChecked(true);
        else mCheck->setChecked(false);
        if(veri.value("lockScreenState").toBool()) lockScreenState->setChecked(true);
        else lockScreenState->setChecked(false);
        if(veri.value("webblockState").toBool()) webblockState->setChecked(true);
        else webblockState->setChecked(false);
        //lockScreenState->setText(veri.value("lockScreenState").toString());
        //webblockState->setText(veri.value("webblockState").toString());

        sr++;
    }

    /********************************************************************/
    QToolButton *newNetworkButton= new QToolButton;
    newNetworkButton->setFixedSize(QSize(boy*40,boy*10));
    newNetworkButton->setIconSize(QSize(boy*40,boy*5));
    newNetworkButton->setStyleSheet("Text-align:center");
    newNetworkButton->setIcon(QIcon(":/icons/boot.svg"));
    newNetworkButton->setAutoRaise(true);
    newNetworkButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    // newNetworkButton->setFont(f2);
    newNetworkButton->setText("Yeni Profiller Ekle");

    connect(newNetworkButton, &QPushButton::clicked, [=]() {
        DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag.json");
        //qDebug()<<"broadcast address:"<<i<<ipmaclist[i].broadcast;
        //QJsonArray dizi=db->Oku();
        //QJsonArray dizi=db->Ara("selectedNetworkProfil",true);

        hostAddressMacButtonSlot();
        for(int k=0;k<interfaceList.count();k++)
        {
            QJsonArray dizi = db->Ara("serverAddress", interfaceList[k].ip);

            if (dizi.isEmpty()) {
                QJsonObject veri;
                veri["networkIndex"] =QString::number(db->getIndex("networkIndex"));
                if(db->Oku().size()==0) veri["selectedNetworkProfil"] =true;
                else veri["selectedNetworkProfil"] =false;
                veri["networkName"] = "network";
                veri["networkTcpPort"] = "7879";
                veri["serverAddress"]=interfaceList[k].ip;
                veri["networkBroadCastAddress"]=interfaceList[k].broadcast;
                veri["subnet"]=interfaceList[k].subnet;
                veri["ftpPort"]="12345";
                veri["rootPath"]="/tmp/";
                veri["language"]="tr_TR";
                veri["multicastAddress"]="239.255.0.11";

                veri["lockScreenState"]=false;
                veri["webblockState"]=false;
                db->Ekle(veri);
            }
        }
        networkProfil();
        networkProfilLoad();
        d->close();
    });

    /*********************************************************************/
    /*********************************************************************/

    QVBoxLayout * vbox = new QVBoxLayout();
    vbox->addWidget(twlh);
    QHBoxLayout * hbox = new QHBoxLayout();
    hbox->addWidget(newNetworkButton);

    vbox->addLayout(hbox);

    d->setLayout(vbox);
    d->exec();


}

void MainWindow::networkProfilLoad()
{
    DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag.json");
    //QJsonArray dizi=db->Oku();
    QJsonArray dizi=db->Ara("selectedNetworkProfil",true);

    if(dizi.count()>0)
    {
        NetProfilList.clear();
        for (const QJsonValue &item : dizi) {
            QJsonObject veri=item.toObject();
            //qDebug()<<"Yüklenen Ağ Profili:" <<veri;
            NetProfil np;
            np.networkIndex=veri["networkIndex"].toString();
            np.selectedNetworkProfil=veri["selectedNetworkProfil"].toBool();
            np.networkName=veri["networkName"].toString();
            np.networkTcpPort=veri["networkTcpPort"].toString();
            np.networkBroadCastAddress=veri["networkBroadCastAddress"].toString();
            np.subnet=veri["subnet"].toString();
            np.serverAddress=veri["serverAddress"].toString();
            np.ftpPort=veri["ftpPort"].toString();
            np.rootPath=veri["rootPath"].toString();
            np.language=veri["language"].toString();
            np.language=veri["multicastAddress"].toString();

            np.lockScreenState=veri["lockScreenState"].toBool();
            np.webblockState=veri["webblockState"].toBool();
            NetProfilList.append(np);
        }
    }else{
        qDebug()<<"Yeni Network Ekleniyor.";

        hostAddressMacButtonSlot();
        for(int i=0;i<interfaceList.count();i++)
        {
            //qDebug()<<"broadcast address:"<<i<<ipmaclist[i].broadcast;
            QJsonObject veri;
            veri["networkIndex"] =QString::number(db->getIndex("networkIndex"));
            veri["selectedNetworkProfil"] =true;
            veri["networkName"] = "network";
            veri["networkTcpPort"] = "7879";
            veri["serverAddress"]=interfaceList[i].ip;
            veri["networkBroadCastAddress"]=interfaceList[i].broadcast;
            veri["subnet"]=interfaceList[i].subnet;
            veri["ftpPort"]="12345";
            veri["rootPath"]="/tmp/";
            veri["language"]="tr_TR";
            veri["multicastAddress"]="239.255.0.11";

            veri["lockScreenState"]=false;
            veri["webblockState"]=false;
            db->Sil("networkBroadCastAddress",interfaceList[i].broadcast);
            db->Ekle(veri);
        }
        networkProfilLoad();
        //qDebug()<<"eagconf bilgileri farklı güncelleniyor.";
       // system("systemctl restart e-ag-networkprofil.service");
    }
}


void MainWindow::bilgiAlButtonSlot()
{

    QTextDocument *doc=new QTextDocument();
    QString yil=QString::number( QDateTime::currentDateTime().date().year());
    doc->setHtml("<center><h2>e-ag Hakkında</h2></center>"
                 "<center><img src=\":/icons/e-ag.svg\" width=75 height=75 /></center> "
                 "Bu uygulama yerel ağda bilgisayarlara erişim ve yönetmek için yazılmıştır."
                 "<br/> <b>Yapılabilecek Eylemler:</b>"
                 "<br/> Açık olan bilgisayarlara linux komutlarını aynı anda çalıştırabilirsiniz."
                 "<br/> Birden fazla bilgisayara aynı anda dosya kopyalayabilirsiniz.  "
                 "<br/> Bütün bilgisayarlara  ya da tek bilgisayarın ekranına mesaj gönderebilirsiniz."
                 "<br/> Bütün bilgisayarları ya da tek bilgisayarın ekranını kilitleyebilirsiniz."
                 "<br/> Bütün bilgisayarları ya da tek bilgisayarı kapatabilirsiniz."
                 "<br/> Bütün bilgisayarları ya da tek bilgisayarı güncellemeler yapabilirsiniz."
                 "<br/> Açık bilgisayarın ekranına erişim ve kullanma. "
                 "<br/> Video yayını yapabilirsiniz."
                 "<br/> Canlı kamera yayını yapabilirsiniz."
                 "<br/> Açık olan kullanıcı masaüstüne dosya kopyalama ve geri toplayabilirsiniz."
                 "<br/> İstediğiniz bilgisayarları seçip sadece seçili olanlara işlem yapabilirsiniz."
                 "<br/> Uzak bilgisayarda script çalıştırabilirsiniz."
                 "<br/> Server bilgisayarın ekranını yansıtma"
                 "<br/><br/>Bu uygulama Açık Kaynak QT ve C++ ile geliştirilmiştir."
                 "<br/>*****************************************************************"
                 "<br/>Built with Qt (LGPLv3) and FFmpeg (LGPLv2.1)"
                 "<br/>© The Qt Company Ltd, © FFmpeg project"
                 "<br/>*****************************************************************"
                 "<br/><br/>e-ag uygulamasını kullanmaktan doğabilecek her türlü hukuki sorumluluğu kullanıcı kabul etmiş sayılır."
                 "<br/><br/> Copyright (C) "+yil+" by Bayram KARAHAN"
                         "<br/>  bayramk@gmail.com"
                         "<br/>  www.bayramkarahan.com.tr"
                         "<br/>  www.bayramkarahan.blogspot.com"

                         "<br/><br/>This program is free software; you can redistribute it and/or modify it under"
                         "the terms of the GNU General Public License as published by the Free Software"
                         "Foundation; either version 3 of the License, or (at your option) any later version."
                         "<br/>"
                         "<br/>This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;"
                         "without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."
                         "See the GNU General Public License for more details."
                         "<br/>"
                         "<br/>You should have received a copy of the GNU General Public License along with"
                         "this program; if not, write to the Free Software Foundation, Inc."
                         ",51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA ."
                 );
    QPrinter pdf;
    pdf.setOutputFileName("/tmp/hakkimda.pdf");
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
    d1->setWindowTitle("Program Hakkında");
    d1->setFixedSize(QSize(boy*200,boy*120));
    auto appIcon = QIcon(":/icons/e-ag.svg");
    d1->setWindowIcon(appIcon);

    d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    d1->setLayout(vbox);
    d1->exec();



}

#endif // SETTINGSWIDGET_H
