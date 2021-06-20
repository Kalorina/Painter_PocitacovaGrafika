/********************************************************************************
** Form generated from reading UI file 'ImageViewer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEVIEWER_H
#define UI_IMAGEVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageViewerClass
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave_as;
    QAction *actionRename;
    QAction *actionClear;
    QAction *actionSet_background_color;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBoxSetUp;
    QGridLayout *gridLayout;
    QPushButton *pushButtonDraw;
    QPushButton *pushButtonClear;
    QLabel *label;
    QComboBox *comboBoxAlg;
    QPushButton *pushButtonBezier;
    QPushButton *pushButtonPolygone;
    QPushButton *pushButtonSquere;
    QPushButton *pushButtonCircle;
    QCheckBox *checkBoxFill;
    QLabel *label_2;
    QComboBox *comboBoxInterpolation;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QPushButton *pushButtonRotate;
    QLabel *label_6;
    QDoubleSpinBox *spinBoxScale_2;
    QDoubleSpinBox *spinBoxScale_1;
    QPushButton *pushButtonScale;
    QDoubleSpinBox *spinBoxRotate;
    QLabel *label_3;
    QPushButton *pushButtonShear;
    QDoubleSpinBox *spinBoxShear;
    QLabel *label_5;
    QLabel *label_4;
    QPushButton *pushButtonLayer;
    QPushButton *pushButtonColorPalette;
    QTabWidget *tabWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuImage;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImageViewerClass)
    {
        if (ImageViewerClass->objectName().isEmpty())
            ImageViewerClass->setObjectName(QString::fromUtf8("ImageViewerClass"));
        ImageViewerClass->resize(1563, 811);
        actionNew = new QAction(ImageViewerClass);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionOpen = new QAction(ImageViewerClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave_as = new QAction(ImageViewerClass);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionRename = new QAction(ImageViewerClass);
        actionRename->setObjectName(QString::fromUtf8("actionRename"));
        actionClear = new QAction(ImageViewerClass);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        actionSet_background_color = new QAction(ImageViewerClass);
        actionSet_background_color->setObjectName(QString::fromUtf8("actionSet_background_color"));
        centralWidget = new QWidget(ImageViewerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBoxSetUp = new QGroupBox(centralWidget);
        groupBoxSetUp->setObjectName(QString::fromUtf8("groupBoxSetUp"));
        gridLayout = new QGridLayout(groupBoxSetUp);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButtonDraw = new QPushButton(groupBoxSetUp);
        pushButtonDraw->setObjectName(QString::fromUtf8("pushButtonDraw"));

        gridLayout->addWidget(pushButtonDraw, 0, 0, 1, 1);

        pushButtonClear = new QPushButton(groupBoxSetUp);
        pushButtonClear->setObjectName(QString::fromUtf8("pushButtonClear"));

        gridLayout->addWidget(pushButtonClear, 1, 0, 1, 1);

        label = new QLabel(groupBoxSetUp);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        comboBoxAlg = new QComboBox(groupBoxSetUp);
        comboBoxAlg->addItem(QString());
        comboBoxAlg->addItem(QString());
        comboBoxAlg->setObjectName(QString::fromUtf8("comboBoxAlg"));

        gridLayout->addWidget(comboBoxAlg, 2, 1, 1, 1);

        pushButtonBezier = new QPushButton(groupBoxSetUp);
        pushButtonBezier->setObjectName(QString::fromUtf8("pushButtonBezier"));

        gridLayout->addWidget(pushButtonBezier, 3, 0, 1, 1);

        pushButtonPolygone = new QPushButton(groupBoxSetUp);
        pushButtonPolygone->setObjectName(QString::fromUtf8("pushButtonPolygone"));

        gridLayout->addWidget(pushButtonPolygone, 4, 0, 1, 1);

        pushButtonSquere = new QPushButton(groupBoxSetUp);
        pushButtonSquere->setObjectName(QString::fromUtf8("pushButtonSquere"));

        gridLayout->addWidget(pushButtonSquere, 5, 0, 1, 1);

        pushButtonCircle = new QPushButton(groupBoxSetUp);
        pushButtonCircle->setObjectName(QString::fromUtf8("pushButtonCircle"));

        gridLayout->addWidget(pushButtonCircle, 6, 0, 1, 1);

        checkBoxFill = new QCheckBox(groupBoxSetUp);
        checkBoxFill->setObjectName(QString::fromUtf8("checkBoxFill"));

        gridLayout->addWidget(checkBoxFill, 7, 0, 1, 1);

        label_2 = new QLabel(groupBoxSetUp);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 8, 0, 1, 1);

        comboBoxInterpolation = new QComboBox(groupBoxSetUp);
        comboBoxInterpolation->addItem(QString());
        comboBoxInterpolation->addItem(QString());
        comboBoxInterpolation->addItem(QString());
        comboBoxInterpolation->setObjectName(QString::fromUtf8("comboBoxInterpolation"));

        gridLayout->addWidget(comboBoxInterpolation, 8, 1, 1, 1);


        horizontalLayout->addWidget(groupBoxSetUp);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pushButtonRotate = new QPushButton(groupBox_2);
        pushButtonRotate->setObjectName(QString::fromUtf8("pushButtonRotate"));

        gridLayout_4->addWidget(pushButtonRotate, 0, 0, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_4->addWidget(label_6, 3, 1, 1, 1);

        spinBoxScale_2 = new QDoubleSpinBox(groupBox_2);
        spinBoxScale_2->setObjectName(QString::fromUtf8("spinBoxScale_2"));
        spinBoxScale_2->setMinimum(-99.989999999999995);
        spinBoxScale_2->setSingleStep(0.010000000000000);
        spinBoxScale_2->setValue(0.000000000000000);

        gridLayout_4->addWidget(spinBoxScale_2, 2, 2, 1, 1);

        spinBoxScale_1 = new QDoubleSpinBox(groupBox_2);
        spinBoxScale_1->setObjectName(QString::fromUtf8("spinBoxScale_1"));
        spinBoxScale_1->setMinimum(-99.989999999999995);
        spinBoxScale_1->setSingleStep(0.010000000000000);
        spinBoxScale_1->setValue(0.000000000000000);

        gridLayout_4->addWidget(spinBoxScale_1, 1, 2, 1, 1);

        pushButtonScale = new QPushButton(groupBox_2);
        pushButtonScale->setObjectName(QString::fromUtf8("pushButtonScale"));

        gridLayout_4->addWidget(pushButtonScale, 1, 0, 1, 1);

        spinBoxRotate = new QDoubleSpinBox(groupBox_2);
        spinBoxRotate->setObjectName(QString::fromUtf8("spinBoxRotate"));
        spinBoxRotate->setMinimum(-360.000000000000000);
        spinBoxRotate->setMaximum(360.000000000000000);
        spinBoxRotate->setSingleStep(1.000000000000000);

        gridLayout_4->addWidget(spinBoxRotate, 0, 2, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_4->addWidget(label_3, 1, 1, 1, 1);

        pushButtonShear = new QPushButton(groupBox_2);
        pushButtonShear->setObjectName(QString::fromUtf8("pushButtonShear"));

        gridLayout_4->addWidget(pushButtonShear, 3, 0, 1, 1);

        spinBoxShear = new QDoubleSpinBox(groupBox_2);
        spinBoxShear->setObjectName(QString::fromUtf8("spinBoxShear"));
        spinBoxShear->setMinimum(-99.989999999999995);
        spinBoxShear->setSingleStep(0.010000000000000);
        spinBoxShear->setValue(0.000000000000000);

        gridLayout_4->addWidget(spinBoxShear, 3, 2, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 2, 1, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 2, 0, 1, 1);

        pushButtonLayer = new QPushButton(groupBox);
        pushButtonLayer->setObjectName(QString::fromUtf8("pushButtonLayer"));

        gridLayout_2->addWidget(pushButtonLayer, 0, 0, 1, 1);

        pushButtonColorPalette = new QPushButton(groupBox);
        pushButtonColorPalette->setObjectName(QString::fromUtf8("pushButtonColorPalette"));

        gridLayout_2->addWidget(pushButtonColorPalette, 1, 0, 1, 1);


        horizontalLayout->addWidget(groupBox);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(true);

        horizontalLayout->addWidget(tabWidget);

        ImageViewerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ImageViewerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1563, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuImage = new QMenu(menuBar);
        menuImage->setObjectName(QString::fromUtf8("menuImage"));
        ImageViewerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImageViewerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ImageViewerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ImageViewerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ImageViewerClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuImage->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave_as);
        menuImage->addAction(actionRename);
        menuImage->addAction(actionClear);
        menuImage->addAction(actionSet_background_color);

        retranslateUi(ImageViewerClass);

        QMetaObject::connectSlotsByName(ImageViewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImageViewerClass)
    {
        ImageViewerClass->setWindowTitle(QCoreApplication::translate("ImageViewerClass", "ImageViewer", nullptr));
        actionNew->setText(QCoreApplication::translate("ImageViewerClass", "New", nullptr));
        actionOpen->setText(QCoreApplication::translate("ImageViewerClass", "Open", nullptr));
        actionSave_as->setText(QCoreApplication::translate("ImageViewerClass", "Save as", nullptr));
        actionRename->setText(QCoreApplication::translate("ImageViewerClass", "Rename", nullptr));
        actionClear->setText(QCoreApplication::translate("ImageViewerClass", "Clear", nullptr));
        actionSet_background_color->setText(QCoreApplication::translate("ImageViewerClass", "Set background color", nullptr));
        groupBoxSetUp->setTitle(QCoreApplication::translate("ImageViewerClass", "Set Up", nullptr));
        pushButtonDraw->setText(QCoreApplication::translate("ImageViewerClass", "Draw Object", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("ImageViewerClass", "Clear", nullptr));
        label->setText(QCoreApplication::translate("ImageViewerClass", "Algorithm", nullptr));
        comboBoxAlg->setItemText(0, QCoreApplication::translate("ImageViewerClass", "DDA", nullptr));
        comboBoxAlg->setItemText(1, QCoreApplication::translate("ImageViewerClass", "Bresenhamov", nullptr));

        pushButtonBezier->setText(QCoreApplication::translate("ImageViewerClass", "Bezier Curve", nullptr));
        pushButtonPolygone->setText(QCoreApplication::translate("ImageViewerClass", "Polygone", nullptr));
        pushButtonSquere->setText(QCoreApplication::translate("ImageViewerClass", "Squere", nullptr));
        pushButtonCircle->setText(QCoreApplication::translate("ImageViewerClass", "Circle", nullptr));
        checkBoxFill->setText(QCoreApplication::translate("ImageViewerClass", "Fill Polygone/Squere/Triangle", nullptr));
        label_2->setText(QCoreApplication::translate("ImageViewerClass", "Interpolacia", nullptr));
        comboBoxInterpolation->setItemText(0, QCoreApplication::translate("ImageViewerClass", "None", nullptr));
        comboBoxInterpolation->setItemText(1, QCoreApplication::translate("ImageViewerClass", "Nearest Neighbor", nullptr));
        comboBoxInterpolation->setItemText(2, QCoreApplication::translate("ImageViewerClass", "Barycentrick", nullptr));

        groupBox->setTitle(QCoreApplication::translate("ImageViewerClass", "Layers & Transformations", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("ImageViewerClass", "Transformations", nullptr));
        pushButtonRotate->setText(QCoreApplication::translate("ImageViewerClass", "Rotate", nullptr));
        label_6->setText(QCoreApplication::translate("ImageViewerClass", "factor", nullptr));
        pushButtonScale->setText(QCoreApplication::translate("ImageViewerClass", "Scale", nullptr));
        label_3->setText(QCoreApplication::translate("ImageViewerClass", "factor (x)", nullptr));
        pushButtonShear->setText(QCoreApplication::translate("ImageViewerClass", "Shear", nullptr));
        label_5->setText(QCoreApplication::translate("ImageViewerClass", "(deg)", nullptr));
        label_4->setText(QCoreApplication::translate("ImageViewerClass", "factor (y)", nullptr));
        pushButtonLayer->setText(QCoreApplication::translate("ImageViewerClass", "Choose Object ", nullptr));
        pushButtonColorPalette->setText(QCoreApplication::translate("ImageViewerClass", "Color Palette", nullptr));
        menuFile->setTitle(QCoreApplication::translate("ImageViewerClass", "File", nullptr));
        menuImage->setTitle(QCoreApplication::translate("ImageViewerClass", "Image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageViewerClass: public Ui_ImageViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEVIEWER_H
