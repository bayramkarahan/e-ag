#ifndef MULTICASTADDRESSDIALOG_H
#define MULTICASTADDRESSDIALOG_H

#include <QDialog>
#include<QTextStream>
#include<QDebug>
#include<Database.h>
class QLineEdit;
class QPushButton;
class QLabel;

class MulticastAddressDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MulticastAddressDialog(int w,int h,QWidget *parent = nullptr);

private slots:
    void saveMulticastAddress();
private:
    QLineEdit *hostnameEdit;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QString localDir;
};

#endif // MULTICASTADDRESSDIALOG_H
