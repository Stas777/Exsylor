#ifndef EXPERTWIDGET_H
#define EXPERTWIDGET_H

#include <QWidget>
#include "../Kernel/Model.h"
namespace Ui {
class ExpertWidget;
}

class ExpertWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExpertWidget(QWidget *parent = 0, Model *moik = 0);
    ~ExpertWidget();

private slots:
    void on_dataButton_clicked();

    void on_KnowledgePushButton_clicked();

    void on_newButton_clicked();

private:
    Ui::ExpertWidget *ui;

    Model *model;
};

#endif // EXPERTWIDGET_H
