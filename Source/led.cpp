#include "led.h"
#include <QPainter>

Led::Led(QWidget* parent)
  : QWidget(parent)
  , m_power(false) {
}

bool Led::power() const {
    return m_power;
}

void Led::setBrushes(QColor ONcolor, QColor Offcolor)
{

    this->ONcolor=ONcolor;
    this->OFFcolor=Offcolor;
}

void Led::setPower(bool power) {
  if(power != m_power) {
    m_power = power;
    emit powerChanged(power);
    update();
  }
}

void Led::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event)
  QPainter ledPainter(this);
  ledPainter.setPen(Qt::black);
  if(m_power)
    ledPainter.setBrush(ONcolor);
  else
    ledPainter.setBrush(Qt::NoBrush);

  ledPainter.drawEllipse(rect().adjusted(0, 0, -1, -1));
}
