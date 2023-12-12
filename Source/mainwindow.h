/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include "data.h"
#include "RecorderMgr.h"
#include <QMovie>
#include <QInputDialog>
#include <QTimer>
#include <QToolTip>
#include "BrowseRecords.h"
#include <QDateTime>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>



QT_BEGIN_NAMESPACE

class QLabel;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class Console;
class SettingsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void changeLayout(QString Lang);
    ~MainWindow();

private slots:
    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData(const QByteArray &data);
    void readData();
    QVector<QString>  strokeData(QString Data);
    void parseData(QVector<QString>);
    void updateData();
    void handleError(QSerialPort::SerialPortError error);
    void on_record_pushButton_clicked();
    void on_newpushButton_15_clicked();
    void ShowResponse(QString Error);
    void puchLastFrame();
    void popLastFrame();
    void on_openpushButton_clicked();
    void on_playpushButton_clicked();
    void on_pausepushButton_clicked();
    void on_StopSavepushButton_clicked();

    void on_reloadpushButton_clicked();

    void on_StoppushButton_clicked();

    void on_TimerSlider_sliderMoved(int position);



    void on_ExportRec_clicked();

    void on_importRec_clicked();

    void on_Framerate_valueChanged(int arg1);
    void on_RecordSelected(QString Record);

  // void updateChart();



private:
    void initActionsConnections();
    void initLedColors();
    void initChart();
    void createChart();
    void setAxis();

private:
    void showStatusMessage(const QString &message);

    Ui::MainWindow *m_ui = nullptr;
    QLabel *m_status = nullptr;
    Console *m_console = nullptr;
    SettingsDialog *m_settings = nullptr;
    BrowseRecords *m_Extract=nullptr;
    Data *m_Data=nullptr;
    QSerialPort *m_serial = nullptr;
    RecorderMgr *m_Recorder;
    QMovie *movie;
    QMovie *Rmovie;
    bool isrecording=false;
    QTimer *timer;
    QTimer *Rtimer;
    QVector<QString> LastFrame;
    int RecordTimeDuration=0;
    int ReplayTimeDuration=0;
    int TotalTimeDuration=0;

    // Create a chart view
       QtCharts::QChartView *chartView;

       // Create a chart
       QtCharts::QChart *chart = new QtCharts::QChart();

       //create LineSeries
QtCharts::QLineSeries *series1 =new QtCharts::QLineSeries;
QtCharts::QLineSeries *series2 =new QtCharts::QLineSeries;
QtCharts::QLineSeries *series3 =new QtCharts::QLineSeries;
QtCharts::QLineSeries *series4 =new QtCharts::QLineSeries;
QtCharts::QLineSeries *series5 =new QtCharts::QLineSeries;

// Create axes
       QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
       QDateTimeAxis *axisX = new QDateTimeAxis;

QTime currentTime = QTime();



};

#endif // MAINWINDOW_H
