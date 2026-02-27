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
    setFixedSize(w,h);
    setWindowTitle("Multicast Address ");

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

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(saveButton);
    btnLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(label);
    mainLayout->addWidget(hostnameEdit);
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
