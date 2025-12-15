#ifndef KEYBOARDMOUSEWIDGET_H
#define KEYBOARDMOUSEWIDGET_H
QWidget* MainWindow::keyboardmouseWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=b*12;
    QWidget *sor=new QWidget();
    sor->setWindowTitle(tr("Klavye Fare Seçenekleri"));
    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
    sor->setFixedSize(yukseklik*1.6,boy*16);
    //sor->setStyleSheet("background-color: #dceded;font-size:"+QString::number(font.toInt()-2)+"px;");

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    // sor->move(x, y);
    /**************************************************/
    QToolButton *keyboardmouseoff=new QToolButton();
    keyboardmouseoff->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    keyboardmouseoff->setIcon(QIcon(":/icons/keyboardmouseoff.svg"));
    keyboardmouseoff->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    keyboardmouseoff->setFixedSize(yukseklik*1.5,b*7);
    keyboardmouseoff->setIconSize(QSize(yukseklik*1.5,b*3.5));
    keyboardmouseoff->setAutoRaise(true);
    keyboardmouseoff->setText(tr("Klavye Fare Kapat"));
    connect(keyboardmouseoff, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot("Pc Seçiniz");return;}
        udpSendData("consolecommand","consolecommand","input-off","",false);

    });
    /**************************************************/
    QToolButton *keyboardmouseon=new QToolButton();
    keyboardmouseon->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    keyboardmouseon->setIcon(QIcon(":/icons/keyboardmouseon.svg"));
    keyboardmouseon->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    keyboardmouseon->setFixedSize(yukseklik*1.5,b*7);
    keyboardmouseon->setIconSize(QSize(yukseklik*1.53,b*3.5));
    keyboardmouseon->setAutoRaise(true);
    keyboardmouseon->setText(tr("Klavye Fare Aç"));

    connect(keyboardmouseon, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}
        udpSendData("consolecommand","consolecommand","input-on","",false);

    });

    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);
    layout->addWidget(keyboardmouseoff, 4,0,1,1,Qt::AlignCenter);
    layout->addWidget(keyboardmouseon, 5,0,1,1,Qt::AlignCenter);

    return sor;
        // sor->show();

    //slotVncFlip(ekranScale->currentText());
}

#endif // KEYBOARDMOUSEWIDGET_H
