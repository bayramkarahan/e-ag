/**
 *
 * @brief TCP client demo for SCD Image Server
 *
 *        SCD Image server is a TCP server for fast uploading/downloading of image or binary files
 *
 * @author Ing. Salvatore Cerami - dev.salvatore.cerami@gmail.com
 *
 * @copyright (c) 2019 Ing. Salvatore Cerami - dev.salvatore.cerami@gmail.com - https://github.com/sc-develop/
 *
*/

#include <QCoreApplication>
#include <QDir>
#include <QTextStream>
#include "scdimgclient.h"

#define  echo QTextStream(stderr) <<

/**
 * @brief called when command execution finished
 */
void onFinished(int status, QString errMsg)
{  
   QCoreApplication::exit(!status); // set historical return status value (0: succes, not 0: error);
}

/**
 * @brief onConnect
 * @param mess
 * @param host
 * @param port
 */
void onConnect(QString mess, QString host, quint16 port)
{
   echo mess << endl;
}

/**
 * @brief onDisconnect
 * @param status
 * @param notifyMess
 */
void onDisconnect(bool success, QString notifyMess)
{
   if (success)
   {
      echo "Command: success" << endl;
      echo notifyMess << endl;
   }
   else
   {
      echo "Command: failure" << endl;
      echo "Error: " + notifyMess << endl;
      echo "Connection: closed" << endl;
   }
}

/**
 * @brief onError
 * @param errorString
 */
void onError(QString errorString)
{
   echo "Socket error: " << errorString << endl;
}

/**
 * @brief onFileReceived
 * @param filename
 */
void onFileReceived(QString filename)
{
   echo "File received: " + filename << endl;
}

/**
 * @brief onFileSaving
 * @param filename
 */
void onFileSaving(QString filename)
{
   echo "File saving: " + filename << endl;
}

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);

   echo "\nSC-Develop Image Client v1.0\n";
   echo "Copyright (c) 2019 (MIT) Ing. Salvatore Cerami - dev.salvatore.cerami@gmail.com\n";
   echo "https://github.com/sc-develop - git.sc.develop@gmail.com\n\n";

   if (argc<5)
   {
      echo "Usage scdimgclient <host> <port> <PUT> <file path to transfer> <dest file path>" << endl;           // single file tranfer: send a file to server
      echo "Usage scdimgclient <host> <port> <PUT> <folder path to transfer> <dest file path> -f " << endl;     // multiple file transfer: send a folder to server
      echo "Usage scdimgclient <host> <port> <GET> <remote file path to get> [-file:<file path>] [-T]" << endl; // get a file and save to disk. -T optin download a thumbnail
      echo "Usage scdimgclient <host> <port> <DEL> <remote file path to delete>" << endl;                       // delete a file from server
      return 0;
   }

   QString host     = argv[1];
   QString port     = argv[2];
   QString action   = argv[3];
   QString filePath = argv[4];

   QStringList args = QCoreApplication::arguments().filter("-f");

   bool ok;

   int Port = port.toInt(&ok);

   SCDImgClient imgc(host,Port,10000);

   imgc.connect(&imgc, &SCDImgClient::finished,         onFinished);
   imgc.connect(&imgc, &SCDImgClient::notifyConnected,  onConnect);
   imgc.connect(&imgc, &SCDImgClient::notifyDisconnect, onDisconnect);
   imgc.connect(&imgc, &SCDImgClient::notifyError,      onError);
   imgc.connect(&imgc, &SCDImgClient::fileReceived,     onFileReceived);
   imgc.connect(&imgc, &SCDImgClient::fileSaving,       onFileSaving);

   int ret=0;

   if (action=="PUT")
   {
      if (argc<6)
      {
         echo "<dest file path> required for PUT" << endl;
         echo "Type scdimgclient for help\n" << endl;
         return 0;
      }

      QString destPath = argv[5];

      if (args.count())
      {
         QDir dir(filePath);

         if (dir.exists())
         {
            ret = imgc.sendFiles(filePath,destPath,false);
         }
      }
      else
      {
        ret = imgc.sendFile(filePath,destPath);
      }
   }
   else
   if (action=="GET")
   {
      QString destPath;
      bool    thumbnail = false;

      if (argc>5)
      {
          args = QCoreApplication::arguments().filter("-file:"); // check for -file: option

          if (args.count())
          {
             args = args.at(0).split(':');

             if (args.count()==2)
             {
                destPath = args.at(1); // set destionation path
             }
          }

          args = QCoreApplication::arguments().filter("-T");  // check for -T option

          thumbnail = (args.count()>0); // set thumbnail
      }

      if (destPath.isEmpty())
      {
         ret = imgc.requestFile(filePath,thumbnail,true); // download the file and streams it to stdout
      }
      else
      {
         ret = imgc.requestFile(filePath,destPath,thumbnail); // download the file to dest path
      }
   }
   else
   if (action=="DEL")
   {
      ret = imgc.deleteFile(filePath);
   }

   QString error;

   if (ret)
   {
      ret = !a.exec();
   }
   else
   {
     error = imgc.getLastError();
   }

   switch (ret)
   {
      case 1:
        echo "status: ok\n\n";
      break;

      case 0:

        if (!error.isEmpty())
        {
           echo "Error: " + error << "\n";
        }

        echo "status: ko\n\n";

      break;
   }

   return ret;
}
