#include <QApplication>
#include <QVBoxLayout>
#include "vlcwidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QWidget window;
    window.setWindowTitle("Multicast VLC Viewer");

    QVBoxLayout *layout = new QVBoxLayout(&window);
    VLCWidget *player = new VLCWidget();
    layout->addWidget(player);

    window.resize(640, 480);
    window.show();

    player->play("udp://@239.0.0.1:1234?pkt_size=1316&ttl=2");

    return a.exec();
}
