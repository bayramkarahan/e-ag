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
#include<QTabWidget>
#include<QLabel>
#include<QGridLayout>
#include<QPushButton>
#include<QFile>
#include<QFileDialog>
#include<QRegularExpression>
#include<QTimeEdit>
#include<QDate>
#include<QTimer>
#include<QTime>
#include<QMessageBox>
#include<QApplication>
#include<QDesktopWidget>
#include<QMenu>
#include<QCloseEvent>
#include<QProcess>
#include<QAuthenticator>
#include<QApplication>
#include <stdio.h>
#include <QtCore/QCoreApplication>
#include <iostream>
#include<Database.h>
#include<userprivilegehelper.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
 {
    localDir="/usr/share/e-ag/";
    /*******************************************************************/
     gelenKomut=new QLabel("-------------------");

    trayIcon=new QSystemTrayIcon(this);
    this->resize(340,300);
    setFixedWidth(400);
    setFixedHeight(400);
    setWindowTitle("e-ag-client-tray");
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()/2 - this->width()/2);
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
    this->setStyleSheet("background-color: #dfdfdf;");


      //*******************tray***********************************/
      // Tray icon menu
      auto menu = this->createMenu();
      this->trayIcon->setContextMenu(menu);

      // App icon
      auto appIcon = QIcon(":/icons/e-ag.svg");
      this->trayIcon->setIcon(appIcon);
      this->setWindowIcon(appIcon);

      // Displaying the tray icon
      this->trayIcon->show();     // Note: without explicitly calling show(), QSystemTrayIcon::activated signal will never be emitted!

      // Interaction
      connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);


      timergizle = new QTimer(this);
      connect(timergizle, SIGNAL(timeout()), this, SLOT(gizle()));
      timergizle->start(1);

      QLocalServer::removeServer("eag_tray_Detached");
      trayServerDetached = new QLocalServer(this);

      if (!trayServerDetached->listen("eag_tray_Detached")) {
          qDebug() << "eag_trayDetached Server başlatılamadı:" << trayServerDetached->errorString();
          return;
      }

      connect(trayServerDetached, &QLocalServer::newConnection, this, [this]() {
          QLocalSocket *sock = trayServerDetached->nextPendingConnection();

          connect(sock, &QLocalSocket::readyRead, this, [sock](/*...*/) {
              QString cmd = QString::fromUtf8(sock->readAll()).trimmed();
              if (cmd.isEmpty())
                  return;

              qDebug() << "eag_trayDetached Çalıştırılacak Komut ilk hali:" << cmd;
              // Ortam değişkenlerini hazırla
              UserPrivilegeHelper helper;
              QString user = helper.detectActiveUser();       // GUI kullanıcısı
              UserInfo info = helper.getUserInfo(user);       // UID, GID, home, sessionId
             /* QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
              env.insert("DISPLAY",info.display);
              env.insert("XAUTHORITY", "/home/"+info.username+"/.Xauthority");
            */

              QProcessEnvironment env = helper.buildUserEnvironment(info);
              QProcess *p = new QProcess;
              p->setProcessEnvironment(env);
              p->startDetached("/bin/bash", {"-c", cmd});

                // Socket'i hemen kapat
              if (sock->isOpen())
                  sock->close();
          });

          connect(sock, &QLocalSocket::disconnected, sock, &QLocalSocket::deleteLater);
      });

    /****************************************************************/
      QLocalServer::removeServer("eag_tray");
      trayServer = new QLocalServer(this);
      if (!trayServer->listen("eag_tray")) {
          qDebug() << "eag_tray Server başlatılamadı:" << trayServer->errorString();
          return;
      }

      connect(trayServer, &QLocalServer::newConnection, this, [this]() {
          QLocalSocket *sock = trayServer->nextPendingConnection();

          connect(sock, &QLocalSocket::readyRead, this, [this, sock]() {
              QString cmd = QString::fromUtf8(sock->readAll()).trimmed();
              if (!cmd.isEmpty()) {
                  qDebug() << "eag_tray Çalıştırılacak Komut:" << cmd;
                  /**************************************************/
                  QProcess *process = new QProcess(this);
                  process->setProcessChannelMode(QProcess::MergedChannels);

                  connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                          [this, process,sock](int, QProcess::ExitStatus){
                              QString output = process->readAll();
                              if (sock && sock->isOpen()) {
                                  sock->write(output.toUtf8());
                                  sock->flush();
                                  sock->close();
                              }
                              process->deleteLater();
                          });

                  process->start(cmd);
                  /*******************************************************/
              }
          });

          connect(sock, &QLocalSocket::disconnected, sock, &QLocalSocket::deleteLater);
      });
}


MainWindow::~MainWindow()
{
    trayServer->close();
}

void  MainWindow::gizle()
{
       QWidget::hide();
    timergizle->stop();

  }
void  MainWindow::widgetShow()
{

  //  qDebug()<<"ekranı göster";
  //  system("sh -c \"pkexec env DISPLAY=$DISPLAY XAUTHORITY=$XAUTHORITY e-ag-gui\"");
 }

QMenu* MainWindow::createMenu()
{

    auto minimizeAction = new QAction(tr("Gi&zle"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);
    auto restoreAction = new QAction(tr("&Ayarlar"), this);
    ///connect( restoreAction, SIGNAL(triggered()), this, SLOT(widgetShow()));
    auto menu = new QMenu(this);
    ///menu->addAction(minimizeAction);
    //menu->addAction(maximizeAction);
    ///menu->addAction(restoreAction);
    ///menu->addSeparator();

    return menu;
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason_)
{
  switch (reason_) {
  case QSystemTrayIcon::Trigger:
    this->trayIcon->showMessage("e-ag", "Ağ Yönetim Yazılımı");
        ///widgetShow();
    break;
  default:
    ;
  }
}

void MainWindow::WidgetClosed()
{

    QWidget::hide();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
     emit WidgetClosed();
     //QWidget::hide();
     event->ignore();

}
