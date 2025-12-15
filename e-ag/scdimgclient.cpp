/**
 * @class  SCDImgClient
 *
 * @brief TCP Client for SCD Image Server
 *
 *        SCD Image server is a TCP server for fast uploading/downloading of image or binary files
 *
 * @author Ing. Salvatore Cerami - dev.salvatore.cerami@gmail.com
 *
 * @copyright (c) 2019 Ing. Salvatore Cerami - dev.salvatore.cerami@gmail.com - https://github.com/sc-develop/
 *
*/

#include <QDebug>
#include <QThread>
#include <QFile>
#include <QCoreApplication>
#include <QDir>

#include "scdimgclient.h"

/**
 * @brief SCDImgClient::SCDImgClient
 * @param Host
 * @param Port
 * @param Timeout
 */
SCDImgClient::SCDImgClient(QString host, quint16 port, int timeout=0) : host(host),port(port),timeout(timeout)
{
   connect(this, SIGNAL(connected())                        , this, SLOT(onConnected()));
   connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
   connect(this, SIGNAL(disconnected())                     , this, SLOT(onDisconnected()));
   connect(this, SIGNAL(readyRead())                        , this, SLOT(onReadyRead()));

   commandStatus = TS_INACTIVE;
   transferMode  = TM_NONE;
}

/**
 * @brief SCDImgClient::putFile
 * @return
 */
int SCDImgClient::putFile()
{
   if (write(header.constData(),header.size())==-1)
   {
      lastError = "Write file header error!";
      return 0;
   }

   if (write(fileBuff->constData(),fileBuff->size())==-1)
   {
      lastError = "Write file error!";
      return 0;
   }

   return 1;
}

/**
 * @brief SCDImgClient::getFile
 * @return
 */
int SCDImgClient::getFile()
{
   if (write(header.constData(),header.size())==-1)
   {
      lastError = "Socket write error: " + header;
      return 0;
   }

   operationStatus = WAITINGFORHEADER;

   buffer.clear();

   readedBytes = 0;

   return 1;
}

/**
 * @brief SCDImgClient::delFile
 * @return
 */
int SCDImgClient::delFile()
{
   if (write(header.constData(),header.size())==-1)
   {
      lastError = "Socket write error: " + header;
      return 0;
   }

   return 1;
}

/**
 * @brief SCDImgClient::emitEndSignal
 */
void SCDImgClient::emitEndSignal(bool emitFinished, QString errMess)
{
   bool success = this->success();

   switch (operationType)
   {
      case PUT:
        emit uploadFinished(success, errMess);
      break;

      case GET:
        emit downloadFinished(success, errMess);
        emit downloadFinished(success, fileName, buffer, errMess);
      break;

      case DEL:
        emit deleteFinished(success, errMess);
      break;
   }

   if (emitFinished)
   {
      emit finished(success, errMess);
   }
}

/**
 * @brief SCDImgClient::sendFile
 * @param fileName
 */
int SCDImgClient::sendFile(QString fileName, QString destPath)
{
   commandStatus = TS_INACTIVE;

   if (!QFile::exists(fileName))
   {
      lastError = "File not found: " + fileName;
      return 0;
   }

   QFile f(fileName);

   if (!f.open(QIODevice::ReadOnly))
   {
      lastError = "Open File Error: " + fileName + " => " + f.errorString();
      return 0;
   }

   buffer = f.readAll();

   if (buffer.size()==0)
   {
      lastError = "Error to read file: " + fileName + " => " + f.errorString();
      return 0;
   }

   f.close();

   sendFileBuff(destPath, &buffer);

   return 1;
}

/**
 * @brief SCDImgClient::sendFiles send all files of a folder.
 * @param folderPath     => path of folder containig all files to send
 * @param destFolderPath => server destination folder
 * @return
 */
int SCDImgClient::sendFiles(QString folderPath, QString destFolder, bool breakOnError)
{
   fList = QDir(folderPath).entryList(QDir::Files,QDir::Name);

   sourceFolder = folderPath;

   this->destFolder = destFolder;

   if (fList.count())
   {
      errCount = 0;
      fIndex   = 0;
      transferMode = TM_MULTIFILE;

      this->breakOnError = breakOnError;

      return sendFile(sourceFolder + fList.at(fIndex), destFolder+fList.at(fIndex));
   }

   lastError = "No files found";

   return 0;
}

/**
 * @brief SCDImgClient::requestFile
 * @param filePath
 * @return
 */
