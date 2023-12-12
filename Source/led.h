#ifndef LED_H
#define LED_H

#include <QWidget>
#include <QDebug>
class Led : public QWidget {
  Q_OBJECT
  Q_PROPERTY(bool power READ power WRITE setPower NOTIFY powerChanged)
  Led(const Led&) = delete;
  Led& operator=(const Led&) = delete;
 public:
  explicit Led(QWidget* parent = nullptr);
  bool power() const;
  void setBrushes(QColor ONcolor=Qt::green,QColor Offcolor=Qt::NoBrush);
 public slots:
  void setPower(bool power);
 signals:
  void powerChanged(bool);
 protected:
  virtual void paintEvent(QPaintEvent* event) override;
 private:
  bool m_power;
  QColor ONcolor=Qt::green;
  QColor OFFcolor=Qt::NoBrush;
};
#endif // LED_HH
