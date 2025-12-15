#ifndef COMMANRUNNER_H
#define COMMANRUNNER_H
#include<QObject>
#include<QLocalSocket>
#include<QProcess>
//#include<QOverload>

class CommandRunner : public QObject {
    Q_OBJECT
public:
    explicit CommandRunner(QObject *parent = nullptr) : QObject(parent) {}
    void run(const QString &cmd, QLocalSocket *sock) {
        // Komutu bağımsız çalıştır (process bitmesini bekleme)
        QProcess::startDetached(cmd);

        // Hiçbir çıktı göndermeden hemen socket'i kapat
        if (sock && sock->isOpen()) {
            sock->close();
        }

        // CommandRunner nesnesi artık gereksiz → kendini yok et
        this->deleteLater();
    }
/*
    void run(const QString &cmd, QLocalSocket *sock) {
        QProcess *p = new QProcess(this);
        p->setProcessChannelMode(QProcess::MergedChannels);

        connect(p, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                this, [p, sock](int, QProcess::ExitStatus) {

                    QString out = p->readAll();

                    if (sock && sock->isOpen()) {
                        sock->write(out.toUtf8());
                        sock->flush();
                        sock->close();
                    }
                    p->deleteLater();
                });

        p->start(cmd);
    }
*/
};

#endif // COMMANRUNNER_H
