#include "newfile.h"
#include "ui_newfile.h"
#include "../Kernel/ScrDoc.h"

NewFile::NewFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFile)
{
    ui->setupUi(this);
}

NewFile::~NewFile()
{
    delete ui;
}
