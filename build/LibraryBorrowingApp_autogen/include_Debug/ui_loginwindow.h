/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QFormLayout *formLayout;
    QLabel *labelUsername;
    QLineEdit *lineEditUsername;
    QLabel *labelPassword;
    QLineEdit *lineEditPassword;
    QGroupBox *groupBoxRole;
    QHBoxLayout *horizontalLayoutRole;
    QRadioButton *radioButtonReader;
    QRadioButton *radioButtonAdmin;
    QHBoxLayout *horizontalLayoutButtons;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonLogin;
    QPushButton *pushButtonReset;
    QPushButton *pushButtonRegister;
    QSpacerItem *horizontalSpacer_2;
    QLabel *statusLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(480, 320);
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(16);
        verticalLayout->setObjectName("verticalLayout");
        labelTitle = new QLabel(centralwidget);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setAlignment(Qt::AlignCenter);
        labelTitle->setMargin(8);

        verticalLayout->addWidget(labelTitle);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setFormAlignment(Qt::AlignHCenter|Qt::AlignTop);
        labelUsername = new QLabel(centralwidget);
        labelUsername->setObjectName("labelUsername");
        labelUsername->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelUsername);

        lineEditUsername = new QLineEdit(centralwidget);
        lineEditUsername->setObjectName("lineEditUsername");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEditUsername);

        labelPassword = new QLabel(centralwidget);
        labelPassword->setObjectName("labelPassword");
        labelPassword->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelPassword);

        lineEditPassword = new QLineEdit(centralwidget);
        lineEditPassword->setObjectName("lineEditPassword");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEditPassword);


        verticalLayout->addLayout(formLayout);

        groupBoxRole = new QGroupBox(centralwidget);
        groupBoxRole->setObjectName("groupBoxRole");
        horizontalLayoutRole = new QHBoxLayout(groupBoxRole);
        horizontalLayoutRole->setObjectName("horizontalLayoutRole");
        radioButtonReader = new QRadioButton(groupBoxRole);
        radioButtonReader->setObjectName("radioButtonReader");

        horizontalLayoutRole->addWidget(radioButtonReader);

        radioButtonAdmin = new QRadioButton(groupBoxRole);
        radioButtonAdmin->setObjectName("radioButtonAdmin");

        horizontalLayoutRole->addWidget(radioButtonAdmin);


        verticalLayout->addWidget(groupBoxRole);

        horizontalLayoutButtons = new QHBoxLayout();
        horizontalLayoutButtons->setObjectName("horizontalLayoutButtons");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutButtons->addItem(horizontalSpacer);

        pushButtonLogin = new QPushButton(centralwidget);
        pushButtonLogin->setObjectName("pushButtonLogin");

        horizontalLayoutButtons->addWidget(pushButtonLogin);

        pushButtonReset = new QPushButton(centralwidget);
        pushButtonReset->setObjectName("pushButtonReset");

        horizontalLayoutButtons->addWidget(pushButtonReset);

        pushButtonRegister = new QPushButton(centralwidget);
        pushButtonRegister->setObjectName("pushButtonRegister");

        horizontalLayoutButtons->addWidget(pushButtonRegister);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutButtons->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayoutButtons);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setAlignment(Qt::AlignCenter);
        statusLabel->setWordWrap(true);

        verticalLayout->addWidget(statusLabel);

        LoginWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LoginWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 480, 22));
        LoginWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(LoginWindow);
        statusbar->setObjectName("statusbar");
        LoginWindow->setStatusBar(statusbar);

        retranslateUi(LoginWindow);

        pushButtonLogin->setDefault(true);


        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "\345\233\276\344\271\246\345\200\237\351\230\205\347\256\241\347\220\206\347\263\273\347\273\237 - \347\231\273\345\275\225", nullptr));
        labelTitle->setText(QCoreApplication::translate("LoginWindow", "\346\254\242\350\277\216\344\275\277\347\224\250\345\265\214\345\205\245\345\274\217\345\233\276\344\271\246\345\200\237\351\230\205\347\256\241\347\220\206\345\260\217\347\250\213\345\272\217", nullptr));
        labelUsername->setText(QCoreApplication::translate("LoginWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        labelPassword->setText(QCoreApplication::translate("LoginWindow", "\345\257\206\347\240\201\357\274\232", nullptr));
        groupBoxRole->setTitle(QCoreApplication::translate("LoginWindow", "\351\200\211\346\213\251\350\247\222\350\211\262", nullptr));
        radioButtonReader->setText(QCoreApplication::translate("LoginWindow", "\350\257\273\350\200\205", nullptr));
        radioButtonAdmin->setText(QCoreApplication::translate("LoginWindow", "\347\256\241\347\220\206\345\221\230", nullptr));
        pushButtonLogin->setText(QCoreApplication::translate("LoginWindow", "\347\231\273\345\275\225", nullptr));
        pushButtonReset->setText(QCoreApplication::translate("LoginWindow", "\351\207\215\347\275\256", nullptr));
        pushButtonRegister->setText(QCoreApplication::translate("LoginWindow", "\346\263\250\345\206\214\350\264\246\345\217\267", nullptr));
        statusLabel->setText(QCoreApplication::translate("LoginWindow", "\350\257\267\351\200\211\346\213\251\350\247\222\350\211\262\345\271\266\350\276\223\345\205\245\350\264\246\345\217\267\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
