#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H


QWidget*  MainWindow::sliderWidget()
{
    QWidget *sWidget=new QWidget();

    slider = new QSlider(sWidget);

    slider->setMinimum(50);
    slider->setMaximum(400);
    slider->setValue(100);
    slider->setSingleStep(50);
    //slider->setSingleStep(10);
    slider->setFixedSize(100,25);

    slider->setOrientation(Qt::Horizontal);
    slider->setStyleSheet("QSlider::groove:horizontal { "
                          "border: 0px solid #990000; "
                          "height: 5px; "
                          "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4); "
                          "margin: 5px 0px; "
                          "} "
                          "QSlider::handle:horizontal { "
                          "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #b4b4b4); "
                          "border: 0px solid #00005c; "
                          "width: 15px; "
                          "height: 8px; "
                          "margin: -8px 0px; "
                          "} ");

    QLabel *label1 = new QLabel("50",sWidget);
    QLabel *label2 = new QLabel("100",sWidget);
    QLabel *label3 = new QLabel("400",sWidget);
    sliderValuelabel = new QLabel("100",sWidget);
    int fnt=font.toInt();
    label1->setStyleSheet("font-size:"+QString::number(fnt-5)+"px; background-color:rgba(0,255,0,0);");
    label2->setStyleSheet("font-size:"+QString::number(fnt-5)+"px; background-color:rgba(0,255,0,0);");
    label3->setStyleSheet("font-size:"+QString::number(fnt-5)+"px; background-color:rgba(0,255,0,0);");
    sliderValuelabel->setStyleSheet("font-size:"+QString::number(fnt-5)+"px; background-color:rgba(0,255,0,0);");
    sliderValuelabel->setFixedSize(en*3,boy*4);
    QGridLayout *layouts = new QGridLayout(sWidget);
    layouts->setContentsMargins(0, 0, 0,0);
    layouts->setVerticalSpacing(0);
    layouts->setHorizontalSpacing(0);

    layouts->addWidget(slider, 0, 0, 1, 3,Qt::AlignCenter);
    layouts->addWidget(sliderValuelabel, 0, 3, 2, 1,Qt::AlignCenter);
    layouts->addWidget(label1, 1, 0, 1, 1,Qt::AlignLeft);
    layouts->addWidget(label2, 1, 1, 1, 1,Qt::AlignCenter);
    layouts->addWidget(label3, 1, 2, 1, 1,Qt::AlignRight);
    connect(slider, SIGNAL(valueChanged(int)), SLOT(updateSlider(int)),Qt::QueuedConnection);
    sWidget->setFixedSize(en*23,boy*5);
    sWidget->setLayout(layouts);
    return sWidget;
}

void MainWindow::updateSlider(int val)
{
    sliderValuelabel->setText(QString::number(val));
    //double nwidth=en*13*val/100;
    double nwidth=en*20*val/100;
    double nheight=en*20*val/100;
    int columnSayisi=hostListe->width()/(nwidth+en*4);
    //pcListeGuncelleSlot(columnSayisi,nwidth,nheight);
    pcListeGuncelleSlot("updateSlider");
    mesajSlot(tr("Host Boyutları Değiştirildi."));
}

#endif // SLIDERWIDGET_H
