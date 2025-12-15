#ifndef MULTICAST_RECEIVER_H
#define MULTICAST_RECEIVER_H

#include <QObject>
#include <QImage>
#include <QThread>
#include <atomic>   // atomic için

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}

class MulticastReceiver : public QThread {
    Q_OBJECT

public:
    explicit MulticastReceiver(QObject *parent = nullptr);
    ~MulticastReceiver();

    void run() override;
    void stop();

    QString urlAddress;

signals:
    void frameReady(const QImage &image);

private:
    std::atomic<bool> m_running{false};  // atomic flag
};

#endif // MULTICAST_RECEIVER_H
