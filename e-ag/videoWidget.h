#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H
#include<QProcessEnvironment>
QWidget* MainWindow::videoWidget()
{
    int e=en;
    int b=boy;
    // qDebug()<<"ayar click";
    QFont ff( "Arial", 15, 0);
    int yukseklik=b*7.5;

    QWidget * d = new QWidget();
    d->setWindowTitle("video Yayın Penceresi");
    QToolButton *videoStopButton=new QToolButton();
    QToolButton *liveStreamStopButton=new QToolButton();

    QLineEdit *commandFileLE = new QLineEdit();
    commandFileLE->setFixedSize(e*60,yukseklik);
    //commandFileLE->setFont(ff);
    commandFileLE->setStyleSheet("font-size:"+QString::number(font.toInt()+2)+"px;");

    QLabel *commandFileLabel=new QLabel(tr("Video Dosyası:"));
    commandFileLabel->setFixedSize(e*15,yukseklik);
    commandFileLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    QComboBox * kamera = new QComboBox();
    kamera->setFixedSize(e*29,yukseklik);
    // kamera->setFont(ff);
    kamera->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    /**********************************video giriş listesi alma işlemi******************************************************/


    QStringList kameralst;
    if(QFile::exists("/dev/video0"))kameralst<<"/dev/video0";
    if(QFile::exists("/dev/video1"))kameralst<<"/dev/video1";
    if(QFile::exists("/dev/video2"))kameralst<<"/dev/video2";
    if(QFile::exists("/dev/video3"))kameralst<<"/dev/video3";
    if(QFile::exists("/dev/video4"))kameralst<<"/dev/video4";
    kamera->addItems(kameralst);
    /****************************************************************************************/

    ses = new QComboBox();
    ses->setFixedSize(e*29,yukseklik);
    // ses->setFont(ff);
    ses->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    /**********************************ses giriş listesi alma işlemi******************************************************/
    QString result="";
    eagtraySendData("pactl get-default-source", [this](const QString &output){
                //qDebug().noquote() << "Komut sonucu:\n" << output;
                //qDebug() << "Komut sonucu:\n" << output;

                trayCommandResult=output.trimmed();
                if(trayCommandResult!="")
                {
                    QStringList seslst;
                    seslst=trayCommandResult.split("\n");
                    ses->addItems(seslst);
                }
            });
/*
    QStringList arguments;
    arguments << "-c" << QString("pactl list short sources | grep 'input' | awk '{print $2}'");
    QProcess process;
    process.start("/bin/bash",arguments);
    if(process.waitForFinished(-1))
    {
        result = process.readAll();
        result.chop(1);
    }
*/
    /****************************************************************************************/
    QLabel *pathLabel=new QLabel(tr("Kamera ve Ses:"));
    pathLabel->setFixedSize(e*15,yukseklik);
    pathLabel->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    // messageBox.setIcon(QMessageBox::Question);
    QToolButton *videoYayinButton=new QToolButton();
    videoYayinButton->setFixedSize(e*14,yukseklik*2);
    videoYayinButton->setAutoRaise(true);
    // videoYayinButton->setAutoFillBackground(true);
    videoYayinButton->setIcon(QIcon(":/icons/video.svg"));
    videoYayinButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    videoYayinButton->setIconSize(QSize(b*8,yukseklik*0.9));
    videoYayinButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    videoYayinButton->setText(tr("Videoyu\nÇalıştır"));
    connect(videoYayinButton, &QToolButton::clicked, [=]() {
        // if(pcMac->text()==""){mesajSlot("Pc Seçiniz");return;}
        QString name = QUrl::fromLocalFile(commandFileLE->text()).path(QUrl::FullyEncoded);
        name.replace("%20","%5C%20");
        QUrl pth;
        if(commandFileLE->text()!="")
        {
            streamState=true;
            videoYayinButton->setStyleSheet("QToolButton { background-color: rgba(0, 255, 0, 1.0); }");
            system("pkill servervideo");
            system("clientcamera&");
            QString kmt10="servervideo "+commandFileLE->text()+"&";
            system(kmt10.toStdString().c_str());
        }
      });




    fileSelectButton=new QToolButton();
    fileSelectButton->setFixedSize(e*12,yukseklik*2);
    fileSelectButton->setAutoRaise(true);
    fileSelectButton->setIcon(QIcon(":/icons/openfile.svg"));
    fileSelectButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    fileSelectButton->setIconSize(QSize(b*6,yukseklik*0.9));
    fileSelectButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    fileSelectButton->setText("...");
    connect(fileSelectButton, &QToolButton::clicked, [=]() {
        QString seatUser=getSessionInfo(getSeatId(),"USER=");
        QStringRef _sessionUser=seatUser.rightRef(seatUser.length()-5);
        seatUser=_sessionUser.toString();
        //qDebug()<<"Kullanıcı: "<<sessionUser;
        pcClickSlot(pcMac->text());
        QString fileName = QFileDialog::getOpenFileName(this,tr("Dosya Seç"),"/home/"+seatUser, tr("Files (*.*)"));
        //qDebug()<<fileName;
        commandFileLE->setText(fileName);

        mesajSlot("Dosya Seçildi.");
    });


    QToolButton *liveStreamButton=new QToolButton();
    liveStreamButton->setFixedSize(e*14,yukseklik*2);
    liveStreamButton->setAutoRaise(true);
    liveStreamButton->setIcon(QIcon(":/icons/camera.svg"));
    liveStreamButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    liveStreamButton->setIconSize(QSize(b*8,yukseklik*0.9));
    liveStreamButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    liveStreamButton->setText(tr("Kamerayı\nÇalıştır"));
    connect(liveStreamButton, &QToolButton::clicked, [=]() {
        streamState=true;
        liveStreamButton->setStyleSheet("QToolButton { background-color: rgba(0, 255, 0, 1.0); }");
        qDebug()<<"camera yayın start";
        system("pkill servercamera");
        system("pkill ffmpeg &");
        QString kmt10="servercamera "+kamera->currentText()+" "+ses->currentText()+"&";
        system(kmt10.toStdString().c_str());
        system("clientcamera&");
        mesajSlot("Seçili Pc'ye Komut Gönderildi.");
    });

    videoStopButton->setFixedSize(e*14,yukseklik*2);
    videoStopButton->setAutoRaise(true);
    videoStopButton->setIcon(QIcon(":/icons/videostop.svg"));
    videoStopButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    videoStopButton->setIconSize(QSize(b*8,yukseklik*0.9));
    videoStopButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    videoStopButton->setText(tr("Videoyu\nDurdur"));
    connect(videoStopButton, &QToolButton::clicked, [=]() {
        if(streamState)
        {
            qDebug()<<"video yayın stop"<<streamState;
            system("pkill servervideo");
            system("pkill ffmpeg &");
            ///udpSendData("x11command","x11command","pkill clientcamera");
            mesajSlot(tr("Video durduruldu."));
            streamState=false;
            videoYayinButton->setStyleSheet("QToolButton { background-color: rgba(0,255, 0, 0.0); }");

        }

    });


    liveStreamStopButton->setFixedSize(e*14,yukseklik*2);
    liveStreamStopButton->setAutoRaise(true);
    liveStreamStopButton->setIcon(QIcon(":/icons/camerastop.svg"));
    liveStreamStopButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    liveStreamStopButton->setIconSize(QSize(b*8,yukseklik*0.9));
    liveStreamStopButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    liveStreamStopButton->setText(tr("Kamerayı\nDurdur"));
    connect(liveStreamStopButton, &QToolButton::clicked, [=]() {
        if(streamState)
        {
            qDebug()<<"camera yayın stop"<<streamState;
            system("pkill servercamera &");
            system("pkill ffmpeg &");
            //udpSendData("x11command","x11command","pkill clientcamera");
            streamState=false;
            liveStreamButton->setStyleSheet("QToolButton { background-color: rgba(0, 255, 0, 0.0); }");

        }

    });

    QToolButton *liveStreamShareButton=new QToolButton();
    liveStreamShareButton->setFixedSize(e*14,yukseklik*2);
    liveStreamShareButton->setAutoRaise(true);
    liveStreamShareButton->setIcon(QIcon(":/icons/streamstart.svg"));
    liveStreamShareButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    liveStreamShareButton->setIconSize(QSize(b*8,yukseklik*0.9));
    liveStreamShareButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    liveStreamShareButton->setText(tr("Pc'ye\nYayınla"));
    connect(liveStreamShareButton, &QToolButton::clicked, [=]() {
        //if(streamState)
        //{
            qDebug()<<"akışı paylaş"<<streamState;
            udpSendData("x11command","x11command","pkill clientcamera","",false);
            system("sleep 2");
            udpSendData("x11command","x11command","clientcamera","",false);

            //streamState=false;
       //}

    });

    QToolButton *liveStreamShareStopButton=new QToolButton();
    liveStreamShareStopButton->setFixedSize(e*14,yukseklik*2);
    liveStreamShareStopButton->setAutoRaise(true);
    liveStreamShareStopButton->setIcon(QIcon(":/icons/streamstop.svg"));
    liveStreamShareStopButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    liveStreamShareStopButton->setIconSize(QSize(b*8,yukseklik*0.9));
    liveStreamShareStopButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    liveStreamShareStopButton->setText(tr("Pc Yayını\nDurdur"));
    connect(liveStreamShareStopButton, &QToolButton::clicked, [=]() {
        //if(streamState)
        //{
            qDebug()<<"akışı  durdur"<<streamState;
            //system("pkill servercamera &");
            udpSendData("x11command","x11command","pkill clientcamera","",false);
            //streamState=false;
        //}

    });

    QToolButton *helpButton= new QToolButton;
    helpButton->setFixedSize(e*14,yukseklik*2);
    helpButton->setAutoRaise(true);
    // bilgiButton->setAutoFillBackground(true);
    helpButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    helpButton->setText(tr("Yardım"));
    helpButton->setIcon(QIcon(":/icons/help.svg"));
    helpButton->setIconSize(QSize(b*8,yukseklik*0.9));
    helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(helpButton, &QToolButton::clicked, [=]() {
        QTextDocument *doc=new QTextDocument();

        doc->setHtml(tr("<center><h2>Video/Kamera Yayını</h2></center>"
                     "<center><img src=\":/icons/video.png\" /></center> "
                     "<br/>1-Sunucudaki bir Video Dosyası/Kamera login olmuş kullanıcılarda paylaşılabillir."
                     "<center><img src=\":/icons/istemci.png\" /></center>"
                     "<br/><br/>2-Video Dosyası/Kamera sadece X işareti yeşil olan istemcilere paylaşılabilir."
                     "<br/><br/>3-İstemci simgelerinin altındaki X işareti login olmuş kullanıcıyı ifade eder."
                     "<br/><br/>4-X işareti yeşilse kullanıcı login olduğunu ifade eder. Kırmızı ise login olmadığını ifade eder."
                     "<br/><br/>5-Birden fazla istemciye Video Dosyası/Kamera paylaşmak için istemci seçilerek paylaşılabilir."
                        ));
        QPrinter pdf;
        pdf.setOutputFileName("/tmp/video.pdf");
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
        d1->setWindowTitle(tr("Video/Kamera Yayın Yardım Penceresi"));
        d1->setFixedSize(QSize(boy*215,boy*90));
        auto appIcon = QIcon(":/icons/e-ag.svg");
        d1->setWindowIcon(appIcon);

        d1->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

        d1->setLayout(vbox);
        d1->exec();

    });
    QGridLayout * vbox = new QGridLayout();
    //  vbox->setSpacing(0);
    vbox->setContentsMargins(0, 0,0,0);
    vbox->setVerticalSpacing(0);

    vbox->addWidget(commandFileLabel,1,1,1,1,Qt::AlignLeft);
    vbox->addWidget(commandFileLE,1,2,1,2,Qt::AlignLeft);
    vbox->addWidget(pathLabel,2,1,1,1,Qt::AlignLeft);
    vbox->addWidget(kamera,2,2,1,1,Qt::AlignLeft);
    vbox->addWidget(ses,2,3,1,1,Qt::AlignLeft);
    vbox->addWidget(fileSelectButton,1,5,2,1,Qt::AlignLeft);
    vbox->addWidget(videoYayinButton,1,6,2,1,Qt::AlignLeft);
    vbox->addWidget(videoStopButton,1,8,2,1,Qt::AlignLeft);

    vbox->addWidget(liveStreamButton,1,9,2,1,Qt::AlignLeft);
    vbox->addWidget(liveStreamStopButton,1,11,2,1,Qt::AlignLeft);
    vbox->addWidget(liveStreamShareButton,1,13,2,1,Qt::AlignLeft);
    vbox->addWidget(liveStreamShareStopButton,1,14,2,1,Qt::AlignLeft);


    vbox->addWidget(helpButton,1,16,2,1,Qt::AlignLeft);

    d->setLayout(vbox);
    return d;
}


#endif // VIDEOWIDGET_H
