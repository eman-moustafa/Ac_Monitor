#ifndef RECORDERMGR_H
#define RECORDERMGR_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QDateTime>
#include <sstream>
#include <QObject>
#include <QFileInfo>

#include "xlsxdocument.h"



class RecorderMgr: public QObject
{
    Q_OBJECT
public:
    RecorderMgr();
    QStringList getRecords();
    int getRecordlength(QString RecordName);
    QString createRecord(QString RecordName);
    bool createRecordFrame(QString RecName,QVector<QString> Data);
    QMap<QString,QString> RetrieveFramedata(QString RecName,int index);
    void ExtractRecord(QString RecName,QString cols,int offset,QString Path);
    void importRecord(QString Path);
    QVector<QString>FrameData={"Time","A","MM","FV","MP","MT","OC","SP","EV","M","FC","MV","EC","PM","DL","DA","AM","PT","PF","HK","DS","D","HD","BO","FT","OS","CT","C","CN","CF","STC","BT","VT","NI","PBT","PVT","RTB","ETB","DM","M1","M2","LS","OF","OFS","HS","F","FD","TS","D1","PD","D2","FB","DT","RT","ET","HMS","MZ","HZ","HMZ","ST","CRT","HL","HLP","HM","VL","VLP","VM","SW"};

private:
    QSqlDatabase m_db;
    QSqlQuery *query;
signals:
    void DataBaseError(QString Result);
    void RecordcreateError(QString Result);
    void RecordcreateFrameError(QString Result);
    void RecordRetrieveError(QString Result);
    void RecordImportError(QString Result);
    void RecordExportError(QString Result);
    void RecordimportSucc(QString Result);
    void RecordExportSucc(QString Result);

};

#endif // RECORDERMGR_H
