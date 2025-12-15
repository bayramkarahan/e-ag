#ifndef WOLWIDGET_H
#define WOLWIDGET_H

QWidget *MainWindow::wolWidget()
{
    QWidget *d = new QWidget(nullptr, Qt::Popup);
    d->setAttribute(Qt::WA_DeleteOnClose);
    d->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);

    // qDebug()<<"ayar click";
    //QDialog * d = new QDialog();
    d->setWindowTitle(tr("Kapalı Host Listesi"));
    d->setFixedSize(QSize(boy*100,boy*100));
    d->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    auto appIcon = QIcon(":/icons/e-ag.svg");
    d->setWindowIcon(appIcon);

    /***********************************************************************/
    QTableWidget *twl=new QTableWidget;

    twl->setFixedSize(QSize(boy*95,boy*75));
    twl->setColumnCount(5);
    //twl->setRowCount(0);

    twl->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Seç")));
    twl->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Ip")));
    twl->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Mac")));
    twl->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Adı")));
    twl->setHorizontalHeaderItem(4, new QTableWidgetItem(tr("Host")));

    twl->setSelectionBehavior(QAbstractItemView::SelectRows);
    twl->setSelectionMode(QAbstractItemView::SingleSelection);
    //connect(tw, &QTableWidget::cellClicked, this, cellClicked());
    twl->setRowCount(0);
    twl->setColumnWidth(0, boy*5);
    twl->setColumnWidth(1, boy*20);
    twl->setColumnWidth(2,boy*20);
    twl->setColumnWidth(3,boy*20);
    twl->setColumnWidth(4,boy*20);
    DatabaseHelper *db=new DatabaseHelper(localDir+"persist.json");
    QJsonArray dizi=db->Oku();
    int sr=0;

    for (const QJsonValue &item : dizi) {
        QJsonObject veri=item.toObject();
        twl->setRowCount(twl->rowCount()+1);
        QCheckBox *mCheck = new QCheckBox();
        mCheck->setChecked(false);
        twl->setCellWidget(sr,0,mCheck);
        //qDebug()<<"Kayıtlı Host.";
        twl->setItem(sr, 1, new QTableWidgetItem(veri.value("mac").toString()));//ip
        twl->setItem(sr, 2, new QTableWidgetItem(veri.value("ip").toString()));//mac
        twl->setItem(sr, 3, new QTableWidgetItem(veri.value("caption").toString()));//caption
        twl->setItem(sr, 4, new QTableWidgetItem(veri.value("hostname").toString()));//name
        sr++;
    }

    /********************************************************************/
    QToolButton *powerOnButton= new QToolButton;
    powerOnButton->setFixedSize(QSize(boy*40,boy*10));
    powerOnButton->setIconSize(QSize(boy*40,boy*5));
    powerOnButton->setStyleSheet("Text-align:center");
    powerOnButton->setIcon(QIcon(":/icons/boot.svg"));
    powerOnButton->setAutoRaise(true);
    powerOnButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    // powerOnButton->setFont(f2);
    powerOnButton->setText(tr("Seçili Pc'leri Aç"));

    connect(powerOnButton, &QPushButton::clicked, [=]() {
        int numRows = twl->rowCount();
        for ( int i = 0 ; i < numRows ; i++)
        {
            QCheckBox* mBox = static_cast<QCheckBox*> (twl->cellWidget(i,0));
            if (mBox->isChecked())
            {
                QString  _mac= twl->model()->data(twl->model()->index(i, 1)).toString().simplified();
                QString  _ip= twl->model()->data(twl->model()->index(i, 2)).toString().simplified();
                QString ad = twl->model()->data(twl->model()->index(i, 3)).toString().simplified();
                // qDebug()<<i<<mBox->isChecked()<<_ip<<_mac<<ad;
                slotWakeOnLan(_ip,_mac);
            }
        }
    });
    /*********************************************************************/
    /********************************************************************/
    QToolButton *powerOnButtonAll= new QToolButton;
    powerOnButtonAll->setFixedSize(QSize(boy*40,boy*10));
    powerOnButtonAll->setIconSize(QSize(boy*40,boy*5));
    powerOnButtonAll->setStyleSheet("Text-align:center");
    powerOnButtonAll->setIcon(QIcon(":/icons/boot.svg"));
    powerOnButtonAll->setAutoRaise(true);
    powerOnButtonAll->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //powerOnButtonAll->setFont(f2);
    powerOnButtonAll->setText(tr("Tüm Pc'leri Aç"));

    connect(powerOnButtonAll, &QPushButton::clicked, [=]() {
        int numRows = twl->rowCount();
        for ( int i = 0 ; i < numRows ; i++)
        {
            QString  _mac= twl->model()->data(twl->model()->index(i, 1)).toString().simplified();
            QString  _ip= twl->model()->data(twl->model()->index(i, 2)).toString().simplified();
            //qDebug()<<_ip<<_mac;
            slotWakeOnLan(_ip,_mac);
        }
    });
    /*********************************************************************/

    QVBoxLayout * vbox = new QVBoxLayout();
    vbox->addWidget(twl);
    QHBoxLayout * hbox = new QHBoxLayout();
    hbox->addWidget(powerOnButton);
    hbox->addWidget(powerOnButtonAll);
    vbox->addLayout(hbox);

    d->setLayout(vbox);
    //d->exec();

    return d;

}

void MainWindow::slotWakeOnLan(QString _ip,QString _mac)
{
    _mac=_mac.toUpper();
    qDebug()<<"mac adresi:"<<_mac<<_ip;
    for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState==false&&onlinePcList[i]->ip==_ip&&onlinePcList[i]->mac==_mac)
        {
            QString kmt29="wakeonlan "+onlinePcList[i]->mac+" &";
            system(kmt29.toStdString().c_str());
            qDebug()<<"Açılana Pc: "<<kmt29;
        }
    }
    mesajSlot(tr("Seçili Hostlar Uzaktan  Başlatıl."));

}

#endif // WOLWIDGET_H
