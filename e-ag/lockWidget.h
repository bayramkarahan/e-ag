#ifndef LOCKWIDGET_H
#define LOCKWIDGET_H

QWidget* MainWindow::kilittransparanWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=e*12;
    QWidget *sor=new QWidget();
    sor->setWindowTitle(tr("Ekran Kilitleme Seçenekleri"));
    sor->setStyleSheet("font-size:"+QString::number(font.toInt())+"px;");

    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
    sor->setFixedSize(yukseklik*1.4,boy*16);
    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    // sor->move(x, y);
    /**************************************************/

    QToolButton *transparanUnlockPc=new QToolButton();
    transparanUnlockPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    transparanUnlockPc->setIcon(QIcon(":/icons/transparanunlock.svg"));
    transparanUnlockPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    transparanUnlockPc->setFixedSize(yukseklik*1.4,boy*7);
    transparanUnlockPc->setAutoRaise(true);
    // transparanUnlockPc->setAutoFillBackground(true);
    transparanUnlockPc->setText(tr("Şeffaf Kilit Aç"));
    //transparanUnlockPc->setMenu(sessionMenu());
    //transparanUnlockPc->setPopupMode(QToolButton::MenuButtonPopup);

    connect(transparanUnlockPc, &QToolButton::clicked, [=]() {
        slotTransparanKilitAc();
    });

    /**************************************************/
    QToolButton *transparanLockPc=new QToolButton();
    transparanLockPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    transparanLockPc->setIcon(QIcon(":/icons/transparanlock.svg"));
    transparanLockPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    transparanLockPc->setFixedSize(yukseklik*1.4,boy*7);
    transparanLockPc->setAutoRaise(true);
    // transparanLockPc->setAutoFillBackground(true);
    transparanLockPc->setText(tr("Şeffaf Kilitle"));
    //transparanLockPc->setMenu(sessionMenu());
    //transparanLockPc->setPopupMode(QToolButton::MenuButtonPopup);
    connect(transparanLockPc, &QToolButton::clicked, [=]() {
        slotTransparanKilit();
    });

    QToolButton *transparanKilitMenuButton= new QToolButton();
    // transparanKilitMenuButton->setIcon(QIcon(":/icons/transparanlock.svg"));
    transparanKilitMenuButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    transparanKilitMenuButton->setFixedSize(e*5,b*2);
    transparanKilitMenuButton->setAutoRaise(true);
    //transparanKilitMenuButton->setAutoFillBackground(true);
    transparanKilitMenuButton->setText("");
    transparanKilitMenuButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    transparanKilitMenuButton->setMenu(transparanKilitMenu());
    transparanKilitMenuButton->setPopupMode(QToolButton::InstantPopup);

    connect(transparanKilitMenuButton, &QPushButton::clicked, [=]() {
        // slotKilitAcAll();
    });
    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);
    layout->addWidget(transparanLockPc, 4,1,1,1,Qt::AlignCenter);
    layout->addWidget(transparanUnlockPc, 5,1,1,1,Qt::AlignCenter);
    //layout->addWidget(transparanKilitMenuButton, 6,1,1,1,Qt::AlignRight);
    return sor;
        // sor->show();

    //slotVncFlip(ekranScale->currentText());
}

