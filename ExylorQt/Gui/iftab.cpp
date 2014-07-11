#include "iftab.h"
#include "ui_iftab.h"

IfTab::IfTab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IfTab)
{
    ui->setupUi(this);
}

IfTab::~IfTab()
{
    delete ui;
}
