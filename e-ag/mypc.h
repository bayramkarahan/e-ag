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
#ifndef MYPC_H
#define MYPC_H

#include <QWidget>
#include<QLabel>
#include<QToolButton>
#include<QPushButton>
#include <QTimer>
#include<QCheckBox>
#include<QWidgetAction>
#include<QObject>
#include<QDesktopWidget>
#include<QScreen>
#include<pcdata.h>
#include<QDesktopServices>
#include<QMediaPlayer>
#include<QVideoWidget>
#include<Database.h>
#include <QCoreApplication>
#include<VideoPlayer.h>
#include<multicast_receiver.h>
#include<QSvgRenderer>
#include<QPainter>
#include <QStyle>
class NetProfil
{
public:

    QString networkIndex;
    bool selectedNetworkProfil;
    QString networkName;
    QString serverAddress;
    QString networkBroadCastAddress;
    QString subnet;
    QString networkTcpPort;
    QString ftpPort;
    QString rootPath;
    QString language;
    QString multicastAddress;
    bool lockScreenState;
    bool webblockState;
};
class MyPc: public QWidget
{
    Q_OBJECT
public:
    explicit MyPc(const QString _mac, QString _ip, QWidget *parent = nullptr);
    ~MyPc();
    enum { Type =  20 };

        int type()
        {
            // Enable the use of qgraphicsitem_cast with this item.
            return Type;
        }
            qint64 vncviwerpid=0;
        QLabel *selectLabel;
        bool iconState=false;
        bool iconControlState=false;
        //bool pcState;
        QString sshState;
        QString vncState;
        QString xrdpState;
        bool volumeState=true;
        bool keyboardState=true;
        bool mouseState=true;
        bool internetState=true;
        bool webblockState=true;
        bool youtubeState=true;

        bool connectState=false;
        bool kilitState=false;
        bool kilitControlState=false;
        bool transparanKilitState=false;
        bool transparanKilitControlState=false;
        int tcpConnectCounter=0;
        bool pcScreenViewSignalState=false;
        QString font="12";
        QString mac;
        QString ip;
        QString user;
        QString hostname;
        QString groupname;
        QString version;

        QString caption;
        bool visibleState=true;
        bool hostnameVisible = true;
        QString command="";
        QString commandDetail="";
        QString commandState="";

        QString vncport=0;
        bool select;
        bool multiSelect;
        NetProfil netProfil;
protected:
void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:
void pcDoubleClickSignal(QString mac);
void pcClickSignal(QString mac);
void pcRightClickSignal();
void pcListeSignal();
void pcHideSignal(QString _mac);
void pcSettingUpdateSignal(QString _mac,QString mission);
void pcCloseSignal(QString ip,QString mac);
void pcScreenViewSignal(QString mac,QString ip);
/*void pcListeStateSignal();
void pcTcpPortControlSignal(QString mac,QString ip);
void pcSshPortControlSignal(QString mac,QString ip);
void pcVncPortControlSignal(QString mac,QString ip);
void pcXrdpPortControlSignal(QString mac,QString ip);
void pcKilitStateControlSignal(QString mac,QString ip,bool _kilitstate);
void pcKilitTransparanStateControlSignal(QString mac,QString ip,bool _transparankilitstate);
void pcIconStateControlSignal(QString mac,QString ip,bool _iconstate);
*/
void pcMenuSignal(QString mac,QString ip,QString _slot);

public slots:
void setSize(int _w, int _h, QString _font);
//void setCaption(QString cap);
//void setDisplay(QString _dis);
void setUser(QString _os);
void setHostname(QString _hostname);
//void setAcount(QString username, QString password);
void setKilitState(bool state);
void setKilitTransparanState(bool state);
void setIconControlState(bool state);
void timertcpConnectControlSlot();
void setConnectState(bool state);
void setCommandButonState(bool state);
void setSshState(QString state);
void setVncState(QString state);
void setXrdpState(QString state);
void setVersionState(QString state);
void setVolumeState(bool state);
void setKeyboardState(bool state);
void setMouseState(bool state);
void setInternetState(bool state);
void setWebblockState(bool state);
void setYoutubeState(bool state);


void setCommandState(QString _command,QString _commandDetail,QString _commandState);
void slotMouseClick();
void slotMouseDoubleClick();
void slotSelectPc();
void slotUnselectPc();
void slothidePc();
QPixmap svgToPixmap(const QString &svgPath, const QSize &size);
private slots:
//void pcselectMenu();
QString  getIpPortStatus(QString ip_,QString port);
void slotPcAyar();

private:


bool refreshContinueState=false;
    QTimer *timerPortControl;
    QTimer *timertcpConnectControl;
    QString localDir;


   // QString mac;

    qreal w;
    qreal h;

    QToolButton *btnayar;
    QToolButton *btncommand;
    QLabel *hostnameLabel;
    QLabel *sshstateLabel;
    QLabel *vncstateLabel;
    QLabel *connectstateLabel;
    QLabel *xrdpstateLabel;

    QLabel *userstateLabel;
    QLabel *iconstateLabel;

    QLabel *volumestateLabel;
    QLabel *keyboardstateLabel;
    QLabel *mousestateLabel;
    QLabel *internetstateLabel;
    QLabel *webblockstateLabel;
    QLabel *youtubestateLabel;
    QLabel *kilitstateLabel;
    QLabel *tkilitstateLabel;

    //VideoPlayer *videoWidget;
    MulticastReceiver *receiver;
    //QPointer<MulticastReceiver> receiver;
    QImage prevImage;
};



#endif // MYPC_H
