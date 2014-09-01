#include "datadialogue.h"
#include "ui_datadialogue.h"

int currow = -1;

DataDialogue::DataDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataDialogue)
{
    ui->setupUi(this);
    initTable();
}

DataDialogue::~DataDialogue()
{
    delete ui;
}

void DataDialogue::renumerate()
{
    int rowcount = ui->mainTable->rowCount();
    rowcount++;
    for(int i = 1; i<rowcount; i++)
    {
        QString k = QString::number(i);
        ui->mainTable->setVerticalHeaderItem(i,new QTableWidgetItem(k));
    }
}

void DataDialogue::initTable()
{
    int count = 4; // count = column count from some model
    int rowcount = 5;// rowcount = row count from some model
    ui->mainTable->setColumnCount(count);
    ui->mainTable->setRowCount(rowcount);
    ui->mainTable->setVerticalHeaderItem(0,new QTableWidgetItem("Current row: new"));
    for(int i = 0; i<count; i++)
    {
        QString header = "some header ";
        QString s = QString::number(i+1);
        header +=s;
        int hsize = header.size();
        ui->mainTable->setHorizontalHeaderItem(i,new QTableWidgetItem(header));
        ui->mainTable->setColumnWidth(i,hsize*7);
        ui->mainTable->setItem(0,i, new QTableWidgetItem(""));
    }
    for(int i = 1; i < rowcount; i++)
    {
        QString k = QString::number(i);
        ui->mainTable->setVerticalHeaderItem(i,new QTableWidgetItem(k));
        for(int j = 0; j < count; j++)
        {
            ui->mainTable->setItem(i,j, new QTableWidgetItem("some info"));
            ui->mainTable->item(i,j)->setFlags(Qt::ItemIsEnabled);
        }
    }
}

void DataDialogue::on_addButton_clicked()
{
    int count = ui->mainTable->columnCount();
        if(currow!=-1)
        {
            QString et_item;
            for(int i = 0; i < count ;i++)
            {
                et_item = ui->mainTable->item(0,i)->text();
                ui->mainTable->setItem(currow,i,new QTableWidgetItem(et_item));
                ui->mainTable->item(currow,i)->setFlags(Qt::ItemIsEnabled);
                ui->mainTable->setItem(0,i,new QTableWidgetItem(""));
            }
            currow = -1;
            ui->mainTable->setVerticalHeaderItem(0,new QTableWidgetItem("Current row: new"));
        }
        else
        {
            QString n_item;
            ui->mainTable->insertRow(1);
            renumerate();
            for(int j = 0; j < count ;j++)
            {
                n_item = ui->mainTable->item(0,j)->text();
                ui->mainTable->setItem(1,j,new QTableWidgetItem(n_item));
                ui->mainTable->item(1,j)->setFlags(Qt::ItemIsEnabled);
                ui->mainTable->setItem(0,j,new QTableWidgetItem(""));
            }
        }
        ui->addButton->setText("New line");
}

void DataDialogue::on_mainTable_itemDoubleClicked(QTableWidgetItem *item)
{
    int row = item->row();
      int count = ui->mainTable->columnCount();
      for(int i = 0; i<count; i++)
      {
          if (currow!= -1)
          ui->mainTable->item(currow,i)->setBackgroundColor(Qt::white);
      }
      QString header = "Current row: ";
      if(row != 0)
      {
          ui->addButton->setText("Edit line");
          QString s = QString::number(row);
          header +=s;
          ui->mainTable->setVerticalHeaderItem(0,new QTableWidgetItem(header));
          for(int i = 0; i<count; i++)
          {
              QString mt_item = ui->mainTable->item(row,i)->text();
              ui->mainTable->setItem(0,i, new QTableWidgetItem(mt_item));
              ui->mainTable->item(row,i)->setBackgroundColor(Qt::blue);
              currow = row;
          }
      }
}

void DataDialogue::on_clearButton_clicked()
{
    ui->addButton->setText("New line");
       int count = ui->mainTable->columnCount();
       ui->mainTable->setVerticalHeaderItem(0,new QTableWidgetItem("Current row: new"));
       for(int j = 0; j<count; j++)
       {
           if (currow!= -1)
           ui->mainTable->item(currow,j)->setBackgroundColor(Qt::white);
           ui->mainTable->setItem(0,j,new QTableWidgetItem(""));
       }
       currow = -1;
}
