#include <QApplication>
#include <iostream>
#include<QHostAddress>
#include<QNetworkInterface>
#include<QNetworkAddressEntry>
#include<QProcess>
#include<QScreen>
class IpMac
{
public:
    QString ip;
    QString mac;
    QString broadcast;

};
QList<IpMac> ipmaclist;

void hostAddressMacButtonSlot()
{
    QHostAddress localhost = QHostAddress(QHostAddress::LocalHost);
    ipmaclist.clear();
    foreach (const QNetworkInterface& networkInterface, QNetworkInterface::allInterfaces()) {
        foreach (const QNetworkAddressEntry& entry, networkInterface.addressEntries()) {
            QHostAddress *hostadres=new QHostAddress(entry.ip().toString());
            if(hostadres->protocol() == QAbstractSocket::IPv4Protocol &&
                !hostadres->isLoopback() )
            {
                IpMac im;
                im.ip=entry.ip().toString();
                im.mac=networkInterface.hardwareAddress();
                im.broadcast=entry.broadcast().toString();
                ipmaclist.append(im);

                // qDebug()<<"mac:"<<networkInterface.hardwareAddress();
                //qDebug()<<"ip  address:"<<entry.ip().toString();
                // qDebug()<<"broadcast  address:"<<entry.broadcast().toString();
            }
        }
    }
    //qDebug()<<"ip  address:"<<ipmaclist.count();


}
int main(int argc, char *argv[]) {

    std::vector<std::string> args;
    std::transform(argv, argv + argc, std::back_inserter(args), [](const char* arg) {
        return std::string(arg);
    });

    if(args.size()<3)
    {
        std::cout << "Video Çözünürlüğünü 111x222  239.*.*.* gibi Yazmalısın."<< std::endl;
        return 0;
    }

    std::string videosize=args[1];
    std::string newIp=args[2];

    QApplication a(argc, argv);
    QProcess *ffmpegProcess0= new QProcess();
    QProcess *ffmpegProcess1= new QProcess();

    hostAddressMacButtonSlot();
    //for(int k=0;k<ipmaclist.count();k++)
    //{

       // qDebug()<<newIp;
        //QStringList ipparts=ipmaclist[k].ip.split(".");
        ///QString newIp="239.0."+ipparts[2]+"."+ipparts[3];
        qDebug()<<QString::fromStdString(newIp);
        QSize screenSize = QGuiApplication::primaryScreen()->size();
        QString videoSize = QString("%1x%2")
                                .arg(screenSize.width())
                                .arg(screenSize.height());
        QString remoteVideoSize = QString("%1x%2")
                                .arg(screenSize.width())
                                .arg(screenSize.height());
        remoteVideoSize= QString::fromStdString(videosize);

#ifdef Q_OS_WIN
        QString command = "ffmpeg.exe";
        QStringList arguments = {
            "-f", "gdigrab",               // Windows için ekran yakalama
            "-framerate", "20",
            "-video_size", videoSize,
            "-i", "desktop",
            //"-f", "dshow",                // Windows mikrofon
            //"-i", "audio=Microphone",
#else
        QString command = "ffmpeg";

        QStringList arguments = {
            "-f", "x11grab",              // Linux için ekran yakalama
            "-framerate", "20",
            "-video_size",videoSize,
            "-i", ":0.0",
#endif
            "-vcodec", "libx264",
            "-preset", "ultrafast",
            "-tune", "zerolatency",
            "-pix_fmt", "yuv420p",
            "-s", remoteVideoSize,
            "-b:v", "3000k",
            "-bufsize", "0",
            "-flush_packets", "1",
            "-fflags", "nobuffer",
            "-g", "10",
            "-keyint_min", "10",
            "-f", "mpegts",
            "udp://"+QString::fromStdString(newIp)+":1234?pkt_size=1316&ttl=1"
        };

        //if(k==0)
        //{
            ffmpegProcess0->start(command, arguments);
            if (!ffmpegProcess0->waitForStarted()) {
                qDebug() << "Başlatılamadı-0!";
            } else {
                qDebug() << "Yayın başladı-0.";
            }
        //}
        /*
        if(k==1)
        {
            ffmpegProcess1->start(command, arguments);
            if (!ffmpegProcess1->waitForStarted()) {
                qDebug() << "Başlatılamadı-1!";
            } else {
                qDebug() << "Yayın başladı-1.";
            }
        }
*/
    //}
    return a.exec();
}