int SCDImgClient::requestFile(QString filePath, QString destFolderPath, bool thumbnail)
{
   fileName       = filePath;
   opFileName     = fileName;
   destFolder     = destFolderPath;
   operationType  = GET;
   commandStatus  = TS_PENDING;
   transferMode   = TM_SINGLEFILE;
   downloadStream = thumbnail ? DS_TO_THUMBNAIL : DS_TO_FILE;

   QString thumbOption = thumbnail ? "\tT" : "";

   header.clear();
   header.append("SCDFTH:1.0\tGET:"+fileName+thumbOption+"\n");
   
   connectToHost(host, port, QIODevice::ReadWrite);

   return 1;
}

/**
 * @brief SCDImgClient::requestFile download the file and bufferize it. if stream_to_stdout is set streams it to stdout
 * @param filePath
 * @param stream_to_stdout
 * @return
 */
int SCDImgClient::requestFile(QString filePath, bool thumbnail, bool stream_to_stdout)
{
   fileName       = filePath;
   opFileName     = fileName;
   operationType  = GET;
   commandStatus  = TS_PENDING;
   transferMode   = TM_SINGLEFILE;
   downloadStream = stream_to_stdout ? DS_TO_STDOUT : DS_TO_BUFFER;

   QString thumbOption = thumbnail ? "\tT" : "";

   header.clear();
   header.append("SCDFTH:1.0\tGET:"+fileName+thumbOption+"\n");

   connectToHost(host, port, QIODevice::ReadWrite);

   return 1;
}

/**
 * @brief SCDImgClient::deleteFile
 * @param fileName
 * @return
 */
int SCDImgClient::deleteFile(QString fileName)
{
   opFileName    = fileName;
   operationType = DEL;
   commandStatus = TS_PENDING;
   transferMode  = TM_SINGLEFILE;

   header.clear();
   header.append("SCDFTH:1.0\tDEL:"+fileName+"\n");

   connectToHost(host, port, QIODevice::ReadWrite);

   return 1;
}

/**
 * @brief SCDImgClient::sendFileBuff
 * @param filePath
 */
void SCDImgClient::sendFileBuff(QString filePath, QByteArray *buff)
{
   fileName      = filePath;
   opFileName    = fileName;
   fileBuff      = buff;
   operationType = PUT;
   commandStatus = TS_PENDING;
   transferMode  = (transferMode != TM_MULTIFILE) ? TM_SINGLEFILE : transferMode;

   header.clear();
   header.append("SCDFTH:1.0\tPUT:"+fileName+"\t"+QString::number(buff->size())+"\n");

   connectToHost(host, port, QIODevice::ReadWrite);
}

/**
 * @brief SCDImgClient::getLastError
 * @return
 */
QString SCDImgClient::getLastError()
{
   return lastError;
}

/**
 * @brief SCDImgClient::receivedFile
 * @return
 */
QByteArray *SCDImgClient::receivedFile()
{
    return &buffer;
}

/**
 * @brief SCDImgClient::success return true if commandStatus == TS_SUCCESS.
 *                              You can call this method after disconnection to check command execution result.
 * @return
 */
int SCDImgClient::success()
{
   return (commandStatus==TS_SUCCESS);
}

/**
 * @brief SCDImgClient::onConnected
 */
void SCDImgClient::onConnected()
{
   lastError.clear();

   QString mess = "Connected to: " + host + ":" + QString::number(port);

   emit notifyConnected(mess, host, port);

   int ret;

   switch (operationType)
   {
      case PUT:
      {
         ret = putFile();
      }
      break;

      case GET:
      {
         ret = getFile();         
      }
      break;

      case DEL:
      {
         ret = delFile();
      }
      break;
   }

   if (!ret)
   {
      commandStatus = TS_ERROR;

      abort();
   }
}

/**
 * @brief SCDImgClient::onDisconnected
 */
void SCDImgClient::onDisconnected()
{
   QString mess = "Connection: closed";

   if (commandStatus==TS_ERROR)
   {
      mess = lastError;
   }

   emit notifyDisconnect(success(),mess.trimmed());

   emitEndSignal(transferMode != TM_MULTIFILE, lastError); // finish signal is self emitted by sendNext()

   if (transferMode == TM_MULTIFILE)
   {
      sendNext();
   }   
}

/**
 * @brief SCDImgClient::onError
 * @param socketError
 */
