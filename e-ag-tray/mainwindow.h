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
#pragma once
#include <QMainWindow>
#include<QLineEdit>
#include<QMessageBox>
#include<QSystemTrayIcon>
#include<QGridLayout>
#include<ekran.h>
#include<QTableWidget>
#include<QCheckBox>
#include <QNetworkInterface>
#include<QObject>
#include<QUdpSocket>
#include <iostream>
#include <QLocalServer>
#include <QLocalSocket>
#include <QProcess>
#include <QIcon>
#include<commandrunner.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
virtual void closeEvent ( QCloseEvent * event );

public slots:
    void  WidgetClosed();
    void iconActivated(QSystemTrayIcon::ActivationReason);
    void gizle();
    void  widgetShow();
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();


private:
     QLabel *gelenKomut;
    QWidget *ayar();
    QWidget *aw;
    QWidget *giris();
    QWidget *hakkinda();
    QWidget *qww;
    int boy=30;
    int en=30;
    int btsayisi=4;

     bool webblockstate;
     QString version;
     QString sudoyetki="";
     QString user;
     QString passwordstatus;
     bool status;

    QStringList ayarlst;
    QTimer *timergizle;
    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu;

    QMenu* createMenu();

    QString localDir;

    QGridLayout *layout;
    CommandRunner *runner;
    QTimer *timer;
    QLocalServer *trayServerDetached; // Local server
    QLocalServer *trayServer; // Local server

};

#endif // MAINWINDOW_H
