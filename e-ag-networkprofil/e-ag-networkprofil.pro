QT = core network

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        networkprofil.cpp \
        singleinstance.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
target.path = /usr/bin

networkprofilservice.files = e-ag-networkprofil.service
networkprofilservice.path = /lib/systemd/system/

INSTALLS += target icon auto_start networkprofilservice

DISTFILES += \
    e-ag-networkprofil.service

HEADERS += \
    Database.h \
    networkprofil.h \
    singleinstance.h
