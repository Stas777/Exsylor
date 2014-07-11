#ifndef IFTAB_H
#define IFTAB_H

#include <QDialog>

namespace Ui {
class IfTab;
}

class IfTab : public QDialog
{
    Q_OBJECT

public:
    explicit IfTab(QWidget *parent = 0);
    ~IfTab();

private:
    Ui::IfTab *ui;
};

#endif // IFTAB_H
