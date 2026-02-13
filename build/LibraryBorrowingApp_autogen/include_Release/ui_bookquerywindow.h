/********************************************************************************
** Form generated from reading UI file 'bookquerywindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOKQUERYWINDOW_H
#define UI_BOOKQUERYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BookQueryWindow
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayoutFilters;
    QLabel *labelBookName;
    QLineEdit *lineEditBookName;
    QLabel *labelAuthor;
    QLineEdit *lineEditAuthor;
    QHBoxLayout *layoutButtons;
    QPushButton *pushButtonSearch;
    QPushButton *pushButtonReset;
    QSpacerItem *filterSpacer;
    QTableWidget *tableWidgetBooks;
    QHBoxLayout *horizontalLayoutInfo;
    QLabel *infoLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonBorrow;

    void setupUi(QWidget *BookQueryWindow)
    {
        if (BookQueryWindow->objectName().isEmpty())
            BookQueryWindow->setObjectName("BookQueryWindow");
        BookQueryWindow->resize(800, 480);
        verticalLayout = new QVBoxLayout(BookQueryWindow);
        verticalLayout->setObjectName("verticalLayout");
        formLayoutFilters = new QFormLayout();
        formLayoutFilters->setObjectName("formLayoutFilters");
        formLayoutFilters->setHorizontalSpacing(16);
        formLayoutFilters->setVerticalSpacing(12);
        labelBookName = new QLabel(BookQueryWindow);
        labelBookName->setObjectName("labelBookName");

        formLayoutFilters->setWidget(0, QFormLayout::ItemRole::LabelRole, labelBookName);

        lineEditBookName = new QLineEdit(BookQueryWindow);
        lineEditBookName->setObjectName("lineEditBookName");
        lineEditBookName->setMinimumWidth(200);

        formLayoutFilters->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEditBookName);

        labelAuthor = new QLabel(BookQueryWindow);
        labelAuthor->setObjectName("labelAuthor");

        formLayoutFilters->setWidget(1, QFormLayout::ItemRole::LabelRole, labelAuthor);

        lineEditAuthor = new QLineEdit(BookQueryWindow);
        lineEditAuthor->setObjectName("lineEditAuthor");

        formLayoutFilters->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEditAuthor);

        layoutButtons = new QHBoxLayout();
        layoutButtons->setSpacing(12);
        layoutButtons->setObjectName("layoutButtons");
        pushButtonSearch = new QPushButton(BookQueryWindow);
        pushButtonSearch->setObjectName("pushButtonSearch");

        layoutButtons->addWidget(pushButtonSearch);

        pushButtonReset = new QPushButton(BookQueryWindow);
        pushButtonReset->setObjectName("pushButtonReset");

        layoutButtons->addWidget(pushButtonReset);

        filterSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutButtons->addItem(filterSpacer);


        formLayoutFilters->setLayout(2, QFormLayout::ItemRole::FieldRole, layoutButtons);


        verticalLayout->addLayout(formLayoutFilters);

        tableWidgetBooks = new QTableWidget(BookQueryWindow);
        if (tableWidgetBooks->columnCount() < 6)
            tableWidgetBooks->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetBooks->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetBooks->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetBooks->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetBooks->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetBooks->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetBooks->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidgetBooks->setObjectName("tableWidgetBooks");

        verticalLayout->addWidget(tableWidgetBooks);

        horizontalLayoutInfo = new QHBoxLayout();
        horizontalLayoutInfo->setObjectName("horizontalLayoutInfo");
        infoLabel = new QLabel(BookQueryWindow);
        infoLabel->setObjectName("infoLabel");

        horizontalLayoutInfo->addWidget(infoLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutInfo->addItem(horizontalSpacer);

        pushButtonBorrow = new QPushButton(BookQueryWindow);
        pushButtonBorrow->setObjectName("pushButtonBorrow");

        horizontalLayoutInfo->addWidget(pushButtonBorrow);


        verticalLayout->addLayout(horizontalLayoutInfo);


        retranslateUi(BookQueryWindow);

        QMetaObject::connectSlotsByName(BookQueryWindow);
    } // setupUi

    void retranslateUi(QWidget *BookQueryWindow)
    {
        BookQueryWindow->setWindowTitle(QCoreApplication::translate("BookQueryWindow", "\345\233\276\344\271\246\346\237\245\350\257\242", nullptr));
        labelBookName->setText(QCoreApplication::translate("BookQueryWindow", "\344\271\246\345\220\215\345\214\205\345\220\253\357\274\232", nullptr));
        labelAuthor->setText(QCoreApplication::translate("BookQueryWindow", "\344\275\234\350\200\205\345\214\205\345\220\253\357\274\232", nullptr));
        pushButtonSearch->setText(QCoreApplication::translate("BookQueryWindow", "\346\237\245\350\257\242", nullptr));
        pushButtonReset->setText(QCoreApplication::translate("BookQueryWindow", "\351\207\215\347\275\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetBooks->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("BookQueryWindow", "\344\271\246\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetBooks->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("BookQueryWindow", "\344\271\246\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetBooks->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("BookQueryWindow", "\344\275\234\350\200\205", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetBooks->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("BookQueryWindow", "\345\207\272\347\211\210\347\244\276", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetBooks->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("BookQueryWindow", "\345\272\223\345\255\230", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetBooks->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("BookQueryWindow", "\347\212\266\346\200\201", nullptr));
        infoLabel->setText(QCoreApplication::translate("BookQueryWindow", "\346\217\220\347\244\272\357\274\232\346\237\245\350\257\242\347\273\223\346\236\234\345\260\206\345\256\236\346\227\266\345\210\267\346\226\260\343\200\202", nullptr));
        pushButtonBorrow->setText(QCoreApplication::translate("BookQueryWindow", "\345\200\237\351\230\205\346\211\200\351\200\211\345\233\276\344\271\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BookQueryWindow: public Ui_BookQueryWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOKQUERYWINDOW_H
