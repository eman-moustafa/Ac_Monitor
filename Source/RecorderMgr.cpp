#include "RecorderMgr.h"
#include <QRegularExpression>

RecorderMgr::RecorderMgr()
{
    m_db=QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("Records.sqlite");
    if(m_db.open()){
         query=new QSqlQuery (m_db);
    }
    else {
        emit DataBaseError("Cannot connect To database !!!!"+m_db.lastError().text());

    }

}

QStringList RecorderMgr::getRecords()
{
    if(m_db.isOpen()){
        return m_db.tables();
    }
    else
        {
                emit DataBaseError("Cannot connect To database !!!!"+m_db.lastError().text());
                return {};
    };

}

int RecorderMgr::getRecordlength(QString RecordName)
{
    if(m_db.isOpen()){
        query->exec(QString("SELECT COUNT(*) FROM %1").arg(RecordName));
        if (!query->isActive()) {
            emit RecordRetrieveError("Failed to get rows length :" +query->lastError().text());
            qDebug()<<"Failed to get rows length  :" <<query->lastError().text();
         }
        if(query->next()) return query->value(0).toInt();
        return 0;
    }
    else
        {
                emit DataBaseError("Cannot connect To database !!!!"+m_db.lastError().text());
                return 0;
    };
}

QString RecorderMgr::createRecord(QString RecordName)
{
    if(m_db.isOpen()){
        QString colums="[indx] INTEGER PRIMARY KEY AUTOINCREMENT"
                       ",";
        QVector<QString>::iterator itt;
                for (itt = FrameData.begin(); itt != FrameData.end(); ++itt) {
                    if((*itt)=="Time")colums+=(*itt)+" varchar(20),";
                    else colums+=(*itt)+" varchar(4),";
                }
                if (!colums.isEmpty()) {
                       colums.truncate(colums.size()-1);
                   }
        query->exec(QString("CREATE TABLE %1  (%2)").arg(RecordName,colums));

        // check if the query was executed successfully
        if (!query->isActive()) {
            emit RecordcreateError("Failed to create Record:"+query->lastError().text());
            return NULL;
         }
        return QString("%1").arg(RecordName) ;
    }
    else
        {
                emit DataBaseError("Cannot connect To database !!!!"+m_db.lastError().text());
                return NULL;
        };
}

bool RecorderMgr::createRecordFrame(QString RecName, QVector<QString> Data)
{
    QString colums="";
    QString values="";
    if(m_db.isOpen()){
        QVector<QString>::iterator itt;
                for (itt = Data.begin(); itt != Data.end(); ++itt) {
                    QStringList list = (*itt).split(QRegExp("\\s+"), QString::SkipEmptyParts);
                    if(list.length()>=2){
                        if(FrameData.contains(list[0])){
                            colums+=list[0]+",";
                            values+="\'"+list[1]+"\'"+",";
                        }

                    }
                }
                if (!colums.isEmpty()) {
                       colums.truncate(colums.size()-1);
                   }
                if (!values.isEmpty()) {
                       values.truncate(values.size()-1);
                   }
                query->exec(QString("INSERT INTO %1 (%2 )VALUES (%3)").arg(RecName,colums,values));
                // check if the query was executed successfully
                if (!query->isActive()) {
                    emit RecordcreateFrameError("Failed to insert elements :" +query->lastError().text());
                    qDebug()<<"Failed to insert elements :" <<query->lastError().text()<<endl;
                 }
                return true;
    }
    else
        {
                emit DataBaseError("Cannot connect To database !!!!"+m_db.lastError().text());
                return false;
    };
}

