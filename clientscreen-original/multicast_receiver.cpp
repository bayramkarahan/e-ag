#include "multicast_receiver.h"
#include <QDebug>

MulticastReceiver::MulticastReceiver(QObject *parent)
    : QThread(parent)
{
    avformat_network_init();
}

MulticastReceiver::~MulticastReceiver()
{
    stop();
}

void MulticastReceiver::stop()
{
    m_running = false;
    wait();  // thread sonlanana kadar bekle
}

void MulticastReceiver::run()
{
    m_running = true;

    // Tüm değişkenleri başta tanımla
    AVFormatContext *fmt_ctx = nullptr;
    AVCodecParameters *codecpar = nullptr;
    const AVCodec *codec = nullptr;
    AVCodecContext *codec_ctx = nullptr;
    AVPacket *packet = nullptr;
    AVFrame *frame = nullptr;
    AVFrame *rgb_frame = nullptr;
    SwsContext *sws_ctx = nullptr;
    uint8_t *buffer = nullptr;
    int video_stream_index = -1;
    int num_bytes = 0;
    int ret;

    // Aç ve kontrol et
     ret = avformat_open_input(&fmt_ctx, urlAddress.toStdString().c_str(), nullptr, nullptr);
    if (ret < 0) {
        qWarning() << "Could not open input stream";
        goto cleanup;
    }

    if (avformat_find_stream_info(fmt_ctx, nullptr) < 0) {
        qWarning() << "Failed to retrieve input stream info";
        goto cleanup;
    }

    // Video stream bul
    for (unsigned int i = 0; i < fmt_ctx->nb_streams; ++i) {
        if (fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            video_stream_index = i;
            break;
        }
    }
    if (video_stream_index == -1) {
        qWarning() << "No video stream found";
        goto cleanup;
    }

    // Codec ayarla
    codecpar = fmt_ctx->streams[video_stream_index]->codecpar;
    codec = avcodec_find_decoder(codecpar->codec_id);
    if (!codec) {
        qWarning() << "Unsupported codec";
        goto cleanup;
    }

    codec_ctx = avcodec_alloc_context3(codec);
    if (!codec_ctx) {
        qWarning() << "Could not allocate codec context";
        goto cleanup;
    }

    if (avcodec_parameters_to_context(codec_ctx, codecpar) < 0) {
        qWarning() << "Failed to copy codec parameters to context";
        goto cleanup;
    }

    if (avcodec_open2(codec_ctx, codec, nullptr) < 0) {
        qWarning() << "Failed to open codec";
        goto cleanup;
    }

    // Frame ve packet ayarla
    frame = av_frame_alloc();
    rgb_frame = av_frame_alloc();
    packet = av_packet_alloc();
    if (!frame || !rgb_frame || !packet) {
        qWarning() << "Failed to allocate frames or packet";
        goto cleanup;
    }

    // SwsContext ayarla
    sws_ctx = sws_getContext(codec_ctx->width, codec_ctx->height, codec_ctx->pix_fmt,
                             codec_ctx->width, codec_ctx->height, AV_PIX_FMT_RGB24,
                             SWS_BICUBIC, nullptr, nullptr, nullptr);
    if (!sws_ctx) {
        qWarning() << "Failed to create SwsContext";
        goto cleanup;
    }

    // Buffer ayarla
    num_bytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, codec_ctx->width, codec_ctx->height, 1);
    buffer = (uint8_t *)av_malloc(num_bytes * sizeof(uint8_t));
    if (!buffer) {
        qWarning() << "Failed to allocate buffer";
        goto cleanup;
    }

    av_image_fill_arrays(rgb_frame->data, rgb_frame->linesize, buffer,
                         AV_PIX_FMT_RGB24, codec_ctx->width, codec_ctx->height, 1);

    // Okuma döngüsü
    while (m_running && av_read_frame(fmt_ctx, packet) >= 0) {
        if (packet->stream_index == video_stream_index) {
            if (avcodec_send_packet(codec_ctx, packet) == 0) {
                while (avcodec_receive_frame(codec_ctx, frame) == 0) {
                    sws_scale(sws_ctx, frame->data, frame->linesize, 0, codec_ctx->height,
                              rgb_frame->data, rgb_frame->linesize);
                   /* QImage image(rgb_frame->data[0], codec_ctx->width, codec_ctx->height,
                                 rgb_frame->linesize[0], QImage::Format_RGB888);
                    emit frameReady(image.copy());*/
                    QImage image(rgb_frame->data[0], codec_ctx->width, codec_ctx->height,
                                 rgb_frame->linesize[0], QImage::Format_RGB888);
                    emit frameReady(image.copy());  // copy() yapılmalı, ki orijinal veri safe olsun
                }
            }
        }
        av_packet_unref(packet);
    }

cleanup:
    if (buffer)
        av_free(buffer);
    if (sws_ctx)
        sws_freeContext(sws_ctx);
    if (frame)
        av_frame_free(&frame);
    if (rgb_frame)
        av_frame_free(&rgb_frame);
    if (packet)
        av_packet_free(&packet);
    if (codec_ctx)
        avcodec_free_context(&codec_ctx);
    if (fmt_ctx)
        avformat_close_input(&fmt_ctx);

    m_running = false;
}