QWidget* MainWindow::kilitWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=b*12;
    QWidget *sor=new QWidget();
    sor->setWindowTitle(tr("Kilit Seçenekleri"));
    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
    sor->setFixedSize(yukseklik*1,boy*16);
    //sor->setStyleSheet("background-color: #dceded;font-size:"+QString::number(font.toInt()-2)+"px;");

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    // sor->move(x, y);
    /**************************************************/
    QToolButton *lockPc=new QToolButton();
    lockPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    lockPc->setIcon(QIcon(":/icons/lock.svg"));
    lockPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    lockPc->setFixedSize(yukseklik*1,b*7);
    lockPc->setAutoRaise(true);
    // lockPc->setAutoFillBackground(true);
    lockPc->setText(tr("Kilitle"));

     lockPc->setMenu(kilitMenu());
     lockPc->setPopupMode(QToolButton::MenuButtonPopup);

    connect(lockPc, &QToolButton::clicked, [=]() {
            /***********************************/
        udpSendData("x11command","kilitstatetrue","","kilit-on",false);

    });
    /**************************************************/
    QToolButton *unlockPc=new QToolButton();
    unlockPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    unlockPc->setIcon(QIcon(":/icons/unlock.svg"));
    unlockPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    unlockPc->setFixedSize(yukseklik*1,b*7);
    unlockPc->setAutoRaise(true);
    //unlockPc->setAutoFillBackground(true);
    unlockPc->setText(tr("Kilit Aç"));
    unlockPc->setMenu(unkilitMenu());
    unlockPc->setPopupMode(QToolButton::MenuButtonPopup);

    connect(unlockPc, &QToolButton::clicked, [=]() {
        slotKilitAc();
    });


    QToolButton *kilitMenuButton= new QToolButton();
    // kilitMenuButton->setIcon(QIcon(":/icons/transparanlock.svg"));
    kilitMenuButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    kilitMenuButton->setFixedSize(e*5,b*2);
    kilitMenuButton->setAutoRaise(true);
    //kilitMenuButton->setAutoFillBackground(true);
    kilitMenuButton->setText("");
    kilitMenuButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    kilitMenuButton->setMenu(kilitMenu());
    kilitMenuButton->setPopupMode(QToolButton::InstantPopup);

    connect(kilitMenuButton, &QPushButton::clicked, [=]() {
        // slotKilitAcAll();
    });


    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);
    layout->addWidget(lockPc, 4,0,1,1,Qt::AlignCenter);
    layout->addWidget(unlockPc, 5,0,1,1,Qt::AlignCenter);
    //layout->addWidget(kilitMenuButton, 6,0,1,1,Qt::AlignRight);
    /// layout->addWidget(kilitAllButton, 7,0,1,1);
    /// layout->addWidget(kilitAcAllButton, 8,0,1,1);
    return sor;
        // sor->show();

    //slotVncFlip(ekranScale->currentText());
}

void MainWindow::slotKilit(){
    //system("sleep 1");
    udpSendData("x11command","kilitstatetrue","","",false);
    mesajSlot(tr("Seçili Hostlarda Ekran Kilitlendi."));

}
void MainWindow::slotTransparanKilit()
{
    //system("sleep 1");
    udpSendData("x11command","transparankilitstatetrue","","",false);
    mesajSlot(tr("Seçili Hostlar Şeffaf Kilitlendi."));

}
void MainWindow::slotKilitAc(){
    //system("sleep 1");
    udpSendData("x11command","kilitstatefalse","","",false);
    mesajSlot(tr("Seçili Hostlarda Kilit Açıldı."));

}
void MainWindow::slotTransparanKilitAc(){
    //system("sleep 1");
    udpSendData("x11command","transparankilitstatefalse","","",false);
    mesajSlot(tr("Seçili Hostlarda Şeffaf Kilit Açıldı."));

}

QMenu *MainWindow::kilitMenu()
{
    QMenu *menu = new QMenu(this);
    int yukseklik=en*14;
    /*************************************/

    QPushButton *locktransparentButton= new QPushButton;
    locktransparentButton->setFixedSize(yukseklik*1.7, yukseklik/3);
    locktransparentButton->setIconSize(QSize(yukseklik*1.7,yukseklik/3));

    locktransparentButton->setText(tr("Şeffaf Kilitle"));
    locktransparentButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    locktransparentButton->setFlat(true);
    locktransparentButton->setIcon(QIcon(":icons/transparanlock.svg"));

    connect(locktransparentButton, &QPushButton::clicked, [=]() {
        menu->close();
        slotTransparanKilit();
    });






    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    //  layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(locktransparentButton, 5,0,1,1);


    // layout->addWidget(new QLabel("<font size=1>Ayarları Kaydet</font>"),6,1,1,1,Qt::AlignHCenter);
    //layout->setColumnStretch(6, 255);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
    //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

    menu->setStyleSheet("QMenu { width: "+QString::number(yukseklik*1.7)+" px; height: "+QString::number(yukseklik/1.5) +"px; }");
    return menu;




}

