QT += core gui widgets
CONFIG += c++17
TARGET = MulticastViewer
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    multicast_receiver.cpp

HEADERS += \
    mainwindow.h \
    multicast_receiver.h

FORMS +=

INCLUDEPATH += /usr/include
LIBS += -lavformat -lavcodec -lavutil -lswscale