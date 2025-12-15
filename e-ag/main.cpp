/*****************************************************************************
 *   Copyright (C) 2020 by Bayram KARAHAN                                    *
 *   <bayramk@gmail.com>                                                     *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 3 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .          *
 *****************************************************************************/
#include "mainwindow.h"
#include <QApplication>
#include <QString>
#include <QLockFile>
#include <QDir>
#include<pcdata.h>
#include "scdimgserver.h"
#include <QSettings>
#include <QApplication>
#include <QPushButton>
#include <QStyle>
//! [0]
#include <QTranslator>

#define  echo QTextStream(stderr) <<
class QStyle;
int main(int argc, char *argv[])
{
    QString localDir="/usr/share/e-ag/";
    #if defined(Q_OS_WIN)
        localDir="c:/e-ag/";
    #elif defined(Q_OS_LINUX)
        localDir="/usr/share/e-ag/";
    #endif

     QApplication a(argc, argv);
    //return a.exec();
    QString language="";
    QLocale locale;
    QString systemlanguage = locale.name();
    qDebug()<<"Sistem dili:"<<systemlanguage;
    language=systemlanguage;
    int ftpPort=12345;
    QString rootPath="/tmp";
    /***************************************************/
    DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag.json");
    QJsonArray dizi=db->Ara("selectedNetworkProfil",true);
    if(dizi.count()>0)
    {
        for (const QJsonValue &item : dizi) {
            QJsonObject veri=item.toObject();
            //qDebug()<<"Yüklenen Ağ Profili:" <<veri;
            NetProfil np;
            np.networkIndex=veri["networkIndex"].toString();
            np.selectedNetworkProfil=veri["selectedNetworkProfil"].toBool();
            np.networkName=veri["networkName"].toString();
            np.networkTcpPort=veri["networkTcpPort"].toString();
            np.networkBroadCastAddress=veri["networkBroadCastAddress"].toString();
            np.serverAddress=veri["serverAddress"].toString();
            np.ftpPort=veri["ftpPort"].toString();
            np.rootPath=veri["rootPath"].toString();
            np.language=veri["language"].toString();
            np.lockScreenState=veri["lockScreenState"].toBool();
            np.webblockState=veri["webblockState"].toBool();
            language=np.language;
            rootPath=np.rootPath;
            ftpPort=np.ftpPort.toInt();
        }
    }
    /***************************************************/
    QTranslator *translator = new QTranslator();
    translator->load(localDir+"translations/"+language+".qm");
    qApp->installTranslator(translator);

    MainWindow *w=new MainWindow();
    /******************************************************/
    //qDebug()<<"Language:"<<language<<"rootPath:"<<rootPath<<"ftpPort:"<<ftpPort;
    SCDImgServer srv(0,ftpPort,rootPath);

    if (srv.start())
    {

        w->show();
        a.exec();
    }
    delete w;
    return 0;
}
