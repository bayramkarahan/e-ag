#ifndef IPWATCHER_H
#define IPWATCHER_H

#include <QObject>
#include <QSocketNotifier>
#include <QNetworkInterface>

class IPWatcher : public QObject
{
    Q_OBJECT
public:
    explicit IPWatcher(QObject *parent = nullptr);
    ~IPWatcher();

signals:
    void ipChanged(const QStringList &newIPs);

private slots:
    void handleNetlinkEvent();

private:
    int netlinkSocket = -1;
    QSocketNotifier *notifier = nullptr;
    QStringList lastIPs;

    QStringList getCurrentIPs();
};

#endif // IPWATCHER_H
