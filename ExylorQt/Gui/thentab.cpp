#include "thentab.h"
#include "ui_thentab.h"

ThenTab::ThenTab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThenTab)
{
    ui->setupUi(this);
}

ThenTab::~ThenTab()
{
    delete ui;
}
