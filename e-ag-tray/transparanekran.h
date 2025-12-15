#ifndef TRANSPARANEKRAN_H
#define TRANSPARANEKRAN_H
#include <QCloseEvent>
#include<QWidget>
#include<QLabel>
#include<QDesktopWidget>
#include<QRect>
#include<QDebug>

class TransparanEkran : public QWidget
{
    Q_OBJECT
private:
     void closeEvent(QCloseEvent *bar)
    {
        // Do something
       // bar->accept();
          bar->ignore();
          hide();
    }

public:
     TransparanEkran()
     {
         setAttribute(Qt::WA_StaticContents);
         setAttribute(Qt::WA_TranslucentBackground, true);

         this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint
                              | Qt::X11BypassWindowManagerHint);

     }
       void ekranTransparanKilit()
    {
        QDesktopWidget widget;

        QRect desktopScreenSize = widget.availableGeometry(widget.primaryScreen());
        this->setFixedSize(desktopScreenSize.width(),desktopScreenSize.height()+35);
        this->setAttribute(Qt::WA_TranslucentBackground, true);
        this->setAttribute(Qt::WA_NoSystemBackground, false);
        this->setAttribute(Qt::WA_NoBackground,true);
        this->repaint();
        this->repaint();
        QPalette palet;
        palet.setBrush(QPalette::Background, QColor(0,0,0,1));
        this->setPalette(palet);  //setZeminColor(myZeminColor);



        this->move(0,0);




    }



};
#endif // TRANSPARANEKRAN_H
