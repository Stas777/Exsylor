#ifndef THENTAB_H
#define THENTAB_H

#include <QDialog>

namespace Ui {
class ThenTab;
}

class ThenTab : public QDialog
{
    Q_OBJECT

public:
    explicit ThenTab(QWidget *parent = 0);
    ~ThenTab();

private:
    Ui::ThenTab *ui;
};

#endif // THENTAB_H
