#ifndef BROWSERECORDS_H
#define BROWSERECORDS_H

#include <QDialog>
#include <QFileDialog>
#include <QCheckBox>
#include <QListWidgetItem>
#include "RecorderMgr.h"
#include <QRegularExpression>

namespace Ui {
class BrowseRecords;
}

class BrowseRecords : public QDialog
{
    Q_OBJECT

public:
    explicit BrowseRecords(QWidget *parent = nullptr);
    void initRecords();
    void setRole(QString Role);
    void filterRecords(QString Filter);
    void initcolumns();
    ~BrowseRecords();

    void setRec(RecorderMgr *newRec);

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void TogglecolState(QListWidgetItem *item);

private:
    Ui::BrowseRecords *ui;
    RecorderMgr *m_rec;
    QStringList records;
    QString CurrentRecord="";
    QString Role;
    QMap<QString,QString> FrameColumns={{"Time","Time"},{"A	","Monitor ability (Version)"},{"MM","Monitor Model"},{"FV",		"Flash Version"},{"EV",		"EEP Version"},{"MP",		"Motor code"},{"MT",		"Motor Type"},{"A	",		"Ability"},{"OC",		"Operation cycle"},{"SP",		"SP measure"},{"EV",		"Model EEP"},{"FD",		"FD"},{"M	",	    "Operation Mode"},{"FC",		"Out Fan Control"},{"MV",		"AC Model"},{"EC",		"Error Code"},{"PM",		"Mode Memory"},{"DL",		"Dehumidify (Life Mode)"},{"DA",		"Dehumidify (Auto)"},{"AM",		"Auto (Mask)"},{"PT",		"Operation Time"},{"PF",		"Operation state"},{"HK",		"Hot Keep"},{"DS",		"Dehumidity state"},{"D	",	    "Dehumidity time"},{"HD",		"LCD State"},{"CT",		"LCD Temp"},{"BO",		"Badodor timer"},{"FT",		"Filter Timer"},{"OS",		"Outdoor Temp"},{"CT",		"Corrected Room temp"},{"CT",		"Display Temp"},{"ST",		"Setting Temperature"},{"C	",	    "Comp state"},{"CN",		"Comp On time"},{"CF",		"Comp off (safety)"},{"STC",		"Safety Time counter"},{"BT",		"Blow Temp"},{"VT",		"Valve Temp"},{"RT",		"Temp Now"},{"ET",		"ID Pipe Temp"},{"NI",		"Inverter / Normal"},{"PBT",		"Blow Temp (before)"},{"PVT",		"Valve Temp(before)"},{"RTB",		"Room Temp(before)"},{"ETB",		"ID Pipe Temp (before)"},{"DM",		"ID Pipe min while defrost"},{"M1",		"Main off (T1)"},{"M2",		"Main off (T2)"},{"LS",		"Power led"},{"LS",		"Timer led"},{"LS",		"Turbo led"},{"LS",		"Plasma led"},{"LS",		"Eco led"},{"LS",		"Sleep led"},{"LS",		"filter led"},{"LS",		"cooling led"},{"LS",		"heating led"},{"LS",		"loundry led"},{"OF",		"outdoor fan state "},{"OFS",		"Outdoor fan speed"},{"HS",		"heater state"},{"F	",	    "Fan Speed"},{"FD",		"FD"},{"TS",		"Target speed"},{"FB",		"speed feedback"},{"D1",		"Fan duty"},{"PD",		"Phase data"},{"D2",		"Fan on Delay"},{"FB",		"Fan speed"},{"DT",		"Dry fan on/off timer"},{"RT",		"ID room Temp"},{"ET",		"ID pipe Temp"},{"HMS",		"humidity sensor"},{"MZ",		"ID room Zone"},{"HZ",		"ID pipe zone"},{"HMZ",		"Humidity Zone"},{"ST",		"Remocon set"},{"CRT",		"Control Temp"},{"HL",	    "H-L State (name)"},{"HLP",		"H-l Current angle"},{"HM",		"H-L memory (Angle)"},{"VL",		"V-L State (name)"},{"VLP",		"V-l Current angle"},{"VM",		"V-L memory (Angle)"}};
signals:
    void RecordSelected(QString Rec);

};

#endif // BROWSERECORDS_H
