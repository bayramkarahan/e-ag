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
#ifndef SELECTPC_H
#define SELECTPC_H

void MainWindow::selectPc()
{
    int e=en;
    int b=boy;

    QAction *listeleAction = new QAction(QIcon(":/icons/liste.svg"), tr("&Liste Yenile"), this);
    listeleAction->setShortcut(tr("Listele"));
    listeleAction->setStatusTip(tr("Hostlar Listelendi"));
    connect(listeleAction, SIGNAL(triggered()), this, SLOT(pcListeSlot()));

    QAction *selectAction = new QAction(QIcon(":/icons/select.svg"), tr("&İstemci Seç"), this);
    selectAction->setShortcut(tr("Seç"));
    selectAction->setStatusTip(tr("İstemcileri Seçme Yapıldı"));
    connect(selectAction, SIGNAL(triggered()), this, SLOT(selectSlot()));

    QAction *vncAction = new QAction(QIcon(":/icons/vnc.svg"), tr("&Uzak Masaüstü Bağlantısı"), this);
    vncAction->setShortcut(tr("VNC"));
    vncAction->setStatusTip(tr("Uzak Masaüstü Bağlantısı Başlatıldı"));
    connect(vncAction, SIGNAL(triggered()), this, SLOT(vncDisplaySlot()));


    QAction *xrdpAction = new QAction(QIcon(":/icons/rdp.svg"), tr("&"), this);
    xrdpAction->setShortcut(tr("XRDP"));
    xrdpAction->setStatusTip(tr("xrdp Uzak Masaüstü Erişimi Yapıldı"));
    connect(xrdpAction, SIGNAL(triggered()), this, SLOT(slotRdp()));

    QAction *terminalAction = new QAction(QIcon(":/icons/ssh.svg"), tr("&Terminal"), this);
    terminalAction->setShortcut(tr("Terminal"));
    terminalAction->setStatusTip(tr("Terminal Bağlantısı Yapıldı"));
    connect(terminalAction, SIGNAL(triggered()), this, SLOT(terminalSlot()));

    QAction *ftpAction = new QAction(QIcon(":/icons/ftp.svg"), tr("&Dosya Transfer"), this);
    ftpAction->setShortcut(tr("FTP"));
    ftpAction->setStatusTip(tr("Dosya Transfer"));
    connect(ftpAction, SIGNAL(triggered()), this, SLOT(ftpConnectButtonSlot()));

    QAction *wolAction = new QAction(QIcon(":/icons/wol.svg"), tr("&Uzak Pc Başlatma"), this);
    wolAction->setShortcut(tr("WOL"));
    wolAction->setStatusTip(tr("Uzaktan Pc Başlatma İşlemi Yapıldı"));
    connect(wolAction, SIGNAL(triggered()), this, SLOT(wolSlot()));

    QAction *profilAction = new QAction(QIcon(":/icons/session.svg"), tr("&Ağ Profilleri"), this);
    profilAction->setShortcut(tr("AP"));
    profilAction->setStatusTip(tr("Ağ Profilleri"));
    connect(profilAction, SIGNAL(triggered()), this, SLOT( acountButtonSlot()));

    QToolBar *toolBar=new QToolBar(this);
    toolBar->addAction(listeleAction);
    toolBar->addAction(selectAction);
    toolBar->addAction(vncAction);
    toolBar->addAction(xrdpAction);
    toolBar->addAction(terminalAction);
    toolBar->addAction(ftpAction);
    toolBar->addAction(wolAction);
    toolBar->addAction(profilAction);

    toolBar->setIconSize(QSize(boy*4, boy*4));
    selectWidget=new QWidget();
    selectWidget->setFixedSize(this->width(),b*5);
    selectWidget->setObjectName("selectWidgett");
    selectWidget->setStyleSheet("background-color: #dfdfdf;font-size:"+QString::number(font.toInt()-2)+"px;");
    ///selectWidget->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");

    hostsCountLabel=new QLabel(selectWidget);
    hostsCountLabel->setText("0");
    hostsCountLabel->setStyleSheet("color: #0000ff;font-size:"+QString::number(font.toInt())+"px;");

    pcIplbl=new QLabel(selectWidget);
    pcIplbl->resize(e*8,b*5);
    pcNamelbl=new QLabel(selectWidget);
    pcNamelbl->resize(e*8,b*5);
    pcMaclbl=new QLabel(selectWidget);
    pcMaclbl->resize(e*8,b*5);
    pcUserlbl=new QLabel(selectWidget);
    pcUserlbl->resize(e*8,b*5);
    pcScreenlbl=new QLabel(selectWidget);
    pcScreenlbl->resize(e*8,b*5);
    pcSystemlbl=new QLabel(selectWidget);
    pcSystemlbl->resize(e*8,b*5);
/******************************************************************/

    /*************************************************************/
         auto layoutsp = new QGridLayout();
         layoutsp->setContentsMargins(0, 0, 20,0);
         layoutsp->setVerticalSpacing(0);
         layoutsp->addWidget(toolBar, 0,0,1,1);
         layoutsp->addWidget(pcNamelbl, 0,1,1,1);
         layoutsp->addWidget(pcIplbl, 0,2,1,1);
         layoutsp->addWidget(pcMaclbl, 0,4,1,1);
         layoutsp->addWidget(pcUserlbl, 0,6,1,1);
         layoutsp->addWidget(pcScreenlbl, 0,8,1,1);
         layoutsp->addWidget(pcSystemlbl, 0,10,1,1);
         layoutsp->addWidget(hostsCountLabel, 0,12,1,1);

         selectWidget->setLayout(layoutsp);
}
#endif // SELECTPC_H
