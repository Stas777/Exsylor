#include "expertwidget.h"
#include "ui_expertwidget.h"
#include "datadialogue.h"
#include "knowledgedialogue.h"
#include "newfile.h"
#include "mainwindow.h"

ExpertWidget::ExpertWidget(QWidget *parent, Model *mo) :
    QWidget(parent),
    ui(new Ui::ExpertWidget)
{
    model = mo;
    ui->setupUi(this);
}

ExpertWidget::~ExpertWidget()
{
    delete ui;
}

void ExpertWidget::on_dataButton_clicked()
{

    DataDialogue dataDialogue(this, model);
    dataDialogue.setModal(true);
    dataDialogue.exec();
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
