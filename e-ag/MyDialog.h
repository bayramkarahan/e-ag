#ifndef MYDIALOG_H
#define MYDIALOG_H
#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>

class MyDialog : public QDialog {
public:
    MyDialog(QString baslik, QString mesaj, QString evet, QString hayir, QString tamam, int _w,int _h,QWidget *parent = nullptr) : QDialog(parent) {
        //setWindowTitle("My Dialog");
        /*
        QVBoxLayout *layout = new QVBoxLayout(this);
        */
        QPushButton *okButton = new QPushButton(tr("Tamam"));
        connect(okButton, &QPushButton::clicked, this, &MyDialog::done);
        //layout->addWidget(okButton);

        QPushButton *cancelButton = new QPushButton(tr("Vazgeç"));
        connect(cancelButton, &QPushButton::clicked, this, &MyDialog::reject);
        //layout->addWidget(cancelButton);
        QPushButton *yesButton = new QPushButton(tr("Evet"));
        connect(yesButton, &QPushButton::clicked, this, &MyDialog::accept);
        //layout->addWidget(yesButton);


        //setLayout(layout);

        setFixedSize(_w,_h);
        setWindowIcon(QIcon(":/icons/lock.png"));
        setWindowTitle(baslik);
        QLabel *lmesaj=new QLabel(this);

        lmesaj->setText(mesaj);
        QGridLayout *layout=new QGridLayout(this);
        layout->addWidget(lmesaj, 4,0,1,3,Qt::AlignCenter);
        if(evet=="evet")  layout->addWidget(yesButton, 10,0,1,3,Qt::AlignCenter);
        if(tamam=="tamam")  layout->addWidget(okButton, 10,0,1,3,Qt::AlignCenter);
        if(hayir=="hayir")  layout->addWidget(cancelButton, 10,0,1,3,Qt::AlignCenter);
        setLayout(layout);
        QSize _screenSize = qApp->screens()[0]->size();
        move(_screenSize.width()/2-width()/2,_screenSize.height()/2-height()/2);

    }
};

#endif // MYDIALOG_H
