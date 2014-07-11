#include "newfile.h"
#include "ui_newfile.h"
#include "QFileDialog"

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

void NewFile::on_importButton_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Open model script file"),
                                                    "./", tr("Model script files (*.mod)"));
}
