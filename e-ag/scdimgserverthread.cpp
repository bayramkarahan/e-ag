/**
 * @class SCDImgServerThread - https://github.com/sc-develop/scd-imgserver
 *
 * @brief SCD Image Server Thread management
 *
 *        This is a this part of SCD Image Server
 *
 * @author Ing. Salvatore Cerami - dev.salvatore.cerami@gmail.com
 *
 * @copyright (c) 2019 (MIT) Ing. Salvatore Cerami - dev.salvatore.cerami@gmail.com - https://github.com/sc-develop/
*/

#include <QHostAddress>
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QImageReader>
#include <QRegularExpression>

#include "scdimgserverthread.h"

/**
 * @brief SCDImgServerThread::SCDImgServerThread constructor
 * @param Id
 * @param parent
 */
SCDImgServerThread::SCDImgServerThread(SCDImgServer *parent, qintptr socketDescriptor): QThread(parent), pserver(parent), socketDescriptor(socketDescriptor)
{

}

/**
 * @brief SCDImgServerThread::run => thread main function
 */
void SCDImgServerThread::run()
{
   qDebug() << "Starting connection thread: " << socketDescriptor;

   QTcpSocket *socket = new QTcpSocket();                            // allocates new socket object (live into a thread memory space)

   QString sockSender = "sock." + QString::number(socketDescriptor); // set name of socket connection

   socket->setObjectName(sockSender);                                // assign socket connection name to socket object

   if (socket->setSocketDescriptor(socketDescriptor))                // set a socket descriptor of new allocated socket object
   {
      SignalsHandler sh(this,socket);

      qDebug() << "Accepted connection from host: " << socketDescriptor
               << " Address: " << socket->peerAddress().toString() << ":" << socket->peerPort();

      exec(); // starts event loop and waits until event loop exits
   }
   else
   {
      qDebug() << "Error: Unable to set socket descriptor " << socket->error();
   }

   delete socket; // explict socket deleting

   qDebug() << "Connection thread end: " << socketDescriptor;
}

/**
 * @brief SCDImgServerThread::server
 * @return
 */
SCDImgServer *SCDImgServerThread::server()
{
   return pserver;
}

/**
 * @class SignalsHandler - https://github.com/sc-develop
 *
 * @brief SCD Signals Handler for server threads, this class manage the signals emitted by
 *        the server thread TCP Socket connection. This class live into thread space, and process
 *        the signal of thread event loop.
 *
 *        This is a this part of SCD Image Server
 *
 * @author Ing. Salvatore Cerami - dev.salvatore.cerami@gmail.com
 *
 * @copyright (c) 2019 Ing. Salvatore Cerami - dev.salvatore.cerami@gmail.com - https://github.com/sc-develop/
*/

/**
 * @brief SignalsHandler::SignalsHandler
 * @param socket
 * @param mc
 */
SignalsHandler::SignalsHandler(SCDImgServerThread *parent, QTcpSocket *socket): parent(parent), socket(socket)
{
   commands.insert(GET, "GET");
   commands.insert(PUT, "PUT");
   commands.insert(DEL, "DEL");

   connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
   connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
   connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onSocketError(QAbstractSocket::SocketError)));

   status = WAITFORHEADER;

   maxHeaderSize = 1024;

   rootPath = parent->server()->getRootPath();
}

/**
 * @brief SignalsHandler::lastError
 * @return
 */
QString SignalsHandler::lastError()
{
   return lastErrorMsg;
}

/**
 * @brief SignalsHandler::getHeader return packet header
 * @return
 */
QMap<QString, QVariant> SignalsHandler::getHeader()
{
   return header;
}

/**
 * @brief SignalsHandler::readyRead read data if available
 */
