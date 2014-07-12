#ifndef EFE_H
#define EFE_H

#include <QWidget>

namespace Ui {
class efe;
}

class efe : public QWidget
{
    Q_OBJECT

public:
    explicit efe(QWidget *parent = 0);
    ~efe();

private:
    Ui::efe *ui;
};

#endif // EFE_H
