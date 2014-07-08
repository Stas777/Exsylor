/********************************************************************************
** Form generated from reading UI file 'aboutexylor.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTEXYLOR_H
#define UI_ABOUTEXYLOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AboutExylor
{
public:
    QPushButton *pushButton;
    QLabel *logo;
    QLabel *label;

    void setupUi(QDialog *AboutExylor)
    {
        if (AboutExylor->objectName().isEmpty())
            AboutExylor->setObjectName(QStringLiteral("AboutExylor"));
        AboutExylor->resize(189, 151);
        pushButton = new QPushButton(AboutExylor);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(50, 110, 75, 23));
        logo = new QLabel(AboutExylor);
        logo->setObjectName(QStringLiteral("logo"));
        logo->setGeometry(QRect(20, 30, 71, 51));
        label = new QLabel(AboutExylor);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 10, 111, 91));

        retranslateUi(AboutExylor);

        QMetaObject::connectSlotsByName(AboutExylor);
    } // setupUi

    void retranslateUi(QDialog *AboutExylor)
    {
        AboutExylor->setWindowTitle(QApplication::translate("AboutExylor", "Dialog", 0));
        pushButton->setText(QApplication::translate("AboutExylor", "OK", 0));
        logo->setText(QString());
        label->setText(QApplication::translate("AboutExylor", "Exylor Version 1.0\n"
"\n"
"Copyright (C) 2007", 0));
    } // retranslateUi

};

namespace Ui {
    class AboutExylor: public Ui_AboutExylor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTEXYLOR_H
