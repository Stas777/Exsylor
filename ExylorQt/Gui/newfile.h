#ifndef NEWFILE_H
#define NEWFILE_H

#include <QDialog>

namespace Ui {
class NewFile;
}

class NewFile : public QDialog
{
    Q_OBJECT

public:
    explicit NewFile(QWidget *parent = 0);
    ~NewFile();

private slots:
    void on_importButton_clicked();

    void on_addButton_clicked();

private:
    Ui::NewFile *ui;
};

#endif // NEWFILE_H
