/**
 * @class  SCDImgServer - https://github.com/sc-develop/scd-imgserver
 *
 * @copyright (c) 2019
 *
 * @brief SCD Image Server. SCD Image sever is a TCP server for fast downoad/upload image or binary files.
 *
 * @author Ing. Salvatore Cerami - dev.salvatore.cerami@gmail.com
 *
 * @copyright (c) 2019 (MIT) Ing. Salvatore Cerami - dev.salvatore.cerami@gmail.com - https://github.com/sc-develop/
 *
*/

#include "scdimgserver.h"
#include "scdimgserverthread.h"

/**
 * @brief SCDImgServer::SCDImgServer constructor
 * @param parent
 */
SCDImgServer::SCDImgServer(QObject *parent, int port, QString rootPath) : QTcpServer(parent), port(port), rootPath(rootPath)
{

}

/**
 * @brief SCDImgServer::start start SCDImg server
 */
int SCDImgServer::start()
{
   if (!QFile::exists(rootPath))
   {
      lastErrorMsg = "Root path not exixst\n";
      qDebug() << lastError();
      return 0;
   }

   if (listen(QHostAddress::Any,port))
   {
      lastErrorMsg = "Dosya Transfer server dinleme modunda :" + QString::number(port) + " portundan bağlantı yapılabilir...";
      qDebug() <<  lastError();
      return 1;
   }

   lastErrorMsg = "Unable to start server on port:" + QString::number(port) + this->errorString();

   qDebug() << lastErrorMsg;

   return 0;
}

/**
 * @brief SCDImgServer::lastError
 * @return
 */
QString SCDImgServer::lastError()
{
   return lastErrorMsg;
}

/**
 * @brief SCDImgServer::getRootPath
 * @return
 */
QString SCDImgServer::getRootPath()
{
   return rootPath;
}

/**
 * @brief SCDImgServer::threadDestroyed handle signal threadDestroyed emit when client thared is destroyed
 * @param obj
 */
void SCDImgServer::threadDestroyed(QObject *obj)
{
   SCDImgServerThread *thd = (SCDImgServerThread*) obj;

   QString msg;

   QTextStream mess(&msg);

   mess << "Thread destroyed ID: " << thd->getSocketDescriptor();
}

/**
 * @brief SCDImgServer::incomingConnection
 * @param SocketDescriptor
 */
void SCDImgServer::incomingConnection(qintptr socketDescriptor)
{
   qDebug() << "New socket connection: " << socketDescriptor;

   SCDImgServerThread *sckThread = new SCDImgServerThread(this,socketDescriptor);

   connect(sckThread, SIGNAL(finished())         , sckThread , SLOT(deleteLater()));
   connect(sckThread, SIGNAL(destroyed(QObject*)), this      , SLOT(threadDestroyed(QObject*)));

   sckThread->start();
}
