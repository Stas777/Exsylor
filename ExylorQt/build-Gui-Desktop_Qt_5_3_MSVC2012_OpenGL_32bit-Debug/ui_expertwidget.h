/********************************************************************************
** Form generated from reading UI file 'expertwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPERTWIDGET_H
#define UI_EXPERTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>
#include <../Gui/datadialog.h>

QT_BEGIN_NAMESPACE

class Ui_ExpertWidget
{
public:
    QComboBox *comboBox;
    QPushButton *newButton;
    QPushButton *deleteButton;
    QTreeView *treeView;
    QTabWidget *tabWidget;
    DataDialog *dataTab;
    QWidget *knowledgeTab;

    void setupUi(QWidget *ExpertWidget)
    {
        if (ExpertWidget->objectName().isEmpty())
            ExpertWidget->setObjectName(QStringLiteral("ExpertWidget"));
        ExpertWidget->resize(694, 360);
        comboBox = new QComboBox(ExpertWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(10, 10, 161, 22));
        newButton = new QPushButton(ExpertWidget);
        newButton->setObjectName(QStringLiteral("newButton"));
        newButton->setGeometry(QRect(10, 330, 75, 23));
        deleteButton = new QPushButton(ExpertWidget);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));
        deleteButton->setGeometry(QRect(90, 330, 75, 23));
        treeView = new QTreeView(ExpertWidget);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(530, 60, 151, 271));
        tabWidget = new QTabWidget(ExpertWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 40, 511, 291));
        dataTab = new DataDialog();
        dataTab->setObjectName(QStringLiteral("dataTab"));
        tabWidget->addTab(dataTab, QString());
        knowledgeTab = new QWidget();
        knowledgeTab->setObjectName(QStringLiteral("knowledgeTab"));
        tabWidget->addTab(knowledgeTab, QString());

        retranslateUi(ExpertWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ExpertWidget);
    } // setupUi

    void retranslateUi(QWidget *ExpertWidget)
    {
        ExpertWidget->setWindowTitle(QApplication::translate("ExpertWidget", "Form", 0));
        newButton->setText(QApplication::translate("ExpertWidget", "New", 0));
        deleteButton->setText(QApplication::translate("ExpertWidget", "Delete", 0));
        tabWidget->setTabText(tabWidget->indexOf(dataTab), QApplication::translate("ExpertWidget", "Data", 0));
        tabWidget->setTabText(tabWidget->indexOf(knowledgeTab), QApplication::translate("ExpertWidget", "Knowledge", 0));
    } // retranslateUi

};

namespace Ui {
    class ExpertWidget: public Ui_ExpertWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPERTWIDGET_H
