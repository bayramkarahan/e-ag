#ifndef DATABASE_H
#define DATABASE_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

class DatabaseHelper
{
public:
    QString dosyaYolu;

    explicit DatabaseHelper(const QString &_dosyayolu) {
        dosyaYolu = _dosyayolu;
        QFile dosya(dosyaYolu);
        if (!dosya.exists()) {
            qDebug() << "Veritabanı dosyası yok, yeni oluşturuluyor:" << dosyaYolu;
            if (dosya.open(QIODevice::WriteOnly)) {
                QJsonDocument bos{ QJsonArray() };   // ✅ doğru biçim
                dosya.write(bos.toJson());
                dosya.close();
            }
        }

    }

    void Kaydet(const QJsonArray &veriler) {
        QFile dosya(dosyaYolu);
        if (!dosya.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            qDebug() << "Dosya açma hatası!";
            return;
        }
        QJsonDocument jsonDoc(veriler);
        dosya.write(jsonDoc.toJson());
        dosya.close();
    }

    QJsonArray Oku() {
        QFile dosya(dosyaYolu);
        if (!dosya.open(QIODevice::ReadOnly))
            return QJsonArray();

        QByteArray veri = dosya.readAll();
        dosya.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(veri);
        if (jsonDoc.isNull() || !jsonDoc.isArray())
            return QJsonArray();

        return jsonDoc.array();
    }

    /*int getIndex(const QString &anahtar) {
        int indexnumber = 0;
        for (const QJsonValue &veri : Oku()) {
            int val = veri.toObject().value(anahtar).toInt();
            if (val > indexnumber)
                indexnumber = val;
        }
        return indexnumber + 1;
    }
    */
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
    void Ekle(const QJsonObject &yeniVeri, const QString &uniqueKey = QString()) {
        QJsonArray veriler = Oku();
        if (!uniqueKey.isEmpty()) {
            QString newVal = yeniVeri.value(uniqueKey).toString();
            for (const QJsonValue &veri : veriler) {
                if (veri.toObject().value(uniqueKey).toString() == newVal)
                    return; // kayıt zaten var
            }
        }
        veriler.append(yeniVeri);
        Kaydet(veriler);
    }

    QJsonArray Ara(const QString &anahtar, const QJsonValue &deger) {
        QJsonArray sonuc;
        for (const QJsonValue &veri : Oku()) {
            if (!veri.isObject()) continue;
            QJsonObject obj = veri.toObject();
            if (obj.value(anahtar) == deger)
                sonuc.append(obj);
        }
        return sonuc;
    }

    void Sil(const QString &anahtar, const QJsonValue &deger) {
        QJsonArray guncel;
        for (const QJsonValue &veri : Oku()) {
            if (!veri.isObject()) continue;
            QJsonObject obj = veri.toObject();
            if (obj.value(anahtar) != deger)
                guncel.append(obj);
        }
        Kaydet(guncel);
    }
};

#endif // DATABASE_H
