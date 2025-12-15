#ifndef VLCWIDGET_H
#define VLCWIDGET_H

#include <QWidget>
#include <vlc/vlc.h>

class VLCWidget : public QWidget {
    Q_OBJECT
public:
    explicit VLCWidget(QWidget *parent = nullptr);
    ~VLCWidget();

    void play(const QString &url);

private:
    libvlc_instance_t *vlcInstance = nullptr;
    libvlc_media_player_t *mediaPlayer = nullptr;
};

#endif // VLCWIDGET_H