void SignalsHandler::readyRead()
{
   int ret = 0;

   Command command;

   switch (status)
   {
      case WAITFORHEADER:

        if (readHeader(command))
        {
           if (fileName.startsWith('/'))  // check path syntax
           {
              fileName = rootPath + fileName.remove(0,1);

              switch (command)
              {
                 case GET: // GET command received: downloading file to client

                   qDebug() << "GET: " + fileName;

                   if (thumbnail)
                   {
                      ret = sendThumbnail(fileName);
                   }
                   else
                   {
                      ret = sendFile(fileName); // send a file to client
                   }

                   if (ret>0)
                   {
                      socket->disconnectFromHost();

                      return; // success
                   }

                 break;

                 case DEL: // DEL command received: deleting file from server

                   qDebug() << "DEl: " + fileName;

                   ret = delFile(fileName); // delete a specified file

                   if (ret)
                   {
                      socket->write("ok"); // sends confirm to client: client will close connection.
                      socket->flush();
                      socket->disconnectFromHost();

                      return; // success
                   }

                 break;

                 case PUT: // PUT command found: uploading file to server

                   qDebug() << "PUT: " + fileName;

                   ret = fileReceivingPrepare(fileName); // preparing for file receiving

                   if (ret)
                   {
                      ret = readData(); // read remainign availaible data

                      if (ret==1) // buffer not entirely received: change status to WAITFORDATA
                      {
                         status = WAITFORDATA;
                      }

                      return; // success
                   }

                 break;
              }              
           }
           else
           {
              ret = 0;

              lastErrorMsg = "remote file path must start with '/'";
           }           
        }

      break;

      case WAITFORDATA: // receiving remainig data...

        if (readData()>0)
        {
           return;
        }

      break;
   }

   // on error ---------------------------------------

   qDebug() << lastErrorMsg;

   switch (ret)
   {
      case 0:
        socket->write(lastErrorMsg.toLatin1()+"\n");
        socket->flush();
        thread()->usleep(500);
        socket->close();
      break;

      case -1: // socket error (sendFile() can return -1 on socket write error)
        socket->abort(); // due to socket error do not writes on socket and abort
      break;
   }
}

/**
 * @brief SignalsHandler::disconnected exit from event thread loop (thread end)
 */
void SignalsHandler::disconnected()
{
   qDebug() << "Client disconnected: " << socket->objectName();

   thread()->quit(); // exit from thread event loop
}

/**
 * @brief SignalsHandler::onSocketError
 */
void SignalsHandler::onSocketError(QAbstractSocket::SocketError error)
{
   qDebug() << error << socket->errorString();

   if (f.isOpen())
   {
      f.close();
      f.remove();
   }

   socket->abort();
}

/**
 * @brief SignalsHandler::checkField split header intem anf get field name and valu,
 *                                   if field name match fieldName param add it to header map and return 1
 *                                   else return 0;
 * @param headerItem header item in format <field name>:<value>
 * @param fieldName
 * @return 1 on success, 0 un failure
 */
int SignalsHandler::checkHeaderField(const QString &headerItem, const QString &fieldName)
{
   QStringList field = headerItem.split(":"); // split into field name and value pair

   if (field.size() != 2)
   {
      lastErrorMsg = "Bad header item: " + headerItem;
      return 0;
   }

   QString name = field.at(0).trimmed();

   if (name==fieldName)
   {
       header.insert(name,field.at(1).trimmed());
       return 1;
   }

   lastErrorMsg = "Bad header field name: " + headerItem;

   return 0;
}

/**
 * @brief SCDTopicServer::checkHeaderField
 * @param headerItem
 * @param cmd
 * @return
 */
int SignalsHandler::checkHeaderField(const QString &headerItem, Command &cmd)
{
    QStringList field = headerItem.split(":"); // split into field name and value pair

    if (field.size() != 2)
    {
       lastErrorMsg = "Bad header item: " + headerItem;
       return 0;
    }

    QString name = field.at(0).trimmed();

    int index = commands.indexOf(QRegularExpression(name));

    if (index>-1)
    {
       header.insert(name,field.at(1).trimmed());

       cmd = static_cast<enum Command>(index);

       return 1;
    }

    lastErrorMsg = "Unknown header field: " + name;

    return 0;
}

