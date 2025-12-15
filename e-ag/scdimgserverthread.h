#ifndef SCDIMGSERVERTHREAD_H
#define SCDIMGSERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QByteArray>
#include <QFile>

#include "scdimgserver.h"

/**
 * @brief The SCDImgServerThread class
 */
class SCDImgServerThread : public QThread
{
   Q_OBJECT

   public:

     explicit SCDImgServerThread(SCDImgServer *parent = 0, qintptr socketDescriptor=-1);

     void run(); // thread execution

     qintptr getSocketDescriptor() {return socketDescriptor;}

     SCDImgServer *server();

   private:

     SCDImgServer *pserver;

     qintptr socketDescriptor; // descriptor(handle) of current socket
};

/**
 * @brief The SignalsHandler class
 */
class SignalsHandler : public QObject
{
   Q_OBJECT

   public:

     explicit SignalsHandler(SCDImgServerThread *parent=0, QTcpSocket *socket=0);

     QString lastError();

     QMap <QString,QVariant> getHeader();

   signals:

   private slots:

     void readyRead();
     void disconnected();
     void onSocketError(QAbstractSocket::SocketError error);

   private:

     enum Status  {WAITFORHEADER,WAITFORDATA,DATASEND,DELETE};
     enum Command {GET=0,PUT=1,DEL=2};

     int status;          // current reading status

     SCDImgServerThread *parent;
     QTcpSocket         *socket;  // current connection socket

     QString rootPath;
     QStringList commands;

     QFile f;

     QString fileName;
     QString lastErrorMsg;

     QMap <QString,QVariant> header; // current header entries readed

     int  maxHeaderSize;
     int  readedBytes;
     int  fileSize;
     bool thumbnail;

     int checkHeaderField(const QString &headerItem, const QString &fieldName);
     int checkHeaderField(const QString &headerItem, Command &cmd);
     int readHeader(Command &command);
     int fileReceivingPrepare(QString fileName);
     int readData();
     int sendFile(QString fileName);
     int delFile(QString fileName);
     int makeThumbnail(QString fileName, QString &thumbName);
     int sendThumbnail(QString fileName);

     QString getThumbName(QString fileName);
};

#endif // SCDIMGSERVERTHREAD_H
