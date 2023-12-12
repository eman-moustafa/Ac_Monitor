#ifndef DATA_H
#define DATA_H
#include "QString"
#include "led.h"
#include <QtMath>


class Data
{
public:
    Data();

    // Monitor Data
    QString MonitorabilityVersion=NULL;
    QString MonitorModel=NULL;
    QString FlashVersion=NULL;
    QString EEPVersion=NULL;
    QString MotorPartCode=NULL;
    QString MotorType=NULL;

    //Operation states --->

    QString Ability=NULL;
    QString OperationCycle=NULL;
    QString SpMeasur=NULL;
    QString ModelEEP=NULL;
    QString FD=NULL;
    QString OperationMode=NULL;
    QString OutFanControl=NULL;
    QString ACModel=NULL;
    QString ErrorCode=NULL;
    QString ModeMemory=NULL;
    QString DehumiditylifeMode=NULL;
    QString DehumidityAuto=NULL;
    QString AutoMask=NULL;
    QString OperationTime=NULL;
    QString OperationState=NULL;
    QString HotKeep=NULL;
    QString DehumidityState=NULL;
    QString DehumidityTime=NULL;
    QString LcdState=NULL;
    QString LcdTemp=NULL;
    QString BadodorTimer=NULL;
    QString FilterTimer=NULL;


    //indoor Seettings Display

    QString OutDoorTemp=NULL;
    QString CorrectedroomTemp=NULL;
    QString DisplayTemp=NULL;
    QString SettingTemp=NULL;
    QString CompressorState=NULL;
    QString CompressorOnTime=NULL;
    QString CompressorOFFTime=NULL;
    QString SafetyTimerControl=NULL;
    QString BelowTemp=NULL;
    QString ValveTemp=NULL;
    QString TempNow=NULL;
    QString IDPipeTemp=NULL;
    QString Inverter_Normal=NULL;
    QString BelowTemp_Before=NULL;
    QString ValveTemp_Before=NULL;
    QString RoomTemp_Before=NULL;
    QString IDpipeTemp_Before=NULL;
    QString IDpipeMinWhileDefrost_Before=NULL;
    QString MAinOff_T1=NULL;
    QString MAinOffT2=NULL;

    //led

    bool PowerLed;
    bool TimerLed;
    bool TurboLed;
    bool PlasmaLed;
    bool EcoLed;
    bool SleepLed;
    bool FilterLed;
    bool CoolingLed;
    bool HeatingLed;
    bool LoundryLed;

    //outDoor Fan
    QString outDoorFanState=NULL;
    QString outDoorFanSpeed=NULL;

    //Heater
    QString HeaterState=NULL;


    //Fan

    QString FanSpeed=NULL;
    QString TargetSpeed=NULL;
    QString SpeedFeedBack=NULL;
    QString FanDuty=NULL;
    QString PhaseData=NULL;
    QString FanOnDelay=NULL;
    QString DryFanOnOffTimer=NULL;


    //// A/D
    QString IdRoomTemp=NULL;
    QString HumiditySensor=NULL;
    QString IDRoomZone=NULL;
    QString IDPipeZone=NULL;
    QString HumidityZone=NULL;
    QString RemoconSet=NULL;
    QString ControlTemp=NULL;

    //// Horizontal Louver
    QString H_l_CurrentAngle=NULL;
    QString H_l_StateName=NULL;
    QString H_l_StateAngle=NULL;
    QString H_l_MemoryAngle=NULL;

    //// Vertical Louver
    QString V_l_CurrentAngle=NULL;
    QString V_l_StateName=NULL;
    QString V_l_StateAngle=NULL;
    QString V_l_MemoryAngle=NULL;
    ///

    QString Time=NULL;

