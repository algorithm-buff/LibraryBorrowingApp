/********************************************************************************
** Form generated from reading UI file 'bookmanagewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOKMANAGEWINDOW_H
#define UI_BOOKMANAGEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BookManageWindow
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidgetBooks;
    QGridLayout *gridLayoutForm;
    QLabel *labelBookId;
    QLineEdit *lineEditBookId;
    QLabel *labelBookName;
    QLineEdit *lineEditBookName;
    QLabel *labelAuthor;
    QLineEdit *lineEditAuthor;
    QLabel *labelPublisher;
    QLineEdit *lineEditPublisher;
    QLabel *labelPublishDate;
    QDateEdit *dateEditPublishDate;
    QLabel *labelStock;
    QSpinBox *spinBoxStock;
    QLabel *labelStatus;
    QComboBox *comboBoxStatus;
    QLabel *labelRemark;
    QTextEdit *textEditRemark;
    QHBoxLayout *horizontalLayoutButtons;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonResetForm;

    void setupUi(QDialog *BookManageWindow)
    {
        if (BookManageWindow->objectName().isEmpty())
            BookManageWindow->setObjectName("BookManageWindow");
        BookManageWindow->resize(900, 600);
        verticalLayout = new QVBoxLayout(BookManageWindow);
        verticalLayout->setObjectName("verticalLayout");
        tableWidgetBooks = new QTableWidget(BookManageWindow);
        if (tableWidgetBooks->columnCount() < 8)
            tableWidgetBooks->setColumnCount(8);
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
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetBooks->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetBooks->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tableWidgetBooks->setObjectName("tableWidgetBooks");

        verticalLayout->addWidget(tableWidgetBooks);

        gridLayoutForm = new QGridLayout();
        gridLayoutForm->setObjectName("gridLayoutForm");
        labelBookId = new QLabel(BookManageWindow);
        labelBookId->setObjectName("labelBookId");

        gridLayoutForm->addWidget(labelBookId, 0, 0, 1, 1);

        lineEditBookId = new QLineEdit(BookManageWindow);
        lineEditBookId->setObjectName("lineEditBookId");

        gridLayoutForm->addWidget(lineEditBookId, 0, 1, 1, 1);

        labelBookName = new QLabel(BookManageWindow);
        labelBookName->setObjectName("labelBookName");

        gridLayoutForm->addWidget(labelBookName, 0, 2, 1, 1);

        lineEditBookName = new QLineEdit(BookManageWindow);
        lineEditBookName->setObjectName("lineEditBookName");

        gridLayoutForm->addWidget(lineEditBookName, 0, 3, 1, 1);

        labelAuthor = new QLabel(BookManageWindow);
        labelAuthor->setObjectName("labelAuthor");

        gridLayoutForm->addWidget(labelAuthor, 1, 0, 1, 1);

        lineEditAuthor = new QLineEdit(BookManageWindow);
        lineEditAuthor->setObjectName("lineEditAuthor");

        gridLayoutForm->addWidget(lineEditAuthor, 1, 1, 1, 1);

        labelPublisher = new QLabel(BookManageWindow);
        labelPublisher->setObjectName("labelPublisher");

        gridLayoutForm->addWidget(labelPublisher, 1, 2, 1, 1);

        lineEditPublisher = new QLineEdit(BookManageWindow);
        lineEditPublisher->setObjectName("lineEditPublisher");

        gridLayoutForm->addWidget(lineEditPublisher, 1, 3, 1, 1);

        labelPublishDate = new QLabel(BookManageWindow);
        labelPublishDate->setObjectName("labelPublishDate");

        gridLayoutForm->addWidget(labelPublishDate, 2, 0, 1, 1);

        dateEditPublishDate = new QDateEdit(BookManageWindow);
        dateEditPublishDate->setObjectName("dateEditPublishDate");
        dateEditPublishDate->setCalendarPopup(true);

        gridLayoutForm->addWidget(dateEditPublishDate, 2, 1, 1, 1);

        labelStock = new QLabel(BookManageWindow);
        labelStock->setObjectName("labelStock");

        gridLayoutForm->addWidget(labelStock, 2, 2, 1, 1);

        spinBoxStock = new QSpinBox(BookManageWindow);
        spinBoxStock->setObjectName("spinBoxStock");
        spinBoxStock->setMinimum(0);
        spinBoxStock->setMaximum(9999);

        gridLayoutForm->addWidget(spinBoxStock, 2, 3, 1, 1);

        labelStatus = new QLabel(BookManageWindow);
        labelStatus->setObjectName("labelStatus");

        gridLayoutForm->addWidget(labelStatus, 3, 0, 1, 1);

        comboBoxStatus = new QComboBox(BookManageWindow);
        comboBoxStatus->setObjectName("comboBoxStatus");

        gridLayoutForm->addWidget(comboBoxStatus, 3, 1, 1, 1);

        labelRemark = new QLabel(BookManageWindow);
        labelRemark->setObjectName("labelRemark");

        gridLayoutForm->addWidget(labelRemark, 3, 2, 1, 1);

        textEditRemark = new QTextEdit(BookManageWindow);
        textEditRemark->setObjectName("textEditRemark");
        textEditRemark->setMaximumHeight(80);

        gridLayoutForm->addWidget(textEditRemark, 3, 3, 1, 1);


        verticalLayout->addLayout(gridLayoutForm);

        horizontalLayoutButtons = new QHBoxLayout();
        horizontalLayoutButtons->setObjectName("horizontalLayoutButtons");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutButtons->addItem(horizontalSpacer);

        pushButtonAdd = new QPushButton(BookManageWindow);
        pushButtonAdd->setObjectName("pushButtonAdd");

        horizontalLayoutButtons->addWidget(pushButtonAdd);

        pushButtonUpdate = new QPushButton(BookManageWindow);
        pushButtonUpdate->setObjectName("pushButtonUpdate");

        horizontalLayoutButtons->addWidget(pushButtonUpdate);

        pushButtonDelete = new QPushButton(BookManageWindow);
        pushButtonDelete->setObjectName("pushButtonDelete");

        horizontalLayoutButtons->addWidget(pushButtonDelete);

        pushButtonResetForm = new QPushButton(BookManageWindow);
        pushButtonResetForm->setObjectName("pushButtonResetForm");

        horizontalLayoutButtons->addWidget(pushButtonResetForm);


        verticalLayout->addLayout(horizontalLayoutButtons);


        retranslateUi(BookManageWindow);

        QMetaObject::connectSlotsByName(BookManageWindow);
    } // setupUi

    void retranslateUi(QDialog *BookManageWindow)
    {
        BookManageWindow->setWindowTitle(QCoreApplication::translate("BookManageWindow", "\345\233\276\344\271\246\347\273\264\346\212\244", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetBooks->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("BookManageWindow", "\344\271\246\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetBooks->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("BookManageWindow", "\344\271\246\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetBooks->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("BookManageWindow", "\344\275\234\350\200\205", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetBooks->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("BookManageWindow", "\345\207\272\347\211\210\347\244\276", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetBooks->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("BookManageWindow", "\345\207\272\347\211\210\346\227\245\346\234\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetBooks->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("BookManageWindow", "\345\272\223\345\255\230", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetBooks->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("BookManageWindow", "\347\212\266\346\200\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetBooks->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("BookManageWindow", "\345\244\207\346\263\250", nullptr));
        labelBookId->setText(QCoreApplication::translate("BookManageWindow", "\344\271\246\345\217\267\357\274\232", nullptr));
        labelBookName->setText(QCoreApplication::translate("BookManageWindow", "\344\271\246\345\220\215\357\274\232", nullptr));
        labelAuthor->setText(QCoreApplication::translate("BookManageWindow", "\344\275\234\350\200\205\357\274\232", nullptr));
        labelPublisher->setText(QCoreApplication::translate("BookManageWindow", "\345\207\272\347\211\210\347\244\276\357\274\232", nullptr));
        labelPublishDate->setText(QCoreApplication::translate("BookManageWindow", "\345\207\272\347\211\210\346\227\245\346\234\237\357\274\232", nullptr));
        labelStock->setText(QCoreApplication::translate("BookManageWindow", "\345\272\223\345\255\230\357\274\232", nullptr));
        labelStatus->setText(QCoreApplication::translate("BookManageWindow", "\347\212\266\346\200\201\357\274\232", nullptr));
        labelRemark->setText(QCoreApplication::translate("BookManageWindow", "\345\244\207\346\263\250\357\274\232", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("BookManageWindow", "\346\226\260\345\242\236", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("BookManageWindow", "\344\277\256\346\224\271", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("BookManageWindow", "\345\210\240\351\231\244", nullptr));
        pushButtonResetForm->setText(QCoreApplication::translate("BookManageWindow", "\346\270\205\347\251\272\350\241\250\345\215\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BookManageWindow: public Ui_BookManageWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOKMANAGEWINDOW_H
