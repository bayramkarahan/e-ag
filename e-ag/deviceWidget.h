#ifndef DEVICEWIDGET_H
#define DEVICEWIDGET_H
QWidget* MainWindow::deviceWidget()
{
    int e=en;
    int b=boy;
    // qDebug()<<"ayar click";
    QFont ff( "Arial", 20, 0);
    int yukseklik=b*7.5;

    QWidget *sor = new QWidget();
    sor->setWindowTitle(tr("Ses Seçenekleri"));
    sor->setStyleSheet("font-size:" + QString::number(font.toInt() - 2) + "px;");
    sor->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
    //sor->setFixedSize(yukseklik * 1.4, boy * 16);

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width()) / 2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    // sor->move(x, y);

    /**************************************************/
    QToolButton *offVolumePc = new QToolButton();
    offVolumePc->setIcon(QIcon(":/icons/volumeoff.svg"));
    offVolumePc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    offVolumePc->setFixedSize(e*18,yukseklik*2);
    offVolumePc->setAutoRaise(true);
    offVolumePc->setText(tr("Ses Pasif"));
    offVolumePc->setIconSize(QSize(b*10,yukseklik*1.3));
    connect(offVolumePc, &QToolButton::clicked, [=]() {
        if (pcMac->text() == "") { mesajSlot("Pc Seçiniz"); return; }
        udpSendData("x11command", "volumeoff", "","volume-off",true);
    });

    /**************************************************/
    QToolButton *onVolumePc = new QToolButton();
    onVolumePc->setIcon(QIcon(":/icons/volumeon.svg"));
    onVolumePc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    onVolumePc->setFixedSize(e*18,yukseklik*2);
    onVolumePc->setIconSize(QSize(b*10,yukseklik*1.3));
    onVolumePc->setAutoRaise(true);
    onVolumePc->setText(tr("Ses Aktif"));
    connect(onVolumePc, &QToolButton::clicked, [=]() {
        if (pcMac->text() == "") { mesajSlot(tr("Pc Seçiniz")); return; }
        udpSendData("x11command", "volumeon", "","volume-on",true);
    });

    /**************************************************/
    QToolButton *keyboardoff = new QToolButton();
    keyboardoff->setIcon(QIcon(":/icons/keyboardoff.svg"));
    keyboardoff->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    keyboardoff->setFixedSize(e*18,yukseklik*2);
    keyboardoff->setIconSize(QSize(b*10,yukseklik*1.3));
    keyboardoff->setAutoRaise(true);
    keyboardoff->setText(tr("Klavye Pasif"));
    connect(keyboardoff, &QToolButton::clicked, [=]() {

        if (pcMac->text() == "") { mesajSlot("Pc Seçiniz"); return; }
        //udpSendData("consolecommand", "consolecommand", "bash /usr/bin/input-km keyboard disable","keyboard-off",true);
        udpSendData("x11command", "keyboardoff", "","keyboard-off",true);

    });

    /**************************************************/
    QToolButton *keyboardon = new QToolButton();
    keyboardon->setIcon(QIcon(":/icons/keyboardon.svg"));
    keyboardon->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    keyboardon->setFixedSize(e*18,yukseklik*2);
    keyboardon->setIconSize(QSize(b*10,yukseklik*1.3));
    keyboardon->setAutoRaise(true);
    keyboardon->setText(tr("Klavye Aktif"));
    connect(keyboardon, &QToolButton::clicked, [=]() {
        if (pcMac->text() == "") { mesajSlot(tr("Pc Seçiniz")); return; }
        //udpSendData("consolecommand", "consolecommand", "bash /usr/bin/input-km keyboard enable","keyboard-on",true);
        udpSendData("x11command", "keyboardon", "","keyboard-on",true);

    });

    /**************************************************/
    QToolButton *mouseoff = new QToolButton();
    mouseoff->setIcon(QIcon(":/icons/mouseoff.svg"));
    mouseoff->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mouseoff->setFixedSize(e*18,yukseklik*2);
    mouseoff->setIconSize(QSize(b*10,yukseklik*1.3));
    mouseoff->setAutoRaise(true);
    mouseoff->setText(tr("Fare Pasif"));
    connect(mouseoff, &QToolButton::clicked, [=]() {
        if (pcMac->text() == "") { mesajSlot("Pc Seçiniz"); return; }
        //udpSendData("consolecommand", "consolecommand", "bash /usr/bin/input-km mouse disable","mouse-off",true);
        udpSendData("x11command", "mouseoff", "","mouse-off",true);

    });

    /**************************************************/
    QToolButton *mouseon = new QToolButton();
    mouseon->setIcon(QIcon(":/icons/mouseon.svg"));
    mouseon->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mouseon->setFixedSize(e*18,yukseklik*2);
    mouseon->setIconSize(QSize(b*10,yukseklik*1.3));
    mouseon->setAutoRaise(true);
    mouseon->setText(tr("Fare Aktif"));
    connect(mouseon, &QToolButton::clicked, [=]() {
        if (pcMac->text() == "") { mesajSlot(tr("Pc Seçiniz")); return; }
        //udpSendData("consolecommand", "consolecommand", "bash /usr/bin/input-km mouse enable","mouse-on",true);
        udpSendData("x11command", "mouseon", "","mouse-on",true);

    });
    QToolButton *stopInternetButton=new QToolButton();
    stopInternetButton->setFixedSize(e*18,yukseklik*2);
    stopInternetButton->setAutoRaise(true);
    //stopInternetButton->setAutoFillBackground(true);
    stopInternetButton->setText(tr("İnternet Pasif"));
    stopInternetButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    stopInternetButton->setIcon(QIcon(":/icons/stopinternet.svg"));
    stopInternetButton->setIconSize(QSize(b*10,yukseklik*1.3));
    stopInternetButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    stopInternetButton->setIconSize(QSize(b*10,yukseklik*1.3));
    connect(stopInternetButton, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}
        //udpSendData("consolecommand","consolecommand","internet-off","internet-off",false);
        udpSendData("consolecommand","consolecommand","/usr/share/webblock/script/internet-off","internet-off",true);

    });

    QToolButton *openInternetButton=new QToolButton();
    openInternetButton->setFixedSize(e*18,yukseklik*2);
    openInternetButton->setAutoRaise(true);
    //openInternetButton->setAutoFillBackground(true);
    openInternetButton->setText(tr("İnternet Aktif"));
    openInternetButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    openInternetButton->setIcon(QIcon(":/icons/openinternet.svg"));
    openInternetButton->setIconSize(QSize(b*10,yukseklik*1.3));
    openInternetButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(openInternetButton, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}
        //udpSendData("x11command","x11command",webEdit->text());
        //udpSendData("consolecommand","consolecommand","internet-on","internet-on",true);
        udpSendData("consolecommand","consolecommand","/usr/share/webblock/script/internet-on","internet-on",true);

    });

    QToolButton *stopPowerButton=new QToolButton();
    stopPowerButton->setFixedSize(e*18,yukseklik*2);
    stopPowerButton->setAutoRaise(true);
    //stopPowerButton->setAutoFillBackground(true);
    stopPowerButton->setText(tr("Güç Düğmesi Pasif"));
    stopPowerButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    stopPowerButton->setIcon(QIcon(":/icons/stoppower.svg"));
    stopPowerButton->setIconSize(QSize(b*10,yukseklik*1.3));
    stopPowerButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(stopPowerButton, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}
        //udpSendData("x11command","x11command",webEdit->text());
        udpSendData("consolecommand","consolecommand","bash /usr/bin/input-sleep-off","sleepbuuton-off",true);
        udpSendData("consolecommand","consolecommand","bash /usr/bin/input-power-off","powerbuttton-off",true);
    });

    QToolButton *openPowerButton=new QToolButton();
    openPowerButton->setFixedSize(e*18,yukseklik*2);
    openPowerButton->setAutoRaise(true);
    //openPowerButton->setAutoFillBackground(true);
    openPowerButton->setText(tr("Güç Düğmesi Aktif"));
    openPowerButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    openPowerButton->setIcon(QIcon(":/icons/openpower.svg"));
    openPowerButton->setIconSize(QSize(b*10,yukseklik*1.3));
    openPowerButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(openPowerButton, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}
        //udpSendData("x11command","x11command",webEdit->text());
        udpSendData("consolecommand","consolecommand","bash /usr/bin/input-sleep-on","sleepbutton-on",true);
        udpSendData("consolecommand","consolecommand","bash /usr/bin/input-power-on","powerbutton-on",true);
    });

    /**************************************************/
    // 🔧 Layout burada doğrudan 'sor' üzerine uygulanıyor
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setVerticalSpacing(5);
    layout->setHorizontalSpacing(10);

    layout->addWidget(keyboardoff,  0, 0, Qt::AlignCenter);
    layout->addWidget(keyboardon, 0, 1, Qt::AlignCenter);

    layout->addWidget(mouseoff,  0, 2, Qt::AlignCenter);
    layout->addWidget(mouseon, 0, 3, Qt::AlignCenter);

    layout->addWidget(offVolumePc,      0, 4, Qt::AlignCenter);
    layout->addWidget(onVolumePc,       0, 5, Qt::AlignCenter);
    layout->addWidget(stopInternetButton,0, 8, Qt::AlignCenter);
    layout->addWidget(openInternetButton,0, 9, Qt::AlignCenter);

    ///layout->addWidget(stopPowerButton,0, 10, Qt::AlignCenter);
    ///layout->addWidget(openPowerButton,0, 11, Qt::AlignCenter);

    // 🔹 Boyutları eşitlemek istersen:
  /*  layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 1);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
*/
    return sor;
}

#endif // DEVICEWIDGET_H
