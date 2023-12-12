#include "data.h"
#include "QDebug"
#include <bitset>


Data::Data()
{

}

void Data::setTime(const QString &newTime)
{

    Time = newTime;
}

void Data::setIDpipeMinWhileDefrost_Before(const QString &newIDpipeMinWhileDefrost_Before)
{
    IDpipeMinWhileDefrost_Before = newIDpipeMinWhileDefrost_Before;
}

void Data::setSafetyTimerControl(const QString &newSafetyTimerControl)
{
    SafetyTimerControl = newSafetyTimerControl;
}

void Data::setIDPipeZone(const QString &newIDPipeZone)
{

    if(OperationMode=="Heat"){
        if(newIDPipeZone=="0")IDPipeZone="Zone_IDle";
        else if(newIDPipeZone=="1")IDPipeZone="Zone_0";
        else if(newIDPipeZone=="2")IDPipeZone="Zone_1";
        else if(newIDPipeZone=="3")IDPipeZone="Zone_2";
        else if(newIDPipeZone=="4")IDPipeZone="Zone_3";
        else if(newIDPipeZone=="5")IDPipeZone="Zone_4";
        else if(newIDPipeZone=="6")IDPipeZone="Zone_7";
        else IDPipeZone="undefined";
    }else IDPipeZone="undefined";


}

void Data::setTempNow(const QString &newTempNow)
{
    TempNow = newTempNow;
}

void Data::setIdPIPipeTemp(const QString &newIdPIPipeTemp)
{
    IDPipeTemp = newIdPIPipeTemp;
}

void Data::setDryFanOnOffTimer(const QString &newDryFanOnOffTimer)
{
    DryFanOnOffTimer = std::to_string(qMin((newDryFanOnOffTimer.toInt()*20/1000),180)).c_str();
}

void Data::setFanOnDelay(const QString &newFanOnDelay)
{
    FanOnDelay = newFanOnDelay;
}

void Data::setPhaseData(const QString &newPhaseData)
{
    PhaseData = newPhaseData;
}

void Data::setFanDuty(const QString &newFanDuty)
{
    FanDuty = newFanDuty;
}

void Data::setMAinOff_T2(const QString &newMAinOff_T2)
{
    MAinOffT2 = newMAinOff_T2;
}

void Data::setMAinOff_T1(const QString &newMAinOff_T1)
{
    MAinOff_T1 = newMAinOff_T1;
}



void Data::setIDpipeTemp_Before(const QString &newIDpipeTemp_Before)
{
    IDpipeTemp_Before = newIDpipeTemp_Before;
}

void Data::setIDPipeTemp(const QString &newIDPipeTemp)
{
    IDPipeTemp = newIDPipeTemp;
}



void Data::setBadodorTimer(const QString &newBadodorTimer)
{
    BadodorTimer = std::to_string(qMin((newBadodorTimer.toInt()*20/1000),60)).c_str();
}

void Data::setLedstate(const QString &newledstate)
{
    std::bitset<16> ledstate(newledstate.toInt());
    EcoLed= ledstate.test(0);
    CoolingLed =ledstate.test(1);
    PowerLed =ledstate.test(2);
    HeatingLed =ledstate.test(3);
    TimerLed =ledstate.test(4);
    FilterLed =ledstate.test(4);
    TurboLed =ledstate.test(5);
    SleepLed =ledstate.test(6);
    PlasmaLed =ledstate.test(7);
    LoundryLed =ledstate.test(8);


}



void Data::setLcdState(const QString &newLcdState)
{
    if(newLcdState=="0")LcdState="OFF";
    else if(newLcdState=="1")LcdState="ON";
    else LcdState="undefined";

}



void Data::setCorrectedRoomTemp(const QString &newCorrectedRoomTemp)
{
    CorrectedroomTemp = newCorrectedRoomTemp;
}




void Data::setFilterTimer(const QString &newFilterTimer)
{
    FilterTimer = std::to_string(qMin((newFilterTimer.toInt()*20/(1000*60*60)),250)).c_str();
}

void Data::setV_l_MemoryAngle(const QString &newV_l_MemoryAngle)
{
    V_l_MemoryAngle = newV_l_MemoryAngle;
}

void Data::setV_l_StateAngle(const QString &newV_l_StateAngle)
{
    V_l_StateAngle = newV_l_StateAngle;
}

