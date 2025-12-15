#include "mainwindow.h"
#include<QLabel>
#include<QToolButton>
#include<QScreen>
#include<QGuiApplication>
#include<Database.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //MulticastReceiver *receiver=new MulticastReceiver(this);
    QSize screenSize = QGuiApplication::primaryScreen()->size();
    sahne=new QLabel(this);
    this->setFixedSize(screenSize.width(),screenSize.height());
    sahne->setFixedSize(screenSize.width(),screenSize.height());
    sahne->setScaledContents(true);
    /************************************************************/
    QString localDir="/usr/share/e-ag/";
    #if defined(Q_OS_WIN)
        localDir="c:/e-ag/";
    #elif defined(Q_OS_LINUX)
        localDir="/usr/share/e-ag/";
    #endif
    QString ipaddress="";
    /***********************************************************/
    DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag.json");
    QJsonArray dizi=db->Ara("selectedNetworkProfil",true);
    if(dizi.count()>0)
    {
        for (const QJsonValue &item : dizi) {
            QJsonObject veri=item.toObject();
            //qDebug()<<"Yüklenen Ağ Profili:" <<veri["serverAddress"].toString();
            ipaddress=veri["serverAddress"].toString();
        }
    }
    QStringList ipparts=ipaddress.split(".");
    QString newIp="udp://@239.0."+ipparts[2]+"."+ipparts[3]+":1234";


    /************************************************************/
    QToolButton *startButton = new QToolButton();
    startButton->setText(tr("Start"));
    connect(startButton, &QToolButton::clicked, [=,this]() {
        if (receiver && receiver->isRunning())
            return;

        if (receiver) {
            receiver->stop();
            delete receiver;
            receiver = nullptr;
        }

        receiver = new MulticastReceiver(this);
        receiver->urlAddress =newIp;
            //"udp://@239.0.23.252:1234";
        connect(receiver, &MulticastReceiver::frameReady, this, [this](const QImage &img) {
            if (prevImage != img)
                sahne->setPixmap(QPixmap::fromImage(img).scaled(sahne->size(), Qt::KeepAspectRatio));
            prevImage= img;
        });

        receiver->start();
    });

    QToolButton *stopButton= new QToolButton();
    stopButton->setText(tr("Stop"));
    connect(stopButton, &QToolButton::clicked, [=]() {
        if (receiver) {
            receiver->streamStatus=false;
            receiver->stop();
            receiver->wait();

            disconnect(receiver, nullptr, this, nullptr);  // sinyal bağlantılarını kes
            delete receiver;
            receiver = nullptr;
            sahne->clear(); // Ekranı temizle

        }
    });

    startButton->move(this->width()/2-startButton->width()/2,this->height()-startButton->height());
    stopButton->move(this->width()/2+stopButton->width()/2,this->height()-stopButton->height());
    startButton->click();

}

MainWindow::~MainWindow()
{
    if (receiver) {
        receiver->stop();
        delete receiver;
        receiver = nullptr;
    }
}
