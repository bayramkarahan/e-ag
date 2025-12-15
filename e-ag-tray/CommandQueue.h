#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H
#include <QQueue>
#include <QProcess>
#include <QTimer>
#include <QLocalSocket>

class CommandQueue : public QObject {
    Q_OBJECT
public:
    CommandQueue(QObject *parent = nullptr) : QObject(parent) {}

    void addCommand(const QString &cmd, QLocalSocket *sock) {
        queue.append({cmd, sock});
        processNext();
    }

private:
    struct CmdItem {
        QString cmd;
        QLocalSocket *sock;
    };

    QList<CmdItem> queue;
    bool busy = false;

    void processNext() {
        if (busy || queue.isEmpty())
            return;

        busy = true;
        CmdItem item = queue.takeFirst();

        QProcess *process = new QProcess(this);
        process->setProcessChannelMode(QProcess::MergedChannels);

        connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                [this, process, item](int, QProcess::ExitStatus){
                    QString output = process->readAll();
                    if (item.sock && item.sock->isOpen()) {
                        item.sock->write(output.toUtf8());
                        item.sock->flush();
                        item.sock->close();
                    }
                    process->deleteLater();
                    busy = false;
                    processNext(); // Kuyrukta diğer komutu çalıştır
                });

        process->start(item.cmd);
    }
};


#endif // COMMANDQUEUE_H
