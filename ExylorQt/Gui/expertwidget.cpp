#include "expertwidget.h"
#include "ui_expertwidget.h"
#include "datadialog.h"
#include "knowledgedialogue.h"
#include "newfile.h"

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

void ExpertWidget::on_KnowledgePushButton_clicked()
{
    KnowledgeDialogue knowledgeDialog;
    knowledgeDialog.setModal(true);
    knowledgeDialog.exec();
}

void ExpertWidget::on_newButton_clicked()
{
    NewFile *newfile = new NewFile(this);
    newfile->setModal(true);
    newfile->exec();
}
