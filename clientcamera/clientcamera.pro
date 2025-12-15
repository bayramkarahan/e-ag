QT += widgets
CONFIG += c++11
TARGET=clientcamera
SOURCES += main.cpp \
           vlcwidget.cpp


HEADERS += vlcwidget.h

INCLUDEPATH += /usr/include/vlc
LIBS += -lvlc
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
target.path = /usr/bin
INSTALLS += target
