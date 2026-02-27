#include "multicastaddressdialog.h".h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QProcess>
#include <QMessageBox>
#include <QFile>

MulticastAddressDialog::MulticastAddressDialog(int w, int h, QWidget *parent)
    : QDialog(parent)
{
    localDir="/usr/share/e-ag/";
    setFixedSize(w*2.7,h*2.2);
    setWindowTitle("Ağ Yayın Adresi(Multicast Address) ");

    QLabel *label = new QLabel("Yayın Adresi:");
    hostnameEdit = new QLineEdit;

    DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag-multicastaddress.json");
    QJsonArray dizi=db->Oku();
    if(dizi.count()>0)
    {
        QJsonValue item=dizi.first();
        QJsonObject veri=item.toObject();
        hostnameEdit->setText(veri["multicastAddress"].toString());
    }else
    {
        QJsonObject veri;
        veri["multicastAddress"]="239.255.0.11";
        db->TekKayitYaz(veri);
        hostnameEdit->setText(veri["multicastAddress"].toString());
    }


    saveButton = new QPushButton("Kaydet");
    cancelButton = new QPushButton("İptal");

    connect(saveButton, &QPushButton::clicked, this, &MulticastAddressDialog::saveMulticastAddress);
    connect(cancelButton, &QPushButton::clicked, this, &MulticastAddressDialog::reject);
    QLabel *aciklama = new QLabel(this);
    aciklama->setWordWrap(true);
    aciklama->setText("Yayın adresi(Multicast) Sunucu-İstemci arasında iletişim adresini ifade ediyor.\n"
                      "Yayın adresi, 239.255.0.11 varsayılan değerdir ve bu adres üzerinden haberleşir.\n"
                      "239.255.0.11 yayın adresi Sunucu-İstemci de aynı olmalıdır.\n"
                      "Aynı ağda birden fazla server farklı yayın adresleri kullanarak gruplamalar yapılabilir.\n"
                      "Örneğin;\n"
                      "\tAynı ağda iki farklı LAB varsa yayın adresleri, LAB1=239.255.0.11 ve LAB2=239.255.0.12 gibi ayarlanmalı.\n"
                      "Dikkat edilmesi gereken nokta Sunucu-İstemci de aynı yayın adresi olması.");
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(saveButton);
    btnLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(label);
    mainLayout->addWidget(hostnameEdit);
    mainLayout->addWidget(aciklama);

    mainLayout->addLayout(btnLayout);

    setLayout(mainLayout);
}

void MulticastAddressDialog::saveMulticastAddress()
{
    QString newHostname = hostnameEdit->text().trimmed();

    if (newHostname.isEmpty()) {
        QMessageBox::warning(this, "Hata", "Yayın adresi boş olamaz!");
        return;
    }

    DatabaseHelper *db=new DatabaseHelper(localDir+"e-ag-multicastaddress.json");
    QJsonObject veri;
    veri["multicastAddress"]=newHostname;
    db->TekKayitYaz(veri);
    hostnameEdit->setText(veri["multicastAddress"].toString());
    //updateHostsFile(newHostname);

    QMessageBox::information(this, "Başarılı",
                             "Sunucu yayın adresi başarıyla değiştirildi.");

    //system("systemctl restart e-ag-networkprofil.service");
    int ret = QProcess::execute("bash", QStringList() << "-c" << "systemctl restart e-ag-networkprofil.service");
    if (ret != 0) {
        QMessageBox::critical(this, "Hata", "e-ag-networkprofil yeniden başlatılamadı.");
        return;
    }

    accept();
}
