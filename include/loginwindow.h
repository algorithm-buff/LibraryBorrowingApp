#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QPointer>

class ReaderMainWindow;
class AdminMainWindow;

namespace Ui {
class LoginWindow;
}

// LoginWindow orchestrates the login workflow and dispatches the user to role-aware main windows.
class LoginWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit LoginWindow(QWidget* parent = nullptr);
    ~LoginWindow() override;

private slots:
    void handleLogin();
    void handleReset();
    void handleLogout();
    void openRegistrationDialog();

private:
    void initializeUiState();
    void launchReaderPortal(const QString& userId, const QString& username);
    void launchAdminPortal(const QString& userId, const QString& username);

    Ui::LoginWindow* ui;
    QPointer<ReaderMainWindow> m_readerWindow;
    QPointer<AdminMainWindow> m_adminWindow;
};

#endif // LOGINWINDOW_H
