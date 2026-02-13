/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QFormLayout *formLayout;
    QLabel *labelUsername;
    QLineEdit *lineEditUsername;
    QLabel *labelPassword;
    QLineEdit *lineEditPassword;
    QLabel *labelConfirm;
    QLineEdit *lineEditConfirmPassword;
    QLabel *labelPhone;
    QLineEdit *lineEditPhone;
    QLabel *labelHint;
    QHBoxLayout *buttonLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonSubmit;
    QPushButton *pushButtonClear;
    QPushButton *pushButtonCancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName("RegisterDialog");
        RegisterDialog->resize(420, 360);
        verticalLayout = new QVBoxLayout(RegisterDialog);
        verticalLayout->setSpacing(16);
        verticalLayout->setObjectName("verticalLayout");
        labelTitle = new QLabel(RegisterDialog);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        verticalLayout->addWidget(labelTitle);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setHorizontalSpacing(14);
        formLayout->setVerticalSpacing(12);
        labelUsername = new QLabel(RegisterDialog);
        labelUsername->setObjectName("labelUsername");
        labelUsername->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelUsername);

        lineEditUsername = new QLineEdit(RegisterDialog);
        lineEditUsername->setObjectName("lineEditUsername");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEditUsername);

        labelPassword = new QLabel(RegisterDialog);
        labelPassword->setObjectName("labelPassword");
        labelPassword->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelPassword);

        lineEditPassword = new QLineEdit(RegisterDialog);
        lineEditPassword->setObjectName("lineEditPassword");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEditPassword);

        labelConfirm = new QLabel(RegisterDialog);
        labelConfirm->setObjectName("labelConfirm");
        labelConfirm->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, labelConfirm);

        lineEditConfirmPassword = new QLineEdit(RegisterDialog);
        lineEditConfirmPassword->setObjectName("lineEditConfirmPassword");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, lineEditConfirmPassword);

        labelPhone = new QLabel(RegisterDialog);
        labelPhone->setObjectName("labelPhone");
        labelPhone->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, labelPhone);

        lineEditPhone = new QLineEdit(RegisterDialog);
        lineEditPhone->setObjectName("lineEditPhone");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, lineEditPhone);


        verticalLayout->addLayout(formLayout);

        labelHint = new QLabel(RegisterDialog);
        labelHint->setObjectName("labelHint");
        labelHint->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        labelHint->setWordWrap(true);

        verticalLayout->addWidget(labelHint);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setSpacing(12);
        buttonLayout->setObjectName("buttonLayout");
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonLayout->addItem(horizontalSpacer);

        pushButtonSubmit = new QPushButton(RegisterDialog);
        pushButtonSubmit->setObjectName("pushButtonSubmit");

        buttonLayout->addWidget(pushButtonSubmit);

        pushButtonClear = new QPushButton(RegisterDialog);
        pushButtonClear->setObjectName("pushButtonClear");

        buttonLayout->addWidget(pushButtonClear);

        pushButtonCancel = new QPushButton(RegisterDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");

        buttonLayout->addWidget(pushButtonCancel);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(RegisterDialog);

        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "\350\257\273\350\200\205\346\263\250\345\206\214", nullptr));
        labelTitle->setText(QCoreApplication::translate("RegisterDialog", "\346\254\242\350\277\216\346\263\250\345\206\214\350\257\273\350\200\205\350\264\246\345\217\267", nullptr));
        labelUsername->setText(QCoreApplication::translate("RegisterDialog", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        labelPassword->setText(QCoreApplication::translate("RegisterDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        labelConfirm->setText(QCoreApplication::translate("RegisterDialog", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", nullptr));
        labelPhone->setText(QCoreApplication::translate("RegisterDialog", "\350\201\224\347\263\273\346\226\271\345\274\217\357\274\232", nullptr));
        labelHint->setText(QCoreApplication::translate("RegisterDialog", "\345\257\206\347\240\201\351\234\200\345\214\205\345\220\253\350\207\263\345\260\221 6 \344\275\215\345\255\227\347\254\246\357\274\214\345\273\272\350\256\256\346\267\267\345\220\210\345\255\227\346\257\215\344\270\216\346\225\260\345\255\227\343\200\202", nullptr));
        pushButtonSubmit->setText(QCoreApplication::translate("RegisterDialog", "\346\263\250\345\206\214", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("RegisterDialog", "\346\270\205\347\251\272", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("RegisterDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
