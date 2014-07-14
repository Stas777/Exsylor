#include "newfile.h"
#include "ui_newfile.h"
#include "QFileDialog"
#include <QMessageBox>
#include "mainwindow.h"
#include <QStandardItemModel>

NewFile::NewFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFile)
{
    ui->setupUi(this);
    model = new Model();
    attrListViewModel = new QStandardItemModel();
    ui->attributeslistView->setModel(attrListViewModel);
    valueListViewModel = new QStandardItemModel();
    ui->valueslistView->setModel(valueListViewModel);
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
        QString attr = ui->attributeslineEdit->text();

        model->getDataTemplate()->addAttr(attr);

        QStandardItem* item = new QStandardItem(attr);
        attrListViewModel->appendRow(item);

        //select this element
        int rowCount = attrListViewModel->rowCount();
        QModelIndex currentIndex = attrListViewModel->index(rowCount - 1, 0);
        ui->attributeslistView->setCurrentIndex(currentIndex);

        ui->attributeslineEdit->setText("");
    }
    if (ui->valueslineEdit->text() != NULL) {
        int idAttr = ui->attributeslistView->currentIndex().row();
        QString attrValue = ui->valueslineEdit->text();

        model->getDataTemplate()->addValue(idAttr, attrValue);

        QStandardItem* item = new QStandardItem(attrValue);
        valueListViewModel->appendRow(item);
        ui->valueslineEdit->setText("");
    }
}

Model* NewFile::getModel() {
    return model;
}

void NewFile::on_attributeslistView_clicked(const QModelIndex &index)
{
    int idAttr = ui->attributeslistView->currentIndex().row();

    valueListViewModel->clear();

    DataAttr* dataAttr = model->getDataTemplate()->getAttr(idAttr);

    foreach (QString qstr, dataAttr->getValueNames()) {
        QStandardItem* item = new QStandardItem(qstr);
        valueListViewModel->appendRow(item);
    }
}

void NewFile::on_okButton_clicked()
{
    this->close();

}
