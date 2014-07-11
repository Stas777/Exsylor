#ifndef DATADIALOGUE_H
#define DATADIALOGUE_H

#include <QDialog>

namespace Ui {
class DataDialogue;
}

class DataDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit DataDialogue(QWidget *parent = 0);
    ~DataDialogue();

private:
    Ui::DataDialogue *ui;
};

#endif // DATADIALOGUE_H
