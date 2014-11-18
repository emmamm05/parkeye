/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Nov 18 03:13:28 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *lineParking;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineReference;
    QToolButton *fileBttnParking;
    QToolButton *fileBttnReference;
    QLabel *imgRaw;
    QCommandLinkButton *bttnStep;
    QCommandLinkButton *bttnRestart;
    QLabel *imgRef;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1365, 688);
        MainWindow->setMinimumSize(QSize(640, 0));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lineParking = new QLineEdit(centralwidget);
        lineParking->setObjectName(QString::fromUtf8("lineParking"));
        lineParking->setGeometry(QRect(200, 20, 113, 22));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 171, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 60, 171, 16));
        lineReference = new QLineEdit(centralwidget);
        lineReference->setObjectName(QString::fromUtf8("lineReference"));
        lineReference->setGeometry(QRect(200, 60, 113, 22));
        fileBttnParking = new QToolButton(centralwidget);
        fileBttnParking->setObjectName(QString::fromUtf8("fileBttnParking"));
        fileBttnParking->setGeometry(QRect(310, 20, 23, 21));
        fileBttnReference = new QToolButton(centralwidget);
        fileBttnReference->setObjectName(QString::fromUtf8("fileBttnReference"));
        fileBttnReference->setGeometry(QRect(310, 60, 23, 21));
        imgRaw = new QLabel(centralwidget);
        imgRaw->setObjectName(QString::fromUtf8("imgRaw"));
        imgRaw->setGeometry(QRect(30, 100, 651, 531));
        imgRaw->setAutoFillBackground(false);
        imgRaw->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 127);"));
        bttnStep = new QCommandLinkButton(centralwidget);
        bttnStep->setObjectName(QString::fromUtf8("bttnStep"));
        bttnStep->setGeometry(QRect(1240, 50, 101, 41));
        bttnRestart = new QCommandLinkButton(centralwidget);
        bttnRestart->setObjectName(QString::fromUtf8("bttnRestart"));
        bttnRestart->setGeometry(QRect(1240, 0, 101, 41));
        imgRef = new QLabel(centralwidget);
        imgRef->setObjectName(QString::fromUtf8("imgRef"));
        imgRef->setGeometry(QRect(690, 100, 651, 531));
        imgRef->setAutoFillBackground(false);
        imgRef->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 127);"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1365, 19));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        lineParking->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Imagen de Parqueo", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Imagen de Referencia", 0, QApplication::UnicodeUTF8));
        lineReference->setText(QString());
        fileBttnParking->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        fileBttnReference->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        imgRaw->setText(QString());
        bttnStep->setText(QApplication::translate("MainWindow", "Step", 0, QApplication::UnicodeUTF8));
        bttnRestart->setText(QApplication::translate("MainWindow", "Restart", 0, QApplication::UnicodeUTF8));
        imgRef->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
