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
#ifndef PC_H
#define PC_H

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

class Pc : public QWidget
{
    Q_OBJECT
public:
    explicit Pc(QWidget *parent = nullptr);
    ~Pc();
    enum { Type =  20 };

        int type()
        {
            // Enable the use of qgraphicsitem_cast with this item.
            return Type;
        }
//createPc(QString pcname, QString mac,QString ps,QString ss,QString vs,QString cs,int w,int h,bool setImage,QString iconname)


bool iconState=false;
bool iconControlState=false;
bool csstate=false;
int tcpConnectCounter=0;
int sshConnectCounter=0;
int vncConnectCounter=0;
int ftpConnectCounter=0;

QString font="12";
  QString pcname;
QString ps;
QString ss;
QString vs;
QString cs;
QString fs;
QString lss;
QString ts;
QString lns;
QString S;
QString V;
QString F;
QString C;
bool kilitState=false;
bool kilitControlState=false;
bool transparanKilitState=false;
bool transparanKilitControlState=false;
//void servisStateUpdate();
QString mac;
QString ip;
QString display;
QString user;
QString os;
QString vncport=0;
bool select;
bool multiSelect;
protected:
void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:
void pcClickSignal(QString mac);
void pcListeSignal();
void pcListeStateSignal();
void pcTcpPortControlSignal(QString mac,QString ip);
void pcSshPortControlSignal(QString mac,QString ip);
void pcVncPortControlSignal(QString mac,QString ip);
void pcFtpPortControlSignal(QString mac,QString ip);
void pcKilitStateControlSignal(QString mac,QString ip,bool _kilitstate);
void pcKilitTransparanStateControlSignal(QString mac,QString ip,bool _transparankilitstate);
void pcIconStateControlSignal(QString mac,QString ip,bool _iconstate);
void pcMenuSignal(QString mac,QString ip,QString _slot);

public slots:
void setMac(QString _mac, int _w, int _h, QString _font);
void setSize(int _w, int _h, QString _font);
void setCaption(QString cap);
void setDisplay(QString _dis);
void setUser(QString _os);
void setOs(QString _os);

void setKilitControlState(bool state);
void setKilitTransparanControlState(bool state);
void setIconControlState(bool state);
//void setUpdate(QString mac, bool upd);
void setAcount(QString username, QString password);
void setTcpConnect(bool state);
void setPcState(bool state);
void setSshConnect(bool state);
void setVncConnect(bool state);
void setFtpConnect(bool state);
void slotMouseClick();
void slotMouseDoubleClick();
void slotSelectPc();
void slotUnselectPc();

private slots:
void pcMenu();
void timerPortControlSlot();
void timerPortControlOnlineSlot();
QStringList listRemove(QStringList list,QString data);
QStringList fileToList(QString filename);
void listToFile(QStringList list, QString filename);
QString listGetLine(QStringList list,QString data);
QStringList listReplace(QStringList list, QString oldData, QString newData, int index, QString _mac);
QString getIpPortNmapStatus(QString ip_, QString port);

QString  sshCommandSlot(QString ip_, QString port);
QString  getIpPortStatus(QString ip_,QString port);

void slotVnc0();
void slotVnc1();
void slotVnc2();
void slotVncFlip();
void slotVncFlipStop();
void slotRdp();
void slotFtp();
void slotKilit();
void slotKilitAc();
void slotLogin();
void slotLogout();
void slotReboot();
void slotKapat();
void slotMesaj();
void slotCommand();
void slotEkranIzle();
void slotEkranIzleDurdur();
void slotServisControl();
void slotPcAyar();

private:
QMenu *pContextMenu;
bool refreshContinueState=false;
    QTimer *timerPortControl;
      QTimer *timerPortControlOnline;
    QString remotePassword;
    QString remoteUserName;
    QString localDir;


   // QString mac;

    qreal w;
    qreal h;
    bool setImage;
    QString iconname;
    QLabel *nameLabel;
    QLabel *btnpc;
    QPushButton *btnctrl;
    QToolButton *btnayar;
    QLabel *iconLabel;
    QLabel *pcstateLabel;
    QLabel *pcdrmLabel;
    QLabel *sshstateLabel;
    QLabel *sshdrmLabel;
    QLabel *vncstateLabel;
    QLabel *vncdrmLabel;
    QLabel *connectstateLabel;
    QLabel *connectdrmLabel;
    QLabel *ftpstateLabel;
    QLabel *ftpdrmLabel;
    QLabel *selectLabel;
    QLabel *userstateLabel;

};

#endif // PC_H
