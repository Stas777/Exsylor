#include "expertwidget.h"
#include "ui_expertwidget.h"
#include "datadialog.h"

ExpertWidget::ExpertWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExpertWidget)
{
    ui->setupUi(this);
}

ExpertWidget::~ExpertWidget()
{
    delete ui;
}

void ExpertWidget::on_dataButton_clicked()
{
    DataDialog dataDialog;
    dataDialog.setModal(true);
    dataDialog.exec();
}
