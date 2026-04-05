#ifndef LOGINLOGOUTWIDGET_H
#define LOGINLOGOUTWIDGET_H



QWidget* MainWindow::logoutWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=e*12;

    QWidget *sor=new QWidget();
    sor->setWindowTitle(tr("Oturum Seçenekleri"));
    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
    sor->setFixedSize(yukseklik*1.4,boy*16);

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    sor->move(x, y);
    /**************************************************/
    /******************************************************/
    QToolButton *logoutPc=new QToolButton();
    logoutPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    logoutPc->setIcon(QIcon(":/icons/session.svg"));
    logoutPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //  logoutPc->setIconSize(QSize(yukseklik,yukseklik*0.75));

    logoutPc->setFixedSize(yukseklik*1.4,boy*7);
    logoutPc->setAutoRaise(true);
    // logoutPc->setAutoFillBackground(true);
    logoutPc->setText(tr("Oturum Kapat"));
    // logoutPc->setMenu(sessionMenu());
    // logoutPc->setPopupMode(QToolButton::MenuButtonPopup);

    connect(logoutPc, &QToolButton::clicked, [=]() {
        slotLogout();
    });


    QToolButton* loginPc = new QToolButton(0);
    loginPc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    loginPc->setIcon(QIcon(":/icons/login.svg"));
    loginPc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    // loginPc->setIconSize(QSize(yukseklik,yukseklik*0.75));

    loginPc->setFixedSize(yukseklik*1.4,boy*7);
    loginPc->setAutoRaise(true);
    // portKontrol->setAutoFillBackground(true);
    loginPc->setText(tr("Oturum Aç"));
    connect(loginPc, &QToolButton::clicked, [=]() {
        slotLogin();
    });
    QToolButton *sessionMenuButton= new QToolButton();
        // sessionMenuButton->setIcon(QIcon(":/icons/transparanlock.svg"));
    sessionMenuButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    sessionMenuButton->setFixedSize(e*5,b*2);
    sessionMenuButton->setAutoRaise(true);
    //sessionMenuButton->setAutoFillBackground(true);
    sessionMenuButton->setText("");
    sessionMenuButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    sessionMenuButton->setMenu(sessionMenu());
    sessionMenuButton->setPopupMode(QToolButton::InstantPopup);

    connect(sessionMenuButton, &QPushButton::clicked, [=]() {
        // slotKilitAcAll();
    });

    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);
    layout->addWidget(logoutPc, 4,0,1,1,Qt::AlignCenter);
    ///  layout->addWidget(closePcAll, 5,0,1,1,Qt::AlignCenter);
    layout->addWidget(loginPc, 6,0,1,1,Qt::AlignCenter);
    //layout->addWidget(sessionMenuButton, 7,0,1,1,Qt::AlignRight);

    return sor;
        // sor->show();

    //slotVncFlip(ekranScale->currentText());
}

void MainWindow::slotLogout(){
    QString komut="loginctl terminate-seat seat0";
    udpSendData("seatlogin","seatlogin",komut,"",false);
    mesajSlot("Seçili Hostlarda Oturum Kapatıldı.");

}
void MainWindow::slotLogoutAll(){
    QString komut="loginctl terminate-seat seat0";
    udpSendData("seatlogin","seatlogin",komut,"",false);
    mesajSlot("Tüm Hostlarda Oturum Kapatıldı.");
}
void MainWindow::slotLogin(){
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

            QString komut="sshlogin "+seatUser+" "+seatUserPasswd;
             udpSendData("seatlogin","seatlogin",komut,"",false);

            QString komut1="pardus-login "+seatUser+" "+seatUserPasswd;
            udpSendData("seatlogin","seatlogin",komut1,"",false);
            // qDebug()<<"komut:"<<komut;


        }
        mesajSlot("Seçili Hostlarda Oturum Açıldı.");

}



#endif // LOGINLOGOUTWIDGET_H
