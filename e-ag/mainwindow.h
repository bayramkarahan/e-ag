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
#include<QList>
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
#include<mypc.h>
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
#include <QRubberBand>
#include "scdimgclient.h"
#include<QInputDialog>
#include <iostream>
#include<Database.h>
//#include<qtermwidget5/qtermwidget.h>
#include<CustomInputDialog.h>
#include <QQueue>
#include <QThread>
#include <QLocalSocket>
#include<userprivilegehelper.h>
class QStyle;
class IpMac
{
public:
    QString ip;
    QString mac;
    QString broadcast;
};
struct fileCopyTask {
    QString mesajtype;
    QString ip;
    QString port;
    QString sourcePath;
    QString targetPath;
 };
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool mouseClickState=false;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
      QString _display="2";
      QPoint origin;
      QRubberBand *rubberBand;
      QList<IpMac> interfaceList;
      QList<NetProfil> NetProfilList;
      QQueue<fileCopyTask> fileCopyTasks;
      using TrayResponseCallback = std::function<void(const QString&)>;
 signals:

protected:
     void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
     void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
     void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
     void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
     void paintEvent(QPaintEvent* event);
 public slots:
     void eagtraySendDataDetached(const QString &cmd);
     void eagtraySendData(const QString &cmd,TrayResponseCallback callback);

     void fileReceiveProcess(const QJsonObject &json);
     void clientConfUpdate(const QJsonObject &json);
     void clientCommandState(const QJsonObject &json);

     void slotVnc0();
     void slotVnc1();
     void slotVnc2();
     static  bool karsilastirMyPc(const MyPc *mypc1, const MyPc *mypc2);
     void networkProfilLoad();
     QString getSeatId();
     QString getSessionInfo(QString id, QString parametre);
     //void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
     void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus, fileCopyTask task);

     void listeyiKopyala();
     bool killProcessByName(const QString &processName);

private slots:
     QString getActiveUserName();
     void pcMenu(bool singlepc);

     void udpSocketServerRead();
     //void eagtraySendData(const QString &cmd, std::function<void(const QString &)> callback);
     //void eagtraySendData(const QString &cmd, std::function<void(const QString&)> callback);
     void udpSendData(QString _mesajTur,QString _gorev,QString _ekmesaj,QString desciription, bool mesajVisible);
     QWidget *commandWidget();
     QWidget * webInternetWidget();
     QWidget *sliderWidget();

     QWidget *fileWidget();
     QWidget *videoWidget();
     QWidget *messageWidget();
     QWidget *settingsWidget();
     QWidget* volumeWidget();
     QWidget* deviceWidget();
     QWidget* keyboardmouseWidget();

    QWidget *ekranWidget();
    QWidget *kilitWidget();
    QWidget *kilittransparanWidget();
    QWidget *rdpWidget();
    QWidget *poweroffrebootWidget();
    QWidget *logoutWidget();
    QWidget *groupWidget(QWidget *targetWidget);


    QWidget *baseWidget();
    QWidget *languageWidget();
    QWidget *HostListWidget();
    void webBlockWidget();
    QWidget *wolWidget();
    void hideShowPcSlot();
    void networkProfil();
    void updateSlider(int val);
    void groupListChange(const QList<groupList> &liste);

    void selectSlot();

    void vncDisplaySlot();


    void selectPc();
    void hostAddressMacButtonSlot();
     void selectFileCopySlot(QString _mesajtype,QString _sourcePath, QString _targetPath);

    void pcListeGuncelleSlot(QString mission);
    void pcHideSignalSlot(QString _mac);
    void pcSettingUpdateSignalSlot(QString _mac,QString mission);
    void pcCloseSignalSlot(QString ip,QString mac);
    void pcScreenViewSignalSlot(QString ip,QString mac);

    void bilgiAlButtonSlot();

    void pcRightClickSignalSlot();
    void mesajSlot(QString msg);


QString getMacForIP(QString ipAddress);

    void pcClickSlot(QString _mac);
    void pcDoubleClickSignalSlot(QString _mac);
    void slotWakeOnLan(QString _ip,QString _mac);

    void slotVnc(QString _dsp);
    void slotVncFlip(QString scale,QString viewState);
    void slotVncFlipStop();
    void slotVncFlipAll(QString scale,QString viewState);
    void slotVncFlipAllStop();
    void slotRdp();
    void slotTerminal();
    void slotKilit();
    void slotTransparanKilit();
    void slotKilitAc();
    void slotTransparanKilitAc();
    void slotLogin();
    void slotLogout();
    void slotLogoutAll();

    void slotReboot();
    void slotRebootAll();
    void slotPowerOff();
    void slotPowerOffAll();
    void slotCommand(QString _kmt);
    void slotPcCommandSelect(QString _kmt);

    void slotPcCommandAll(QString _kmt);
    void slotEkranIzle();
    void slotEkranIzleDurdur();
    void slotEkranIzleAll();
    void slotEkranIzleAllDurdur();
    void slotPcEkle(QString _mac,QString _ip);
    void slotPcSil(int _index,QString _mac,QString _ip);

private:
     QWidget *groupwidget1;
    bool pcrightmenu;
    QMenu *pContextMenu;
    QString publickey;
    QStatusBar *statusbar;
    QWidget *mainWidget;
    QLabel *sliderValuelabel;
    QWidget *selectWidget;
    QWidget *ustMenuWidget;
    QSlider *slider;

    bool tamReset=false;
    QWidget *maclistwidget;
    //QTableWidget *tablewidget;
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

     //QTableWidget *twl;

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
    QToolButton *fileCopyInstallScriptButton;

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
    QLabel *pcVersionlbl;
    QLabel *pcSystemlbl;


    QLabel *socketNumberLabel;
    QLabel *destlabel;

    /*****************************************************************/
    bool webblockstate;
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
    QList<MyPc*> onlinePcList;
     QMenu *transparanKilitMenu();
     QMenu *kilitMenu();
     QMenu *unkilitMenu();
     QMenu *poweroffRebootMenu();

     QMenu *duyuruMesajMenu();
     QMenu *ekranImageMenu();
     QMenu *komutMenu();

     QMenu *rdpMenu();
     QMenu *commandExampleMenu();
     QMenu *sessionMenu();
     QMenu *languageMenu();
     QStringList listQmFiles(const QString &directory);
    QUdpSocket *udpSocketGet;
    QString localDir;
    QLineEdit *commandEdit;
    QLineEdit *webEdit;
    QRadioButton *rb1;
    QRadioButton *rb2;
    bool udpSendDataStatus=false;
    bool firstRun=false;
    QSlider *ekranSlider;
        QString trayCommandResult;  // burada sakla
    QComboBox * ses;
  };

#endif // MAINWINDOW_H
