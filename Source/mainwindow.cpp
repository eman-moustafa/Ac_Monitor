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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include "QDebug"
#include <QLabel>
#include <QMessageBox>
#include "QPainter"
#include <QDateTime>
#include <QTimer>


//! [0]
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_status(new QLabel),
    m_settings(new SettingsDialog),
    m_Extract(new BrowseRecords),
    m_Data(new Data),
    m_serial(new QSerialPort(this)),
    m_Recorder(new  RecorderMgr),
    movie(new QMovie(":/images/icons8-recording.gif")),
    Rmovie(new QMovie(":/images/icons8-replay.gif")),
    timer(new QTimer),
    Rtimer(new QTimer)


//! [1]
{
//! [0]
    m_ui->setupUi(this);
    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);
    m_ui->actionQuit->setEnabled(true);
    m_ui->actionConfigure->setEnabled(true);

    m_ui->statusBar->addWidget(m_status);
    m_ui->Record->setMovie(movie);
    m_ui->Replay->setMovie(Rmovie);
    m_Extract->setRec(m_Recorder);
    m_Extract->initRecords();
    initActionsConnections();
    initLedColors();



//! [2]
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);


    //QTimer *timer = new QTimer(this);
     //  connect(timer, SIGNAL(timeout()), this, SLOT(updateClock()));
       // timer->start(1000); // Update every 1 second
//   updateData();

//! [2]
//! [3]
}
//! [3]

MainWindow::~MainWindow()
{
    delete m_settings;
    delete m_ui;
    delete m_Extract;
    delete m_Recorder;
}

//! [4]
void MainWindow::openSerialPort()
{
    const SettingsDialog::Settings p = m_settings->settings();
    m_serial->setPortName(p.name);
    m_serial->setBaudRate(p.baudRate);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setStopBits(p.stopBits);
    m_serial->setFlowControl(p.flowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        m_ui->actionConnect->setEnabled(false);
        m_ui->actionDisconnect->setEnabled(true);
        m_ui->actionConfigure->setEnabled(false);
        m_ui->newpushButton_15->setEnabled(true);
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());

        showStatusMessage(tr("Open error"));
    }
}
//! [4]

