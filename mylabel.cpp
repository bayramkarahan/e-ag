#include "mylabel.h"

MyLabel::MyLabel( ) :
    QLabel()

  {

  }

  MyLabel::~MyLabel()
  {
  }

  void MyLabel::mousePressEvent ( QMouseEvent * event )

  {
      emit clicked();
  }
