/********************************************************************************
** Form generated from reading UI file 'adminmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINMAINWINDOW_H
#define UI_ADMINMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminMainWindow
{
public:
    QAction *actionBookQuery;
    QAction *actionBorrowRecords;
    QAction *actionBookMaintain;
    QAction *actionLogout;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelPlaceholder;
    QMenuBar *menubar;
    QMenu *menuFunctions;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AdminMainWindow)
    {
        if (AdminMainWindow->objectName().isEmpty())
            AdminMainWindow->setObjectName("AdminMainWindow");
        AdminMainWindow->resize(1024, 640);
        actionBookQuery = new QAction(AdminMainWindow);
        actionBookQuery->setObjectName("actionBookQuery");
        actionBorrowRecords = new QAction(AdminMainWindow);
        actionBorrowRecords->setObjectName("actionBorrowRecords");
        actionBookMaintain = new QAction(AdminMainWindow);
        actionBookMaintain->setObjectName("actionBookMaintain");
        actionLogout = new QAction(AdminMainWindow);
        actionLogout->setObjectName("actionLogout");
        centralwidget = new QWidget(AdminMainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        labelPlaceholder = new QLabel(centralwidget);
        labelPlaceholder->setObjectName("labelPlaceholder");
        labelPlaceholder->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelPlaceholder);

        AdminMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AdminMainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1024, 22));
        menuFunctions = new QMenu(menubar);
        menuFunctions->setObjectName("menuFunctions");
        AdminMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(AdminMainWindow);
        statusbar->setObjectName("statusbar");
        AdminMainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFunctions->menuAction());
        menuFunctions->addAction(actionBookQuery);
        menuFunctions->addAction(actionBorrowRecords);
        menuFunctions->addAction(actionBookMaintain);
        menuFunctions->addAction(actionLogout);

        retranslateUi(AdminMainWindow);

        QMetaObject::connectSlotsByName(AdminMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AdminMainWindow)
    {
        AdminMainWindow->setWindowTitle(QCoreApplication::translate("AdminMainWindow", "\347\256\241\347\220\206\345\221\230\344\270\273\351\241\265", nullptr));
        actionBookQuery->setText(QCoreApplication::translate("AdminMainWindow", "\345\233\276\344\271\246\346\237\245\350\257\242", nullptr));
        actionBorrowRecords->setText(QCoreApplication::translate("AdminMainWindow", "\345\200\237\351\230\205\350\256\260\345\275\225\347\256\241\347\220\206", nullptr));
        actionBookMaintain->setText(QCoreApplication::translate("AdminMainWindow", "\345\233\276\344\271\246\347\273\264\346\212\244", nullptr));
        actionLogout->setText(QCoreApplication::translate("AdminMainWindow", "\351\200\200\345\207\272", nullptr));
        labelPlaceholder->setText(QCoreApplication::translate("AdminMainWindow", "\346\255\243\345\234\250\345\212\240\350\275\275\345\233\276\344\271\246\346\237\245\350\257\242\347\225\214\351\235\242...", nullptr));
        menuFunctions->setTitle(QCoreApplication::translate("AdminMainWindow", "\345\212\237\350\203\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminMainWindow: public Ui_AdminMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINMAINWINDOW_H
