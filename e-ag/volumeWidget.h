#ifndef VOLUMEWIDGET_H
#define VOLUMEWIDGET_H
QWidget* MainWindow::volumeWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=b*12;
    QWidget *sor=new QWidget();
    sor->setWindowTitle(tr("Ses Seçenekleri"));
    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
    sor->setFixedSize(yukseklik*1.4,boy*16);
    //sor->setStyleSheet("background-color: #dceded;font-size:"+QString::number(font.toInt()-2)+"px;");

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    // sor->move(x, y);
    /**************************************************/
    QToolButton *offVolumePc=new QToolButton();
    offVolumePc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    offVolumePc->setIcon(QIcon(":/icons/volumeoff.svg"));
    offVolumePc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    offVolumePc->setFixedSize(yukseklik*1,b*7);
    offVolumePc->setAutoRaise(true);
    offVolumePc->setText(tr("Ses Kapat"));
    connect(offVolumePc, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot("Pc Seçiniz");return;}
        udpSendData("x11command","volumeoff","","",false);

    });
    /**************************************************/
    QToolButton *onVolumePc=new QToolButton();
    onVolumePc->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    onVolumePc->setIcon(QIcon(":/icons/volumeon.svg"));
    onVolumePc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    onVolumePc->setFixedSize(yukseklik*1,b*7);
    onVolumePc->setAutoRaise(true);
    onVolumePc->setText(tr("Ses Aç"));

    connect(onVolumePc, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}
        udpSendData("x11command","volumeon","","volumeon",false);

    });

    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);
    layout->addWidget(offVolumePc, 4,0,1,1,Qt::AlignCenter);
    layout->addWidget(onVolumePc, 5,0,1,1,Qt::AlignCenter);

    return sor;
        // sor->show();

    //slotVncFlip(ekranScale->currentText());
}

#endif // VOLUMEWIDGET_H
