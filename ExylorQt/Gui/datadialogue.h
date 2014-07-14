#ifndef DATADIALOGUE_H
#define DATADIALOGUE_H

#include <QDialog>
#include "../Kernel/Model.h"

namespace Ui {
class DataDialogue;
}

class DataDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit DataDialogue(QWidget *parent = 0, Model *m = 0);
    ~DataDialogue();

private:
    Ui::DataDialogue *ui;
    Model *model;
};

#endif // DATADIALOGUE_H