/**
 * @brief SignalsHandler::readHeader read headers lines and fill header map.
 *        Call this method only when statu=WAITFORHEADER.
 *        when header read is complete the stustus change to WAITFORDATA.
 *        on error return 0, otherwise return 1.
 *        Do not use the sequence '|' (sharp) char into complete file path
 *
 *        SCDFTH (one line fast header struct)
 *
 *          PUT command => SCDFTH:1.0\tPUT:<complete file path>\t<FILESIZE>\n<FILESIZE DATA BYTES>
 *          GET command => SCDFTH:1.0\tGET:<complete file path>\n          // download a file
 *          GET command => SCDFTH:1.0\tGET:<complete file path>\tT\n       // get a thumbnail
 *          DEL command => SCDFTH:1.0\tDEL:<complete file path>\n          // delete a file
  *
 *          See SCD Image Client to send a command to server
 *
 *          PUT command upload a binary file to server into a specified path
 *          GET command download a binary file from a specified path
 *          DEL command delete the specified file from server
 *
 * @return 1 on success, 0 on failure
 *
 */
int SignalsHandler::readHeader(Command &command)
{
   QByteArray row;

   row = socket->readLine(maxHeaderSize);

   if (row.size()==0)
   {
      lastErrorMsg = "Null header line";
      return -1;   // socket error
   }

   QString head = QString::fromLatin1(row);

   QStringList fields = head.split("\t",QString::SkipEmptyParts);

   if (fields.size()<2) // header must have at least two elements
   {
      lastErrorMsg = "Invalid header: " + head;
      return 0;
   }

   if (checkHeaderField(fields.at(0),"SCDFTH"))   // first item must be header type declaration
   { 
      if (checkHeaderField(fields.at(1),command)) // get the command
      {
         switch (command)
         {
            case PUT:

              if (fields.size()==3)
              {
                 fileSize = fields.at(2).toInt();

                 if (fileSize>0)
                 {
                    fileName = header[commands[command]].toString();

                    return 1;
                 }
              }
              else
              {
                 lastErrorMsg = "Invalid header: " + head;
              }

            break;

            case GET:

              fileName = header[commands[command]].toString();

              if (fields.size()==3)
              {
                 if (fields.at(2).trimmed()=="T")
                 {
                    thumbnail = true;
                 }
                 else
                 {
                    lastErrorMsg = "Invalid header: " + head;
                    return 0;
                 }
              }
              else
              {
                 thumbnail = false;
              }

            return 1;

            case DEL:

              fileName = header[commands[command]].toString();

            return 1;
         }
      }
   }

   return 0;  // failure
}

/**
 * @brief SignalsHandler::fileReceivingPrepare
 * @return
 */
int SignalsHandler::fileReceivingPrepare(QString fileName)
{
   QDir dir = QFileInfo(fileName).absoluteDir();

   // Create destionation file path if not exists -----------------------------

   if (!dir.mkpath(dir.absolutePath()))
   {
      lastErrorMsg = "Create dir failure: " + dir.absolutePath();
      return 0;
   }

   // remove file if already existing -----------------------------------------

   if (QFile::exists(fileName))
   {
      if (!QFile::remove(fileName))
      {
         lastErrorMsg = "Removing existing file failure: " + fileName;
         return 0;
      }
   }

   // open destionation file for (create/append)--------------------------------

   QString tmpFile = dir.absolutePath() + "/" + QFileInfo(fileName).completeBaseName() + ".tmp";

   f.setFileName(tmpFile);

   if (f.open(QIODevice::WriteOnly))
   {
      readedBytes = 0;
      return 1;
   }

   lastErrorMsg = "open file error: " + f.fileName() + " => " + f.errorString();
   return 0;
}

/**
 * @brief SignalsHandler::readData
 */
