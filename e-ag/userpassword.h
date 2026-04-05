#ifndef USERPASSWORD_H
#define USERPASSWORD_H
#include <qt5keychain/keychain.h>
#include<QDebug>
using namespace QKeychain;
class UserPassword
{
public:
    UserPassword();


void savePassword(QString user, QString password)
{
    WritePasswordJob *job = new WritePasswordJob("e-ag");
    job->setKey(user);
    job->setTextData(password);

    QObject::connect(job, &Job::finished, [](Job *job) {
        if (job->error())
            qDebug() << "Error:" << job->errorString();
        else
            qDebug() << "Password saved";
    });

    job->start();
}

void readPassword(QString user, std::function<void(QString)> callback)
{
    ReadPasswordJob *job = new ReadPasswordJob("e-ag");
    job->setKey(user);

    QObject::connect(job, &QKeychain::Job::finished, [job, callback]() {
        if (job->error()) {
            qDebug() << "Error:" << job->errorString();
            callback(""); // hata durumunda boş gönder
        } else {
            callback(job->textData()); // ✅ password burada güvenli şekilde dönüyor
        }
    });

    job->start();
}


};

#endif // USERPASSWORD_H
