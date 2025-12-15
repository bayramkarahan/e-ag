#include "mainwindow.h"
#include<QLabel>
#include<QToolButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //MulticastReceiver *receiver=new MulticastReceiver(this);
    sahne=new QLabel(this);
    this->setFixedSize(400,350);
    sahne->setFixedSize(400,300);
    QToolButton *startButton = new QToolButton(this);
    startButton->setText(tr("Start"));
    connect(startButton, &QToolButton::clicked, [this]() {
        if (receiver && receiver->isRunning())
            return;

        if (receiver) {
            receiver->stop();
            delete receiver;
            receiver = nullptr;
        }

        receiver = new MulticastReceiver(this);
        receiver->urlAddress = "udp://@239.0.0.1:1234";

        connect(receiver, &MulticastReceiver::frameReady, this, [this](const QImage &img) {
            if (prevImage != img)
                sahne->setPixmap(QPixmap::fromImage(img).scaled(sahne->size(), Qt::KeepAspectRatio));
            prevImage= img;
        });

        receiver->start();
    });

    QToolButton *stopButton= new QToolButton(this);
    stopButton->setText(tr("Stop"));
    connect(stopButton, &QToolButton::clicked, [=]() {
        if (receiver) {
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


}

MainWindow::~MainWindow()
{
    if (receiver) {
        receiver->stop();
        delete receiver;
        receiver = nullptr;
    }
}
