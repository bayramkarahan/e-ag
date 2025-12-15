#include "vlcwidget.h"
#include <QDebug>
//sudo apt install libvdpau-va-gl1
VLCWidget::VLCWidget(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_NativeWindow);
    setAttribute(Qt::WA_DontCreateNativeAncestors);

   /* const char* const vlc_args[] = {
        "--no-xlib",                    // VDPAU/Xlib hatalarını bastırır
        "--avcodec-hw=none",           // Donanım hızlandırmayı kapat
        "--no-video-title-show",       // Üstte VLC yazısını gösterme
        "--network-caching=100",       // 100 ms ağ buffer süresi
        "--clock-jitter=0",            // Zaman senkronizasyon toleransı azaltılır
        "--clock-synchro=1",           // Ses/video senkronu açılır
        "--drop-late-frames",          // Geç kalan kareler atılır
        "--skip-frames",               // Yoğunlukta kareler atlanabilir
        "--quiet"                      // Konsol log'ları bastır
    };*/
    const char* const vlc_args[] = {
        "--avcodec-hw=none",             // Tüm donanım hızlandırma desteğini kapat
        "--no-video-title-show",
        "--network-caching=100",
        "--clock-jitter=0",
        "--clock-synchro=1",
        "--drop-late-frames",
        "--skip-frames",
        "--quiet"
    };
    vlcInstance = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
    mediaPlayer = libvlc_media_player_new(vlcInstance);
    libvlc_media_player_set_rate(mediaPlayer, 1.0); // Normal hızda oynat
}

VLCWidget::~VLCWidget() {
    if (mediaPlayer) {
        libvlc_media_player_stop(mediaPlayer);
        libvlc_media_player_release(mediaPlayer);
    }
    if (vlcInstance)
        libvlc_release(vlcInstance);
}

void VLCWidget::play(const QString &url) {

    // Pencere tanımlayıcısını doğru şekilde VLC'ye bağla
    if (!winId()) {
        createWinId();
    }

#ifdef Q_OS_WIN
    libvlc_media_player_set_hwnd(mediaPlayer, (void*)winId());
#elif defined(Q_OS_MAC)
    libvlc_media_player_set_nsobject(mediaPlayer, (void*)winId());
#else
    libvlc_media_player_set_xwindow(mediaPlayer, winId());
#endif

    libvlc_media_t *media = libvlc_media_new_location(vlcInstance, url.toUtf8().constData());
    libvlc_media_player_set_media(mediaPlayer, media);
    libvlc_media_release(media);
    libvlc_media_player_play(mediaPlayer);
}
