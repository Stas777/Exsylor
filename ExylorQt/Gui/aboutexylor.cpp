#include "aboutexylor.h"
#include "ui_aboutexylor.h"

AboutExylor::AboutExylor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutExylor)
{
    ui->setupUi(this);

    QPixmap logo("../Gui/resources/Exsylor.ico");
    ui->logo->setPixmap(logo);
}

AboutExylor::~AboutExylor()
{
    delete ui;
}

void AboutExylor::on_pushButton_clicked()
{
    this->close();
}
