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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTableWidget>
#include<QPushButton>
#include<QDebug>
#include<QTimer>
#include<QProgressBar>
#include<QLabel>
#include<QLineEdit>
#include<QGridLayout>
#include<QFileDialog>
#include<QTextEdit>
#include <QMessageBox>
#include <QMetaType>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include<QComboBox>
#include<QTextBrowser>
#include<QPlainTextEdit>
#include<QUdpSocket>
#include<QMenu>
#include <QStyle>
#include<pc.h>
#include<QPalette>
#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QVBoxLayout>
#include<QDialogButtonBox>
#include <QPrinter>
#include<QPrintDialog>
#include<QProcess>
#include<QTabWidget>
#include<QScrollArea>
#include<QStatusBar>
#include<pcdata.h>
#include<QRadioButton>
#include<QButtonGroup>

namespace Ui {
class MainWindow;
}
class IpMac
{
public:
    QString ip;
    QString mac;
    QString broadcast;

};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool mouseClickState=false;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
      QString _display="2";

 signals:

protected:
     void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
     void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
     void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
     void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private slots:
     QStringList readArp();
     void udpSocketServerRead();
     QString getIpPortStatus(QString service);
     void udpSendData(QString _mesajTur,QString _mesaj,QString _ip);
     void layoutTemizle();
     void pcListeStateSlot();
     void newPcDetect();
     QWidget *sshCommandWidget();
     QWidget *sliderWidget();

     QWidget *sshScpWidget();
     QWidget *videoWidget();
     QWidget *duyuruWidget();
     QWidget *ayarlarWidget();

     QWidget *ekranWidget();
     QWidget *kilitWidget();
     QWidget *kilittransparanWidget();
     QWidget *rdpWidget();
     QWidget *poweroffrebootWidget();
     QWidget *logoutWidget();
     QWidget *agProfilWidget();

     QWidget *pcInfo();
     QWidget *macListWidget();
     void webBlockSlot();
     void wolSlot();

     void updateSlider(int val);
      QString getIpPortStatus(QString ip_,QString port);
    void slotServisControl();
    QWidget *acountButtonSlot1();
    QWidget *acountButtonSlot2();
    void acountButtonSlot();

    void selectSlot();
    void terminalSlot();
    void vncDisplaySlot();
    void pcTcpPortControlSignalSlot(QString _mac,QString _ip);
    void pcSshPortControlSignalSlot(QString _mac,QString _ip);
    void pcVncPortControlSignalSlot(QString _mac,QString _ip);
    void pcFtpPortControlSignalSlot(QString _mac,QString _ip);
    void pcKilitStateControlSignalSlot(QString _mac, QString _ip, bool kilitstate);
    void pcKilitTransparanStateControlSignalSlot(QString _mac, QString _ip, bool transparankilitstate);
    void pcIconStateControlSignalSlot(QString _mac, QString _ip, bool iconstate);
    void pcMenuSignalSlot(QString _mac,QString _ip,QString _slot);
    void cellDoubleClicked(int iRow, int iColumn);
    void webTableCellDoubleClicked(int iRow, int iColumn);


    void acountLoad();
    void selectPc();


     void printButtonSlot();


    void macListSaveButtonSlot();
    void ftpConnectButtonSlot();
    void hostAddressMacButtonSlot();
    void pcListeSlot();
    void hostListReset();
    QStringList arpListInit();
    void sshCommandAllSlot(QString kmt);
       void sshFileCopyAllSlot(QString _sourcePath, QString _targetPath);
    void sshSelectFileCopySlot(QString _sourcePath, QString _targetPath);

    void sshSelectPcCommandSlot(QString kmt);
    void sshCommandSlot(QString kmt,QString _ip);

    void pcListeGuncelleSlot(int _ColumnSayisi, int pcw, int pch);
    void bilgiAlButtonSlot();
    void ayarKaydetButtonSlot();

    void mesajSlot(QString msg);
    QStringList listRemoveToList(QStringList sourceList, QStringList removeList, int dataIndex);
    void listToFile(QStringList list, QString filename);
    QStringList fileToList(QString filename,QString path);
    QString listGetLine(QStringList list,QString data);
    QStringList listRemove(QStringList list,QString data);
    QStringList listReplace(QStringList list,QString oldData,QString newData,int index);
    QStringList listMerge(QStringList list1, QStringList list2,int dataIndex);
    QStringList listGetList(QStringList list, QString data,int index);
    QStringList listSort(QStringList list ,int dataIndex);

     QString getMacForIP(QString ipAddress);
    void sendBroadcastDatagram();
    void pcClickSlot(QString _mac);
    void slotWakeOnLan(QString _ip,QString _mac);

    void slotVnc(QString _dsp);
    void slotVncFlip(QString scale,QString viewState);
    void slotVncFlipStop();
    void slotVncFlipAll(QString scale,QString viewState);
    void slotVncFlipAllStop();
    void slotRdp();
    void slotFtp();
    void slotKilit();
    void slotKilitAll();
    void slotTransparanKilit();
    void slotTransparanKilitAll();
    void slotKilitAc();
    void slotTransparanKilitAc();
    void slotKilitAcAll();
    void slotTransparanKilitAcAll();

    void slotLogin();
    void slotLogout();
    void slotLogoutAll();
    void slotLoginAll();

    void slotReboot();
    void slotRebootAll();
    void slotPowerOff();
    void slotPowerOffAll();
    void slotSelectPcMesaj(QString _msg);
    void slotCommand(QString _kmt);
    void slotPcCommandSelect(QString _kmt);
    void slotPcCommandAll(QString _kmt);
    bool vncState(QString _mac);
    bool ftpState(QString _mac);

    void slotEkranIzle();
    void slotEkranIzleDurdur();
    void slotEkranIzleAll();
    void slotEkranIzleAllDurdur();
