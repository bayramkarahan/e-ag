#ifndef SSH_H
#define SSH_H
void MainWindow::ssh()
{
    int e=en;
    int b=boy;
     /***************************************************************/
         auto *sshWidget=new QWidget(this);
         sshWidget->resize(this->width(),b*14);
         sshWidget->move(0,b*9+2);
        // sshWidget->setStyleSheet("background-color: #55aaaa;");
        // sshWidget->setStyleSheet("background-image: url(:/icons/ssh.png);");
         auto *sshWidgetbc=new QWidget(sshWidget);
            sshWidgetbc->resize(this->width(),b*14);
            sshWidgetbc->move(0,0);
            sshWidgetbc->setStyleSheet("background-color: #acacac");

    QLabel *commandLabel=new QLabel(sshWidget);
    commandLabel->setFixedSize(e*15,b*13);
   // commandLabel->move(5,50);
    commandLabel->setText("SSH\n"
                          "Komut\n"
                          "Dosya Yolu\n"
                          "Duyuru");


    lineEdit_message=new QLineEdit(sshWidget);
    lineEdit_message->setFixedSize(126*e,b*13);
   // lineEdit_message->move(80,50);
   // lineEdit_message->setStyleSheet("font-size: 30px");
    QFont ff( "Arial", 30, 0);
    lineEdit_message->setFont(ff);

    connect(lineEdit_message, &QLineEdit::textChanged,this, &MainWindow::enableButton);


    commandExecuteButton=new QPushButton(sshWidget);
    commandExecuteButton->setFixedSize(e*18,b*6);
  //  commandExecuteButton->move(710,50);
    commandExecuteButton->setText("Çalıştır");
    connect(commandExecuteButton, SIGNAL(clicked()),this, SLOT(commandExecuteSlot()));
    //commandExecuteButton->setFlat(true);
   // commandExecuteButton->setAutoFillBackground(true);
    //commandExecuteButton->setStyleSheet("background-color: #dcdcdc");

    commandExecuteAllButton=new QPushButton(sshWidget);
    commandExecuteAllButton->setFixedSize(e*16,b*6);
   // commandExecuteAllButton->move(810,50);
    commandExecuteAllButton->setText("Ağ Çalıştır");
    connect(commandExecuteAllButton, SIGNAL(clicked()),this, SLOT(commandExecuteAllSlot()));

    fileSelectButton=new QPushButton(sshWidget);
    fileSelectButton->setFixedSize(e*5,b*6);
   // fileSelectButton->move(710,85);
    fileSelectButton->setText("...");
    connect(fileSelectButton, SIGNAL(clicked()),this, SLOT(fileSelectSlot()));

    fileCopyButton=new QPushButton(sshWidget);
    fileCopyButton->setFixedSize(e*11,b*6);
   // fileCopyButton->move(745,85);
    fileCopyButton->setText("Kopyala");
    connect(fileCopyButton, SIGNAL(clicked()),this, SLOT(fileCopySlot()));

    fileCopyAllButton=new QPushButton(sshWidget);
    fileCopyAllButton->setFixedSize(e*16,b*6);
   // fileCopyAllButton->move(810,85);
    fileCopyAllButton->setText("Ağ Kopyala");
    connect(fileCopyAllButton, SIGNAL(clicked()),this, SLOT(fileCopyAllSlot()));


/*****************************************/
    auto layouts = new QGridLayout(sshWidget);
    layouts->setContentsMargins(3, 0, 3,0);
    layouts->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
    layouts->addWidget(commandLabel, 0,0,2,1);
    layouts->addWidget(lineEdit_message, 0,1,2,1);
   layouts->addWidget(commandExecuteButton, 0,3,1,2);
    layouts->addWidget(commandExecuteAllButton, 0,5,1,1);

     layouts->addWidget(fileSelectButton, 1,3,1,1);
    layouts->addWidget(fileCopyButton, 1,4,1,1);
    layouts->addWidget(fileCopyAllButton, 1,5,1,1);


}
#endif // SSH_H
