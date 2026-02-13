#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <QMessageBox>

#include "adminmainwindow.h"
#include "dbmanager.h"
#include "registerdialog.h"
#include "readermainwindow.h"

LoginWindow::LoginWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow) {
    ui->setupUi(this);
    if (ui->verticalLayout) {
        ui->verticalLayout->setContentsMargins(24, 24, 24, 24);
    }
    initializeUiState();

    connect(ui->pushButtonLogin, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    connect(ui->pushButtonReset, &QPushButton::clicked, this, &LoginWindow::handleReset);
    connect(ui->pushButtonRegister, &QPushButton::clicked, this, &LoginWindow::openRegistrationDialog);
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::handleLogin() {
    const QString username = ui->lineEditUsername->text().trimmed();
    const QString password = ui->lineEditPassword->text();
    const int role = ui->radioButtonAdmin->isChecked() ? 1 : 0;

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, tr("输入不完整"), tr("请填写用户名和密码"));
        return;
    }

    QString userId;
    QString fullUsername;
    QString errorMessage;
    if (!DBManager::instance().validateLogin(username, password, role, &userId, &fullUsername, &errorMessage)) {
        QMessageBox::critical(this, tr("登录失败"), errorMessage);
        return;
    }

    if (role == 0) {
        launchReaderPortal(userId, fullUsername);
    } else {
        launchAdminPortal(userId, fullUsername);
    }
}

void LoginWindow::handleReset() {
    ui->lineEditUsername->clear();
    ui->lineEditPassword->clear();
    ui->radioButtonReader->setChecked(true);
    ui->lineEditUsername->setFocus();
    ui->statusLabel->setText(tr("请选择角色并输入账号信息"));
}

void LoginWindow::handleLogout() {
    if (m_readerWindow) {
        m_readerWindow->close();
        m_readerWindow->deleteLater();
        m_readerWindow = nullptr;
    }
    if (m_adminWindow) {
        m_adminWindow->close();
        m_adminWindow->deleteLater();
        m_adminWindow = nullptr;
    }

    show();
    raise();
    activateWindow();
    handleReset();
}

void LoginWindow::initializeUiState() {
    setWindowTitle(tr("图书借阅管理系统 - 登录"));
    ui->lineEditUsername->setPlaceholderText(tr("请输入用户名"));
    ui->lineEditPassword->setPlaceholderText(tr("请输入密码"));
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    ui->radioButtonReader->setChecked(true);
    ui->statusLabel->setText(tr("请选择角色并输入账号信息"));
}

void LoginWindow::openRegistrationDialog() {
    RegisterDialog dialog(this);
    connect(&dialog, &RegisterDialog::registrationSucceeded, this, [this](const QString& username) {
        ui->lineEditUsername->setText(username);
        ui->lineEditPassword->clear();
        ui->radioButtonReader->setChecked(true);
        ui->statusLabel->setText(tr("注册成功，请输入密码登录"));
        ui->lineEditPassword->setFocus();
    });
    dialog.exec();
}

void LoginWindow::launchReaderPortal(const QString& userId, const QString& username) {
    if (m_adminWindow) {
        m_adminWindow->close();
        m_adminWindow->deleteLater();
        m_adminWindow = nullptr;
    }

    if (!m_readerWindow) {
        m_readerWindow = new ReaderMainWindow();
        connect(m_readerWindow, &ReaderMainWindow::logoutRequested, this, &LoginWindow::handleLogout);
    }

    m_readerWindow->setUserContext(userId, username);
    m_readerWindow->show();
    m_readerWindow->raise();
    m_readerWindow->activateWindow();
    hide();
}

void LoginWindow::launchAdminPortal(const QString& userId, const QString& username) {
    if (m_readerWindow) {
        m_readerWindow->close();
        m_readerWindow->deleteLater();
        m_readerWindow = nullptr;
    }

    if (!m_adminWindow) {
        m_adminWindow = new AdminMainWindow();
        connect(m_adminWindow, &AdminMainWindow::logoutRequested, this, &LoginWindow::handleLogout);
    }

    m_adminWindow->setUserContext(userId, username);
    m_adminWindow->show();
    m_adminWindow->raise();
    m_adminWindow->activateWindow();
    hide();
}