QMap<QString,QString> RecorderMgr::RetrieveFramedata(QString RecName, int index)
{

    QMap<QString,QString> result;
    if(m_db.isOpen()){
        QString colums;
        QVector<QString>::iterator itt;
                for (itt = FrameData.begin(); itt != FrameData.end(); ++itt) {
                    colums+=(*itt)+",";
                }
                if (!colums.isEmpty()) {
                       colums.truncate(colums.size()-1);
                   }

        query->exec(QString("SELECT %1 FROM %2 WHERE indx='%3'").arg(colums,RecName,std::to_string(index).c_str()));
        if (!query->isActive()) {
            emit RecordRetrieveError("Failed to retrieve elements :" +query->lastError().text());
            qDebug()<<"Failed to retrieve elements :" <<query->lastError().text();
         }
        if(query->next()) {
            int counter=0;
            for (itt = FrameData.begin(); itt != FrameData.end(); ++itt) {
                result.insert((*itt),query->value(counter).toString());
                counter++;
            }

        }
    }
    else
        {
                emit DataBaseError("Cannot connect To database !!!!"+m_db.lastError().text());
        }
     return result;

}

void RecorderMgr::ExtractRecord(QString RecName,QString cols,int offset,QString Path){
    if(m_db.isOpen()){
        query->exec(QString("SELECT %1 FROM %2").arg(cols,RecName));
        if (!query->isActive()) {
            qDebug()<<"Failed to Extract record : " <<query->lastError().text();
            emit RecordExportError(QString("Failed to Extract record : " +query->lastError().text()));
            return;
         }
        QSqlRecord record = query->record();
        // Create a new Excel document
        QXlsx::Document xlsx;
        int row = 1;

        // Write the column headers to the first row of the worksheet
        for (int i = 0; i <= record.count(); i++) {
            xlsx.write(row, i+1 , record.fieldName(i));
        }

        // Write the data to the worksheet
        int counter=0;
        while (query->next()) {
            if(counter%offset==0){
                 row++;
                for (int i = 0; i <= record.count(); i++) {
                    xlsx.write(row, i+1, query->value(i).toString());
                }
            }
            counter++;
        }
        emit RecordExportSucc(RecName+" Has Been exported Suc ! to "+Path);

        // Save the Excel document to a file
 qDebug()<<QString(Path+".xlsx");
 xlsx.saveAs(QString(Path+".xlsx"));

    }
    else
        {
                emit DataBaseError("Cannot connect To database !!!!"+m_db.lastError().text());
        };

}

void RecorderMgr::importRecord(QString Path){
    if(m_db.isOpen()){
        QRegularExpression regex("^[0-9\\W]");
        QString newfilename;
               QFile f(Path);
               QFileInfo fileInfo(f.fileName());
               QString filename(fileInfo.baseName());
               QXlsx::Document xlsx(Path);
               // Get the data from the first worksheet of the Excel file

               if(xlsx.load()){


                    //Insert the data into the SQLite table
                   for (int i = 1; i <= xlsx.dimension().rowCount(); i++) {
                       QVector<QString> Values;
                       Values.reserve(FrameData.length());
                       for (int j = 1; j <= xlsx.dimension().columnCount(); j++) {
                           Values.push_back(QString(xlsx.read(1,j).toString()+" "+xlsx.read(i,j).toString()));
                       }
                       if(i==1){
                           if (regex.match(filename).hasMatch()) {
                                   newfilename = "Rec_" + filename;
                                  qDebug() << "Modified File Name:" << filename;
                           createRecord(newfilename);
                           }
                           else {
                                  qDebug() << "File Name:" << Path;
                               if(i==1){

                                   createRecord(filename);

                               }
                               else{
                                   createRecordFrame(filename,Values);
                               }
                           }

                       }
                       else{
                           createRecordFrame(newfilename,Values);
                       }
                   }

                   emit RecordimportSucc(newfilename+ "Importe Succ ! added To Database");

                       }


               else{
                   qDebug()<<"Failed To open File"<<endl;
                   emit RecordImportError("Failed To open File");
               }
           }

        else
            {
                    emit DataBaseError("Cannot connect To database !!!!"+m_db.lastError().text());
            };
}




