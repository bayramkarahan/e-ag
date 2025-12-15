#include <QCoreApplication>
#include<networkprofil.h>
#include <QString>
#include <QDir>
#include<QDebug>
#include<singleinstance.h>
#include <stdio.h>
#include <stdlib.h>
#include <QtCore/QCoreApplication>
#include <QtDBus/QtDBus>
#include <QSettings>
#define  echo QTextStream(stderr) <<

#define SINGLE_INSTANCE ".ServerNetworkProfil"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

     QString name = SINGLE_INSTANCE;

    SingleInstance cInstance;
    if(cInstance.hasPrevious(name, QCoreApplication::arguments()))
    {
        qDebug() << "ServerNetworkProfil Zaten Açık...";
        return 0;
    }
    if (cInstance.listen(name)) {
        qDebug() << "ServerNetworkProfil Çalışıyor..";
    } else {
        qDebug() << "ServerNetworkProfil Çalışması İptal Edildi...";
        return 0;
    }


        NewtworkProfil *cl=new NewtworkProfil();
        //cl->networkProfilLoad();
        return a.exec();


    return 0;
}
