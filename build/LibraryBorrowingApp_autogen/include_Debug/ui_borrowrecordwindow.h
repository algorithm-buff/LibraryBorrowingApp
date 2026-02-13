/********************************************************************************
** Form generated from reading UI file 'borrowrecordwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BORROWRECORDWINDOW_H
#define UI_BORROWRECORDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BorrowRecordWindow
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidgetRecords;
    QHBoxLayout *horizontalLayout;
    QLabel *labelOverdue;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonRefresh;
    QPushButton *pushButtonReturn;

    void setupUi(QDialog *BorrowRecordWindow)
    {
        if (BorrowRecordWindow->objectName().isEmpty())
            BorrowRecordWindow->setObjectName("BorrowRecordWindow");
        BorrowRecordWindow->resize(820, 520);
        verticalLayout = new QVBoxLayout(BorrowRecordWindow);
        verticalLayout->setObjectName("verticalLayout");
        tableWidgetRecords = new QTableWidget(BorrowRecordWindow);
        if (tableWidgetRecords->columnCount() < 8)
            tableWidgetRecords->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetRecords->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetRecords->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetRecords->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetRecords->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetRecords->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetRecords->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetRecords->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetRecords->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tableWidgetRecords->setObjectName("tableWidgetRecords");

        verticalLayout->addWidget(tableWidgetRecords);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        labelOverdue = new QLabel(BorrowRecordWindow);
        labelOverdue->setObjectName("labelOverdue");

        horizontalLayout->addWidget(labelOverdue);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonRefresh = new QPushButton(BorrowRecordWindow);
        pushButtonRefresh->setObjectName("pushButtonRefresh");

        horizontalLayout->addWidget(pushButtonRefresh);

        pushButtonReturn = new QPushButton(BorrowRecordWindow);
        pushButtonReturn->setObjectName("pushButtonReturn");

        horizontalLayout->addWidget(pushButtonReturn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(BorrowRecordWindow);

        QMetaObject::connectSlotsByName(BorrowRecordWindow);
    } // setupUi

    void retranslateUi(QDialog *BorrowRecordWindow)
    {
        BorrowRecordWindow->setWindowTitle(QCoreApplication::translate("BorrowRecordWindow", "\345\200\237\351\230\205\350\256\260\345\275\225", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetRecords->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("BorrowRecordWindow", "\350\256\260\345\275\225ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetRecords->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("BorrowRecordWindow", "\344\271\246\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetRecords->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("BorrowRecordWindow", "\344\271\246\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetRecords->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("BorrowRecordWindow", "\345\200\237\351\230\205\346\227\245\346\234\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetRecords->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("BorrowRecordWindow", "\345\272\224\350\277\230\346\227\245\346\234\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetRecords->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("BorrowRecordWindow", "\345\275\222\350\277\230\347\212\266\346\200\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetRecords->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("BorrowRecordWindow", "\351\200\276\346\234\237\345\244\251\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetRecords->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("BorrowRecordWindow", "\345\200\237\351\230\205\344\272\272", nullptr));
        labelOverdue->setText(QCoreApplication::translate("BorrowRecordWindow", "\351\200\276\346\234\237\350\256\260\345\275\225\357\274\2320 \346\235\241", nullptr));
        pushButtonRefresh->setText(QCoreApplication::translate("BorrowRecordWindow", "\345\210\267\346\226\260", nullptr));
        pushButtonReturn->setText(QCoreApplication::translate("BorrowRecordWindow", "\345\275\222\350\277\230\346\211\200\351\200\211\350\256\260\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BorrowRecordWindow: public Ui_BorrowRecordWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BORROWRECORDWINDOW_H
