#ifndef MYBUTTON_H
#define MYBUTTON_H
#pragma once

#include <QPushButton>

class MyButton : public QPushButton
{
public:
    explicit MyButton(QWidget* parent = nullptr);
    virtual ~MyButton();

    void setPixmap(const QPixmap& pixmap);

    virtual QSize sizeHint() const override;

protected:
    virtual void paintEvent(QPaintEvent* e) override;

private:
    QPixmap m_pixmap;
};
#endif // MYBUTTON_H
