#ifndef GROUPWIDGET_H
#define GROUPWIDGET_H

/*
QWidget* MainWindow::groupWidget()
{
    int e = en;
    int b = boy;
    int yukseklik = e * 12;

    localDir="/usr/share/e-ag/";
#if defined(Q_OS_WIN)
    localDir="c:/e-ag/";
#elif defined(Q_OS_LINUX)
    localDir="/usr/share/e-ag/";
#endif

    DatabaseHelper *db = new DatabaseHelper(localDir + "persist.json");
    QJsonArray dizi = db->Oku();
    if (dizi.count() > 0)
    {
        for (const QJsonValue &item : dizi)
        {
            QJsonObject veri = item.toObject();
            bool findState = false;

            for (const groupList &itemliste : PcData::groupListe)
            {
                if (itemliste.groupName == veri.value("groupname").toString())
                {
                    findState = true;
                    break;
                }
            }

            if (!findState)
                PcData::groupListe.append({true, veri.value("groupname").toString()});
        }
    }

    QWidget *sor = new QWidget();
    sor->setWindowTitle(tr("Group Listesi"));
    sor->setObjectName("groupWidget");
    sor->setStyleSheet(
        "#groupWidget { border: 1px solid #e1e1e1; font-size:" + QString::number(font.toInt() - 2) + "px; }"
        );
    sor->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
    sor->setFixedSize(yukseklik * 1.4, boy * 14); // 🔹 bir tık daha küçük

    // Arka plan parent rengi olsun
    QPalette pal = sor->palette();
    QColor bgColor = pal.color(QPalette::Window);
    //pal.setColor(QPalette::Window, bgColor);
    //sor->setAutoFillBackground(true);
   // sor->setPalette(pal);

    // Ekranın ortasına al
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width()) / 2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    sor->move(x, y);

    // Ana layout
    QVBoxLayout *mainLayout = new QVBoxLayout(sor);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Küçük sade başlık
    QLabel *headerLabel = new QLabel(tr("Gruplar"));
    headerLabel->setAlignment(Qt::AlignCenter);
    headerLabel->setStyleSheet(
        "font-weight: bold;"
        "font-size: 9px;"
        "color: #333;"
        "margin-bottom: 0px;"
        );
    mainLayout->addWidget(headerLabel);

    // Scroll area
    QScrollArea *scroll = new QScrollArea(sor);
    scroll->setWidgetResizable(true);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setStyleSheet("background: transparent;");

    // Liste konteyneri
    QWidget *container = new QWidget();
    QVBoxLayout *listLayout = new QVBoxLayout(container);
    listLayout->setContentsMargins(2, 2, 2, 2);
    listLayout->setSpacing(2);

    // PcData::groupListe içeriğini oluştur
    for (int i = 0; i < PcData::groupListe.size(); ++i)
    {
        groupList &grp = PcData::groupListe[i];

        QWidget *row = new QWidget();
        QHBoxLayout *rowLayout = new QHBoxLayout(row);
        rowLayout->setContentsMargins(2, 0, 2, 0);
        rowLayout->setSpacing(5);

        QCheckBox *check = new QCheckBox();
        check->setChecked(grp.groupSelect);
        check->setObjectName("checkWidget");
        check->setStyleSheet(
            "#checkWidget { border: 1px solid #e1e1e1; font-size:" + QString::number(font.toInt() - 2) + "px; }"
            );

        QLabel *label = new QLabel(grp.groupName);
        label->setStyleSheet("color: #222;");

        // 🔹 Sinyali bağla
        connect(check, &QCheckBox::toggled, this, [i, check, this]() {
            // Seçim durumunu güncelle
            PcData::groupListe[i].groupSelect = check->isChecked();

            // Güncel listeyi gönder
            groupListeYenile(PcData::groupListe);
        });

        rowLayout->addWidget(check);
        rowLayout->addWidget(label);
        rowLayout->addStretch();
        row->setLayout(rowLayout);
        listLayout->addWidget(row);
    }


    listLayout->addStretch();
    container->setLayout(listLayout);

    scroll->setWidget(container);
    mainLayout->addWidget(scroll);
    sor->setLayout(mainLayout);

    return sor;
}
*/
QWidget* MainWindow::groupWidget(QWidget *targetWidget)
{
    int e = en;
    int b = boy;
    int yukseklik = e * 12;

    localDir = "/usr/share/e-ag/";
#if defined(Q_OS_WIN)
    localDir = "c:/e-ag/";
#elif defined(Q_OS_LINUX)
    localDir = "/usr/share/e-ag/";
#endif

    DatabaseHelper db(localDir + "persist.json");
    QJsonArray dizi = db.Oku();
    PcData::groupListe.clear();
    if (dizi.count() > 0) {
        for (const QJsonValue &item : dizi) {
            QJsonObject veri = item.toObject();
            bool findState = false;
            for (const groupList &itemliste : PcData::groupListe) {
                if (itemliste.groupName == veri.value("groupname").toString()) {
                    findState = true;
                    break;
                }
            }
            if (!findState)
                PcData::groupListe.append({true, veri.value("groupname").toString()});
        }
    }

    QWidget *sor = targetWidget;
    if (!sor) {
        sor = new QWidget();
        sor->setObjectName("groupWidget");
        sor->setStyleSheet("#groupWidget { border: 1px solid #e1e1e1; }");
        sor->setFixedSize(yukseklik * 1.4, boy * 14);
    } else {
        // 🔹 Eski içeriği temizle
        QLayout *oldLayout = sor->layout();
        if (oldLayout) {
            QLayoutItem *item;
            while ((item = oldLayout->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
            delete oldLayout;
        }
    }

    // 🔹 Yeni layout ve içerik
    QVBoxLayout *mainLayout = new QVBoxLayout(sor);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    QLabel *headerLabel = new QLabel(tr("Gruplar"));
    headerLabel->setAlignment(Qt::AlignCenter);
    headerLabel->setStyleSheet("font-weight:bold;font-size:9px;color:#333;");
    mainLayout->addWidget(headerLabel);

    QScrollArea *scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setStyleSheet("background:transparent;");

    QWidget *container = new QWidget();
    QVBoxLayout *listLayout = new QVBoxLayout(container);
    listLayout->setContentsMargins(2, 2, 2, 2);
    listLayout->setSpacing(2);

    for (int i = 0; i < PcData::groupListe.size(); ++i) {
        groupList &grp = PcData::groupListe[i];

        QWidget *row = new QWidget();
        QHBoxLayout *rowLayout = new QHBoxLayout(row);
        rowLayout->setContentsMargins(2, 0, 2, 0);
        rowLayout->setSpacing(5);

        QCheckBox *check = new QCheckBox();
        check->setChecked(grp.groupSelect);
        QLabel *label = new QLabel(grp.groupName);
        check->setObjectName("checkWidget");
        check->setStyleSheet("#checkWidget { border: 1px solid #e1e1e1; }");

   /*     connect(check, &QCheckBox::toggled, sor, [i, check]() {
            PcData::groupListe[i].groupSelect = check->isChecked();
            groupListeYenile(PcData::groupListe);
        });*/
        connect(check, &QCheckBox::toggled, sor, [this, i, check]() {

            PcData::groupListe[i].groupSelect = check->isChecked();
            groupListChange(PcData::groupListe);
        });

        rowLayout->addWidget(check);
        rowLayout->addWidget(label);
        rowLayout->addStretch();
        listLayout->addWidget(row);
    }

    listLayout->addStretch();
    container->setLayout(listLayout);
    scroll->setWidget(container);
    mainLayout->addWidget(scroll);

    sor->setLayout(mainLayout);
    return sor;
}

void MainWindow::groupListChange(const QList<groupList> &liste)
{
    ///qDebug()<<"groupListChange1"<<PcData::groupListe.length();
  //if(PcData::groupListe.length()>0) PcData::groupListe.clear();
    //if(PcData::groupListe.size()>0) PcData::groupListe.clear();
  /*  for (const groupList &g : liste) {
        //qDebug() << g.groupName << (g.groupSelect ? "✓" : "✗");
        PcData::groupListe.append({g.groupSelect,g.groupName});
    }*/
    // Burada artık güncel grup durumlarını istediğin gibi kullanabilirsin  
    ///qDebug()<<"groupListChange2";
    pcListeGuncelleSlot("groupListChange");
}


#endif // GROUPWIDGET_H
