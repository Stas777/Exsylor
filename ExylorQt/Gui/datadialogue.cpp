#include "datadialogue.h"
#include "ui_datadialogue.h"

DataDialogue::DataDialogue(QWidget *parent, Model *m) :
    QDialog(parent),
    ui(new Ui::DataDialogue)
{
    ui->setupUi(this);
    ui->treeView = new TreeCheckboxWidget();
    ui->treeView->initWithRadiobuttonItems(model, new Data(model->getDataTemplate()));
}

DataDialogue::~DataDialogue()
{
    delete ui;
}
