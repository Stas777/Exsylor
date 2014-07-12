#ifndef ELSETAB_H
#define ELSETAB_H

#include <QDialog>

namespace Ui {
class ElseTab;
}

class ElseTab : public QDialog
{
    Q_OBJECT

public:
    explicit ElseTab(QWidget *parent = 0);
    ~ElseTab();

private:
    Ui::ElseTab *ui;
};

#endif // ELSETAB_H
