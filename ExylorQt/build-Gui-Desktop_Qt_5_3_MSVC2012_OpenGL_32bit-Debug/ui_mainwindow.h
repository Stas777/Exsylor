/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "expertwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionAbout_Exsylor;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    ExpertWidget *expertMode;
    QWidget *recognizeMode;
    QMenuBar *menuBar;
    QMenu *menuNew;
    QMenu *menuAbove;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(695, 405);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAbout_Exsylor = new QAction(MainWindow);
        actionAbout_Exsylor->setObjectName(QStringLiteral("actionAbout_Exsylor"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 0, 671, 341));
        expertMode = new ExpertWidget();
        expertMode->setObjectName(QStringLiteral("expertMode"));
        tabWidget->addTab(expertMode, QString());
        recognizeMode = new QWidget();
        recognizeMode->setObjectName(QStringLiteral("recognizeMode"));
        tabWidget->addTab(recognizeMode, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 695, 21));
        menuNew = new QMenu(menuBar);
        menuNew->setObjectName(QStringLiteral("menuNew"));
        menuAbove = new QMenu(menuBar);
        menuAbove->setObjectName(QStringLiteral("menuAbove"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuNew->menuAction());
        menuBar->addAction(menuAbove->menuAction());
        menuNew->addAction(actionNew);
        menuNew->addAction(actionOpen);
        menuNew->addSeparator();
        menuNew->addAction(actionExit);
        menuAbove->addAction(actionAbout_Exsylor);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionAbout_Exsylor->setText(QApplication::translate("MainWindow", "About Exsylor", 0));
        tabWidget->setTabText(tabWidget->indexOf(expertMode), QApplication::translate("MainWindow", "Expert Mode", 0));
        tabWidget->setTabText(tabWidget->indexOf(recognizeMode), QApplication::translate("MainWindow", "Recognize Mode", 0));
        menuNew->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuAbove->setTitle(QApplication::translate("MainWindow", "About", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
