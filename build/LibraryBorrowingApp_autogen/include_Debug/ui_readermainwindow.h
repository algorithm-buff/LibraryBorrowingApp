/********************************************************************************
** Form generated from reading UI file 'readermainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_READERMAINWINDOW_H
#define UI_READERMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReaderMainWindow
{
public:
    QAction *actionBookQuery;
    QAction *actionBorrowRecords;
    QAction *actionLogout;
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QWidget *headerWidget;
    QHBoxLayout *headerLayout;
    QPushButton *pushButtonBack;
    QLabel *labelWelcome;
    QSpacerItem *headerSpacer;
    QFrame *contentFrame;
    QVBoxLayout *contentLayout;
    QWidget *queryContainer;
    QVBoxLayout *queryContainerLayout;
    QGroupBox *groupBoxBorrowed;
    QVBoxLayout *borrowedLayout;
    QLabel *labelBorrowTip;
    QTableWidget *tableWidgetBorrowed;
    QMenuBar *menubar;
    QMenu *menuFunctions;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ReaderMainWindow)
    {
        if (ReaderMainWindow->objectName().isEmpty())
            ReaderMainWindow->setObjectName("ReaderMainWindow");
        ReaderMainWindow->resize(960, 600);
        actionBookQuery = new QAction(ReaderMainWindow);
        actionBookQuery->setObjectName("actionBookQuery");
        actionBorrowRecords = new QAction(ReaderMainWindow);
        actionBorrowRecords->setObjectName("actionBorrowRecords");
        actionLogout = new QAction(ReaderMainWindow);
        actionLogout->setObjectName("actionLogout");
        centralwidget = new QWidget(ReaderMainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setSpacing(18);
        mainLayout->setObjectName("mainLayout");
        headerWidget = new QWidget(centralwidget);
        headerWidget->setObjectName("headerWidget");
        headerLayout = new QHBoxLayout(headerWidget);
        headerLayout->setSpacing(12);
        headerLayout->setObjectName("headerLayout");
        headerLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonBack = new QPushButton(headerWidget);
        pushButtonBack->setObjectName("pushButtonBack");
        pushButtonBack->setMinimumSize(QSize(90, 36));

        headerLayout->addWidget(pushButtonBack);

        labelWelcome = new QLabel(headerWidget);
        labelWelcome->setObjectName("labelWelcome");
        labelWelcome->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);

        headerLayout->addWidget(labelWelcome);

        headerSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(headerSpacer);


        mainLayout->addWidget(headerWidget);

        contentFrame = new QFrame(centralwidget);
        contentFrame->setObjectName("contentFrame");
        contentFrame->setFrameShape(QFrame::NoFrame);
        contentLayout = new QVBoxLayout(contentFrame);
        contentLayout->setSpacing(18);
        contentLayout->setObjectName("contentLayout");
        queryContainer = new QWidget(contentFrame);
        queryContainer->setObjectName("queryContainer");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(queryContainer->sizePolicy().hasHeightForWidth());
        queryContainer->setSizePolicy(sizePolicy);
        queryContainerLayout = new QVBoxLayout(queryContainer);
        queryContainerLayout->setSpacing(0);
        queryContainerLayout->setObjectName("queryContainerLayout");
        queryContainerLayout->setContentsMargins(0, 0, 0, 0);

        contentLayout->addWidget(queryContainer);

        groupBoxBorrowed = new QGroupBox(contentFrame);
        groupBoxBorrowed->setObjectName("groupBoxBorrowed");
        borrowedLayout = new QVBoxLayout(groupBoxBorrowed);
        borrowedLayout->setSpacing(12);
        borrowedLayout->setObjectName("borrowedLayout");
        labelBorrowTip = new QLabel(groupBoxBorrowed);
        labelBorrowTip->setObjectName("labelBorrowTip");

        borrowedLayout->addWidget(labelBorrowTip);

        tableWidgetBorrowed = new QTableWidget(groupBoxBorrowed);
        if (tableWidgetBorrowed->columnCount() < 5)
            tableWidgetBorrowed->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetBorrowed->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetBorrowed->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetBorrowed->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetBorrowed->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetBorrowed->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetBorrowed->setObjectName("tableWidgetBorrowed");
        tableWidgetBorrowed->setAlternatingRowColors(true);

        borrowedLayout->addWidget(tableWidgetBorrowed);


        contentLayout->addWidget(groupBoxBorrowed);


        mainLayout->addWidget(contentFrame);

        ReaderMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ReaderMainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 960, 22));
        menuFunctions = new QMenu(menubar);
        menuFunctions->setObjectName("menuFunctions");
        ReaderMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ReaderMainWindow);
        statusbar->setObjectName("statusbar");
        ReaderMainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFunctions->menuAction());
        menuFunctions->addAction(actionBookQuery);
        menuFunctions->addAction(actionBorrowRecords);
        menuFunctions->addAction(actionLogout);

        retranslateUi(ReaderMainWindow);

        QMetaObject::connectSlotsByName(ReaderMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ReaderMainWindow)
    {
        ReaderMainWindow->setWindowTitle(QCoreApplication::translate("ReaderMainWindow", "\350\257\273\350\200\205\344\270\273\351\241\265", nullptr));
        actionBookQuery->setText(QCoreApplication::translate("ReaderMainWindow", "\345\233\276\344\271\246\346\237\245\350\257\242", nullptr));
        actionBorrowRecords->setText(QCoreApplication::translate("ReaderMainWindow", "\346\210\221\347\232\204\345\200\237\351\230\205\350\256\260\345\275\225", nullptr));
        actionLogout->setText(QCoreApplication::translate("ReaderMainWindow", "\351\200\200\345\207\272", nullptr));
        pushButtonBack->setText(QCoreApplication::translate("ReaderMainWindow", "\350\277\224\345\233\236", nullptr));
        labelWelcome->setText(QCoreApplication::translate("ReaderMainWindow", "\346\254\242\350\277\216\344\275\277\347\224\250\345\233\276\344\271\246\345\200\237\351\230\205\347\263\273\347\273\237", nullptr));
        groupBoxBorrowed->setTitle(QCoreApplication::translate("ReaderMainWindow", "\346\210\221\347\232\204\345\200\237\351\230\205\344\271\246\347\261\215", nullptr));
        labelBorrowTip->setText(QCoreApplication::translate("ReaderMainWindow", "\344\270\213\346\226\271\345\210\227\345\207\272\345\275\223\345\211\215\345\260\232\346\234\252\345\275\222\350\277\230\347\232\204\344\271\246\347\261\215\357\274\214\345\217\257\345\234\250\346\255\244\347\233\264\346\216\245\345\275\222\350\277\230\343\200\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetBorrowed->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ReaderMainWindow", "\344\271\246\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetBorrowed->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ReaderMainWindow", "\344\271\246\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetBorrowed->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ReaderMainWindow", "\344\275\234\350\200\205", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetBorrowed->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ReaderMainWindow", "\345\200\237\351\230\205\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetBorrowed->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ReaderMainWindow", "\346\223\215\344\275\234", nullptr));
        menuFunctions->setTitle(QCoreApplication::translate("ReaderMainWindow", "\345\212\237\350\203\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReaderMainWindow: public Ui_ReaderMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_READERMAINWINDOW_H
