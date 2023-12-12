#include "BrowseRecords.h"
#include "ui_BrowseRecords.h"

BrowseRecords::BrowseRecords(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrowseRecords)
{
    ui->setupUi(this);
    initcolumns();



}

void BrowseRecords::initRecords()
{
   records = m_rec->getRecords();
   ui->recordsWidjet->clear();
   for (int i=1;i<records.length() ;i++ ) {
       QListWidgetItem *newItem = new QListWidgetItem;
         newItem->setText(records[i]);
         ui->recordsWidjet->addItem(newItem);
   }


   disconnect(ui->recordsWidjet,&QListWidget::itemDoubleClicked,this,&BrowseRecords::on_pushButton_clicked);

   connect(ui->recordsWidjet,&QListWidget::itemClicked,this,[&](QListWidgetItem *Item){
       CurrentRecord=Item->text();

   });
   connect(ui->recordsWidjet,&QListWidget::itemDoubleClicked,this,&BrowseRecords::on_pushButton_clicked);


}

void BrowseRecords::setRole(QString Role)
{
    this->Role=Role;
    if(Role=="Browse"){
        ui->Path->setVisible(false);
        ui->pushButton->setVisible(false);
        ui->pushButton_2->setVisible(false);
        ui->parmeterscontainer->setVisible(false);


    }
    else{
        ui->Path->setVisible(true);
        ui->pushButton->setVisible(true);
        ui->pushButton_2->setVisible(true);
        ui->parmeterscontainer->setVisible(true
                                           );
    }

}


void BrowseRecords::filterRecords(QString Filter)
{
    ui->recordsWidjet->clear();
    for (int i=1;i<records.length() ;i++ ) {
        if(records[i].contains(Filter)){
            QListWidgetItem *newItem = new QListWidgetItem;
               newItem->setText(records[i]);
               ui->recordsWidjet->addItem(newItem);

        }
    }

}

void BrowseRecords::initcolumns()
{
    auto it=FrameColumns.begin();
    QListWidgetItem *item=new QListWidgetItem();
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
    item->setCheckState(Qt::Checked);
    item->setText("Select all");
    connect(ui->columnsBox,&QListWidget::itemChanged,this,&BrowseRecords::TogglecolState);
    ui->columnsBox->addItem(item);
    while(it!=FrameColumns.end()){
        QListWidgetItem *item=new QListWidgetItem();
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
        item->setCheckState(Qt::Checked);
        item->setText(it.value());
        ui->columnsBox->addItem(item);
        it++;
    }

}


BrowseRecords::~BrowseRecords()
{
    delete ui;
}

void BrowseRecords::on_lineEdit_textChanged(const QString &arg1)
{
    filterRecords(arg1);

}


void BrowseRecords::on_pushButton_2_clicked()
{
    QUrl fileName =QFileDialog::getSaveFileUrl(this,"Choose file name");
    ui->Path->setText(fileName.toString().remove(0,8));

}


void BrowseRecords::on_pushButton_clicked()
{
    QString cols="";
    int offset=ui->offset->value();
    if(Role=="Browse")emit RecordSelected(CurrentRecord);


    else {
        for (int i=1;i<ui->columnsBox->count();i++ ) {
            if(ui->columnsBox->item(i)->checkState()==Qt::Checked){
                QString col=ui->columnsBox->item(i)->text();
                cols+=FrameColumns.key(col)+",";
            }


        }
        if (!cols.isEmpty()) {
               cols.truncate(cols.size()-1);
           }
        m_rec->ExtractRecord(CurrentRecord,cols,offset,ui->Path->text());
    }
    this->hide();
}

void BrowseRecords::TogglecolState(QListWidgetItem *item)
{
    auto state=item->checkState();
    if(item->text()=="Select all"){
        for (int i=0;i<ui->columnsBox->count();i++ ) {
            ui->columnsBox->item(i)->setCheckState(state);
        }

    }


}

void BrowseRecords::setRec(RecorderMgr *newRec)
{
    m_rec = newRec;
}

