#ifndef NEWFILE_H
#define NEWFILE_H

#include <QDialog>
#include <QStandardItemModel>
#include "../Kernel/Model.h"

namespace Ui {
class NewFile;
}

class NewFile : public QDialog
{
    Q_OBJECT

public:
    explicit NewFile(QWidget *parent = 0);
    ~NewFile();
    Model* getModel();
    QStandardItemModel* attrListViewModel;
    QStandardItemModel* valueListViewModel;

private slots:
    void on_importButton_clicked();

    void on_addButton_clicked();

    void on_attributeslistView_clicked(const QModelIndex &index);

private:
    Ui::NewFile *ui;
    Model* model;
};

#endif // NEWFILE_H