int SignalsHandler::readData()
{
   QByteArray buff = socket->readAll(); // read all available data from socket connection

   readedBytes += buff.size();   

   if (f.write(buff)!=-1)    // file writing success
   {
      if (readedBytes>=fileSize) // if file is entirely readed close file
      {
         f.close();

         if (f.rename(fileName))
         {
            socket->write("ok");          // sends confirm to client: client will close connection.
            socket->flush();
            socket->disconnectFromHost(); // close connection

            return 2; // file entirely received
         }
         else
         {
            f.remove(); // delete file

            lastErrorMsg = "Rename file error: " + f.fileName() + " => " + f.errorString();

            return 0;
         }
      }

      return 1; // success buffer received
   }

   // on write error ----------------------------------------------------------

   f.close();  // close file
   f.remove(); // delete file

   lastErrorMsg = "write file error: " + f.fileName() + " => " + f.errorString();

   return 0;
}

/**
 * @brief SignalsHandler::sendFile
 * @return
 */
int SignalsHandler::sendFile(QString fileName)
{
   if (!QFile::exists(fileName))
   {
      lastErrorMsg = "File not exists: " + fileName;
      return 0; // system file error
   }

   QFile f(fileName);

   // send file to client -----------------------------

   if (!f.open(QIODevice::ReadOnly))
   {
      lastErrorMsg = "Open file error: " + fileName;
      return 0; // system file error
   }

   // Get file size ----------------------------------

   int size = f.size();

   QByteArray buff = QByteArray::number(size);

   buff.append("\n");

   // write header ------------------------------------

   if (socket->write(buff.constData(),buff.size())==-1)
   {
      lastErrorMsg = "Write error";
      return -1; // socket error
   }

   buff = f.readAll(); //read file

   if (buff.size()==0)
   {
      f.close();
      lastErrorMsg = "Read file error: " + fileName;
      return 0; // system file error
   }

   if (socket->write(buff.constData(),buff.size())==-1)
   {
      f.close();
      lastErrorMsg = "Socket write error";
      return -1; // socket error
   }

   f.close();

   return 1;
}

/**
 * @brief SignalsHandler::delFile
 * @return
 */
int SignalsHandler::delFile(QString fileName)
{
   QFile f(fileName);

   if (!f.remove())
   {
      lastErrorMsg = "Delete file error: " + fileName + " => " + f.errorString();
      return 0; // system file error
   }

   return 1;
}

/**
 * @brief SignalsHandler::makeThumbnail make a thumbanil from image file filename, if already exists it will not be re-generated
 * @param fileName  name of file from which the thumbnail will be generated
 * @param thumbName output params file name of tuhmbnail generated thumbnail name has PNG extension
 * @return
 */
int SignalsHandler::makeThumbnail(QString fileName, QString &thumbName)
{
   thumbName = getThumbName(fileName);

   if (!QFile::exists(thumbName)) // if thumbnai not exists
   {
      QImageReader imgr;

      imgr.setDecideFormatFromContent(true);
      imgr.setScaledSize(QSize(100,25));
      imgr.setFileName(fileName);

      QByteArray format = imgr.format();

      QImage img;

      if (img.load(fileName,format.constData())) // load image file name
      {
         QImage thumbnail = img.scaled(100,75,Qt::IgnoreAspectRatio,Qt::SmoothTransformation); // make thumbnail

         if (thumbnail.save(thumbName,"png")) // save thumbnail to file in format PNG
         {
            return 1; // return success
         }

         lastErrorMsg = "Save thumbail error: " + thumbName;
      }
      else
      {
         lastErrorMsg = "loading image file error: " + fileName;
      }

      return 0;
   }

   return 1; // success: thumbnail already exists
}

/**
 * @brief SignalsHandler::sendThumbnail
 * @param fileName
 * @return
 */
int SignalsHandler::sendThumbnail(QString fileName)
{
   QString thumbnail;

   if (makeThumbnail(fileName,thumbnail))
   {
      return sendFile(thumbnail);
   }

   return 0;
}

/**
 * @brief SignalsHandler::getThumbName get thumnail file name path: by default extension is png
 * @param fileName
 * @return
 */
QString SignalsHandler::getThumbName(QString fileName)
{
   QFileInfo fi(fileName);

   return fi.absoluteDir().absolutePath() + "/" + fi.completeBaseName() + ".tmb.png";
}
