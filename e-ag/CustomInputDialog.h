#ifndef CUSTOMINPUTDIALOG_H
#define CUSTOMINPUTDIALOG_H
#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QDebug>
#include <qt5keychain/keychain.h>

using namespace QKeychain;
class CustomInputDialog : public QDialog {
public:
    CustomInputDialog(QString baslik, QString girdimesaj, QString defaultvalue,int w,int h,QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle(baslik);
        label_ = new QLabel(girdimesaj);
        lineEdit_ = new QLineEdit;
        lineEdit_->setText(defaultvalue);
        okButton_ = new QPushButton(tr("Tamam"));
        cancelButton_ = new QPushButton(tr("İptal"));
        this->w=w;
        this->h=h;
        QHBoxLayout *buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(okButton_);
        buttonLayout->addWidget(cancelButton_);

        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addWidget(label_);
        mainLayout->addWidget(lineEdit_);
        mainLayout->addLayout(buttonLayout);

        setLayout(mainLayout);
        resize(w, h); // Başlangıç boyutunu ayarlayın

        connect(okButton_, &QPushButton::clicked, this, &CustomInputDialog::accept);
        connect(cancelButton_, &QPushButton::clicked, this, &CustomInputDialog::reject);

    }

     void setData(QString metadata,QString data,QString type){
       qDebug() <<"setData"<<metadata<< data << type;

         readMetaData(metadata, [this,metadata,data,type](QString _data){
              qDebug() <<metadata<< " okundu:" << _data;
              if(type=="passwd"){
                  lineEdit_->setEchoMode(QLineEdit::Password);
                  lineEdit_->setContextMenuPolicy(Qt::NoContextMenu);
                  lineEdit_->setDragEnabled(false);
              }
              if(_data=="")
              {
                   lineEdit_->setText(data);

              }else
              {
                   lineEdit_->setText(_data);
              }
         });

        ///this->exec();

 //});

    }
    QString getText() const {

        return lineEdit_->text();
    }
     void saveMetaData(QString metaData, QString data)
    {
        WritePasswordJob *job = new WritePasswordJob("e-ag");
        job->setKey(metaData);
        job->setTextData(data);

        QObject::connect(job, &Job::finished, [metaData,data](Job *job) {
            if (job->error())
                qDebug() << "Error:" << job->errorString();
            else
                qDebug() << "metaData saved"<<metaData;
        });

        job->start();
    }

    void readMetaData(QString user, std::function<void(QString)> callback)
    {
        ReadPasswordJob *job = new ReadPasswordJob("e-ag");
        job->setKey(user);

        QObject::connect(job, &QKeychain::Job::finished, [job, callback]() {
            if (job->error()) {
                qDebug() << "Error:" << job->errorString();
                callback(""); // hata durumunda boş gönder
            } else {
                callback(job->textData()); // ✅ data burada güvenli şekilde dönüyor
            }
        });

        job->start();
    }

private:
    QLabel *label_;
    QLineEdit *lineEdit_;
    QPushButton *okButton_;
    QPushButton *cancelButton_;
    int w,h;
};

#endif // CUSTOMINPUTDIALOG_H
