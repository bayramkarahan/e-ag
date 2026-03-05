#ifndef FILETRANSFERCLIENT_H
#define FILETRANSFERCLIENT_H

#include <QObject>
#include "scdimgclient.h"

class FileTransferClient : public QObject
{
    Q_OBJECT

public:
    explicit FileTransferClient(QString host,
                                quint16 port,
                                QObject *parent = nullptr);


        void uploadFile(QString localFile, QString remoteFile);
    void downloadFile(QString remoteFile, QString localFolder);
    void deleteFile(QString remoteFile);


        signals:
                  void finished(bool success, QString message);

private slots:
    void onFinished(bool success, QString error);
    void onError(QString err);

private:
    SCDImgClient *client;
};

#endif
