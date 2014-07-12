#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Kernel/Model.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Model* getModel();
    void setModel(const Model &value);

private slots:
    void on_actionAbout_Exsylor_triggered();

    void on_actionExit_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    Model model;
};

#endif // MAINWINDOW_H
