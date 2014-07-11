#include "elsetab.h"
#include "ui_elsetab.h"

ElseTab::ElseTab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ElseTab)
{
    ui->setupUi(this);
}

ElseTab::~ElseTab()
{
    delete ui;
}
