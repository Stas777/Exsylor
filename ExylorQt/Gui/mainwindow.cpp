#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutexylor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_Exsylor_triggered()
{
    AboutExylor *about = new AboutExylor(this);
    about->show();
}