//! [5]
void MainWindow::closeSerialPort()
{
    if (m_serial->isOpen())
        m_serial->close();
    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);
    m_ui->actionConfigure->setEnabled(true);
    m_ui->newpushButton_15->setEnabled(false);
    showStatusMessage(tr("Disconnected"));
}
//! [5]

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simple MonitorIndoor"),
                       tr("The <b>Simple MonitorIndoor</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}

//! [6]
void MainWindow::writeData(const QByteArray &data)
{
    m_serial->write(data);
}
//! [6]

//! [7]
void MainWindow::readData()
{

    if(m_serial->canReadLine()){


        const QByteArray data = m_serial->readLine();
        qDebug()<<data<<endl;
//        qDebug()<<strokeData(QString(data).trimmed());
        parseData(strokeData(QString(data).trimmed()));
        updateData();



}
}

QVector<QString> MainWindow::strokeData(QString Data)
{
    QVector<QString> res;
        QString delim = ",";
        QString token = "";
        bool flag;
        for (int i = 0; i < Data.size(); i++) {
             flag = true;
            if(Data[i]!=delim)flag = false;
            if (flag) {
                if (token.size() > 0) {
                    res.push_back(token);
                    token = "";
                }
            } else {
                token += Data[i];
            }
        }
        res.push_back(token);
        return res;

}

void MainWindow::parseData(QVector<QString> Data)
{
    LastFrame=Data;
    QVector<QString>::iterator itt;
            for (itt = Data.begin(); itt != Data.end(); ++itt) {
                QStringList list = (*itt).split(QRegExp("\\s+"), QString::SkipEmptyParts);
                if(list.length()>=2){
                    //Monitor Data
                    if(list[0]=="A"){
                        m_Data->setAbility(list[1]);
                        m_Data->setMonitorabilityVersion(list[1]);
                    }

                    else if (list[0]=="MM") m_Data->setMonitorModel(list[1]);
                    else if (list[0]=="FV") m_Data->setFlashVersion(list[1]);
                    else if (list[0]=="EV") {
                                            m_Data->setEEPVersion(list[1]);
                                            m_Data->setModelEEP(list[1]);
                    }
                    else if (list[0]=="MP") m_Data->setMotorPartCode(list[1]);
                    else if (list[0]=="MT") m_Data->setMotorType(list[1]);

                    //operation states
                    else if (list[0]=="OC") m_Data->setOperationCycle(list[1]);
                    else if (list[0]=="SP") m_Data->setSpMeasur(list[1]);
                    else if (list[0]=="FD") {
                                            m_Data->setFD(list[1]);
                    }
                    else if (list[0]=="M")  m_Data->setOperationMode(list[1]);
                    else if (list[0]=="FC") m_Data->setoutFanControl(list[1]);
                    else if (list[0]=="MV") m_Data->setACModel(list[1]);
                    else if (list[0]=="EC") m_Data->setErrorCode(list[1]);
                    else if (list[0]=="PM") m_Data->setModeMemory(list[1]);
                    else if (list[0]=="DL") m_Data->setDehumiditylifeMode(list[1]);
                    else if (list[0]=="DA") m_Data->setDehumidityAuto(list[1]);
                    else if (list[0]=="AM") m_Data->setAutoMask(list[1]);
                    else if (list[0]=="PT") m_Data->setOperationTime(list[1]);
                    else if (list[0]=="PF") m_Data->setOperationState(list[1]);
                    else if (list[0]=="HK") m_Data->setHotKeep(list[1]);
                    else if (list[0]=="DS") m_Data->setDehumidityState(list[1]);
                    else if (list[0]=="D")  m_Data->setDehumidityTime(list[1]);
                    else if (list[0]=="HD")  m_Data->setLcdState(list[1]);
                    else if (list[0]=="CT") {
                                            m_Data->setLcdTemp(list[1]);
                                            m_Data->setDisplaySettingsTemp(list[1]);
                                            m_Data->setCorrectedRoomTemp(list[1]);
                    }
                    else if (list[0]=="BO") m_Data->setBadodorTimer(list[1]);
                    else if (list[0]=="FT") m_Data->setFilterTimer(list[1]);

                    //indoor Settings
                    else if (list[0]=="OS") m_Data->setOutDoorTemp(list[1]);
                    else if (list[0]=="ST"){
                                            m_Data->setSettingTemp(list[1]);
                                            m_Data->setRemoconSet(list[1]);
                    }
                    else if (list[0]=="C")  m_Data->setCompressorState(list[1]);
                    else if (list[0]=="CN") m_Data->setCompressorOnTime(list[1]);
                    else if (list[0]=="CF") m_Data->setCompressorOFFTime(list[1]);
                    else if (list[0]=="STC") m_Data->setSafetyTimerControl(list[1]);
                    else if (list[0]=="BT") m_Data->setBelowTemp(list[1]);
                    else if (list[0]=="VT") m_Data->setValveTemp(list[1]);
                    else if (list[0]=="RT") {
                                            m_Data->setTempNow(list[1]);
                                            m_Data->setIdRoomSensorTemp(list[1]);
                    }
                    else if (list[0]=="ET") {
                                             m_Data->setIDPipeTemp(list[1]);
                    }
                    else if (list[0]=="NI")  m_Data->setInverter_Normal(list[1]);
                    else if (list[0]=="PBT") m_Data->setBelowTemp_Before(list[1]);
                    else if (list[0]=="PVT") m_Data->setValveTemp_Before(list[1]);
                    else if (list[0]=="RTB") m_Data->setRoomTemp_Before(list[1]);
                    else if (list[0]=="ETB") m_Data->setIDpipeTemp_Before(list[1]);
                    else if (list[0]=="DM")  m_Data->setIDpipeMinWhileDefrost_Before(list[1]);
                    else if (list[0]=="M1")  m_Data->setMAinOff_T1(list[1]);
                    else if (list[0]=="M2")  m_Data->setMAinOff_T2(list[1]);

                    //led state

                    else if (list[0]=="LS")  m_Data->setLedstate(list[1]);
                    //outdoor fan
                    else if (list[0]=="OF")  m_Data->setOutDoorFanState(list[1]);
                    else if (list[0]=="OFS") m_Data->setOutDoorFanSpeed(list[1]);
                    //heater
                    else if (list[0]=="HS")  m_Data->setHeaterState(list[1]);
                    //Fan
                    else if (list[0]=="F")   m_Data->setFanSpeed(list[1]);
                    else if (list[0]=="TS")  m_Data->setTargetSpeed(list[1]);
                    else if (list[0]=="FB")  m_Data->setFanSpeedFeedBack(list[1]);
                    else if (list[0]=="D1")  m_Data->setFanDuty(list[1]);
                    else if (list[0]=="PD")  m_Data->setPhaseData(list[1]);
                    else if (list[0]=="D2")  m_Data->setFanOnDelay(list[1]);
                    else if (list[0]=="DT")  m_Data->setDryFanOnOffTimer(list[1]);
                    //A/D

                    else if (list[0]=="HMS") m_Data->setHumiditySensor(list[1]);
                    else if (list[0]=="MZ")  m_Data->setIDRoomZone(list[1]);
                    else if (list[0]=="HZ")  m_Data->setIDPipeZone(list[1]);
                    else if (list[0]=="HMZ") m_Data->setHumidityZone(list[1]);
                    else if (list[0]=="CRT") m_Data->setControlTemp(list[1]);

                    //H-L Louver
                    else if (list[0]=="HLP") {
                                             m_Data->setH_l_CurrentAngle(list[1]);
                    }
                    else if (list[0]=="HL")  m_Data->setH_l_StateName(list[1]);
                    else if (list[0]=="HM")  m_Data->setH_l_MemoryAngle(list[1]);

                    //V-L louver
                    else if (list[0]=="VLP") {
                                             m_Data->setV_l_CurrentAngle(list[1]);
                    }
                    else if (list[0]=="VL")  m_Data->setV_l_StateName(list[1]);
                    else if (list[0]=="VM")  m_Data->setV_l_MemoryAngle(list[1]);
                    else if (list[0]=="Time")  m_Data->setTime(list[1]);
                    else qDebug()<<"Undefined Key Frame : "<<list[0]<<endl;



            }
            }

}

void MainWindow::updateData()
{
    ///operation status

    if(m_Data->Ability!=NULL)            m_ui->Ability_textEdit->setText(m_Data->Ability);
    if(m_Data->OperationCycle!=NULL)     m_ui->Operaingcycle_textedit->setText(m_Data->OperationCycle);
    if(m_Data->SpMeasur!=NULL)           m_ui->SpMeasure_textEdit->setText(m_Data->SpMeasur);
    if(m_Data->ModelEEP!=NULL)           m_ui->ModelEEP_textEdit->setText(m_Data->ModelEEP);
    if(m_Data->FD!=NULL)                 m_ui->FD_textEdit->setText(m_Data->FD);
    if(m_Data->OperationMode!=NULL)      m_ui->OperatingMode_textEdit->setText(m_Data->OperationMode);
    if(m_Data->OutFanControl!=NULL)      m_ui->OutFanCtrl_textEdit->setText(m_Data->OutFanControl);
    if(m_Data->ACModel!=NULL)            m_ui->ACModel_textEdit->setText(m_Data->ACModel);
    if(m_Data->ErrorCode!=NULL)          m_ui->ErrorCode_ltextEdit->setText(m_Data->ErrorCode);
    if(m_Data->ModeMemory!=NULL)         m_ui->ModeMemory_textEdit->setText(m_Data->ModeMemory);
    if(m_Data->DehumiditylifeMode!=NULL) m_ui->DehumidityLifeMode_textEdit->setText(m_Data->DehumiditylifeMode);
    if(m_Data->DehumidityAuto!=NULL)     m_ui->DehumidityAuto_textEdit->setText(m_Data->DehumidityAuto);
    if(m_Data->AutoMask!=NULL)           m_ui->AutoMask_textEdit->setText(m_Data->AutoMask);
    if(m_Data->OperationTime!=NULL)      m_ui->OperationTime_textEdit->setText(m_Data->OperationTime);
    if(m_Data->OperationState!=NULL)     m_ui->OperationState_textEdit->setText(m_Data->OperationState);
    if(m_Data->HotKeep!=NULL)            m_ui->HotKeep_textEdit->setText(m_Data->HotKeep);
    if(m_Data->DehumidityState!=NULL)    m_ui->DehmudityState_textEdit->setText(m_Data->DehumidityState);
    if(m_Data->DehumidityTime!=NULL)     m_ui->Dehmuditytime_textEdit->setText(m_Data->DehumidityTime);
    if(m_Data->LcdTemp!=NULL)            m_ui->Lcdtemp_textEdit->setText(m_Data->LcdTemp);
    if(m_Data->LcdState!=NULL)           m_ui->LcdState_textEdit->setText(m_Data->LcdState);
    if(m_Data->BadodorTimer!=NULL)       m_ui->BadodorTimer_textEdit->setText(m_Data->BadodorTimer);
    if(m_Data->FilterTimer!=NULL)        m_ui->FilterTimer_textEdit->setText(m_Data->FilterTimer);

    //Monitor

    if(m_Data->MonitorabilityVersion!=NULL) m_ui->Abilityversion_textEdit_2->setText(m_Data->MonitorabilityVersion);
    if(m_Data->MonitorModel!=NULL)          m_ui->AcModel_textEdit_2->setText(m_Data->MonitorModel);
    if(m_Data->FlashVersion!=NULL)          m_ui->Flashv_textEdit->setText(m_Data->FlashVersion);
    if(m_Data->EEPVersion!=NULL)            m_ui->EEPV_textEdit->setText(m_Data->EEPVersion);
    if(m_Data->MotorPartCode!=NULL)         m_ui->MotorCode_textEdit->setText(m_Data->MotorPartCode);
    if(m_Data->MotorType!=NULL)             m_ui->MotorType_textEdit->setText(m_Data->MotorType);


    /// indoor settings display
    if(m_Data->OutDoorTemp!=NULL)         m_ui->OutDoorTemp_textEdit->setText(m_Data->OutDoorTemp);
    if(m_Data->CorrectedroomTemp!=NULL)   m_ui->CorrectedRoomTemp_Temp_textEdit_3->setText(m_Data->CorrectedroomTemp);
    if(m_Data->DisplayTemp!=NULL)         m_ui->DispTemp_textEdit->setText(m_Data->DisplayTemp);
    if(m_Data->SettingTemp!=NULL)         m_ui->SettingTemp__textEdit->setText(m_Data->SettingTemp);
    if(m_Data->CompressorState!=NULL)     m_ui->CompState_textEdit->setText(m_Data->CompressorState);
    if(m_Data->CompressorOnTime!=NULL)    m_ui->CompON_textEdit->setText(m_Data->CompressorOnTime);
    if(m_Data->CompressorOFFTime!=NULL)   m_ui->CompOFF_textEdit->setText(m_Data->CompressorOFFTime);
    if(m_Data->SafetyTimerControl!=NULL)     m_ui->Safety_textEdit->setText(m_Data->SafetyTimerControl);
    if(m_Data->ValveTemp!=NULL)           m_ui->ValveTemp_textEdit->setText(m_Data->ValveTemp);
    if(m_Data->BelowTemp!=NULL)           m_ui->BelowTemp__textEdit->setText(m_Data->BelowTemp);
    if(m_Data->ValveTemp!=NULL)           m_ui->ValveTemp_textEdit->setText(m_Data->ValveTemp);
    if(m_Data->TempNow!=NULL)             m_ui->TempNow_textEdit->setText(m_Data->TempNow);
    if(m_Data->IDPipeTemp!=NULL)          m_ui->IdPipeTemp_textEdit->setText(m_Data->IDPipeTemp);
    if(m_Data->Inverter_Normal!=NULL)     m_ui->InverterNormal_textEdit->setText(m_Data->Inverter_Normal);
    if(m_Data->BelowTemp_Before!=NULL)    m_ui->BelowTempBefore_textEdit->setText(m_Data->BelowTemp_Before);
    if(m_Data->ValveTemp_Before!=NULL)    m_ui->ValveTempBefore_textedit->setText(m_Data->ValveTemp_Before);
    if(m_Data->RoomTemp_Before!=NULL)     m_ui->RoomTempBefore_textEdit->setText(m_Data->RoomTemp_Before);
    if(m_Data->IDpipeTemp_Before!=NULL)      m_ui->idPipeTempbefor_textEdit->setText(m_Data->IDpipeTemp_Before);
    if(m_Data->IDpipeMinWhileDefrost_Before!=NULL)      m_ui->idPipeMinWhileDefrost_textEdit->setText(m_Data->IDpipeMinWhileDefrost_Before);
    if(m_Data->MAinOff_T1!=NULL)         m_ui->mainoffT1_textEdit->setText(m_Data->MAinOff_T1);
    if(m_Data->MAinOffT2!=NULL)          m_ui->mainoffT2_textEdit->setText(m_Data->MAinOffT2);
    //Leds
    m_ui->PowerLed->setPower(m_Data->PowerLed);
    m_ui->TimerLed->setPower(m_Data->TimerLed);
    m_ui->Turboledd->setPower(m_Data->TurboLed);
    m_ui->PlasmaLed->setPower(m_Data->PlasmaLed);
    m_ui->EcoLed->setPower(m_Data->EcoLed);
    m_ui->SleepLed->setPower(m_Data->SleepLed);
    m_ui->FilterLed->setPower(m_Data->FilterLed);
    m_ui->CoolingLed->setPower(m_Data->CoolingLed);
    m_ui->HeatingLed->setPower(m_Data->HeatingLed);
    m_ui->LoundryLed->setPower(m_Data->LoundryLed);

    //out door info
    if(m_Data->outDoorFanState!=NULL)  m_ui->outdoorFanstate_textedit->setText(m_Data->outDoorFanState);
    if(m_Data->outDoorFanSpeed!=NULL)  m_ui->outdoorFanSpeed_textedit->setText(m_Data->outDoorFanSpeed);


    //heater info
    if(m_Data->HeaterState!=NULL)  m_ui->HeaterState_textedit->setText(m_Data->HeaterState);

    ///Fan

    if(m_Data->FanSpeed!=NULL)          m_ui->FanSpeed_textEdit->setText(m_Data->FanSpeed);
    if(m_Data->FD!=NULL)                m_ui->FD_textEdit_2->setText(m_Data->FD);
    if(m_Data->TargetSpeed!=NULL)       m_ui->TargetSpeed_textEdit->setText(m_Data->TargetSpeed);
    if(m_Data->SpeedFeedBack!=NULL)     m_ui->SpeedFeedBack_textEdit->setText(m_Data->SpeedFeedBack);
    if(m_Data->FanDuty!=NULL)           m_ui->FanDuty_textEdit->setText(m_Data->FanDuty);
    if(m_Data->PhaseData!=NULL)         m_ui->PhaseData_textEdit->setText(m_Data->PhaseData);
    if(m_Data->FanOnDelay!=NULL)        m_ui->FanOnDelay_textEdit->setText(m_Data->FanOnDelay);
    if(m_Data->SpeedFeedBack!=NULL)     m_ui->SpeedFeedBack_textEdit_3->setText(m_Data->SpeedFeedBack);
    if(m_Data->DryFanOnOffTimer!=NULL)  m_ui->DryFanTimer_textEdit_2->setText(m_Data->DryFanOnOffTimer);


    ////A/D

      if(m_Data->IdRoomTemp!=NULL)       m_ui->IdRoomTemp_textEdit->setText(m_Data->IdRoomTemp);
      if(m_Data->IDPipeTemp!=NULL)       m_ui->IdPipeTemp_textEdit_2->setText(m_Data->IDPipeTemp);
      if(m_Data->HumiditySensor!=NULL)   m_ui->humiSensor_textEdit->setText(m_Data->HumiditySensor);
      if(m_Data->IDRoomZone!=NULL)       m_ui->IDroomZOne_textEdit->setText(m_Data->IDRoomZone);
      if(m_Data->IDPipeZone!=NULL)       m_ui->IDpipeZone_textEdi->setText(m_Data->IDPipeZone);
      if(m_Data->HumidityZone!=NULL)     m_ui->HumidityZone_textEdit->setText(m_Data->HumidityZone);
      if(m_Data->RemoconSet!=NULL)       m_ui->RemoconSet_textEdit->setText(m_Data->RemoconSet);
      if(m_Data->ControlTemp!=NULL)      m_ui->CtrTemp_textEdit->setText(m_Data->ControlTemp);

      /// Horizontal louver


      if(m_Data->H_l_StateName!=NULL)     m_ui->H_l_State_textEdit->setText(m_Data->H_l_StateName);
      if(m_Data->H_l_CurrentAngle!=NULL)  m_ui->H_L_currentAngle_textEdit_2->setText(m_Data->H_l_CurrentAngle);
      if(m_Data->H_l_MemoryAngle!=NULL)   m_ui->H_lMemory->setText(m_Data->H_l_MemoryAngle);






      /// vertical louver

      if(m_Data->V_l_StateName!=NULL)     m_ui->V_l_State_textEdit->setText(m_Data->V_l_StateName);
      if(m_Data->V_l_CurrentAngle!=NULL)  m_ui->V_L_currentAngle_textEdit_->setText(m_Data->V_l_CurrentAngle);
      if(m_Data->V_l_MemoryAngle!=NULL)   m_ui->V_lMemory->setText(m_Data->V_l_MemoryAngle);


      if(m_Data->Time!=NULL) m_ui->RealTime->setText(m_Data->Time);

      m_ui->RealTime->setText(QDateTime::currentDateTime().toString("dd.MM.yyyy.h:m:s ap"));

}


//! [7]

//! [8]
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}
//! [8]

