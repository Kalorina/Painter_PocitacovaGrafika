/********************************************************************************
** Form generated from reading UI file 'ObjectLayers.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTLAYERS_H
#define UI_OBJECTLAYERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *loginGroupBox;
    QGridLayout *gridLayout;
    QSpinBox *spinBoxLayer;
    QTableWidget *tableWidget;
    QGroupBox *bottonGroupBox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *buttonBox;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(610, 414);
        verticalLayout_3 = new QVBoxLayout(Dialog);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        loginGroupBox = new QGroupBox(Dialog);
        loginGroupBox->setObjectName(QString::fromUtf8("loginGroupBox"));
        gridLayout = new QGridLayout(loginGroupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        spinBoxLayer = new QSpinBox(loginGroupBox);
        spinBoxLayer->setObjectName(QString::fromUtf8("spinBoxLayer"));
        spinBoxLayer->setMinimum(1);

        gridLayout->addWidget(spinBoxLayer, 1, 0, 1, 2);

        tableWidget = new QTableWidget(loginGroupBox);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 2);


        verticalLayout_3->addWidget(loginGroupBox);

        bottonGroupBox = new QGroupBox(Dialog);
        bottonGroupBox->setObjectName(QString::fromUtf8("bottonGroupBox"));
        horizontalLayout_2 = new QHBoxLayout(bottonGroupBox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(172, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        buttonBox = new QDialogButtonBox(bottonGroupBox);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_3->addWidget(bottonGroupBox);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        loginGroupBox->setTitle(QString());
        bottonGroupBox->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTLAYERS_H
