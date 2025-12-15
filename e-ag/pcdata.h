#ifndef PCDATA_H
#define PCDATA_H

#include<QStringList>
class groupList
{
public:
    bool groupSelect;
    QString groupName;
};
class PcData
{
public:
    static QStringList onlinePcListe;
    static QList<groupList> groupListe;
};
/*
namespace Ui {
class MainWindow;
}*/


#endif // PCDATA_H