QMenu *MainWindow::unkilitMenu()
{
    QMenu *menu = new QMenu(this);
    int yukseklik=en*14;
    /*************************************/

    QPushButton *unlocktransparentButton= new QPushButton;
    unlocktransparentButton->setFixedSize(yukseklik*1.7, yukseklik/3);
    unlocktransparentButton->setIconSize(QSize(yukseklik*1.7,yukseklik/3));

    unlocktransparentButton->setText(tr("Şeffaf Kilit Aç"));
    unlocktransparentButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    unlocktransparentButton->setFlat(true);
    unlocktransparentButton->setIcon(QIcon(":icons/transparanunlock.svg"));

    connect(unlocktransparentButton, &QPushButton::clicked, [=]() {
        menu->close();
        slotTransparanKilitAc();
    });






    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    //  layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(unlocktransparentButton, 5,0,1,1);


    // layout->addWidget(new QLabel("<font size=1>Ayarları Kaydet</font>"),6,1,1,1,Qt::AlignHCenter);
    //layout->setColumnStretch(6, 255);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
    //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

    menu->setStyleSheet("QMenu { width: "+QString::number(yukseklik*1.7)+" px; height: "+QString::number(yukseklik/1.5) +"px; }");
    return menu;




}

QMenu *MainWindow::transparanKilitMenu()
{
    QMenu *menu = new QMenu(this);
    int yukseklik=en*14;
    /*************************************/
    QPushButton *transparanKilitAllButton= new QPushButton;
    transparanKilitAllButton->setFixedSize(yukseklik*1.7, yukseklik/3);
    transparanKilitAllButton->setIconSize(QSize(yukseklik*1.7,yukseklik/3));
    transparanKilitAllButton->setText(tr(" Tümünü Kilitle"));
    transparanKilitAllButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    transparanKilitAllButton->setFlat(true);
    transparanKilitAllButton->setIcon(QIcon(":icons/transparanlock.svg"));

    connect(transparanKilitAllButton, &QPushButton::clicked, [=]() {
        menu->close();
    });



    QPushButton *transparankilitAcAllButton= new QPushButton;
    transparankilitAcAllButton->setFixedSize(yukseklik*1.7, yukseklik/3);
    transparankilitAcAllButton->setIconSize(QSize(yukseklik*1.7,yukseklik/3));
    transparankilitAcAllButton->setText(tr(" Tüm Kilitleri Aç"));
    transparankilitAcAllButton->setStyleSheet("Text-align:left; font-size:"+QString::number(font.toInt()-2)+"px;");
    transparankilitAcAllButton->setFlat(true);
    transparankilitAcAllButton->setIcon(QIcon(":icons/transparanunlock.svg"));

    connect(transparankilitAcAllButton, &QPushButton::clicked, [=]() {
        menu->close();

    });

    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    //  layout->setColumnMinimumWidth(0, 37);
    // layout->addWidget(kilitButton, 2,0,1,2);
    // layout->addWidget(kilitAllButton, 3,0,1,2);
    // layout->addWidget(logoutButton, 4,0,1,2);
    layout->addWidget(transparanKilitAllButton, 5,0,1,1);
    layout->addWidget(transparankilitAcAllButton, 6,0,1,1);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
    //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

    menu->setStyleSheet("QMenu { width: "+QString::number(yukseklik*1.7)+" px; height: "+QString::number(yukseklik/1.5) +"px; }");
    return menu;

}

#endif // LOCKWIDGET_H
