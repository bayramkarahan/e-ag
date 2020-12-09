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
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void newMessage(QString);
private slots:
    void newConnection();
    void appendToSocketList(QTcpSocket* socket);

    void readSocket();
    void discardSocket();
    void connectControl();
    void displayMessage(const QString& str);
    void sendMessage(QTcpSocket* socket);
    void sendMessageInit();
  //  void sendMessageButtonSlot();
   // void sendMessageAllButtonSlot();

    void ekranImageRead();
protected:
     void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

public slots:
    void cellDoubleClicked(int iRow, int iColumn);
    void createTable();
    void init();
    void acount();
    void ssh();
    void selectPc();
    void createButton();
    void barStatusSlot();
    void agTaraButtonSlot();
    void macListButtonSlot();
    void macListSaveButtonSlot();
  //  void vncConnectButtonSlot();
    void ftpConnectButtonSlot();
    void hostAddressButtonSlot();
    void hostAddressMacButtonSlot();
    void pcListeSlot();

    void hostListReset();
   // void macListeSlot();
    void commandExecuteSlot();
    void commandExecuteAllSlot();
    void sshCommandSlot(QString kmt);
    void sshCommandAllSlot(QString kmt);
    void fileSelectSlot();
    void fileCopySlot();
    void fileCopyAllSlot();
    void fileHostportCopyAllSlot();
    void sshAramaButtonSlot();
    void vncAramaButtonSlot();
    void ftpAramaButtonSlot();
  ///  void pcAramaButtonSlot();
    void pcListeGuncelleSlot();
    void pcButtonGuncelleSlot(QString mac,bool setImage,QString iconname,bool pcupdate);
    void bilgiAlButtonSlot();
    void tcpekranKilitButtonSlot();
    void tcpduyuruMesajButtonSlot();
    void tcppcKapatButtonSlot();
    void tcpekranImageButtonSlot();
    void tcpcommandsendMessageButtonSlot();
    void ayarKaydetButtonSlot();
    void taramaButtonSlot();
    void tcpPanoButtonSlot();
    void rdpButtonSlot();
    void mesajSlot(QString msg);
    QStringList listRemove(QStringList list,QString data);
    QStringList fileToList(QString filename);
    void listToFile(QStringList list, QString filename);
    QString listGetLine(QStringList list,QString data);
     QString getMacForIP(QString ipAddress);
    void sendBroadcastDatagram();
    void enableButton();
    void ekranImage();
    void ekranImageAll();
    void timerClickSlot();
private:
    int en,boy;
    QTableWidget *tw;
    QGridLayout *layout;
    QPushButton *ayarKaydetButton;

    QToolButton *hostTableListButton;
    QToolButton *macListSaveButton;
    QToolButton *hostTableListNameFindButton;
    QToolButton *vncConnectButton;
    QToolButton *ftpConnectButton;
    QToolButton *hostAddressButton;
    QToolButton *macListeButton;
    QPushButton *taramaButton;
    QToolButton* listePcButton;

    QPushButton *commandExecuteButton;
    QPushButton *commandExecuteAllButton;
    QPushButton *fileSelectButton;
    QPushButton *fileCopyButton;
    QPushButton *fileCopyAllButton;
    QPushButton *sshAramaButton;
    QPushButton *vncAramaButton;

    QToolButton *sendMessageButton;
    QToolButton *sendMessageAllButton;

    QToolButton *tcpekranImageButton;
    QToolButton *tcpekranKilitButton;
    QToolButton *tcpduyuruMesajButton;
    QToolButton *tcppcKapatButton;
    QToolButton *tcpcommandsendMessageButton;
    QToolButton *tcpPanoButton;

    QToolButton *bilgiAlButton;
    QProgressBar *bar;
    int barValue;
    QLabel *pcIp;
    QLabel *pcMac;
    QLabel *pcName;
    QLabel *pcIplbl;
    QLabel *pcNamelbl;
    QLabel *pcMaclbl;

    QLabel *socketNumberLabel;
    QLabel *destlabel;
    QLineEdit *localNetwork;
    QLineEdit *tcpPort;

    QLineEdit *remotePassword;
    QLineEdit *remoteUsername;
    QLineEdit *localPassword;
    QLineEdit *localUsername;

    //QLineEdit *command;
   // QLineEdit *filePath;
    QLineEdit *status;
    QWidget *lst;
    QPalette *palette;
    QString broadCastAddress;
    QTextEdit *te;
    QTcpServer* m_server;
    QList<QTcpSocket*> connection_list;
    QComboBox *comboBox_receiver;
    QLineEdit *lineEdit_message;
    QPlainTextEdit *textBrowser_receivedMessages;
   /// QStringList onLinePcList;
    QUdpSocket *udpSocket = nullptr;
    QTimer *timerUdpSocket;
    QString myMacAddress;
    QString myIpAddress;
    //QString serverPort;
    QList<Pc*> btnlist;

     QMenu *kilitMenu();
     QMenu *kapatMenu();
     QMenu *duyuruMesajMenu();
     QMenu *ekranImageMenu();
     QMenu *komutMenu();
     QMenu *taramaMenu();
     QMenu *panoMenu();
     QMenu *rdpMenu();

     QUdpSocket *ekranSocketServer;
     QImage *ekranImages;
     QTimer *timerEkranImageAll;
     QTimer *timerEkranImage;
     QTimer *timerClick;
     bool pcKilitStatus;
     bool pcKilitAllStatus;
     bool pcEkranImageStatus;
     bool pcEkranImageAllStatus;
     QString tcpKomut;
    QString localDir;
  };

#endif // MAINWINDOW_H
