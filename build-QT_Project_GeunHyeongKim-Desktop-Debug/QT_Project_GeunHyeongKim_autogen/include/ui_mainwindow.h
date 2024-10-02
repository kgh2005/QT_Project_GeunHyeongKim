/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListView *listView;
    QListView *listView_2;
    QPushButton *Startbutton;
    QGraphicsView *Startimage;
    QLineEdit *Name;
    QLabel *label;
    QSlider *Level;
    QLabel *label_2;
    QGraphicsView *Wood;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        listView = new QListView(centralwidget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(0, 0, 500, 571));
        listView->setStyleSheet(QString::fromUtf8("background-image: url(:/new/background/image/background.png);"));
        listView_2 = new QListView(centralwidget);
        listView_2->setObjectName(QString::fromUtf8("listView_2"));
        listView_2->setGeometry(QRect(520, 20, 260, 530));
        listView_2->setStyleSheet(QString::fromUtf8("background-color: rgb(35, 31, 31);"));
        Startbutton = new QPushButton(centralwidget);
        Startbutton->setObjectName(QString::fromUtf8("Startbutton"));
        Startbutton->setGeometry(QRect(600, 420, 100, 50));
        Startbutton->setStyleSheet(QString::fromUtf8("font: 25 16pt \"URW Bookman\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(154, 153, 150);"));
        Startimage = new QGraphicsView(centralwidget);
        Startimage->setObjectName(QString::fromUtf8("Startimage"));
        Startimage->setGeometry(QRect(90, 480, 331, 361));
        Startimage->setStyleSheet(QString::fromUtf8("background: transparent;"));
        Name = new QLineEdit(centralwidget);
        Name->setObjectName(QString::fromUtf8("Name"));
        Name->setGeometry(QRect(630, 100, 120, 40));
        Name->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(43, 24, 24);"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(540, 110, 80, 20));
        label->setStyleSheet(QString::fromUtf8("font: 25 16pt \"URW Bookman\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(35, 31, 31);"));
        Level = new QSlider(centralwidget);
        Level->setObjectName(QString::fromUtf8("Level"));
        Level->setGeometry(QRect(570, 280, 160, 16));
        Level->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        Level->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(620, 240, 67, 17));
        label_2->setStyleSheet(QString::fromUtf8("font: 25 16pt \"URW Bookman\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(35, 31, 31);"));
        Wood = new QGraphicsView(centralwidget);
        Wood->setObjectName(QString::fromUtf8("Wood"));
        Wood->setGeometry(QRect(100, 80, 291, 241));
        Wood->setStyleSheet(QString::fromUtf8("background: transparent;"));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Startbutton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        Name->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Name :", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Level", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
