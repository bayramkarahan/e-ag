#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QCameraInfo>
#include <iostream>
#include <QApplication>

QString detectAudioSystem()
{
    QProcess process;
    QString output;

    // Öncelikle pipewire-pulse aktif mi kontrol edelim
    process.start("pactl", {"info"});
    process.waitForFinished(500);
    output = process.readAllStandardOutput();

    if (output.contains("Server Name: PulseAudio") || output.contains("Server Name: PipeWire"))
        return "pulse"; // Pulse veya PipeWire (Pulse uyumluluğunda) mevcut

    // ALSA aygıtı var mı kontrol et
    process.start("arecord", {"-l"});
    process.waitForFinished(500);
    output = process.readAllStandardOutput();

    if (output.contains("card"))
        return "alsa";

    // Hiçbiri bulunamadıysa varsayılan olarak alsa dön
    return "alsa";
}


int main(int argc, char *argv[]) {
    std::vector<std::string> args;
    std::transform(argv, argv + argc, std::back_inserter(args), [](const char* arg) {
        return std::string(arg);
    });

    if(args.size()<2)
    {
        std::cout << "Kamera Yolunu Yazmalısın."<< std::endl;
        return 0;
    }

    std::string camerapath=args[1];
   // std::string audipath=args[2];
    QCoreApplication app(argc, argv);

    QProcess *ffmpeg = new QProcess(&app);
    QStringList arguments;
    QStringList kameras;

    for (const QCameraInfo &cameraInfo : QCameraInfo::availableCameras()) {
        kameras.append(cameraInfo.description());
        //qDebug() << "Kamera bulundu:" << cameraInfo.deviceName();
        // qDebug() << "Kamera bulundu:" << cameraInfo.description();
    }
//return 0;
    QString audioSystem = detectAudioSystem();
    QString audioFormat = (audioSystem == "pulse") ? "pulse" : "alsa";

#ifdef Q_OS_WIN
    QString videoDeviceName = "Integrated Camera"; // Varsayılan
    if (!kameras.isEmpty()) {
        videoDeviceName = kameras.first();
         qDebug() <<"kullanılacak kamera:"<<videoDeviceName;
    }


    arguments << "-f" << "dshow"
         << "-video_size" << "640x480"
         << "-framerate" << "30"
         << "-i" << "video=Integrated Camera:audio=Mikrofon (Realtek High Definition Audio)";
    /*
         << "-vcodec" << "libx264"
         << "-preset" << "ultrafast"
         << "-tune" << "zerolatency"
         << "-pix_fmt" << "yuv420p"
         << "-acodec" << "aac"
         << "-ar" << "44100"
         << "-ac" << "2"
         << "-b:a" << "128k"
         << "-f" << "mpegts"
         << "udp://239.0.0.1:1234?ttl=1&pkt_size=1316";*/

#endif

#ifdef Q_OS_LINUX
    arguments << "-f" << "v4l2"
         << "-framerate" << "24"
         << "-video_size" << "320x240"
         << "-i" << QString::fromStdString(camerapath)
         << "-f" << audioFormat
         << "-i" << "default";
#endif

    arguments << "-c:v" << "libx264"
         << "-preset" << "ultrafast"
         << "-tune" << "zerolatency"
         << "-pix_fmt" << "yuv420p"
         << "-c:a" << "aac"
         << "-b:a" << "128k"
         << "-ar" << "44100"
         << "-ac" << "2"
         << "-fflags" << "+genpts+nobuffer"
         << "-flags" << "low_delay"
         << "-muxdelay" << "0"
         << "-fflags" << "+nobuffer+genpts+igndts"
         << "-flags" << "low_delay"
         << "-strict" << "-2"
         << "-f" << "mpegts"
         << "udp://239.0.0.1:1234?ttl=10&pkt_size=1316";

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

    qDebug() << "UDP multicast yayını başladı.";
    return app.exec();
}