void Data::setV_l_StateName(const QString &newV_l_StateName)
{

    if (ACModel=="TY-C12AEE")
    {
        if(newV_l_StateName=="0")V_l_StateName="Not exist";
            else if(newV_l_StateName=="1")V_l_StateName="MIDDLE";
            else if(newV_l_StateName=="2")V_l_StateName="LEFT";
            else if(newV_l_StateName=="3")V_l_StateName="SWING";
            else if(newV_l_StateName=="5")V_l_StateName="MY AREA RIGHT";
            else if(newV_l_StateName=="6")V_l_StateName="MY AREA MIDDLE";
            else if(newV_l_StateName=="7")V_l_StateName="MY AREA LEFT";
            else if(newV_l_StateName=="8")V_l_StateName="DEFAULT";
            else V_l_StateName="None";
    }
    else
    {
        if(newV_l_StateName=="0")V_l_StateName="RIGHT";
    else if(newV_l_StateName=="1")V_l_StateName="MIDDLE";
    else if(newV_l_StateName=="2")V_l_StateName="LEFT";
    else if(newV_l_StateName=="3")V_l_StateName="SWING";
    else if(newV_l_StateName=="5")V_l_StateName="MY AREA RIGHT";
    else if(newV_l_StateName=="6")V_l_StateName="MY AREA MIDDLE";
    else if(newV_l_StateName=="7")V_l_StateName="MY AREA LEFT";
    else if(newV_l_StateName=="8")V_l_StateName="DEFAULT";
    else V_l_StateName="None";
}
}

void Data::setV_l_CurrentAngle(const QString &newV_l_CurrentAngle)
{
    V_l_CurrentAngle = newV_l_CurrentAngle;
}

void Data::setH_l_MemoryAngle(const QString &newH_l_MemoryAngle)
{
    H_l_MemoryAngle = newH_l_MemoryAngle;
}

void Data::setH_l_StateAngle(const QString &newH_l_StateAngle)
{
    H_l_StateAngle = newH_l_StateAngle;
}

void Data::setH_l_StateName(const QString &newH_l_StateName)
{
    if(newH_l_StateName=="0")H_l_StateName="Close";
    else if(newH_l_StateName=="1")H_l_StateName="OPEN";
    else if(newH_l_StateName=="2")H_l_StateName="SWING";
    else if(newH_l_StateName=="3")H_l_StateName="SWING";
    else if(newH_l_StateName=="4")H_l_StateName="COMFORT";
    else if(newH_l_StateName=="5")H_l_StateName="MY AREA_UP";
    else if(newH_l_StateName=="6")H_l_StateName="MY AREA_DOWN";
    else if(newH_l_StateName=="7")H_l_StateName="DEFAULT";
    else if(newH_l_StateName=="8")H_l_StateName="TURBO";
    else if(newH_l_StateName=="9")H_l_StateName="CLEAN";
    else if(newH_l_StateName=="10")H_l_StateName="SWING";
    else if(newH_l_StateName=="11")H_l_StateName="SWING";
    else if(newH_l_StateName=="12")H_l_StateName="COMFORT";
    else if(newH_l_StateName=="13")H_l_StateName="MY AREA_UP";
    else if(newH_l_StateName=="14")H_l_StateName="MY AREA_DOWN";
    else if(newH_l_StateName=="15")H_l_StateName="DEFAULT";
    else if(newH_l_StateName=="16")H_l_StateName="TURBO";
    else if(newH_l_StateName=="17")H_l_StateName="HEX_0_1";
    else if(newH_l_StateName=="18")H_l_StateName="SWING_FIXED";
    else if(newH_l_StateName=="19")H_l_StateName="SWING";
    else if(newH_l_StateName=="20")H_l_StateName="IDLE";
    else H_l_StateName="undefined";



}

void Data::setH_l_CurrentAngle(const QString &newH_l_CurrentAngle)
{
    H_l_CurrentAngle = newH_l_CurrentAngle;
}

void Data::setControlTemp(const QString &newControlTemp)
{
    ControlTemp = newControlTemp;
}

void Data::setRemoconSet(const QString &newRemoconSet)
{
    RemoconSet = newRemoconSet;
}

void Data::setHumidityZone(const QString &newHumidityZone)
{
    HumidityZone = newHumidityZone;
}



