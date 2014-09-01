#ifndef DATADIALOGUE_H
#define DATADIALOGUE_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class DataDialogue;
}

class DataDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit DataDialogue(QWidget *parent = 0);
    ~DataDialogue();

private slots:
    void on_addButton_clicked();

    void on_mainTable_itemDoubleClicked(QTableWidgetItem *item);

    void on_clearButton_clicked();

private:
    void renumerate();
    void initTable();
    Ui::DataDialogue *ui;
};

#endif // DATADIALOGUE_H
