/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *enterBut;
    QLabel *label;
    QLabel *error;
    QLineEdit *enterPass;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(420, 497);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        enterBut = new QPushButton(centralwidget);
        enterBut->setObjectName(QString::fromUtf8("enterBut"));
        enterBut->setGeometry(QRect(60, 240, 241, 41));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 30, 261, 61));
        error = new QLabel(centralwidget);
        error->setObjectName(QString::fromUtf8("error"));
        error->setGeometry(QRect(100, 110, 191, 41));
        enterPass = new QLineEdit(centralwidget);
        enterPass->setObjectName(QString::fromUtf8("enterPass"));
        enterPass->setGeometry(QRect(30, 180, 301, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 420, 29));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        enterBut->setText(QCoreApplication::translate("MainWindow", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\270\320\275-\320\272\320\276\320\264 \320\264\320\273\321\217 \320\262\321\205\320\276\320\264\320\260!", nullptr));
        error->setText(QCoreApplication::translate("MainWindow", "\320\237\320\270\320\275-\320\272\320\276\320\264 \320\275\320\265\320\262\320\265\321\200\320\275\321\213\320\271!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