void SCDImgClient::onError(QAbstractSocket::SocketError socketError)
{
   emit notifyError("Socket error (" + QString::number(socketError) + ") : " + errorString());

   commandStatus = TS_ERROR;

   QAbstractSocket::SocketState socketState = state();

   if (socketState==QAbstractSocket::UnconnectedState)
   {
       emitEndSignal(transferMode!=TM_MULTIFILE,lastError); // finish signal is self emitted by sendNext()

       if (transferMode==TM_MULTIFILE)
       {
          sendNext(); // send the next file of list
       }
   }
   else
   {
      // disconnectFromHost();
   }
}

/**
 * @brief SCDImgClient::onReadyRead
 */
void SCDImgClient::onReadyRead()
{
   switch (operationType)
   {
      case DEL:  // server response to DEL command
      case PUT:  // server response to PUT command
      {
         QByteArray buff = readAll();

         if (buff.trimmed()=="ok")
         {
            commandStatus = TS_SUCCESS;           
            disconnectFromHost();
         }
         else
         {
            lastError = buff;
            commandStatus = TS_ERROR;
            abort();
         }
      }
      return;

      case GET: // server response to GET command
      {
         switch(operationStatus)
         {
            case WAITINGFORHEADER:  // read header
            {
               QByteArray buff = readLine(256);

               bool ok;

               filesize = QString(buff).trimmed().toInt(&ok);

               if (ok)
               {
                  operationStatus = WAITINGFORDATA;
               }
               else
               {
                  lastError = buff;

                  commandStatus = TS_ERROR;

                  abort();

                  break;
               }
            }

            case WAITINGFORDATA:  // read data (file sent from server)
            {
               buffer += readAll();

               if (buffer.size()>=filesize)
               {
                  emit fileReceived(fileName);

                  switch(downloadStream)
                  {
                     case DS_TO_STDOUT: // write output to stdout

                       fwrite(buffer.constData(),1,static_cast<size_t>(buffer.size()),stdout);

                     case DS_TO_BUFFER:

                       commandStatus = TS_SUCCESS;

                       disconnectFromHost();

                     return;

                     case DS_TO_THUMBNAIL:
                     case DS_TO_FILE:   // write output to file
                     {
                        if (downloadStream==DS_TO_THUMBNAIL)
                        {
                           fileName = getThumbName(fileName);
                        }

                        QFileInfo fi(fileName);

                        QDir dir(destFolder);

                        if (dir.mkpath(dir.absolutePath()))
                        {
                           QString filePath = dir.absolutePath() + "/" + fi.fileName();

                           QFile f(filePath);

                           emit fileSaving(filePath);

                           if (f.open(QIODevice::WriteOnly))
                           {
                              qint64 ret = f.write(buffer);

                              f.close();

                              if (ret>0)
                              {
                                 commandStatus = TS_SUCCESS;                      

                                 disconnectFromHost();

                                 return;
                              }
                              else
                              {
                                 lastError = "Write file error: " + fileName + " => " + f.errorString();
                              }
                           }
                           else
                           {
                              lastError = "Open file error: " + fileName + " => " + f.errorString();
                           }
                        }
                        else
                        {
                           lastError = "Make dir error: " + dir.absolutePath();
                        }
                     }
                     break;
                  }

                  commandStatus = TS_ERROR;

                  abort();
               }
            }
            break;
         }
      }
      break;
   }
}

/**
 * @brief SCDImgClient::onSendNext send next file of list on end of list emits finished signal
 */
void SCDImgClient::sendNext()
{
   if (transferMode != TM_MULTIFILE)
   {
      return;
   }

   if (commandStatus!=TS_SUCCESS)
   {
      errCount++; // increase error count in multiple file transfer

      if (breakOnError)
      {
         transferMode = TM_NONE;
         return;
      }
   }

   fIndex++;

   if (fIndex<fList.count())
   {
      sendFile(sourceFolder + fList.at(fIndex), destFolder+fList.at(fIndex));
   }
   else
   {
      transferMode = TM_NONE;

      emit finished(errCount==0, "Some files has not been transferred: " + QString::number(errCount));
   }
}

/**
 * @brief SignalsHandler::getThumbName
 * @param fileName
 * @return
 */
QString SCDImgClient::getThumbName(QString fileName)
{
   QFileInfo fi(fileName);

   return fi.absoluteDir().absolutePath() + "/" + fi.completeBaseName() + ".tmb.png";
}

/**
 * @brief SCDImgClient::getCurrentFileName return the name of file involved
 *                                         in the last operation requested to server (GET/PUT/DEL)
 * @return
 */
QString SCDImgClient::getCurrentFileName()
{
   return opFileName;
}

/**
 * @brief SCDImgClient::stop
 */
void SCDImgClient::stop()
{
   abort();
}
