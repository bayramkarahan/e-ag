#ifndef SCDIMGSERVER_H
#define SCDIMGSERVER_H

#include <QTcpServer>

class SCDImgServer : public QTcpServer
{
   Q_OBJECT

   private:

     int port;
     QString rootPath;
     QString lastErrorMsg;

   public:

     explicit SCDImgServer(QObject *parent = 0, int port=12345, QString rootPath="./");

     int start(); // Start tcp server for incoming connections

     QString lastError();

     QString getRootPath();

   signals:

   public slots:

     void threadDestroyed(QObject *obj);

   protected:

     void incomingConnection(qintptr SocketDescriptor);

};

#endif // SCDIMGSERVER_H