void Data::setIDRoomZone(const QString &newIDRoomZone)
{
    if(OperationMode=="Heat"){
        if(newIDRoomZone=="0")IDRoomZone="Idle";
        else if(newIDRoomZone=="1")IDRoomZone="Zone_Z";
        else if(newIDRoomZone=="2")IDRoomZone="Zone_A";
        else if(newIDRoomZone=="3")IDRoomZone="Zone_B";
        else if(newIDRoomZone=="4")IDRoomZone="Zone_C";
        else if(newIDRoomZone=="5")IDRoomZone="Zone_D";
        else if(newIDRoomZone=="6")IDRoomZone="Zone_E";
        else if(newIDRoomZone=="7")IDRoomZone="Zone_F";
        else if(newIDRoomZone=="8")IDRoomZone="Zone_G";
        else if(newIDRoomZone=="9")IDRoomZone="Zone_H";
        else if(newIDRoomZone=="10")IDRoomZone="Zone_I";
        else if(newIDRoomZone=="11")IDRoomZone="Zone_J";
        else if(newIDRoomZone=="12")IDRoomZone="Zone_K";
        else IDRoomZone="undefined";
    }
    else if(OperationMode=="Cool"){
                if(newIDRoomZone=="0")IDRoomZone="Zone_Idle";
                else if(newIDRoomZone=="4")IDRoomZone="Zone_C";
                else if(newIDRoomZone=="5")IDRoomZone="Zone_D";
                else if(newIDRoomZone=="6")IDRoomZone="Zone_E";
                else if(newIDRoomZone=="7")IDRoomZone="Zone_F";
                else if(newIDRoomZone=="8")IDRoomZone="Zone_G";
                else if(newIDRoomZone=="9")IDRoomZone="Zone_H";
                else if(newIDRoomZone=="10")IDRoomZone="Zone_I";
                else if(newIDRoomZone=="11")IDRoomZone="Zone_J";
                else if(newIDRoomZone=="12")IDRoomZone="Zone_K";
                else IDRoomZone="undefined";
    }
    else if(OperationMode=="Dry"){
        if(newIDRoomZone=="0")IDRoomZone="Zone_Idle";
        else if(newIDRoomZone=="1")IDRoomZone="Zone_C";
        else if(newIDRoomZone=="2")IDRoomZone="Zone_D";
        else if(newIDRoomZone=="3")IDRoomZone="Zone_E";
        else if(newIDRoomZone=="4")IDRoomZone="Zone_F";
        else if(newIDRoomZone=="5")IDRoomZone="Zone_G";
        else if(newIDRoomZone=="6")IDRoomZone="Zone_H";
        else if(newIDRoomZone=="7")IDRoomZone="Zone_I";
        else if(newIDRoomZone=="8")IDRoomZone="Zone_J";
        else if(newIDRoomZone=="9")IDRoomZone="Zone_K";
        else IDRoomZone="undefined";
    }

    else IDRoomZone="undefined";
}

void Data::setHumiditySensor(const QString &newHumiditySensor)
{
    HumiditySensor = newHumiditySensor;
}



void Data::setIdRoomSensorTemp(const QString &newIdRoomSensorTemp)
{
    IdRoomTemp = newIdRoomSensorTemp;
}

void Data::setFanSpeedFeedBack(const QString &newFanSpeedFeedBack)
{
    SpeedFeedBack = newFanSpeedFeedBack;
}

void Data::setTargetSpeed(const QString &newTargetSpeed)
{
    TargetSpeed = newTargetSpeed;
}



void Data::setFanSpeed(const QString &newFanSpeed)
{
    if(newFanSpeed=="2") FanSpeed="Auto";
    else if(newFanSpeed=="3") FanSpeed="Low";
    else if(newFanSpeed=="5") FanSpeed="Medium";
    else if(newFanSpeed=="7") FanSpeed="High";
    else FanSpeed = "undefined";
}

void Data::setHeaterState(const QString &newHeaterState)
{
    HeaterState = newHeaterState;
}

void Data::setOutDoorFanSpeed(const QString &newOutDoorFanSpeed)
{
    outDoorFanSpeed = newOutDoorFanSpeed;
}

void Data::setOutDoorFanState(const QString &newOutDoorFanState)
{
    if(newOutDoorFanState=="0")outDoorFanState="OFF";
    else if(newOutDoorFanState=="1")outDoorFanState="ON";
    else outDoorFanState="undefined";
}


void Data::setRoomTemp_Before(const QString &newRoomTemp_Before)
{
    RoomTemp_Before = newRoomTemp_Before;
}

void Data::setValveTemp_Before(const QString &newValveTemp_Before)
{
    ValveTemp_Before = newValveTemp_Before;
}

