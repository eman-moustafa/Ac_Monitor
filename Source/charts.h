#ifndef CHARTS_H
#define CHARTS_H

#include <QMainWindow>
#include <QChartView>
#include <QValueAxis>
#include<QtCharts>
#include "data.h"

namespace Ui {
class Charts;
}

class Charts : public QMainWindow
{
    Q_OBJECT

public:

    explicit Charts(QWidget *parent = nullptr);
    ~Charts();




private slots:


private:
    Ui::Charts *ui;
    Data *m_Data;

    QLineSeries *series1 =new QLineSeries();
    QLineSeries *series2 =new QLineSeries();
    QLineSeries *series3 =new QLineSeries();
    QLineSeries *series4 =new QLineSeries();
    QLineSeries *series5 =new QLineSeries();


    QChart *chart = new QChart();
    QChartView * chartView =new QChartView();

    QValueAxis *axisY = new QValueAxis();
    QDateTimeAxis *axisX = new QDateTimeAxis;




};

#endif // CHARTS_H
