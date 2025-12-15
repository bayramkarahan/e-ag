#ifndef COMMANDRUNNER_H
#define COMMANDRUNNER_H
class CommandRunner : public QObject {
    Q_OBJECT
public:
    explicit CommandRunner(QObject *parent = nullptr) : QObject(parent) {}

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
};

#endif // COMMANDRUNNER_H
