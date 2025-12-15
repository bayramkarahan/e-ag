#ifndef CUSTOMINPUTDIALOG_H
#define CUSTOMINPUTDIALOG_H
#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QDebug>

class CustomInputDialog : public QDialog {
public:
    CustomInputDialog(QString baslik, QString girdimesaj, QString defaultvalue,int w,int h,QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle(baslik);

        label_ = new QLabel(girdimesaj);
        lineEdit_ = new QLineEdit;
        lineEdit_->setText(defaultvalue);
        okButton_ = new QPushButton(tr("Tamam"));
        cancelButton_ = new QPushButton(tr("İptal"));

        QHBoxLayout *buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(okButton_);
        buttonLayout->addWidget(cancelButton_);

        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addWidget(label_);
        mainLayout->addWidget(lineEdit_);
        mainLayout->addLayout(buttonLayout);

        setLayout(mainLayout);
        resize(w, h); // Başlangıç boyutunu ayarlayın

        connect(okButton_, &QPushButton::clicked, this, &CustomInputDialog::accept);
        connect(cancelButton_, &QPushButton::clicked, this, &CustomInputDialog::reject);
    this->exec();
    }

    QString getText() const {

        return lineEdit_->text();
    }

private:
    QLabel *label_;
    QLineEdit *lineEdit_;
    QPushButton *okButton_;
    QPushButton *cancelButton_;
};

#endif // CUSTOMINPUTDIALOG_H
