#ifndef ABOUTEXYLOR_H
#define ABOUTEXYLOR_H

#include <QDialog>

namespace Ui {
class AboutExylor;
}

class AboutExylor : public QDialog
{
    Q_OBJECT

public:
    explicit AboutExylor(QWidget *parent = 0);
    ~AboutExylor();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AboutExylor *ui;
};

#endif // ABOUTEXYLOR_H
