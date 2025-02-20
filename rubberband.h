#ifndef RUBBERBAND_H
#define RUBBERBAND_H

#include <QRubberBand>
#include <QPaintEvent>

class RubberBand : public QRubberBand
{
    Q_OBJECT
public:
    explicit RubberBand(Shape s, QWidget * p = 0);


signals:

protected:
    void paintEvent(QPaintEvent *event);

public slots:

};

#endif // RUBBERBAND_H
