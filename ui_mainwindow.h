/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *sizeValid_btn;
    QLabel *image1_label;
    QPushButton *randomValid_btn;
    QLabel *image2_label;
    QPushButton *GetRandomImage_btn;
    QPushButton *GetSameImage_btn_3;
    QLabel *result_label;
    QLabel *label;
    QLabel *label_2;
    QPushButton *matchtest4all_btn_2;
    QPushButton *sizeTest4All_btn;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(611, 458);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizeValid_btn = new QPushButton(centralWidget);
        sizeValid_btn->setObjectName(QString::fromUtf8("sizeValid_btn"));
        sizeValid_btn->setGeometry(QRect(430, 270, 151, 31));
        image1_label = new QLabel(centralWidget);
        image1_label->setObjectName(QString::fromUtf8("image1_label"));
        image1_label->setGeometry(QRect(90, 30, 141, 81));
        randomValid_btn = new QPushButton(centralWidget);
        randomValid_btn->setObjectName(QString::fromUtf8("randomValid_btn"));
        randomValid_btn->setGeometry(QRect(270, 270, 141, 31));
        image2_label = new QLabel(centralWidget);
        image2_label->setObjectName(QString::fromUtf8("image2_label"));
        image2_label->setGeometry(QRect(400, 40, 151, 71));
        GetRandomImage_btn = new QPushButton(centralWidget);
        GetRandomImage_btn->setObjectName(QString::fromUtf8("GetRandomImage_btn"));
        GetRandomImage_btn->setGeometry(QRect(350, 190, 131, 31));
        GetSameImage_btn_3 = new QPushButton(centralWidget);
        GetSameImage_btn_3->setObjectName(QString::fromUtf8("GetSameImage_btn_3"));
        GetSameImage_btn_3->setGeometry(QRect(350, 230, 131, 31));
        result_label = new QLabel(centralWidget);
        result_label->setObjectName(QString::fromUtf8("result_label"));
        result_label->setGeometry(QRect(10, 350, 571, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans"));
        font.setPointSize(11);
        result_label->setFont(font);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 140, 59, 14));
        QFont font1;
        font1.setFamily(QString::fromUtf8("DejaVu Sans"));
        font1.setPointSize(12);
        label->setFont(font1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(410, 150, 59, 14));
        label_2->setFont(font);
        matchtest4all_btn_2 = new QPushButton(centralWidget);
        matchtest4all_btn_2->setObjectName(QString::fromUtf8("matchtest4all_btn_2"));
        matchtest4all_btn_2->setGeometry(QRect(30, 230, 191, 31));
        sizeTest4All_btn = new QPushButton(centralWidget);
        sizeTest4All_btn->setObjectName(QString::fromUtf8("sizeTest4All_btn"));
        sizeTest4All_btn->setGeometry(QRect(30, 270, 191, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 611, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        sizeValid_btn->setText(QApplication::translate("MainWindow", "Size Validation", 0, QApplication::UnicodeUTF8));
        image1_label->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        randomValid_btn->setText(QApplication::translate("MainWindow", "Car Matching", 0, QApplication::UnicodeUTF8));
        image2_label->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        GetRandomImage_btn->setText(QApplication::translate("MainWindow", "Get Random Car", 0, QApplication::UnicodeUTF8));
        GetSameImage_btn_3->setText(QApplication::translate("MainWindow", "Get Same Car", 0, QApplication::UnicodeUTF8));
        result_label->setText(QApplication::translate("MainWindow", "Result", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Car 1", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Car 2", 0, QApplication::UnicodeUTF8));
        matchtest4all_btn_2->setText(QApplication::translate("MainWindow", "Match Test for All Images", 0, QApplication::UnicodeUTF8));
        sizeTest4All_btn->setText(QApplication::translate("MainWindow", "Size Test for All Matches", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