private:
    QStatusBar *statusbar;
    QWidget *mainWidget;
    QLabel *sliderValuelabel;
    QWidget *selectWidget;
    QWidget *ustMenuWidget;
    QSlider *slider;
    QList<IpMac> ipmaclist;
    bool tamReset=false;
      QWidget *maclistwidget;
    QTableWidget *tablewidget;
    QComboBox * ekranScale;
    int gercekliste;
    int pcopencount;
    QScrollArea *scrollArea;
    QString font="12";
    QTimer *newPcDetectTimer;
    int tabWidgetIndex=0;
    QLabel *hostsCountLabel;

    QTabWidget *tabwid;
     QTabWidget *tabwidprofil;
    bool streamState;
    QProcess videoProcess;

     QTableWidget *twl;

    int en,boy;

    QGridLayout *layout;

    QPushButton *ayarKaydetButton;
     QToolButton *hostTableListButton;
    QToolButton *hostTableListNameFindButton;
    QToolButton *vncConnectButton;
    QToolButton *ftpConnectButton;
    QToolButton *hostAddressButton;
    QToolButton *macListeButton;
    QToolButton *settingButton;
    QToolButton* listePcButton;
    QToolButton* sshButton;
    QToolButton *commandExampleButton;
    QToolButton *commandExecuteButton;
    QToolButton *commandExecuteAllButton;
    QToolButton *fileSelectButton;
    QToolButton *fileCopyButton;
    QToolButton *fileCopyInstallButton;

    QToolButton *fileCopyAllButton;
    QToolButton *sshAramaButton;
    QToolButton *vncAramaButton;

    QToolButton *sendMessageButton;
    QToolButton *sendMessageAllButton;

    QToolButton *tcpekranImageButton;
    QToolButton *tcpekranKilitButton;
    QToolButton *tcpduyuruMesajButton;
    QToolButton *tcppcKapatButton;
    QToolButton *tcppcRebootButton;

    QToolButton *tcpcommandsendMessageButton;
    QToolButton *tcpcommandsessionButton;
    QToolButton *bilgiAlButton;


    QToolButton *fileTransferButton;

     QLabel *pcIp;
    QLabel *pcMac;
    QLabel *pcName;
    QLabel *pcIplbl;
    QLabel *pcNamelbl;
    QLabel *pcMaclbl;
    QLabel *pcUserlbl;
    QLabel *pcScreenlbl;
    QLabel *pcSystemlbl;


    QLabel *socketNumberLabel;
    QLabel *destlabel;
    /****************************Ag Profil********************************/
    QString selectAgProfil;
    QString agProfil;
    QString remotePassword;
    QString remoteUserName;
    QString localUserName;
    QString localPassword;
    QString tcpPort;
    QString broadCastAddress1;
    QString broadCastAddress2;
    bool webblockstate;
    bool selectAgProfil1;
    QString agProfil1;
    QString remotePassword1;
    QString remoteUserName1;
    QString localUserName1;
    QString localPassword1;
    QString tcpPort1;
    QString broadCastAddress11;
    QString broadCastAddress12;
    //bool webblockstate1;
    bool selectAgProfil2;
    QString agProfil2;
    QString remotePassword2;
    QString remoteUserName2;
    QString localUserName2;
    QString localPassword2;
    QString tcpPort2;
    QString broadCastAddress21;
    QString broadCastAddress22;
    //bool webblockstate2;
    /*****************************************************************/
    QLineEdit *status;
    QWidget *hostListe;
    QPalette *palette;

    QTextEdit *te;
//    QTcpServer* m_server;
    QList<QTcpSocket*> connection_list;
    QComboBox *comboBox_receiver;
    QLineEdit *lineEdit_message;
    QPlainTextEdit *textBrowser_receivedMessages;
    QUdpSocket *udpSocketSend = nullptr;
    QTimer *timerUdpSocketSend;
     QString selectMac="";
     QList<Pc*> btnlist;
    QList<Pc*> tempbtnlist;
     QMenu *transparanKilitMenu();
     QMenu *kilitMenu();
     QMenu *poweroffRebootMenu();

     QMenu *duyuruMesajMenu();
     QMenu *ekranImageMenu();
     QMenu *komutMenu();

     QMenu *rdpMenu();
     QMenu *commandExampleMenu();
     QMenu *sessionMenu();
    QUdpSocket *udpSocketGet;
    QString localDir;
    QLineEdit *commandFileL;
    QRadioButton *rb1;
    QRadioButton *rb2;

  };

#endif // MAINWINDOW_H