void Data::setBelowTemp_Before(const QString &newBelowTemp_Before)
{
    BelowTemp_Before = newBelowTemp_Before;
}

void Data::setInverter_Normal(const QString &newInverter_Normal)
{
    if(newInverter_Normal=="0")Inverter_Normal="Normal";
    else if(newInverter_Normal=="1")Inverter_Normal="Inverter";
    else Inverter_Normal="undefined";
}


void Data::setTempNo(const QString &newTempNo)
{
    TempNow = newTempNo;
}

void Data::setValveTemp(const QString &newValveTemp)
{
    ValveTemp = newValveTemp;
}

void Data::setBelowTemp(const QString &newBelowTemp)
{
    BelowTemp = newBelowTemp;
}

void Data::setCompressorOFFTime(const QString &newCompressorOFFTime)
{
    if (newCompressorOFFTime==1) CompressorOFFTime="None";
    else CompressorOFFTime = newCompressorOFFTime;
}

void Data::setCompressorOnTime(const QString &newCompressorOnTime)
{
    CompressorOnTime = newCompressorOnTime;
}

void Data::setCompressorState(const QString &newCompressorState)
{
    if(newCompressorState=="0")CompressorState="OFF";
    else if(newCompressorState=="1")CompressorState="ON";
    else CompressorState="undefined";
}

void Data::setSettingTemp(const QString &newSettingTemp)
{
    SettingTemp = newSettingTemp;
}

void Data::setDisplaySettingsTemp(const QString &newDisplaySettingsTemp)
{
    DisplayTemp =std::to_string(newDisplaySettingsTemp.toUInt()/100).c_str();
}

void Data::setOutDoorTemp(const QString &newOutDoorTemp)
{
    OutDoorTemp = newOutDoorTemp;
}

void Data::setLcdTemp(const QString &newLcdTemp)
{

    LcdTemp = std::to_string(newLcdTemp.toUInt()/100).c_str();
}

void Data::setDehumidityTime(const QString &newDehumidityTime)
{
    DehumidityTime = newDehumidityTime;
}

void Data::setDehumidityState(const QString &newDehumidityState)
{
    DehumidityState = newDehumidityState;
}

void Data::setHotKeep(const QString &newHotKeep)
{
    HotKeep = newHotKeep;
}

void Data::setDehumidityAuto(const QString &newDehumidityAuto)
{
    DehumidityAuto = newDehumidityAuto;
}

void Data::setOperationState(const QString &newOperationState)
{
    if(newOperationState=="0")OperationState="OFF";
    else if(newOperationState=="1")OperationState="ON";
    else OperationState="undefined";
}

void Data::setOperationTime(const QString &newOperationTime)
{

    OperationTime = std::to_string((newOperationTime.toInt()*20/1000)).c_str();
}

void Data::setAutoMask(const QString &newAutoMask)
{
    AutoMask = newAutoMask;
}



void Data::setDehumiditylifeMode(const QString &newDehumiditylifeMode)
{
    DehumiditylifeMode = newDehumiditylifeMode;
}

void Data::setModeMemory(const QString &newModeMemory)
{
    if(newModeMemory=="0")ModeMemory="Auto";
    else if(newModeMemory=="1")ModeMemory="Heat";
    else if(newModeMemory=="2")ModeMemory="Cool";
    else if(newModeMemory=="3")ModeMemory="Dry";
    else if(newModeMemory=="4")ModeMemory="Fan";
    else if(newModeMemory=="5")ModeMemory="Clean";
    else if(newModeMemory=="6")ModeMemory="idle";
    else ModeMemory="undefined";

}

void Data::setErrorCode(const QString &newErrorCode)
{
    if(newErrorCode=="0")ErrorCode="error Free (0)";
    else if(newErrorCode=="1")ErrorCode="Sensor Open Circuit (1)";
    else if(newErrorCode=="2")ErrorCode="Display indication hi error (2)";
    else if(newErrorCode=="3")ErrorCode="Fan Stopped (3)";
    else if(newErrorCode=="4")ErrorCode="eva Over Heat (4)";
    else if(newErrorCode=="5")ErrorCode="Delta Temp Pass Five Cool Dry (5)";
    else if(newErrorCode=="6")ErrorCode="Delta Temp Pass Five heat (6)";
    else if(newErrorCode=="7")ErrorCode="Sensor Short Circuit (7)";
    else if(newErrorCode=="8")ErrorCode="Gas Leakage (8)";
    else ErrorCode="undefined";

}

