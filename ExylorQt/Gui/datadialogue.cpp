#include "datadialogue.h"
#include "ui_datadialogue.h"

DataDialogue::DataDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataDialogue)
{
    ui->setupUi(this);
}

DataDialogue::~DataDialogue()
{
    delete ui;
}