void MainWindow::initActionsConnections()
{
    connect(m_ui->actionConnect, &QAction::triggered, this, &MainWindow::openSerialPort);
    connect(m_ui->actionDisconnect, &QAction::triggered, this, &MainWindow::closeSerialPort);
    connect(m_ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(m_ui->actionConfigure, &QAction::triggered, m_settings, &SettingsDialog::showSettings);
    connect(m_ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(m_ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(m_Recorder, &RecorderMgr::DataBaseError,this,&MainWindow::ShowResponse);
    connect(m_Recorder, &RecorderMgr::RecordcreateError,this,&MainWindow::ShowResponse);
    connect(m_Recorder, &RecorderMgr::RecordExportError,this,&MainWindow::ShowResponse);
    connect(m_Recorder, &RecorderMgr::RecordImportError,this,&MainWindow::ShowResponse);
    connect(m_Recorder, &RecorderMgr::RecordExportSucc,this,&MainWindow::ShowResponse);
    connect(m_Recorder, &RecorderMgr::RecordimportSucc,this,&MainWindow::ShowResponse);
    connect(m_Extract, &BrowseRecords::RecordSelected,this,&MainWindow::on_RecordSelected);
//    connect(m_Recorder, &RecorderMgr::RecordcreateFrameError,this,&MainWindow::handlError);
//    connect(m_Recorder, &RecorderMgr::RecordRetrieveError,this,&MainWindow::handlError);
    connect(timer, &QTimer::timeout,this,&MainWindow::puchLastFrame);
    connect(Rtimer,&QTimer::timeout,this,&MainWindow::popLastFrame);
    timer->setInterval(1000);
    Rtimer->setInterval(1000);
}

void MainWindow::initLedColors()
{
    m_ui->PowerLed->  setBrushes(Qt::red,Qt::NoBrush);
    m_ui->TimerLed->  setBrushes(Qt::yellow,Qt::NoBrush);
    m_ui->Turboledd-> setBrushes(Qt::green,Qt::NoBrush);
    m_ui->PlasmaLed-> setBrushes(Qt::darkBlue,Qt::NoBrush);
    m_ui->EcoLed->    setBrushes(Qt::green,Qt::NoBrush);
    m_ui->SleepLed->  setBrushes(Qt::blue,Qt::NoBrush);
    m_ui->FilterLed-> setBrushes(Qt::yellow,Qt::NoBrush);
    m_ui->CoolingLed->setBrushes(Qt::blue,Qt::NoBrush);
    m_ui->HeatingLed->setBrushes(Qt::red,Qt::NoBrush);
    m_ui->LoundryLed->setBrushes(Qt::darkYellow,Qt::NoBrush);

}
void MainWindow::ShowResponse(QString info){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText(info);
    msgBox.exec();
}

void MainWindow::puchLastFrame()
{
    QString timenow="Time ";
    timenow.append(QDateTime::currentDateTime().toString("dd.MM.yyyy.h:m:s ap"));
    LastFrame.push_front(timenow);
    m_Recorder->createRecordFrame(m_ui->RecordName->toPlainText(),LastFrame);
    RecordTimeDuration++;
    m_ui->RecordTime->setText( QDateTime::fromTime_t(RecordTimeDuration).toUTC().toString("hh:mm:ss"));

}

void MainWindow::popLastFrame()
{
    QMap<QString,QString>data= m_Recorder->RetrieveFramedata(m_ui->RecordName->toPlainText(),ReplayTimeDuration);
    QVector<QString>Data;
    QMap<QString,QString>::Iterator it;
     for(it=data.begin();it!=data.end();it++){
         Data.push_back(it.key()+" "+it.value());
     }
    ReplayTimeDuration++;
    parseData(Data);
    updateData();
    m_ui->ReplayTime->setText( QDateTime::fromTime_t(ReplayTimeDuration).toUTC().toString("hh:mm:ss"));
    m_ui->CurrentTimelabel->setText( QDateTime::fromTime_t(ReplayTimeDuration).toUTC().toString("hh:mm:ss"));
    m_ui->TimerSlider->setValue(ReplayTimeDuration);
    if(ReplayTimeDuration==TotalTimeDuration)on_StoppushButton_clicked();


}

void MainWindow::showStatusMessage(const QString &message)
{
    m_status->setText(message);
}

void MainWindow::on_StopSavepushButton_clicked()
{
    RecordTimeDuration=0;
    timer->stop();
    movie->stop();
    m_ui->Record->setVisible(false);
    isrecording=false;
    m_ui->newpushButton_15->setEnabled(true);
    m_ui->record_pushButton->setEnabled(false);
    m_ui->StopSavepushButton->setEnabled(false);
    m_ui->openpushButton->setEnabled(true);
    m_ui->RecordName->setText("");
    m_ui->RecordTime->setText("");

}

void MainWindow::on_record_pushButton_clicked()
{
    timer->start();
    movie->start();
    m_ui->newpushButton_15->setEnabled(false);
    m_ui->record_pushButton->setEnabled(false);
    m_ui->StopSavepushButton->setEnabled(true);
    m_ui->Record->setVisible(true);
    isrecording=true;

}

void MainWindow::on_newpushButton_15_clicked()
{
    QDateTime date = QDateTime::currentDateTime();
    QString RecordName =NULL;
    bool ok=false;
     while(RecordName==NULL){
        QString name=QInputDialog::getText(this,"","Enter Record Name", QLineEdit::Normal,QString("Rec_"+date.toString("dd_MM_yyyy_hh_mm_ss")),&ok);
        if(ok){
            m_ui->newpushButton_15->setEnabled(false);
            m_ui->record_pushButton->setEnabled(true);
            m_ui->StopSavepushButton->setEnabled(true);
            m_ui->openpushButton->setEnabled(false);
            RecordName=m_Recorder->createRecord(name);
            m_ui->RecordName->setText(RecordName);
        }
     }

}

void MainWindow::on_openpushButton_clicked()
{
    m_Extract->setRole("Browse");
    m_Extract->initRecords();
    m_Extract->show();



}

void MainWindow::on_playpushButton_clicked()
{
    closeSerialPort();
    Rtimer->setInterval(1000/m_ui->Framerate->value());
    Rtimer->start();
    Rmovie->start();
    m_ui->Replay->setVisible(true);
    m_ui->openpushButton->setEnabled(false);
    m_ui->playpushButton->setEnabled(false);
    m_ui->pausepushButton->setEnabled(true);
    m_ui->StoppushButton->setEnabled(true);
    m_ui->reloadpushButton->setEnabled(true);
    m_ui->actionConnect->setEnabled(false);

}

void MainWindow::on_pausepushButton_clicked()
{
    Rtimer->stop();
    Rmovie->stop();
    m_ui->openpushButton->setEnabled(false);
    m_ui->playpushButton->setEnabled(true);
    m_ui->pausepushButton->setEnabled(false);
    m_ui->StoppushButton->setEnabled(true);
    m_ui->reloadpushButton->setEnabled(true);

}

void MainWindow::on_reloadpushButton_clicked()
{
    ReplayTimeDuration=0;
}

void MainWindow::on_StoppushButton_clicked()
{
    Rtimer->stop();
    Rmovie->stop();
    m_ui->Replay->setVisible(false);
    m_ui->RecordName->setText("");
    TotalTimeDuration=m_Recorder->getRecordlength("");
    m_ui->TotalTime->setText(QDateTime::fromTime_t(0).toUTC().toString("hh:mm:ss"));
    m_ui->ReplayTime->setText( QDateTime::fromTime_t(0).toUTC().toString("hh:mm:ss"));
    m_ui->CurrentTimelabel->setText( QDateTime::fromTime_t(0).toUTC().toString("hh:mm:ss"));
    m_ui->TimerSlider->setRange(0,0);
    m_ui->openpushButton->setEnabled(true);
    m_ui->playpushButton->setEnabled(false);
    m_ui->pausepushButton->setEnabled(false);
    m_ui->StoppushButton->setEnabled(false);
    m_ui->reloadpushButton->setEnabled(false);
    m_ui->newpushButton_15->setEnabled(true);
    m_ui->actionConnect->setEnabled(true);
    ReplayTimeDuration=0;
    TotalTimeDuration=0;


}

void MainWindow::on_TimerSlider_sliderMoved(int position)
{
    ReplayTimeDuration=position;
    QToolTip::showText(QCursor::pos(), QString(QDateTime::fromTime_t(position).toUTC().toString("hh:mm:ss")), nullptr);
}

void MainWindow::changeLayout(QString Lang)
{
    if(Lang=="English"){
         m_ui->centralWidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

    }
    else if(Lang=="Arabic"){
         m_ui->centralWidget->setLayoutDirection(Qt::LayoutDirection::RightToLeft);



    }

}

void MainWindow::on_ExportRec_clicked()
{
    m_Extract->setRole("");
    m_Extract->initRecords();
    m_Extract->show();

}

void MainWindow::on_importRec_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Select Record"),"",tr("Record files (*.xlsx)"));
    m_Recorder->importRecord(fileName);
}

void MainWindow::on_Framerate_valueChanged(int arg1)
{
    Rtimer->setInterval(1000/arg1);
}

void MainWindow::on_RecordSelected(QString RecName)
{
   if(RecName!=""){
        m_ui->RecordName->setText(RecName);
        TotalTimeDuration=m_Recorder->getRecordlength(RecName);
        m_ui->TotalTime->setText(QDateTime::fromTime_t(TotalTimeDuration).toUTC().toString("hh:mm:ss"));
        m_ui->TimerSlider->setRange(0,TotalTimeDuration);
        m_ui->openpushButton->setEnabled(false);
        m_ui->playpushButton->setEnabled(true);
        m_ui->pausepushButton->setEnabled(true);
        m_ui->StoppushButton->setEnabled(true);
        m_ui->reloadpushButton->setEnabled(true);
        m_ui->newpushButton_15->setEnabled(false);
   }

}





