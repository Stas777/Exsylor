#include "knowledgedialogue.h"
#include "ui_knowledgedialogue.h"

KnowledgeDialogue::KnowledgeDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KnowledgeDialogue)
{
    ui->setupUi(this);
}

KnowledgeDialogue::~KnowledgeDialogue()
{
    delete ui;
}
