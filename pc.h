#ifndef PC_H
#define PC_H

#include <QWidget>
#include<QLabel>
#include<QToolButton>
#include<QPushButton>

class Pc : public QWidget
{
    Q_OBJECT
public:
    explicit Pc(QWidget *parent = nullptr);
//createPc(QString pcname, QString mac,QString ps,QString ss,QString vs,QString cs,int w,int h,bool setImage,QString iconname)
void setMac(QString _mac, int _w, int _h);
void setCaption(QString cap);
void setIcon(QString file);
void setUpdate(QString mac, bool upd);

void servisStateUpdate();

protected:
void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:
QStringList listRemove(QStringList list,QString data);
QStringList fileToList(QString filename);
void listToFile(QStringList list, QString filename);
QString listGetLine(QStringList list,QString data);
QString getIpSshStatus(QString ip_);
QString getIpVncStatus(QString ip_);
QString getIpFtpStatus(QString ip_);

private:
    QString localDir;
    QString ip;
    QString pcname;
    QString mac;
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
    int w;
    int h;
    bool setImage;
    QString iconname;
    QLabel *nameLabel;
    QToolButton *btnpc;
    QPushButton *btnctrl;
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

};

#endif // PC_H
