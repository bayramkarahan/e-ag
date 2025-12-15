#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H
#include "VideoDecodeThread.h"
#include<QLabel>

class VideoPlayer : public QLabel {
    Q_OBJECT
public:
    VideoPlayer(QWidget* parent = nullptr) : QLabel(parent) {
        setAlignment(Qt::AlignCenter);
    }

    void setAddress(const QString& url) {
        thread = new VideoDecodeThread(url, this);
        connect(thread, &VideoDecodeThread::frameReady, this, &VideoPlayer::updateFrame);
        thread->start();
        this->show();
    }

    void stop() {
        if (thread) {
            thread->requestInterruption();
            thread->wait();
            delete thread;
            thread = nullptr;
        }
        this->close();
    }

    ~VideoPlayer() {
        stop();
    }

private slots:
    void updateFrame(const QImage& image) {
        setPixmap(QPixmap::fromImage(image).scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

private:
    VideoDecodeThread* thread = nullptr;
};



#endif // VIDEOPLAYER_H
