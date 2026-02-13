#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H
QWidget* MainWindow::messageWidget()
{
    int e=en;
    int b=boy;
    // qDebug()<<"ayar click";
    QFont ff( "Arial", 20, 0);
    int yukseklik=b*7;
    QWidget * d = new QWidget();
    // d->setFixedSize(this->width(),boy*16);
    d->setWindowTitle(tr("Duyuru Mesaj Penceresi"));
    QTextEdit *mesajLE = new QTextEdit();
    mesajLE->setFixedSize(e*80,boy*15);
    // mesajLE->setFont(ff);
    mesajLE->setStyleSheet("font-size:"+QString::number(font.toInt()+2)+"px;");

    QLabel *mesajLabel=new QLabel(tr("Mesaj / Duyuru"));
    mesajLabel->setFixedSize(e*15,yukseklik);
    mesajLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");



    QToolButton *duyuruButton=new QToolButton();
    duyuruButton->setFixedSize(e*24,yukseklik*2);
    duyuruButton->setAutoRaise(true);
    // duyuruButton->setAutoFillBackground(true);
    duyuruButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    duyuruButton->setText(tr("Seçili Pc'lere Gönder"));
    duyuruButton->setIcon(QIcon(":/icons/selectpcmessage.svg"));
    duyuruButton->setIconSize(QSize(b*8,yukseklik));
    duyuruButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(duyuruButton, &QToolButton::clicked, [=]() {
        if(pcMac->text()==""){mesajSlot(tr("Pc Seçiniz"));return;}
        udpSendData("x11command","ekranmesaj",mesajLE->toPlainText(),"",false);
        mesajSlot("Seçili Pc'ye Mesaj Gönderildi.");
    });



    QToolButton *duyuruAllButton=new QToolButton();
    duyuruAllButton->setFixedSize(e*24,yukseklik*2);
    duyuruAllButton->setAutoRaise(true);
    // duyuruAllButton->setAutoFillBackground(true);
    duyuruAllButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    duyuruAllButton->setText(tr("Tüm Pc'lere Gönder"));
    duyuruAllButton->setIcon(QIcon(":/icons/allpcmessage.svg"));
    duyuruAllButton->setIconSize(QSize(b*8,yukseklik));
    duyuruAllButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(duyuruAllButton, &QToolButton::clicked, [=]() {
         udpSendData("x11command","ekranmesaj",mesajLE->toPlainText(),"",false);
        mesajSlot(tr("Ağ'a Mesaj Gönderildi."));
    });

    QToolButton *helpButton= new QToolButton;
    helpButton->setFixedSize(e*12,yukseklik*2);
    helpButton->setAutoRaise(true);
    // bilgiButton->setAutoFillBackground(true);
    helpButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    helpButton->setText(tr("Yardım"));
    helpButton->setIcon(QIcon(":/icons/help.svg"));
    helpButton->setIconSize(QSize(b*8,yukseklik));
    helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(helpButton, &QToolButton::clicked, [=]() {
        QTextDocument *doc=new QTextDocument();

        doc->setHtml(tr("<center><h2>Mesaj Gönderme</h2></center>"
                     "<center><img src=\":/icons/mesaj.png\" /></center> "
                     "<br/>1-Mesaj sadece X işareti yeşil olan istemcilere gönderilebilir."
                     "<center><img src=\":/icons/istemci.png\" /></center>"
                     "<br/><br/>2-İstemci simgelerinin altındaki X işareti login olmuş kullanıcıyı ifade eder."
                     "<br/><br/>3-X işareti yeşilse kullanıcı login olduğunu ifade eder. Kırmızı ise login olmadığını ifade eder."
                     "<br/><br/>4-Birden fazla istemciye mesaj göndermek için istemciler seçilerek gönderilebilir."
                        ));
        QPrinter pdf;
        pdf.setOutputFileName("/tmp/mesaj.pdf");
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
        d1->setWindowTitle(tr("Mesaj Gönderme Penceresi"));
        d1->setFixedSize(QSize(boy*215,boy*100));
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

    layout->addWidget(mesajLabel, 0,0,1,1,Qt::AlignCenter);
    layout->addWidget(mesajLE, 0,1,1,1,Qt::AlignCenter);
    layout->addWidget(duyuruButton, 0,2,1,1,Qt::AlignCenter);
    layout->addWidget(duyuruAllButton, 0,3,1,1,Qt::AlignCenter);
    layout->addWidget(helpButton, 0,4,1,1,Qt::AlignCenter);


    d->setLayout(layout);

    return d;
}


#endif // MESSAGEWIDGET_H
