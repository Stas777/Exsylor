#include "newfile.h"
#include "ui_newfile.h"
#include "QFileDialog"
#include <QMessageBox>
#include "mainwindow.h"

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

void NewFile::on_addButton_clicked()
{
    if (ui->attributeslineEdit->text() != NULL && ui->valueslineEdit->text() != NULL) {
        QMessageBox::information(this,"Format error", "both form can't be filled");
        return;
    }
    if (ui->attributeslineEdit->text() == NULL && ui->valueslineEdit->text() == NULL) {
        QMessageBox::information(this,"Format error", "one, and anly one form must be filled before adding");
        return;
    }
    if (ui->attributeslineEdit->text() != NULL) {
        ((MainWindow*)parentWidget())->getModel()->getDataTemplate()->addAttr(ui->attributeslineEdit->text());
    }



    ui->attributeslineEdit->text();
}
