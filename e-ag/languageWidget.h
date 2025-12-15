#ifndef LANGUAGEWIDGET_H
#define LANGUAGEWIDGET_H


QWidget* MainWindow::languageWidget()
{
    int e=en;
    int b=boy;
    int yukseklik=e*12;

    QWidget *sor=new QWidget();
    sor->setWindowTitle(tr("Çoklu Dil"));
    sor->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    sor->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool);
    sor->setFixedSize(e*8,b*16);

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - sor->width())/2;
    int y = (screenGeometry.height() - sor->height()) / 2;
    sor->move(x, y);
    /******************************************************/
    QString appPath ="/usr/share/e-ag";// a.applicationDirPath();
    QSettings cfg(appPath + "/config.cfg",QSettings::IniFormat);
    QString language = cfg.value("language").toString();
    /******************************************************/
    QToolButton *languageLabelButton= new QToolButton();
    languageLabelButton->setIcon(QIcon(":/icons/language.svg"));
    languageLabelButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    languageLabelButton->setFixedSize(e*8,b*5);
    languageLabelButton->setAutoRaise(true);
    //languageLabelButton->setAutoFillBackground(true);
    languageLabelButton->setText(language.split("_")[0]);
    languageLabelButton->setStyleSheet("font-size:"+QString::number(font.toInt())+"px;");

    QToolButton *languageMenuButton= new QToolButton();
        // sessionMenuButton->setIcon(QIcon(":/icons/transparanlock.svg"));
    languageMenuButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    languageMenuButton->setFixedSize(e*8,b*7);
    languageMenuButton->setAutoRaise(true);
    //languageMenuButton->setAutoFillBackground(true);
    languageMenuButton->setText(tr("Dil"));
    languageMenuButton->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    QMenu *menuu=languageMenu();
    languageMenuButton->setMenu(menuu);
    languageMenuButton->setPopupMode(QToolButton::InstantPopup);

    connect(languageMenuButton, &QPushButton::clicked, [=]() {
        // slotKilitAcAll();
    });

    auto widget = new QWidget;
    auto layout = new QGridLayout(sor);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

    //layout->addWidget(cb, 4,0,1,2);

    layout->addWidget(languageLabelButton, 5,0,1,1,Qt::AlignRight);
    layout->addWidget(languageMenuButton, 7,0,1,1,Qt::AlignRight);

    return sor;
        // sor->show();

    //slotVncFlip(ekranScale->currentText());
}



#endif // LANGUAGEWIDGET_H
