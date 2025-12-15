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
#include<singleinstance.h>
#include <stdio.h>
#include <stdlib.h>
#include <QtCore/QCoreApplication>
#define SINGLE_INSTANCE ".e-ag-tray"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString name = SINGLE_INSTANCE;

   SingleInstance cInstance;
   if(cInstance.hasPrevious(name, QCoreApplication::arguments()))
   {
       qDebug() << "e-ag-tray Zaten Açık...";
       return 0;
   }
   if (cInstance.listen(name)) {
       qDebug() << "e-ag-tray Çalışıyor..";
   } else {
       qDebug() << "e-ag-tray Çalışması İptal Edildi...";
       return 0;
   }
MainWindow w;


    w.show();

    return a.exec();
}
