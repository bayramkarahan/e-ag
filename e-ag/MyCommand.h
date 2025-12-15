#ifndef MYCOMMAND_H
#define MYCOMMAND_H

#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QGridLayout>
#include <QScreen>
#include <QIcon>

class MyCommand : public QDialog {
    Q_OBJECT
public:
    MyCommand(QString baslik,QString command, QString commandDetail,QString commandStatus,
             QString evet, QString hayir, QString tamam,
             int _w, int _h,
             QWidget *parent = nullptr)
        : QDialog(parent)
    {
        // Bellekten otomatik silinmesi için:
        setAttribute(Qt::WA_DeleteOnClose);

        // Pencere başlığı ve ikon
        setWindowTitle(baslik);
        setWindowIcon(QIcon(":/icons/lock.png"));
        setFixedSize(_w, _h);
        // Command label'ı
        QLabel *lcommand = new QLabel(this);
        lcommand->setText(command);
        lcommand->setFixedWidth(_w*0.98);
        // CommandStatus label'ı
        QLabel *lcommandStatus = new QLabel(this);
        lcommandStatus->setFixedWidth(_w*0.98);
        if(commandStatus=="0"&&command!="")
        {
        lcommandStatus->setText("Komut İstemcide Başarılı Şekilde Yürütüldü.");
        lcommandStatus->setStyleSheet("background-color:rgba(0,100,0,100)");
        }
       if(commandStatus=="1"&&command!="")
        {
        lcommandStatus->setText("Komut İstemcide Yürütülürken Hatalar Oluştu.");
        lcommandStatus->setStyleSheet("background-color:rgba(100,0,0,100)");
        }
        // CommandDetail label'ı
        QLabel *lcommandDetail = new QLabel(this);
        lcommandDetail->setText(commandDetail);
        lcommandDetail->setWordWrap(true);
        lcommandDetail->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        //lmesaj->setFixedWidth(_w*0.8);
        // Scroll alanı içine mesajı koy
        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setWidget(lcommandDetail);
        scrollArea->setWidgetResizable(true);
        scrollArea->setFixedSize(_w*0.98, _h*0.8);




        // Butonlar
        QPushButton *okButton = new QPushButton(tr("Tamam"));
        //connect(okButton, &QPushButton::clicked, this, &MyDialog::accept);

        QPushButton *cancelButton = new QPushButton(tr("Vazgeç"));
        //connect(cancelButton, &QPushButton::clicked, this, &MyDialog::reject);

        QPushButton *yesButton = new QPushButton(tr("Evet"));
        //connect(yesButton, &QPushButton::clicked, this, &MyDialog::accept);

        // Ana layout
        QGridLayout *layout = new QGridLayout(this);
        layout->addWidget(lcommand, 0, 0, 1, 3);
        layout->addWidget(lcommandStatus, 1, 0, 1, 3);
        layout->addWidget(scrollArea, 2, 0, 1, 3);

        int buttonCol = 0;
        if (evet == "evet")
            layout->addWidget(yesButton, 3, buttonCol++, 1, 1);
        if (tamam == "tamam")
            layout->addWidget(okButton, 3, buttonCol++, 1, 1);
        if (hayir == "hayir")
            layout->addWidget(cancelButton, 3, buttonCol++, 1, 1);

        setLayout(layout);
        QSize screenSize = qApp->screens()[0]->size();
        // Ekranın ortasına taşı
        move(screenSize.width() / 2 - width() / 2,
             screenSize.height() / 2 - height() / 2);
    }
  ~MyCommand()
    {
        //  delete ui;
    }
};

#endif // MYCOMMAND_H
