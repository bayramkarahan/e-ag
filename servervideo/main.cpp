#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <iostream>
#include <QApplication>
int main(int argc, char *argv[]) {

    std::vector<std::string> args;
    std::transform(argv, argv + argc, std::back_inserter(args), [](const char* arg) {
        return std::string(arg);
    });

    if(args.size()<2)
    {
        std::cout << "Video Yolunu Yazmalısın."<< std::endl;
        return 0;
    }

    std::string videopath=args[1];



    QCoreApplication app(argc, argv);

    QProcess *ffmpeg = new QProcess(&app);
//        "-an",                         // Ses yoksa CPU tasarrufu
//            "-stream_loop", "-1",         // Sonsuz döngü (isteğe bağlı)
    QStringList arguments = {
        "-re",                         // Gerçek zamanlı okuma (iyi)
        "-i", QString::fromStdString(videopath),
        "-c:v", "libx264",
        "-preset", "veryfast",         // 'ultrafast' daha fazla bitrate ve CPU tüketir
        "-tune", "zerolatency",
        "-bufsize", "512k",            // Küçük buffer
        "-f", "mpegts",
        "udp://239.0.0.1:1234?pkt_size=1316"
    };
    ffmpeg->setProgram("ffmpeg");
    ffmpeg->setArguments(arguments);

    QObject::connect(ffmpeg, &QProcess::readyReadStandardError, [=]() {
        qDebug() << ffmpeg->readAllStandardError();
    });

    ffmpeg->start();

    if (!ffmpeg->waitForStarted()) {
        qCritical() << "FFmpeg başlatılamadı.";
        return -1;
    }

    qDebug() << "Düşük gecikmeli multicast yayını başlatıldı.";
    return app.exec();
}
