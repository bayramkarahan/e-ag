#ifndef SCDIMGCLIENT_H
#define SCDIMGCLIENT_H

#include <QObject>
#include <QByteArray>
#include <QTcpSocket>
#include <QDir>

class SCDImgClient : public QTcpSocket
{
  Q_OBJECT

  private:

    enum OperationType   {PUT,GET,DEL};
    enum OperationStatus {WAITINGFORHEADER,WAITINGFORDATA};
    enum CommandStatus   {TS_INACTIVE,TS_PENDING,TS_SUCCESS,TS_ERROR};
    enum TransferMode    {TM_NONE=0,TM_SINGLEFILE=1,TM_MULTIFILE=2};
    enum DownloadStream  {DS_TO_BUFFER,DS_TO_STDOUT,DS_TO_FILE,DS_TO_THUMBNAIL};

    QString host;
    quint16 port;

    int  timeout;

    QString fileName;         // file name to GET/PUT
    QString opFileName;       // last operation file name
    QString sourceFolder;     // source folder path
    QString destFolder;       // destination folder path

    QStringList fList;        // file list
    bool        breakOnError; // break file transfer if an error occurred in multiple file transfer
    int         fIndex;       // current index of file list
    int         errCount;

    QString lastError;

    QByteArray  header;
    QByteArray  buffer;
    QByteArray *fileBuff = Q_NULLPTR;

    int operationType;
    int operationStatus; // used only for GET Operation
    int commandStatus;
    int downloadStream;  // used only for GET command
    int transferMode;

    int filesize;
    int readedBytes;

    // private methods ----------------------------------------

    int putFile();
    int getFile();
    int delFile();

    void sendNext();

    void emitEndSignal(bool emitFinished, QString errMess);

  public:

    SCDImgClient(QString host, quint16 port, int timeout);

    int sendFile(QString fileName, QString destPath);

    int sendFiles(QString folderPath, QString destFolderPath, bool breakOnError);

    int requestFile(QString filePath, bool thumbnail=false, bool stream_to_stdout=false);

    int requestFile(QString filePath, QString destFolderPath, bool thumbnail=false);

    int deleteFile(QString fileName);

    void sendFileBuff(QString filePath, QByteArray *buff);

    QString getLastError();

    QByteArray *receivedFile();

    int success();

    QString getThumbName(QString fileName);

    QString getCurrentFileName();

    void stop();

  public slots:

    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);

    void onReadyRead();

  signals:

    void notifyConnected(QString notifyMess, QString host, quint16 port);  // emitted when client connect
    void notifyDisconnect(bool success, QString notifyMess);               // emitted when client disconnetc

    void notifyError(QString errorString); // emitted when an socket error is raised

    void finished(bool success, QString errMsg);            // emitted when current command execution end

    void deleteFinished(bool success, QString errMsg);      // emitted whenever delete (DEL) command execution end   (on disconnect or socket error)
    void uploadFinished(bool success, QString errMsg);      // emitted whenever upload (PUT) command execution end   (on disconnect or socket error)
    void downloadFinished(bool success, QString errMsg);    // emitted whenever dowmload (GET) command execution end (on disconnect or socket error)
    void downloadFinished(bool success, QString fileName, const QByteArray &rcvBuffer, QString errMsg); // emitted whenever dowmload (GET) command execution end (on disconnect or socket error)

    void fileReceived(QString filePath); // emitted when file data successfully received and bufferized. (socket still opened and before to send data to output stream)
    void fileSaving(QString filePath);   // emitted when received file is about to saving on disk
};

#endif // SCDIMGCLIENT_H
