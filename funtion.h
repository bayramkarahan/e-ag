#ifndef FUNTION_H
#define FUNTION_H
void MainWindow::updateSlider(int val)
{
     sliderValuelabel->setText(QString::number(val));
    double nwidth=en*13*val/100;
    double nheight=en*15*val/100;
    int columnSayisi=hostListe->width()/(nwidth+en*4);
     pcListeGuncelleSlot(columnSayisi,nwidth,nheight);

    mesajSlot("Host Boyutları Değiştirildi.");
return;
}
void MainWindow::selectSlot()
{
    for(int i=0;i<btnlist.count();i++)
    {
        // btnlist[i]->select=!(btnlist[i]->select);
        /// btnlist[i]->slotMouseClick();
        btnlist[i]->slotMouseDoubleClick();
    }
    mesajSlot("Host Seçimi Yapıldı.");
}
void MainWindow::terminalSlot()
{
    QString kmt10="x-terminal-emulator -x -e \"ssh "+remoteUserName+"@"+pcIp->text()+"\"";
    system(kmt10.toStdString().c_str());
    mesajSlot("Seçili Hostda Terminal Başlatıldı.");
}
void MainWindow::vncDisplaySlot()
{
    slotVnc(_display);
}
void MainWindow::slotWakeOnLan(QString _ip,QString _mac)
{

   _mac=_mac.toUpper();
    QHostAddress FakeAddress;
    QUdpSocket udpSocket1;
//qDebug()<<"mac adresi:"<<_mac;
    hostAddressMacButtonSlot();
   for(int k=0;k<ipmaclist.count();k++)
    {
             if(ipmaclist[k].ip.section(".",0,2)==_ip.section(".",0,2))
            {
                char MACAddr [6];
                char MagicPacket [102]; // Magic package for remote boot

                int j = sscanf (_mac.toLatin1().data(), "%2x-%2x-%2x-%2x-%2x-%2x",
                                & MACAddr [0], & MACAddr [1], & MACAddr [2], & MACAddr [3], & MACAddr [4], & MACAddr [5]);

                // Set to hexadecimal before the magicpacket array 6 characters ff
                memset (MagicPacket, 0xff, 6);

                int packetsize = 6; // the beginning of the initial value is 6, do not wrong. I is because the effect of the initial value of the written as 0, it is too effortless.
                // Build MagicPacket.
                for (int z = 0; z <16; z++)
                {
                    memcpy (MagicPacket + packetsize, MACAddr, 6);
                    packetsize += 6;
                }

                FakeAddress.setAddress (ipmaclist[k].broadcast);
               // qDebug()<<"broad cast adress:"<<ipmaclist[k].broadcast;
              // udpSocket1.writeDatagram(MagicPacket, 102, QHostAddress(ipmaclist[k].broadcast), 9);
               //system("sleep 0.5");

               QString kmt29="wakeonlan "+_mac;
                system(kmt29.toStdString().c_str());


            }


    }
   mesajSlot("Seçili Hostlar Uzaktan  Başlatıl.");

}
void MainWindow::macListSaveButtonSlot()
{
    QStringList iplistname=fileToList("persistlist");  //liste olşturuluyor

    for(int i=0;i<=tablewidget->rowCount()-1;i++)
               {

                   QString pcname;
                   QString ip=tablewidget->item(i, 0)->text();
                   QString mac=tablewidget->item(i, 1)->text();
                   QString pcstate=tablewidget->item(i, 2)->text();
                   QString sshstate=tablewidget->item(i, 3)->text();
                   QString vncstate=tablewidget->item(i, 4)->text();
                   QString ftpstate=tablewidget->item(i, 5)->text();
                   QString connectstate=tablewidget->item(i, 6)->text();

                   if(tablewidget->item(i, 7)) pcname=tablewidget->item(i, 7)->text();
                   else pcname="";

                   iplistname=listRemove(iplistname,mac); //değişecek satır siliniyor


                   QString iptaleh=tablewidget->item(i, 8)->text();
                  // QString socketid=tablewidget->item(i, 9)->text();
                 //  QString linkid=tablewidget->item(i, 10)->text();
                 //  QString S=tablewidget->item(i, 11)->text();
                 //  QString V=tablewidget->item(i, 12)->text();
                  // QString F=tablewidget->item(i, 13)->text();

                 iplistname<<ip+"|"+mac+"|" +pcstate+"|" +sshstate+"|" +vncstate+"|" +ftpstate+"|"+connectstate+"|"+pcname+"|"+iptaleh+"|||||";
                 listToFile(iplistname,"iplistname");

                 QStringList persistlist=fileToList("persistlist");
                 persistlist=listRemove(persistlist,mac); //değişecek satır siliniyor
                 persistlist<<ip+"|"+mac+"|" +pcstate+"|" +sshstate+"|" +vncstate+"|" +ftpstate+"|"+connectstate+"|"+pcname+"|"+iptaleh+"|||||";
                 listToFile(persistlist,"persistlist");


    }


    //qDebug()<<"Mac Listesi Kaydedildi!";
   mesajSlot("Mac Listesi Kaydedildi!");

}
void MainWindow::printButtonSlot()
{

    QString strStream;
    QTextStream out(&strStream);

    const int rowCount =tablewidget->model()->rowCount();
    const int columnCount = tablewidget->model()->columnCount();
    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg(QString("Ağ IP ve Mac Adres Listesi"))
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead>";
    out << QString("<tr><th colspan=9>%1</th></tr>").arg(QString("Ağ IP ve Mac Adres Listesi"));

      out<<"<tr bgcolor=#f0f0f0>";

    for (int column = 0; column < columnCount; column++)
        if (!tablewidget->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(tablewidget->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column =0; column < columnCount; column++) {

            if (!tablewidget->isColumnHidden(column)) {
                QString data = tablewidget->model()->data(tablewidget->model()->index(row, column)).toString().simplified();
                QString bilgi=(!data.isEmpty()) ? data : QString("&nbsp;");
                if(column==0)
                out << QString("<td bkcolor=0 style='font-size:12px;'>%1-%2</td>").arg(QString::number(row+1),bilgi);
                else
                    out << QString("<td bkcolor=0 style='font-size:12px;'>%1</td>").arg(bilgi);
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;
    //printer.Orientation(QPrinter::Landscape);
    //printer.setOrientation(QPrinter::Landscape);
    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    printer.setOutputFileName(QDir::homePath()+"macliste.pdf");
  // printer.setOutputFormat(QPrinter::PdfFormat);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}

void MainWindow::cellDoubleClicked(int iRow, int iColumn)
{
     QString mac= tablewidget->item(iRow, 2)->text();
     QStringList list=fileToList("persistlist");
/******************************************************************/
    //QMessageBox::StandardButton reply;
    // reply = QMessageBox::question(this, "Uyarı", "Bilgisayar Silinecek! Emin misiniz?",
      //                             QMessageBox::Yes|tr(QMessageBox::No);
     QMessageBox messageBox(this);
     messageBox.setText("Uyarı");

     messageBox.setInformativeText("Host İçin İşlem Seçiniz!");
     QAbstractButton *evetButton =messageBox.addButton(tr("Sil"), QMessageBox::ActionRole);
     QAbstractButton *hayirButton =messageBox.addButton(tr("Düzenle"), QMessageBox::ActionRole);
     messageBox.setIcon(QMessageBox::Question);
             messageBox.exec();
             if (messageBox.clickedButton() == evetButton) {
                // qDebug()<<"evet basıldı";
                 list=listRemove(list,mac);
                 listToFile(list,"persistlist");
                 mesajSlot("Bilgisayar Listeden Silindi!");

                        macListWidget()->show();

             }
             if (messageBox.clickedButton() == hayirButton) {
                 //qDebug()<<"hayır basıldı";
             }


}


void MainWindow::slotVnc(QString _dsp){
    QString display=_dsp;
    QString  komut;
     komut.append("nohup ssvncviewer -scale 0.75 ").append(pcIp->text()).append(":"+display+" \-passwd \/usr\/bin\/x11vncpasswd &");
   ///   qDebug()<<"vnc:"<<komut;
    system(komut.toStdString().c_str());
    mesajSlot("Seçili Hostda Vnc Başlatıldı.");

  }
void MainWindow::slotVncFlip(QString scale,QString viewState){

    QString kmt10="kill $(ps -aux|grep 5901|awk '{print $2 }')";
    system(kmt10.toStdString().c_str());
    QString kmt20="";
    if(scale!="")
        kmt20="nohup /usr/bin/x11vnc -geometry "+scale+" -forever -loop -noxdamage -repeat -rfbauth /usr/bin/x11vncpasswd -rfbport 5901 -shared &";
    else
        kmt20="nohup /usr/bin/x11vnc -forever -loop -noxdamage -repeat -rfbauth /usr/bin/x11vncpasswd -rfbport 5901 -shared &";

    system(kmt20.toStdString().c_str());
    QString kmt11="sleep 1";
    system(kmt11.toStdString().c_str());

 hostAddressMacButtonSlot();
for(int k=0;k<ipmaclist.count();k++)
 {
    QString  kmt;
    kmt.append("vncviewer "+viewState+" -fullscreen ").append(ipmaclist[k].ip).append(":5901 \-passwd \/usr\/bin\/x11vncpasswd");
      for(int i=0;i<btnlist.count();i++)
     {
         if(btnlist[i]->cs=="online"&&
         (btnlist[i]->select||btnlist[i]->multiSelect)&&
         ipmaclist[k].ip.section(".",0,2)==btnlist[i]->ip.section(".",0,2))
         {
             udpSendData("x11komut",kmt,btnlist[i]->ip);
         }
     }
     system("sleep 0.1");
 }
mesajSlot("Seçili Hostlara Ekran Yansıltıldı.");

}
void MainWindow::slotVncFlipStop(){
    QString  kmt;
    kmt.append("pkill vncviewer");
      for(int i=0;i<btnlist.count();i++)
    {
        if(btnlist[i]->cs=="online"&&(btnlist[i]->select||btnlist[i]->multiSelect))
        {
             udpSendData("x11komut",kmt,btnlist[i]->ip);
        }
    }
    QString kmt10="kill $(ps -aux|grep 5901|awk '{print $2 }')";
    system(kmt10.toStdString().c_str());
    mesajSlot("Seçili Hostlarda Ekran Yansıtma Durduruldu.");

}
void MainWindow::slotVncFlipAll(QString scale,QString viewState){
    QString kmt10="kill $(ps -aux|grep 5901|awk '{print $2 }')";
    system(kmt10.toStdString().c_str());

    QString kmt20="";
    if(scale!="")
    kmt20="nohup /usr/bin/x11vnc -geometry "+scale+" -forever -loop -noxdamage -repeat -rfbauth /usr/bin/x11vncpasswd -rfbport 5901 -shared &";
    else
    kmt20="nohup /usr/bin/x11vnc -forever -loop -noxdamage -repeat -rfbauth /usr/bin/x11vncpasswd -rfbport 5901 -shared &";
    system(kmt20.toStdString().c_str());
    QString kmt11="sleep 1";
    system(kmt11.toStdString().c_str());
    hostAddressMacButtonSlot();
   for(int k=0;k<ipmaclist.count();k++)
    {
       QString  kmt;
       kmt.append("vncviewer "+viewState+" -fullscreen ").append(ipmaclist[k].ip).append(":5901 \-passwd \/usr\/bin\/x11vncpasswd");
         for(int i=0;i<btnlist.count();i++)
        {
            if(btnlist[i]->cs=="online"&&
            ipmaclist[k].ip.section(".",0,2)==btnlist[i]->ip.section(".",0,2))
            {
                udpSendData("x11komut",kmt,btnlist[i]->ip);
            }
        }
        system("sleep 0.1");
    }
   mesajSlot("Tüm Hostlara Ekran Yansıltıldı.");

}
void MainWindow::slotVncFlipAllStop(){
    QString  kmt;
    kmt.append("pkill vncviewer");
      for(int i=0;i<btnlist.count();i++)
    {
        if(btnlist[i]->cs=="online")
        {
             udpSendData("x11komut",kmt,btnlist[i]->ip);
        }
    }
    QString kmt10="kill $(ps -aux|grep 5901|awk '{print $2 }')";
    system(kmt10.toStdString().c_str());
    mesajSlot("Tüm Hostlarda Ekran Yansıtma Durduruldu.");

}
void MainWindow::slotRdp(){
    hostAddressMacButtonSlot();
    QString  komut;
            QMessageBox msgBox;
             msgBox.setText(" Uzak masaüstüne açık olan kullanıcı hesabından erişemezsiniz."
                            "\n Eğer uzak masaüstüne erişemiyorsanız;"
                            "\n Açık masaüstü için Vnc seçeneklerini kullanın.");
             msgBox.exec();

    komut.append("nohup  rdesktop ").append(" -u ").append(remoteUserName).append(" -p ").append(remotePassword+" ").append(pcIp->text()).append(" -g 75% &");
 system(komut.toStdString().c_str());
 //qDebug()<<"rdp:"<<komut;
 mesajSlot("Seçili Hostda Rdp Başlatıldı.");

  }
void MainWindow::slotFtp(){
ftpConnectButtonSlot();
mesajSlot("Seçili Hostda Ftp Başlatıldı.");

}
void MainWindow::slotKilit(){
    slotPcCommandSelect("gsettings set org.gnome.settings-daemon.plugins.power power-button-action nothing");
    system("sleep 1");
    for(int i=0;i<btnlist.count();i++)
    {
         if(btnlist[i]->cs=="online"&&(btnlist[i]->select||btnlist[i]->multiSelect))
         {
             btnlist[i]->setKilitControlState(true);
             pcKilitStateControlSignalSlot(btnlist[i]->mac,btnlist[i]->ip,true);//kilitle
           }
    }
    mesajSlot("Seçili Hostlarda Ekran Kilitlendi.");

}
void MainWindow::slotKilitAll(){
    slotPcCommandAll("gsettings set org.gnome.settings-daemon.plugins.power power-button-action nothing");
    system("sleep 1");

    for(int i=0;i<btnlist.count();i++)
    {
        if(btnlist[i]->cs=="online")
        {
            btnlist[i]->setKilitControlState(true);
            pcKilitStateControlSignalSlot(btnlist[i]->mac,btnlist[i]->ip,true);//kilitle

        }
    }
    mesajSlot("Tüm Hostlar kilitlendi.");

}
void MainWindow::slotTransparanKilit()
{
    slotPcCommandSelect("gsettings set org.gnome.settings-daemon.plugins.power power-button-action nothing");
    system("sleep 1");

    for(int i=0;i<btnlist.count();i++)
    {
        if(btnlist[i]->cs=="online"&&(btnlist[i]->select||btnlist[i]->multiSelect))
        {
            btnlist[i]->setKilitTransparanControlState(true);
            pcKilitTransparanStateControlSignalSlot(btnlist[i]->mac,btnlist[i]->ip,true);
        }
    }
    mesajSlot("Seçili Hostlar Şeffaf Kilitlendi.");

}
void MainWindow::slotTransparanKilitAll()
{
    slotPcCommandAll("gsettings set org.gnome.settings-daemon.plugins.power power-button-action nothing");
    system("sleep 1");

   for(int i=0;i<btnlist.count();i++)
    {
         if(btnlist[i]->cs=="online")
         {
             btnlist[i]->setKilitTransparanControlState(true);
             pcKilitTransparanStateControlSignalSlot(btnlist[i]->mac,btnlist[i]->ip,true);

           }
    }
   mesajSlot("Tüm Hostlar Şeffaf Kilitlendi.");

}
void MainWindow::slotKilitAc(){
    slotPcCommandSelect("gsettings set org.gnome.settings-daemon.plugins.power power-button-action interactive");
     system("sleep 1");
    for(int i=0;i<btnlist.count();i++)
    {
         if(btnlist[i]->cs=="online"&&(btnlist[i]->select||btnlist[i]->multiSelect))
            {
                btnlist[i]->setKilitControlState(false);
                pcKilitStateControlSignalSlot(btnlist[i]->mac,btnlist[i]->ip,false);//kilit aç

             }
    }
    mesajSlot("Seçili Hostlarda Kilit Açıldı.");

}
void MainWindow::slotTransparanKilitAc(){
    slotPcCommandSelect("gsettings set org.gnome.settings-daemon.plugins.power power-button-action interactive");
     system("sleep 1");

    for(int i=0;i<btnlist.count();i++)
    {
         if(btnlist[i]->cs=="online"&&(btnlist[i]->select||btnlist[i]->multiSelect))
            {
                 btnlist[i]->setKilitTransparanControlState(false);
                 pcKilitTransparanStateControlSignalSlot(btnlist[i]->mac,btnlist[i]->ip,false);//kilit aç

             }
    }
    mesajSlot("Seçili Hostlarda Şeffaf Kilit Açıldı.");

}
void MainWindow::slotKilitAcAll(){
    slotPcCommandAll("gsettings set org.gnome.settings-daemon.plugins.power power-button-action interactive");
     system("sleep 1");

    for(int i=0;i<btnlist.count();i++)
    {
         if(btnlist[i]->cs=="online")
            {
                btnlist[i]->setKilitControlState(false);
                btnlist[i]->setKilitTransparanControlState(false);
                pcKilitStateControlSignalSlot(btnlist[i]->mac,btnlist[i]->ip,false);//kilit aç

             }
    }
    mesajSlot("Tüm Hostlarda Kilit Açıldı.");

}
void MainWindow::slotTransparanKilitAcAll(){
    slotPcCommandAll("gsettings set org.gnome.settings-daemon.plugins.power power-button-action interactive");
     system("sleep 1");

    for(int i=0;i<btnlist.count();i++)
    {
         if(btnlist[i]->cs=="online")
            {
             btnlist[i]->setKilitTransparanControlState(false);
             pcKilitTransparanStateControlSignalSlot(btnlist[i]->mac,btnlist[i]->ip,false);//kilit aç

             }
    }
    mesajSlot("Tüm Hostlarda Şeffaf Kilit Açıldı.");

}
void MainWindow::slotLogin(){

 }
void MainWindow::slotLogout(){
    QString komut="loginctl terminate-seat seat0";
    for(int i=0;i<btnlist.count();i++)
    {
        if(btnlist[i]->cs=="online"&&(btnlist[i]->select||btnlist[i]->multiSelect))
        {
            udpSendData("pckapat",komut,btnlist[i]->ip);
        }
    }
    mesajSlot("Seçili Hostlarda Oturum Kapatıldı.");

}
void MainWindow::slotLogoutAll(){
    QString komut="loginctl terminate-seat seat0";
    for(int i=0;i<btnlist.count();i++)
    {
        if(btnlist[i]->cs=="online")
        {
            udpSendData("pckapat",komut,btnlist[i]->ip);
        }
    }
    mesajSlot("Tüm Hostlarda Oturum Kapatıldı.");

}
void MainWindow::slotReboot(){
    for(int i=0;i<btnlist.count();i++)
    {
        if(btnlist[i]->cs=="online"&&(btnlist[i]->select||btnlist[i]->multiSelect))
        {
            udpSendData("pcbaslat","/sbin/reboot",btnlist[i]->ip);
            btnlist[i]->setTcpConnect(false);
            btnlist[i]->setSshConnect(false);
            btnlist[i]->setVncConnect(false);
            btnlist[i]->setFtpConnect(false);
            btnlist[i]->setUser("noLogin");
            btnlist[i]->tcpConnectCounter=0;
        }
    }
    mesajSlot("Seçili Hostlar Yeniden Başlatıldı.");

}
void MainWindow::slotRebootAll(){
    for(int i=0;i<btnlist.count();i++)
    {
        if(btnlist[i]->cs=="online")
        {
            udpSendData("pcbaslat","/sbin/reboot",btnlist[i]->ip);
            btnlist[i]->setTcpConnect(false);
            btnlist[i]->setSshConnect(false);
            btnlist[i]->setVncConnect(false);
            btnlist[i]->setFtpConnect(false);
            btnlist[i]->setUser("noLogin");
            btnlist[i]->tcpConnectCounter=0;
        }
    }
    mesajSlot("Tüm Hostlar Yeniden Başlatıldı.");

}
void MainWindow::slotPowerOff(){
    for(int i=0;i<btnlist.count();i++)
    {
        if(btnlist[i]->cs=="online"&&(btnlist[i]->select||btnlist[i]->multiSelect))
        {
            udpSendData("pckapat","/sbin/poweroff",btnlist[i]->ip);
            btnlist[i]->setTcpConnect(false);
            btnlist[i]->setSshConnect(false);
            btnlist[i]->setVncConnect(false);
            btnlist[i]->setFtpConnect(false);
            btnlist[i]->setUser("noLogin");
            btnlist[i]->tcpConnectCounter=0;
        }
    }
    mesajSlot("Seçili Hostlar Kapatıldı.");

}
void MainWindow::slotPowerOffAll(){
    for(int i=0;i<btnlist.count();i++)
    {
        if(btnlist[i]->cs=="online")
        {
            udpSendData("pckapat","/sbin/poweroff",btnlist[i]->ip);
            btnlist[i]->setTcpConnect(false);
            btnlist[i]->setSshConnect(false);
            btnlist[i]->setVncConnect(false);
            btnlist[i]->setFtpConnect(false);
            btnlist[i]->setUser("noLogin");
            btnlist[i]->tcpConnectCounter=0;
        }
    }
    mesajSlot("Tüm Hostlar Kapatıldı.");

}
void MainWindow::slotSelectPcMesaj(QString _msg){
    for(int i=0;i<btnlist.count();i++)
    {
        if(btnlist[i]->cs=="online"&&(btnlist[i]->select||btnlist[i]->multiSelect))
        {
            udpSendData("ekranmesaj",_msg,btnlist[i]->ip);
        }
    }
    mesajSlot("Seçili Hostlara Mesaj Gönderildi.");

}
void MainWindow::slotEkranIzle()
{
    for(int i=0;i<btnlist.count();i++)
    {
        if(btnlist[i]->cs=="online"&&(btnlist[i]->select||btnlist[i]->multiSelect))
        {
            btnlist[i]->setIconControlState(true);
            pcIconStateControlSignalSlot(btnlist[i]->mac,btnlist[i]->ip,true);//kilitle

        }
    }
    mesajSlot("Seçili Ekran İzlemeler Başlatıldı.");

}
void MainWindow::slotEkranIzleDurdur()
{
    for(int i=0;i<btnlist.count();i++)
    {
        if(btnlist[i]->cs=="online"&&(btnlist[i]->select||btnlist[i]->multiSelect))
        {
            btnlist[i]->setIconControlState(false);
            pcIconStateControlSignalSlot(btnlist[i]->mac,btnlist[i]->ip,false);//kilitle

        }
    }
    mesajSlot("Seçili Ekran İzlemeler Durduruldu.");

}
void MainWindow::slotEkranIzleAll()
{
    for(int i=0;i<btnlist.count();i++)
    {
        if(btnlist[i]->cs=="online")
        {
              btnlist[i]->setIconControlState(true);
              pcIconStateControlSignalSlot(btnlist[i]->mac,btnlist[i]->ip,true);//kilitle

        }
    }
    mesajSlot("Tüm Ekran İzlemeler Başlatıldı.");

}
void MainWindow::slotEkranIzleAllDurdur()
{
    for(int i=0;i<btnlist.count();i++)
    {
        if(btnlist[i]->cs=="online")
        {
             btnlist[i]->setIconControlState(false);
             pcIconStateControlSignalSlot(btnlist[i]->mac,btnlist[i]->ip,false);//kilitle

        }
    }
    mesajSlot("Tüm Ekran İzlemeler Durduruldu.");

}
void MainWindow::slotCommand(QString _kmt)
{
       for(int i=0;i<btnlist.count();i++)
    {
        if(btnlist[i]->cs=="online"&&(btnlist[i]->select||btnlist[i]->multiSelect))
        {
              udpSendData("x11komut",_kmt,btnlist[i]->ip);
         }
    }
       mesajSlot("Komut Seçili Hostlarda Çalıştırıldı.");

}
void MainWindow::slotPcCommandSelect(QString _kmt){
    for(int i=0;i<btnlist.count();i++)
    {
       if(btnlist[i]->select||btnlist[i]->multiSelect)
        {
             udpSendData("x11komut",_kmt,btnlist[i]->ip);

       }
    }
    mesajSlot("Komut Seçili Hostlarda Çalıştırıldı.");

 }
void MainWindow::slotPcCommandAll(QString _kmt){
    for(int i=0;i<btnlist.count();i++)
    {

             udpSendData("x11komut",_kmt,btnlist[i]->ip);


    }
    mesajSlot("Komut Tüm Hostlarda Çalıştırıldı.");

 }

QString MainWindow::getIpPortStatus(QString ip_,QString port)
{
    QString result="";
    QStringList arguments;
    arguments << "-c" << QString("nc -zv -w1 %1 %2 2>&1|grep 'open'|wc -l").arg(ip_,port);
    QProcess process;
    process.start("/bin/bash",arguments);
    if(process.waitForFinished(-1))
    {
        result = process.readAll();
        result.chop(1);
    }
    qDebug()<<"Port sorgulama:"<<ip_<<result<<port;
    if(result.toInt()>0){ return "open";}
    else {return "close";}
}
void MainWindow::slotServisControl()
{
    QString F="e",fs;
    QString S="e",ss;
    QString V="e",vs;
    QString C="e",cs="online",ps="pcopen";

    if (getIpPortStatus(pcIp->text(),"5900")=="open"){ vs="vncopen";}
    else {vs="vncclose";V="h";}

    if (getIpPortStatus(pcIp->text(),"22")=="open"){ ss="sshopen";}
    else {ss="sshclose";S="h";}

    if (getIpPortStatus(pcIp->text(),"21")=="open") {fs="ftpopen";}
    else {fs="ftpclose";F="h";}

   /// servisStateUpdate();

    QStringList list=fileToList("iplistname");
    QString line=listGetLine(list,pcMac->text());
    list=listRemove(list,pcMac->text()); //değişecek satır siliniyor

    list<<pcIp->text()+"|"+pcMac->text()+"|" +ps+"|" +ss+"|" +vs+"|"+fs+"|"+ cs+"|"+line.split("|")[7]+"|"+line.split("|")[8];
    listToFile(list,"iplistname");
    mesajSlot("Hosta ait servisler kontrol edildi.");

}
void MainWindow::sshFileCopyAllSlot(QString _sourcePath,QString _targetPath)
{
    for(int i=0;i<btnlist.count();i++)
    {
      //  if(btnlist[i]->ss=="sshopen")
        {
            QString komut="nohup sshpass -p "+remotePassword+" scp -o StrictHostKeyChecking=no "+_sourcePath+" "+
                    remoteUserName+"@"+btnlist[i]->ip+":"+_targetPath+" &";
            //         sshpass -p 1299+1923tr  scp -o StrictHostKeyChecking=no iplistname etapadmin@10.107.248.247:/usr/share/e-ag/
            // qDebug()<<komut;
            mesajSlot(komut);
            QStringList arguments;
            arguments << "-c" << komut;
            QProcess process;
            process.start("/bin/bash",arguments);
            process.waitForFinished(-1); // will wait forever until finished
        }
    }
    mesajSlot("Komut Ağ'da Çalıştırıldı");
    mesajSlot("Dosya Ağ'da Bütün Pc'lere Kopyalandı");
}
void MainWindow::sshSelectFileCopySlot(QString _sourcePath,QString _targetPath)
{
    for(int i=0;i<btnlist.count();i++)
    {
        if((btnlist[i]->select||btnlist[i]->multiSelect))
        {
            //if(btnlist[i]->ss=="sshopen")
            {
            QString komut="nohup sshpass -p "+remotePassword+" scp -o StrictHostKeyChecking=no "+_sourcePath+" "+
                    remoteUserName+"@"+btnlist[i]->ip+":"+_targetPath+" &";
            //         sshpass -p 1299+1923tr  scp -o StrictHostKeyChecking=no iplistname etapadmin@10.107.248.247:/usr/share/e-ag/
            // qDebug()<<komut;
            mesajSlot(komut);
            QStringList arguments;
            arguments << "-c" << komut;
            QProcess process;
            process.start("/bin/bash",arguments);
            process.waitForFinished(-1); // will wait forever until finished
            }
        }
    }
    mesajSlot("Dosya Seçili Pc'lere Kopyalandı");
}
void MainWindow::fileHostportCopyAllSlot()
{
    QStringList liste=fileToList("iplistname");
/*********************************************************/

    for(int i=0;i<liste.count();i++)
    {
        QString line=liste[i];
        line.chop(1);
        QStringList lst=line.split("|");

        // qDebug()<<lst[0]<<lst[3];
        if (lst[6]=="online")//sshstate
        {
            //sshpass -p $parola scp $dosya $username@$name:/home/$username/
            QString komut="nohup sshpass -p "+remotePassword+" scp -o StrictHostKeyChecking=no "+localDir+"hostport "+
                    remoteUserName+"@"+lst[0]+":/usr/share/e-ag/&";
            ///qDebug()<<komut;
            mesajSlot(komut);
            QStringList arguments;
            arguments << "-c" << komut;
            QProcess process;
            process.start("/bin/bash",arguments);
            process.waitForFinished(-1); // will wait forever until finished

        }

    }
    mesajSlot("Dosya Ağ'da Bütün Pc'lere Kopyalandı");
}
void MainWindow::sshCommandAllSlot(QString kmt)
{
    for(int i=0;i<btnlist.count();i++)
    {
        //if(btnlist[i]->ss=="sshopen")
        {
           /* QString komut="nohup sshpass -p "+remotePassword+" ssh -o StrictHostKeyChecking=no -n "+
                    remoteUserName+"@"+btnlist[i]->ip+" 'echo "+remotePassword+" | sudo -S' "+kmt+" &";
            */
            QString komut="nohup sshpass -p "+remotePassword+" ssh -o CheckHostIP=no -o StrictHostKeyChecking=no -n "+
                  remoteUserName+"@"+btnlist[i]->ip+" 'echo "+remotePassword+" | sudo -S' "+kmt+ "&";

             system(komut.toStdString().c_str());

            mesajSlot(komut);
            //qDebug()<<komut;
            QStringList arguments;
            arguments << "-c" << komut;
            QString result;
            QProcess process;
          /*  process.start("/bin/bash",arguments);
            if(process.waitForFinished())
            {
                result = process.readAll();
            }*/
           /// return result;
        }
    }
     mesajSlot("Komut Tüm Ağ'da Çalıştırıldı.");
}
void MainWindow::sshSelectPcCommandSlot(QString kmt)
{
    for(int i=0;i<btnlist.count();i++)
    {
      //  qDebug()<<"pc: "<<btnlist[i]->ip<<btnlist[i]->ss<<btnlist[i]->select<<btnlist[i]->multiSelect;

        if((btnlist[i]->select||btnlist[i]->multiSelect))
        {
           // if(btnlist[i]->ss=="sshopen")
            {
                QString komut="nohup sshpass -p "+remotePassword+" ssh -o CheckHostIP=no -o StrictHostKeyChecking=no -n "+
                        remoteUserName+"@"+btnlist[i]->ip+" 'echo "+remotePassword+" | sudo -S' "+kmt+ "&";

                //system(komut.toStdString().c_str());

                mesajSlot(komut);
                //qDebug()<<komut;
                QStringList arguments;
                arguments << "-c" << komut;
                QString result;
                QProcess process;
                 process.start("/bin/bash",arguments);
            if(process.waitForFinished())
            {
                result = process.readAll();
            }
                // return result;
            }
        }
    }
   // return "";
     mesajSlot("Komut Seçili Hostlarda Çalıştırıldı.");
}
void MainWindow::sshCommandSlot(QString kmt,QString _ip)
{
    QString komut="nohup sshpass -p "+remotePassword+" ssh -o CheckHostIP=no -o StrictHostKeyChecking=no -n "+
    remoteUserName+"@"+_ip+" 'echo "+remotePassword+" | sudo -S' "+kmt+ "&";
   // system(komut.toStdString().c_str());
    mesajSlot(komut);
    QStringList arguments;
    arguments << "-c" << komut;
    QString result;
    QProcess process;
    process.start("/bin/bash",arguments);
    if(process.waitForFinished())
    {
        result = process.readAll();
    }
    mesajSlot("Komut Seçili Hostlarda Çalıştırıldı.");

}
#endif // FUNTION_H
