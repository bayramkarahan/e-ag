#include "mybutton.h"

#include <QPainter>

MyButton::MyButton(QWidget* parent) : QPushButton(parent)
{
}

MyButton::~MyButton()
{
}

QSize MyButton::sizeHint() const
{
    const auto parentHint = QPushButton::sizeHint();
    // add margins here if needed
    return QSize(parentHint.width() + m_pixmap.width(), std::max(parentHint.height(), m_pixmap.height()));
}

void MyButton::setPixmap(const QPixmap& pixmap)
{
    m_pixmap = pixmap;
}

void MyButton::paintEvent(QPaintEvent* e)
{
    QPushButton::paintEvent(e);

    if (!m_pixmap.isNull())
    {
        const int y = (height() - m_pixmap.height()) / 2; // add margin if needed
        QPainter painter(this);
        painter.drawPixmap(5, y, m_pixmap); // hardcoded horizontal margin
    }
}
