#include "filetransferclient.h"
#include <QDebug>

FileTransferClient::FileTransferClient(QString host,
                                       quint16 port,
                                       QObject *parent)
    : QObject(parent)
{
    client = new SCDImgClient(host, port, 10000, this);
    //client = new SCDImgClient(host, port);

        connect(client, &SCDImgClient::finished,
                this, &FileTransferClient::onFinished);

    connect(client, &SCDImgClient::notifyError,
            this, &FileTransferClient::onError);


}

void FileTransferClient::uploadFile(QString localFile, QString remoteFile)
{
    client->sendFile(localFile, remoteFile);
}

void FileTransferClient::downloadFile(QString remoteFile, QString localFolder)
{
    client->requestFile(remoteFile, localFolder, false);
}

void FileTransferClient::deleteFile(QString remoteFile)
{
    client->deleteFile(remoteFile);
}

void FileTransferClient::onFinished(bool success, QString error)
{
    if(success)
        emit finished(true, "Transfer completed");
    else
        emit finished(false, error);
}

void FileTransferClient::onError(QString err)
{
    qDebug() << "Socket error:" << err;
}