    void setLedstate(const QString &ledstate);
    void setAbility(const QString &newAbility);
    void setOperationCycle(const QString &newOperationCycle);
    void setSpMeasur(const QString &newSpMeasur);
    void setMonitorabilityVersion(const QString &newMonitorabilityVersion);
    void setMonitorModel(const QString &newMonitorModel);
    void setFlashVersion(const QString &newFlashVersion);
    void setEEPVersion(const QString &newEEPVersion);
    void setMotorPartCode(const QString &newMotorPartCode);
    void setMotorType(const QString &newMotorType);
    void setModelEEP(const QString &newModelEEP);
    void setFD(const QString &newTS);
    void setOperationMode(const QString &newOperationMode);
    void setoutFanControl(const QString &newFanControl);
    void setACModel(const QString &newModel);
    void setErrorCode(const QString &newErrorCode);
    void setModeMemory(const QString &newModeMemory);
    void setDehumiditylifeMode(const QString &newDehumiditylifeMode);
    void setAutoMask(const QString &newAutoMask);
    void setOperationTime(const QString &newUnitOnTime);
    void setOperationState(const QString &newOperationState);
    void setDehumidityAuto(const QString &newDehumidityAuto);
    void setHotKeep(const QString &newHotKeep);
    void setDehumidityState(const QString &newDehumidityState);
    void setDehumidityTime(const QString &newDehumidityTime);
    void setLcdTemp(const QString &newLcdTemp);
    void setOutDoorTemp(const QString &newOutDoorTemp);
    void setDisplaySettingsTemp(const QString &newDisplaySettingsTemp);
    void setSettingTemp(const QString &newSettingTemp);
    void setCompressorState(const QString &newCompressorState);
    void setCompressorOnTime(const QString &newCompressorOnTime);
    void setCompressorOFFTime(const QString &newCompressorOFFTime);
    void setBelowTemp(const QString &newBelowTemp);
    void setValveTemp(const QString &newValveTemp);
    void setTempNo(const QString &newTempNo);
    void setHexTemp(const QString &newHexTemp);
    void setInverter_Normal(const QString &newInverter_Normal);
    void setBelowTemp_Before(const QString &newBelowTemp_Before);
    void setValveTemp_Before(const QString &newValveTemp_Before);
    void setRoomTemp_Before(const QString &newRoomTemp_Before);
    void setHexTemp_Before(const QString &newHexTemp_Before);
    void setPowerLed(const Led &newPowerLed);
    void setOutDoorFanState(const QString &newOutDoorFanState);
    void setOutDoorFanSpeed(const QString &newOutDoorFanSpeed);
    void setHeaterState(const QString &newHeaterState);
    void setFanSpeed(const QString &newFanSpeed);
    void setFDS(const QString &newFDS);
    void setTargetSpeed(const QString &newTargetSpeed);
    void setFanSpeedFeedBack(const QString &newFanSpeedFeedBack);
    void setIdRoomSensorTemp(const QString &newIdRoomSensorTemp);
    void setHexTemprature(const QString &newHexTemprature);
    void setHumiditySensor(const QString &newHumiditySensor);
    void setIDRoomZone(const QString &newIDRoomZone);
    void setHexZone(const QString &newHexZone);
    void setHumidityZone(const QString &newHumidityZone);
    void setRemoconSet(const QString &newRemoconSet);
    void setControlTemp(const QString &newControlTemp);
    void setH_l_CurrentAngle(const QString &newH_l_CurrentAngle);
    void setH_l_StateName(const QString &newH_l_StateName);
    void setH_l_StateAngle(const QString &newH_l_StateAngle);
    void setH_l_MemoryAngle(const QString &newH_l_MemoryAngle);
    void setV_l_CurrentAngle(const QString &newV_l_CurrentAngle);
    void setV_l_StateName(const QString &newV_l_StateName);
    void setV_l_StateAngle(const QString &newV_l_StateAngle);
    void setV_l_MemoryAngle(const QString &newV_l_MemoryAngle);
    void setFilterTimer(const QString &newFilterTimer);
    void setBedRoomTimer(const QString &newBedRoomTimer);
    void setDryFan_ON_OFF_Timer(const QString &newDryFan_ON_OFF_Timer);
    void setCorrectedRoomTemp(const QString &newCorrectedRoomTemp);
    void setSafetyTimeCounter(const QString &newSafetyTimeCounter);
    void setLcdState(const QString &newLcdState);
    void setHexMinWhileDefrost(const QString &newHexMinWhileDefrost);
    void setBadodorTimer(const QString &newBadodorTimer);
    void setIDPipeTemp(const QString &newIDPipeTemp);
    void setIDpipeTemp_Before(const QString &newIDpipeTemp_Before);
    void setMAinOff_T1(const QString &newMAinOff_T1);
    void setMAinOff_T2(const QString &newMAinOff_T2);
    void setFanDuty(const QString &newFanDuty);
    void setPhaseData(const QString &newPhaseData);
    void setFanOnDelay(const QString &newFanOnDelay);
    void setDryFanOnOffTimer(const QString &newDryFanOnOffTimer);
    void setIdPIPipeTemp(const QString &newIdPIPipeTemp);
    void setTempNow(const QString &newTempNow);
    void setIDPipeZone(const QString &newIDPipeZone);
    void setSafetyTimerControl(const QString &newSafetyTimerControl);
    void setIDpipeMinWhileDefrost_Before(const QString &newIDpipeMinWhileDefrost_Before);
    void setTime(const QString &newTime);
};

#endif // DATA_H
