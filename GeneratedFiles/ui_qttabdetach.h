/********************************************************************************
** Form generated from reading UI file 'qttabdetach.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTTABDETACH_H
#define UI_QTTABDETACH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTTabDetachClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTTabDetachClass)
    {
        if (QTTabDetachClass->objectName().isEmpty())
            QTTabDetachClass->setObjectName(QStringLiteral("QTTabDetachClass"));
        QTTabDetachClass->resize(600, 400);
        menuBar = new QMenuBar(QTTabDetachClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QTTabDetachClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTTabDetachClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QTTabDetachClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QTTabDetachClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QTTabDetachClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QTTabDetachClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QTTabDetachClass->setStatusBar(statusBar);

        retranslateUi(QTTabDetachClass);

        QMetaObject::connectSlotsByName(QTTabDetachClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTTabDetachClass)
    {
        QTTabDetachClass->setWindowTitle(QApplication::translate("QTTabDetachClass", "QTTabDetach", 0));
    } // retranslateUi

};

namespace Ui {
    class QTTabDetachClass: public Ui_QTTabDetachClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTTABDETACH_H
