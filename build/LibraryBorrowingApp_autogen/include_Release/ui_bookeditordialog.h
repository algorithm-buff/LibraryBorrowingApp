/********************************************************************************
** Form generated from reading UI file 'bookeditordialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOKEDITORDIALOG_H
#define UI_BOOKEDITORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BookEditorDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
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
    QPlainTextEdit *plainTextEditRemark;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacer;
    QPushButton *pushButtonSubmit;
    QPushButton *pushButtonCancel;
    QSpacerItem *buttonSpacerRight;

    void setupUi(QDialog *BookEditorDialog)
    {
        if (BookEditorDialog->objectName().isEmpty())
            BookEditorDialog->setObjectName("BookEditorDialog");
        BookEditorDialog->resize(520, 420);
        verticalLayout = new QVBoxLayout(BookEditorDialog);
        verticalLayout->setSpacing(16);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setHorizontalSpacing(14);
        formLayout->setVerticalSpacing(12);
        labelBookId = new QLabel(BookEditorDialog);
        labelBookId->setObjectName("labelBookId");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelBookId);

        lineEditBookId = new QLineEdit(BookEditorDialog);
        lineEditBookId->setObjectName("lineEditBookId");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEditBookId);

        labelBookName = new QLabel(BookEditorDialog);
        labelBookName->setObjectName("labelBookName");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelBookName);

        lineEditBookName = new QLineEdit(BookEditorDialog);
        lineEditBookName->setObjectName("lineEditBookName");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEditBookName);

        labelAuthor = new QLabel(BookEditorDialog);
        labelAuthor->setObjectName("labelAuthor");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, labelAuthor);

        lineEditAuthor = new QLineEdit(BookEditorDialog);
        lineEditAuthor->setObjectName("lineEditAuthor");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, lineEditAuthor);

        labelPublisher = new QLabel(BookEditorDialog);
        labelPublisher->setObjectName("labelPublisher");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, labelPublisher);

        lineEditPublisher = new QLineEdit(BookEditorDialog);
        lineEditPublisher->setObjectName("lineEditPublisher");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, lineEditPublisher);

        labelPublishDate = new QLabel(BookEditorDialog);
        labelPublishDate->setObjectName("labelPublishDate");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, labelPublishDate);

        dateEditPublishDate = new QDateEdit(BookEditorDialog);
        dateEditPublishDate->setObjectName("dateEditPublishDate");
        dateEditPublishDate->setCalendarPopup(true);

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, dateEditPublishDate);

        labelStock = new QLabel(BookEditorDialog);
        labelStock->setObjectName("labelStock");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, labelStock);

        spinBoxStock = new QSpinBox(BookEditorDialog);
        spinBoxStock->setObjectName("spinBoxStock");
        spinBoxStock->setMinimum(0);
        spinBoxStock->setMaximum(9999);

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, spinBoxStock);

        labelStatus = new QLabel(BookEditorDialog);
        labelStatus->setObjectName("labelStatus");

        formLayout->setWidget(6, QFormLayout::ItemRole::LabelRole, labelStatus);

        comboBoxStatus = new QComboBox(BookEditorDialog);
        comboBoxStatus->setObjectName("comboBoxStatus");

        formLayout->setWidget(6, QFormLayout::ItemRole::FieldRole, comboBoxStatus);

        labelRemark = new QLabel(BookEditorDialog);
        labelRemark->setObjectName("labelRemark");

        formLayout->setWidget(7, QFormLayout::ItemRole::LabelRole, labelRemark);

        plainTextEditRemark = new QPlainTextEdit(BookEditorDialog);
        plainTextEditRemark->setObjectName("plainTextEditRemark");
        plainTextEditRemark->setMaximumHeight(100);

        formLayout->setWidget(7, QFormLayout::ItemRole::FieldRole, plainTextEditRemark);


        verticalLayout->addLayout(formLayout);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setSpacing(12);
        buttonLayout->setObjectName("buttonLayout");
        buttonSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonLayout->addItem(buttonSpacer);

        pushButtonSubmit = new QPushButton(BookEditorDialog);
        pushButtonSubmit->setObjectName("pushButtonSubmit");

        buttonLayout->addWidget(pushButtonSubmit);

        pushButtonCancel = new QPushButton(BookEditorDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");

        buttonLayout->addWidget(pushButtonCancel);

        buttonSpacerRight = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonLayout->addItem(buttonSpacerRight);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(BookEditorDialog);

        QMetaObject::connectSlotsByName(BookEditorDialog);
    } // setupUi

    void retranslateUi(QDialog *BookEditorDialog)
    {
        BookEditorDialog->setWindowTitle(QCoreApplication::translate("BookEditorDialog", "\344\271\246\347\261\215\344\277\241\346\201\257", nullptr));
        labelBookId->setText(QCoreApplication::translate("BookEditorDialog", "\344\271\246\345\217\267\357\274\232", nullptr));
        labelBookName->setText(QCoreApplication::translate("BookEditorDialog", "\344\271\246\345\220\215\357\274\232", nullptr));
        labelAuthor->setText(QCoreApplication::translate("BookEditorDialog", "\344\275\234\350\200\205\357\274\232", nullptr));
        labelPublisher->setText(QCoreApplication::translate("BookEditorDialog", "\345\207\272\347\211\210\347\244\276\357\274\232", nullptr));
        labelPublishDate->setText(QCoreApplication::translate("BookEditorDialog", "\345\207\272\347\211\210\346\227\245\346\234\237\357\274\232", nullptr));
        labelStock->setText(QCoreApplication::translate("BookEditorDialog", "\345\272\223\345\255\230\346\225\260\351\207\217\357\274\232", nullptr));
        labelStatus->setText(QCoreApplication::translate("BookEditorDialog", "\347\212\266\346\200\201\357\274\232", nullptr));
        labelRemark->setText(QCoreApplication::translate("BookEditorDialog", "\345\244\207\346\263\250\357\274\232", nullptr));
        pushButtonSubmit->setText(QCoreApplication::translate("BookEditorDialog", "\347\241\256\345\256\232", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("BookEditorDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BookEditorDialog: public Ui_BookEditorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOKEDITORDIALOG_H
