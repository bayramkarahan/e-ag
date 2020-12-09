#ifndef BUTONCLICK_H
#define BUTONCLICK_H
void MainWindow::ayarKaydetButtonSlot()
{
    QStringList lst;
    hostAddressMacButtonSlot();
    if(tcpPort->text()=="")tcpPort->setText("7879");
    lst.append(myIpAddress+"|"+tcpPort->text()+"|Server");
    listToFile(lst,"hostport");

    QStringList ayar;
    QString ru="remoteUser|"+remoteUsername->text()+"|"+remotePassword->text();
    QString lu="localUser|"+localUsername->text()+"|"+localPassword->text();
    QString rn="localNetwork|"+localNetwork->text();
    QString tcp="tcpPort|"+tcpPort->text();
    ayar<<ru<<lu<<rn<<tcp;
    listToFile(ayar,"E-Ag.conf");

  }
void MainWindow::taramaButtonSlot()
{
    QMenu *taramaMenus=taramaMenu();
    taramaMenus->exec(mapToGlobal(taramaButton->pos() + QPoint(-40,20)));
}
void MainWindow::tcpekranKilitButtonSlot()
{
    timerClickSlot();
    QMenu *kilitMenus=kilitMenu();
    kilitMenus->exec(mapToGlobal(tcpekranKilitButton->pos() + QPoint(-40,40+boy*29+1)));
}
void MainWindow::tcpPanoButtonSlot()
{
    timerClickSlot();
    QMenu *panoMenus=panoMenu();
    panoMenus->exec(mapToGlobal(tcpPanoButton->pos() + QPoint(-40,40+boy*29+1)));
}
void MainWindow::tcpduyuruMesajButtonSlot()
{
    timerClickSlot();
    QMenu *duyuruMesajMenus=duyuruMesajMenu();
    duyuruMesajMenus->exec(mapToGlobal(tcpduyuruMesajButton->pos() + QPoint(-40,40+boy*29+1)));
}
void MainWindow::tcppcKapatButtonSlot()
{
    timerClickSlot();
    QMenu *kapatMenus=kapatMenu();
    kapatMenus->exec(mapToGlobal(tcppcKapatButton->pos() + QPoint(-40,40+boy*29+1)));
}
void MainWindow::tcpcommandsendMessageButtonSlot()
{
    timerClickSlot();
    QMenu *komutMenus=komutMenu();
    komutMenus->exec(mapToGlobal(tcpcommandsendMessageButton->pos() + QPoint(-40,40+boy*29+1)));

}
void MainWindow::tcpekranImageButtonSlot()
{
    timerClickSlot();
    QMenu *ekranImageMenus=ekranImageMenu();
    ekranImageMenus->exec(mapToGlobal(tcpekranImageButton->pos() + QPoint(-40,40+boy*29+1)));

}
void MainWindow::rdpButtonSlot()
{
    timerClickSlot();
    QMenu *rdpMenus=rdpMenu();
    rdpMenus->exec(mapToGlobal(vncConnectButton->pos() + QPoint(-40,40+boy*29+1)));
}

void MainWindow::bilgiAlButtonSlot()
{




    QMessageBox::information(this,"E-Ağ 4.0",
                              "\n\nUygulamanın sorunsuz çalışması için;"
                              "\n1-Bütün tahtaların kullanıcı adı şifresi aynı olmalıdır."
                              "\n2-Uygulamanın kurulu olduğu makine yönetici hesabıyla açılmış olmalı.."
                              "\n3-Uygulamadaki Yerel Ad-Şifre: yazılımın kurulu olduğu makine kullanıcı adı ve şifresi."
                              "\n4-Uygulamadaki Uzak Ad-Şifre: kontrol edilecek makinelerin kullanıcı adı ve sifresi."
                              "\n5-Uygulamadaki Yerel Ağ: bulunduğumuz ağ örn:192.168.1.255 şeklinde girilmeli."
                              "\n6-Uygulamadaki Tcp Port: yazılımın kullandığı port boş bırakılırsa 7879 olarak ayarlar."
                              "\n7-Yukarıdaki 1-6 maddeler mutlaka doldurulmalı ve '+' butonu ile kaydedilmeli."
                              "\n8-Bu bilgiler kaydedildikten sonra mutlaka yazılım yeniden başlatılmalı."
                              "\n\n9-Yapılan şifre, ip ve port değişikliklerini Client'ların algılaması için;."
                             "\nAraçlar menüsünden Client Ayarlarını Güncelle seçilmelidir.."
                              "\n10-Ftp servisi kurulu olmasına rağmen erişilmiyorsa $HOME/.ssh dizinindeki dosya silinmelidir.  "
                             "\n11-Pc'lerin sağ üst köşedeki ? işareti ile çalışan servisler o Pc için kontrol edilebilir."
                              "\n");



     QMessageBox::information(this,"E-Ağ 4.0",
                              "Bu uygulamayı kullanmaktan doğabilecek her türlü hukuki sorumluluğu kullanıcı kabul etmiş sayılır."
                              "\n\nBu uygulama etkileşimli tahtalarda kullanılmak üzere yazılmıştır."
                              "\n"
                              "\n Yapılabilecek Eylemler:"
                              "\n* Dosya Kopyalama"
                              "\n* Vnc Servisi Kurulu Bilgisayarlara Erişim"
                              "\n* Ssh Servisi Kurulu Bilgisayarlarda Komut Çalıştıma"
                              "\n* Ftp Servisi Kurulu Bilgisayarlara Dosya Yöneticisi İle Erişme"
                              "\n* Komutla Yapılabilen Bütün İşlemleri Yapma..."
                              "\n* Bireysel ya da Genel Mesajlar Gönderme Alma."
                              "\n"
                              "\n"
                              "\n\t         Bayram KARAHAN"
                              "\n\tBilişim Teknolojileri Öğretmeni"
                              "\n"
                              "\n"
                              "İstek ve önerileriniz için;"
                              "\nE-Posta: bayramk@gmail.com"
                              "\nwww.bayramkarahan.blogspot.com"
                              "\n");
       /*QMessageBox msgBox;
    msgBox.setText(str);
    msgBox.setStandardButtons(QMessageBox::Ok);msgBox.exec();
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");

*/
   //  layout->removeWidget(btnlist[2]);
//layout->update();
//qDebug()<<"işlem yapıldı";
}
void MainWindow::timerClickSlot()
{

   //qDebug()<<"copy timer";
    FileCrud *fc=new FileCrud();
    fc->dosya=localDir+"click";

   if((fc->fileExists()))
    {
        QString strmymac=fc->fileSearch("mac");strmymac.chop(1);
           QString mac=strmymac.split("=")[1];
      /////  qDebug()<<"okunan bilgi:"<<mac;
         QString line=listGetLine(fileToList("iplistname"),mac);
         if(line!="")
         {

         pcIp->setText(line.split("|")[0]);
         pcMac->setText(line.split("|")[1]);
         pcName->setText(line.split("|")[7]);
         socketNumberLabel->setText(line.split("|")[9]);
         if(line.split("|")[9]=="arpscan"||line.split("|")[9]=="nmapscan"||line.split("|")[9]=="disconnect")
         socketNumberLabel->setText("");
         pcNamelbl->setText("Seçili Bilgisayar: "+pcName->text());
         pcIplbl->setText("Ip: "+pcIp->text());
         pcMaclbl->setText("Mac: "+pcMac->text());
         destlabel->setText("Hedef: "+line.split("|")[7]);//pcname

         }

   }
}
#endif // BUTONCLICK_H
