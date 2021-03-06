#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutexylor.h"
#include "newfile.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new Model();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_Exsylor_triggered()
{
    AboutExylor *about = new AboutExylor(this);
    about->setModal(true);
    about->exec();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionNew_triggered()
{
    NewFile *newfile = new NewFile(this);
    newfile->setModal(true);
    newfile->exec();
    model = newfile->getModel();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open script file"),
                                                    "./", tr("Script files (*.scr)"));
}
Model *MainWindow::getModel()
{
    return model;
}

void MainWindow::setModel(Model &value)
{
    model = &value;
}

