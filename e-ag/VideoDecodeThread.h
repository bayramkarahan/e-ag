#ifndef VIDEODECODETHREAD_H
#define VIDEODECODETHREAD_H

#include <QThread>
#include <QImage>
#include <QString>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

class VideoDecodeThread : public QThread
{
    Q_OBJECT
public:
    explicit VideoDecodeThread(const QString& url, QObject *parent = nullptr)
        : QThread(parent), m_url(url) {}

signals:
    void frameReady(const QImage&);

protected:
    void run() override {
        avformat_network_init();
        AVFormatContext* fmt_ctx = nullptr;
        if (avformat_open_input(&fmt_ctx, m_url.toStdString().c_str(), nullptr, nullptr) != 0)
            return;

        if (avformat_find_stream_info(fmt_ctx, nullptr) < 0)
            return;

        int video_stream_index = -1;
        for (unsigned i = 0; i < fmt_ctx->nb_streams; ++i) {
            if (fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                video_stream_index = i;
                break;
            }
        }
        if (video_stream_index == -1)
            return;

        AVCodecParameters* codecpar = fmt_ctx->streams[video_stream_index]->codecpar;
        const AVCodec* codec = avcodec_find_decoder(codecpar->codec_id);
        AVCodecContext* codec_ctx = avcodec_alloc_context3(codec);
        avcodec_parameters_to_context(codec_ctx, codecpar);
        if (avcodec_open2(codec_ctx, codec, nullptr) < 0)
            return;

        AVFrame* frame = av_frame_alloc();
        AVPacket* pkt = av_packet_alloc();
        SwsContext* sws_ctx = sws_getContext(codec_ctx->width, codec_ctx->height, codec_ctx->pix_fmt,
                                             codec_ctx->width, codec_ctx->height, AV_PIX_FMT_RGB32,
                                             SWS_BILINEAR, nullptr, nullptr, nullptr);

        while (!isInterruptionRequested()) {
            if (av_read_frame(fmt_ctx, pkt) < 0)
                continue;

            if (pkt->stream_index == video_stream_index) {
                if (avcodec_send_packet(codec_ctx, pkt) == 0) {
                    while (avcodec_receive_frame(codec_ctx, frame) == 0) {
                        QImage img(codec_ctx->width, codec_ctx->height, QImage::Format_RGB32);
                        uint8_t* dest[1] = { img.bits() };
                        int dest_linesize[1] = { static_cast<int>(img.bytesPerLine()) };

                        sws_scale(sws_ctx, frame->data, frame->linesize, 0,
                                  codec_ctx->height, dest, dest_linesize);

                        emit frameReady(img);
                    }
                }
            }
            av_packet_unref(pkt);
        }

        av_frame_free(&frame);
        av_packet_free(&pkt);
        avcodec_free_context(&codec_ctx);
        avformat_close_input(&fmt_ctx);
        sws_freeContext(sws_ctx);
    }

private:
    QString m_url;
};

#endif // VIDEODECODETHREAD_H
