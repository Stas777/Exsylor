#include "efe.h"
#include "ui_efe.h"

efe::efe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::efe)
{
    ui->setupUi(this);
}

efe::~efe()
{
    delete ui;
}
