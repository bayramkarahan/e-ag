#include "rubberband.h"
#include <QPainter>
RubberBand::RubberBand(QRubberBand::Shape s, QWidget *p) :
    QRubberBand(s,p)
{
}

void RubberBand::paintEvent(QPaintEvent *event)
{
    QRubberBand::paintEvent(event);
    QPainter p(this);
    p.setPen(QPen(Qt::black,2));
    if(size().width() >10 && size().height() >10)
    {
        p.drawText(20,20,QString("%1,%2").arg(size().width()).arg(size().height()));
    }
}
