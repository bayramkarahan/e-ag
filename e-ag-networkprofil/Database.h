#ifndef DATABASE_H
#define DATABASE_H
#include<QSettings>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include<QSize>
class DatabaseHelper
{
public:
    QString dosyaYolu;
    DatabaseHelper(QString _dosyayolu){
        dosyaYolu=_dosyayolu;
        QFile dosya(dosyaYolu);
        if (!dosya.exists()) {
            qDebug() << "Veritabanı Dosyası Yok.. Yeni Açılıyor!";

            dosya.open(QIODevice::WriteOnly);
            //QJsonObject veri;
            //Ekle(veri);
            dosya.close();
        }
    }

    // Verileri dosyaya kaydetme
   void Kaydet(const QJsonArray &veriler) {
        QFile dosya(dosyaYolu);
        if (!dosya.open(QIODevice::WriteOnly)) {
            qDebug() << "Dosya açma hatası!";
            return;
        }

        QJsonDocument jsonDoc(veriler);
        dosya.write(jsonDoc.toJson());
        dosya.close();
    }

    // Verileri dosyadan okuma
    QJsonArray Oku() {
        QFile dosya(dosyaYolu);
        if (!dosya.open(QIODevice::ReadOnly)) {
            qDebug() << "Dosya açma hatası!";
            return QJsonArray();
        }

        QByteArray veri = dosya.readAll();
        dosya.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(veri);
         //if (jsonDoc.isNull() || !jsonDoc.isArray()) {
        if (jsonDoc.isNull() || !jsonDoc.isArray()) {
            qDebug() << "Geçersiz JSON verisi!";
            return QJsonArray();
        }

        return jsonDoc.array();
    }

    int getIndex(const QString &anahtar)
    {
        int indexnumber=0;
        for (const QJsonValue &veri :Oku()) {
            if (veri.toObject().value(anahtar).toString().toInt()>indexnumber) {
                indexnumber=veri.toObject().value(anahtar).toString().toInt();
            }
        }
        indexnumber++;
        return indexnumber;
    }
    void Ekle(const QJsonObject &yeniVeri) {
        QJsonArray veriler = Oku();
        veriler.append(yeniVeri);
        Kaydet(veriler);
    }

    QJsonArray Ara(const QString &anahtar, const QJsonValue &deger) {
        QJsonArray veriler = Oku();
        QJsonArray sonuc;

        for (const QJsonValue &veri : veriler) {
            if (veri.isObject() && veri.toObject().contains(anahtar) && veri.toObject().value(anahtar) == deger) {
                sonuc.append(veri.toObject());
            }
        }

        return sonuc;
    }

    // Örnek kullanım:
    ///QJsonArray bulunanKayitlar = verileriAra("ad", "Ayşe");
    //qDebug() << bulunanKayitlar;
    void Sil(const QString &anahtar, const QJsonValue &deger) {
        QJsonArray veriler = Oku();
        QJsonArray guncellenmisVeriler;

        for (const QJsonValue &veri : veriler) {
            if (veri.isObject() && (!veri.toObject().contains(anahtar) || veri.toObject().value(anahtar) != deger)) {
                guncellenmisVeriler.append(veri.toObject());
            }
        }

        Kaydet(guncellenmisVeriler);
    }

    // Örnek kullanım:
    //veriSil("ad", "Ayşe");


    void network1Save()
    {
        QString appPath ="/usr/share/e-ag";
        QSettings ayarlar(appPath + "/e-ag.cfg",QSettings::IniFormat);
        ayarlar.setValue("selectNetworkProfil1", true);
        ayarlar.setValue("networkProfil1", "Netwokr-1");
        ayarlar.setValue("networkTcpPort1", 7879);
        ayarlar.setValue("networkBroadCastAddress11", 800);
        ayarlar.setValue("networkBroadCastAddress12", 800);
    }
    void Remove()
    {
        QString appPath ="/usr/share/e-ag";
        QSettings ayarlar(appPath + "/persistlist1.cfg","hosts");
        ayarlar.remove("sonKullanilanDosya");
        ayarlar.remove("pencereBoyutu");
    }
    void Find()
    {
        QString appPath ="/usr/share/e-ag";
        QSettings ayarlar(appPath + "/e-ag.cfg",QSettings::IniFormat);
        QString sonDosya = ayarlar.value("sonKullanilanDosya").toString();
        int genislik = ayarlar.value("pencereGenisligi", 640).toInt(); // Varsayılan değer 640
        QSize boyut = ayarlar.value("pencereBoyutu").toSize();
    }

};

#endif // DATABASE_H