void Data::setACModel(const QString &newModel)
{
    if(newModel=="0")ACModel="TY-C12AEE";
    else if(newModel=="1")ACModel="TY-C18BEE";
    else if(newModel=="2")ACModel="TY-C24BEE";
    else if(newModel=="3")ACModel="TH-C12AEE";
    else if(newModel=="4")ACModel="TH-C18BEE";
    else if(newModel=="5")ACModel="TH-C24BEE";
    else ACModel="undefined";
}

void Data::setoutFanControl(const QString &newFanControl)
{
    OutFanControl = newFanControl;
}

void Data::setOperationMode(const QString &newOperationMode)
{
    if(newOperationMode=="0")OperationMode="Auto";
    else if(newOperationMode=="1")OperationMode="Heat";
    else if(newOperationMode=="2")OperationMode="Cool";
    else if(newOperationMode=="3")OperationMode="Dry";
    else if(newOperationMode=="4")OperationMode="Fan";
    else if(newOperationMode=="5")OperationMode="Clean";
    else if(newOperationMode=="6")OperationMode="idle";
    else OperationMode="undefined";
}

void Data::setFD(const QString &newTS)
{
    if(OperationMode=="Heat"){
        if(newTS=="0")FD="__";
        else if(newTS=="1")FD="FD1";
        else if(newTS=="2")FD="FD2";
        else if(newTS=="3")FD="FD3";
        else if(newTS=="4")FD="FD4";
        else if(newTS=="5")FD="FD5";
        else if(newTS=="6")FD="FD6";
        else if(newTS=="7")FD="FD7";
        else if(newTS=="8")FD="FD8";
        else if(newTS=="9")FD="FD9";
        else if(newTS=="10")FD="FD10";
        else if(newTS=="11")FD="FD 11";
        else if(newTS=="12")FD="FD12";
        else if(newTS=="13")FD="FD13";
        else FD="undefined";
    }
    else if(OperationMode=="Cool"){
        if(newTS=="3")FD="FD3";
        else if(newTS=="4")FD="FD4";
        else if(newTS=="5")FD="FD5";
        else if(newTS=="6")FD="FD6";
        else if(newTS=="7")FD="FD7";
        else if(newTS=="8")FD="FD8";
        else if(newTS=="9")FD="FD9";
        else FD="undefined";
    }
    else if(OperationMode=="Dry"){
        if(newTS=="1")FD="FD1";
        else if(newTS=="2")FD="FD2";
        else FD="undefined";
    }
    else if(OperationMode=="Fan"){
        if(newTS=="3")FD="FD3";
        else if(newTS=="6")FD="FD6";
        else if(newTS=="9")FD="FD9";
        else FD="undefined";
    }
    else FD="undefined";


}

void Data::setModelEEP(const QString &newModelEEP)
{

    ModelEEP = newModelEEP;
}

void Data::setMotorType(const QString &newMotorType)
{
    if(newMotorType=="0") MotorType="AC";
    else if(newMotorType=="1") MotorType="DC";
    else MotorType="undefined";
}

void Data::setMotorPartCode(const QString &newMotorPartCode)
{
    MotorPartCode = newMotorPartCode;
}

void Data::setEEPVersion(const QString &newEEPVersion)
{
    EEPVersion = newEEPVersion;
}

void Data::setFlashVersion(const QString &newFlashVersion)
{
    FlashVersion = newFlashVersion;
}

void Data::setMonitorModel(const QString &newMonitorModel)
{
    MonitorModel = newMonitorModel;
}

void Data::setMonitorabilityVersion(const QString &newMonitorabilityVersion)
{
    if(newMonitorabilityVersion=="0") MonitorabilityVersion = "12K";
    else if(newMonitorabilityVersion=="1") MonitorabilityVersion = "18K";
    else if(newMonitorabilityVersion=="2") MonitorabilityVersion = "24K";
    else     MonitorabilityVersion ="undefined";
}

void Data::setSpMeasur(const QString &newSpMeasur)
{
    SpMeasur = newSpMeasur;
}

void Data::setOperationCycle(const QString &newOperationCycle)
{
    if(newOperationCycle=="0") OperationCycle="HP";
    else if(newOperationCycle=="1") OperationCycle="Cool Only";
    else OperationCycle="undefined";
}

void Data::setAbility(const QString &newAbility)
{
    if(newAbility=="0") Ability = "12K";
    else if(newAbility=="1") Ability = "18K";
    else if(newAbility=="2") Ability = "24K";
    else Ability="undefined";
}


