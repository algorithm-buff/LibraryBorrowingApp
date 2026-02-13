#include "registerdialog.h"
#include "ui_registerdialog.h"

#include <QMessageBox>
#include <QRegularExpression>

#include "dbmanager.h"

namespace {
bool isPasswordStrongEnough(const QString& password) {
    if (password.size() < 6) {
        return false;
    }
    const bool hasLetter = password.contains(QRegularExpression(QStringLiteral("[A-Za-z]")));
    const bool hasDigit = password.contains(QRegularExpression(QStringLiteral("\\d")));
    return hasLetter && hasDigit;
}
}

RegisterDialog::RegisterDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog) {
    ui->setupUi(this);
    if (ui->verticalLayout) {
        ui->verticalLayout->setContentsMargins(24, 24, 24, 24);
    }

    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    ui->lineEditConfirmPassword->setEchoMode(QLineEdit::Password);

    connect(ui->pushButtonSubmit, &QPushButton::clicked, this, &RegisterDialog::handleSubmit);
    connect(ui->pushButtonClear, &QPushButton::clicked, this, &RegisterDialog::handleClear);
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &RegisterDialog::reject);
}

RegisterDialog::~RegisterDialog() {
    delete ui;
}

void RegisterDialog::handleSubmit() {
    QString errorMessage;
    if (!validateForm(&errorMessage)) {
        showValidationError(errorMessage);
        return;
    }

    const QString username = ui->lineEditUsername->text().trimmed();
    const QString password = ui->lineEditPassword->text();
    const QString phone = ui->lineEditPhone->text().trimmed();

    QString dbError;
    if (!DBManager::instance().registerUser(username, password, phone, &dbError)) {
        if (dbError.isEmpty()) {
            dbError = tr("注册失败，请稍后重试");
        }
        showValidationError(dbError);
        return;
    }

    QMessageBox::information(this, tr("注册成功"), tr("账号已创建，您可以使用新账号登录。"));
    emit registrationSucceeded(username);
    accept();
}

void RegisterDialog::handleClear() {
    ui->lineEditUsername->clear();
    ui->lineEditPassword->clear();
    ui->lineEditConfirmPassword->clear();
    ui->lineEditPhone->clear();
    ui->lineEditUsername->setFocus();
}

bool RegisterDialog::validateForm(QString* errorMessage) const {
    const QString username = ui->lineEditUsername->text().trimmed();
    const QString password = ui->lineEditPassword->text();
    const QString confirmPassword = ui->lineEditConfirmPassword->text();
    const QString phone = ui->lineEditPhone->text().trimmed();

    if (username.isEmpty()) {
        if (errorMessage) {
            *errorMessage = tr("请填写用户名");
        }
        return false;
    }

    if (!isPasswordStrongEnough(password)) {
        if (errorMessage) {
            *errorMessage = tr("密码需至少 6 位，且同时包含字母和数字");
        }
        return false;
    }

    if (password != confirmPassword) {
        if (errorMessage) {
            *errorMessage = tr("两次输入的密码不一致");
        }
        return false;
    }

    if (!phone.isEmpty()) {
        const QRegularExpression phoneRegex(QStringLiteral("^\\+?\\d{6,15}$"));
        if (!phoneRegex.match(phone).hasMatch()) {
            if (errorMessage) {
                *errorMessage = tr("请输入正确的联系方式（仅数字，支持前缀 +）");
            }
            return false;
        }
    }

    return true;
}

void RegisterDialog::showValidationError(const QString& message) {
    QMessageBox::warning(this, tr("信息不完整"), message);
}
