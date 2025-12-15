#ifndef POWERREBOOTWIDGET_H
#define POWERREBOOTWIDGET_H

QWidget* MainWindow::poweroffrebootWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=e*12;

    QWidget *sor=new QWidget();
    sor->setWindowTitle(tr("Kapatma ve Yeniden Başlatma Seçenekleri"));
    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
    sor->setFixedSize(yukseklik*1.4,boy*16);

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    sor->move(x, y);
    /**************************************************/

    QToolButton *closePc=new QToolButton();
    closePc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    closePc->setIcon(QIcon(":/icons/close.svg"));
    closePc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    closePc->setFixedSize(yukseklik*1.4,boy*7);
    closePc->setAutoRaise(true);
    //closePc->setAutoFillBackground(true);
    closePc->setText(tr("Kapat"));
    // closePc->setMenu(sessionMenu());
    // closePc->setPopupMode(QToolButton::MenuButtonPopup);
    connect(closePc, &QToolButton::clicked, [=]() {
        slotPowerOff();
    });

    QToolButton *rebootPc=new QToolButton();
    rebootPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    rebootPc->setIcon(QIcon(":/icons/reboot.svg"));
    rebootPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    rebootPc->setFixedSize(yukseklik*1.4,boy*7);
    rebootPc->setAutoRaise(true);
    //rebootPc->setAutoFillBackground(true);
    rebootPc->setText(tr("Yeniden Başlat"));
    // rebootPc->setMenu(sessionMenu());
    // rebootPc->setPopupMode(QToolButton::MenuButtonPopup);

    connect(rebootPc, &QToolButton::clicked, [=]() {
        slotReboot();
    });

    QToolButton *poweroffRebootMenuButton= new QToolButton();
    // poweroffRebootMenuButton->setIcon(QIcon(":/icons/transparanlock.svg"));
    poweroffRebootMenuButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    poweroffRebootMenuButton->setFixedSize(e*5,b*2);
    poweroffRebootMenuButton->setAutoRaise(true);
    //poweroffRebootMenuButton->setAutoFillBackground(true);
    poweroffRebootMenuButton->setText("");
    poweroffRebootMenuButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    poweroffRebootMenuButton->setMenu(poweroffRebootMenu());
    poweroffRebootMenuButton->setPopupMode(QToolButton::InstantPopup);

    connect(poweroffRebootMenuButton, &QPushButton::clicked, [=]() {
        // slotKilitAcAll();
    });
    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);
    layout->addWidget(closePc, 4,0,1,1,Qt::AlignCenter);
    ///layout->addWidget(closePcAll, 5,0,1,1,Qt::AlignCenter);
    layout->addWidget(rebootPc, 6,0,1,1,Qt::AlignCenter);
    //layout->addWidget(poweroffRebootMenuButton, 7,0,1,1,Qt::AlignRight);

    return sor;
}

void MainWindow::slotReboot(){
     udpSendData("consolecommand","consolecommand","/sbin/reboot","",false);
    for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect))
        {
           // udpSendData("pcbaslat","/sbin/reboot",onlinePcList[i]->ip);
            onlinePcList[i]->setConnectState(false);
            onlinePcList[i]->setSshState("c");
            onlinePcList[i]->setVncState("c");
            onlinePcList[i]->setXrdpState("c");
            onlinePcList[i]->setUser("noLogin");
            onlinePcList[i]->tcpConnectCounter=5;
        }
    }
    mesajSlot(tr("Seçili Hostlar Yeniden Başlatıldı."));

}
void MainWindow::slotRebootAll(){
    udpSendData("consolecommand","consolecommand","/sbin/reboot","",false);
    for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState)
        {
            ///udpSendData("pcbaslat","/sbin/reboot",onlinePcList[i]->ip);
            onlinePcList[i]->setConnectState(false);
            onlinePcList[i]->setSshState("c");
            onlinePcList[i]->setVncState("c");
            onlinePcList[i]->setXrdpState("c");
            onlinePcList[i]->setUser("noLogin");
            onlinePcList[i]->tcpConnectCounter=5;
        }
    }
    mesajSlot(tr("Tüm Hostlar Yeniden Başlatıldı."));

}
void MainWindow::slotPowerOff(){
    udpSendData("consolecommand","consolecommand","/sbin/poweroff","",false);
    for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState&&(onlinePcList[i]->select||onlinePcList[i]->multiSelect))
        {
            //udpSendData("pckapat","/sbin/poweroff",onlinePcList[i]->ip);
            onlinePcList[i]->setConnectState(false);
            onlinePcList[i]->setSshState("no");
            onlinePcList[i]->setVncState("no");
            onlinePcList[i]->setXrdpState("no");
            onlinePcList[i]->setUser("noLogin");
            onlinePcList[i]->tcpConnectCounter=5;
        }
    }
    mesajSlot(tr("Seçili Hostlar Kapatıldı."));

}
void MainWindow::slotPowerOffAll(){
    udpSendData("consolecommand","consolecommand","/sbin/poweroff","",false);
    for(int i=0;i<onlinePcList.count();i++)
    {
        if(onlinePcList[i]->connectState)
        {
            //udpSendData("pckapat","/sbin/poweroff",onlinePcList[i]->ip);
            onlinePcList[i]->setConnectState(false);
            onlinePcList[i]->setSshState("no");
            onlinePcList[i]->setVncState("no");
            onlinePcList[i]->setXrdpState("no");
            onlinePcList[i]->setUser("noLogin");
            onlinePcList[i]->tcpConnectCounter=5;
        }
    }
    mesajSlot(tr("Tüm Hostlar Kapatıldı."));

}

#endif // POWERREBOOTWIDGET_H
