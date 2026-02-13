#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

// RegisterDialog collects reader credentials, validates inputs, and forwards them for persistence.
class RegisterDialog : public QDialog {
    Q_OBJECT
public:
    explicit RegisterDialog(QWidget* parent = nullptr);
    ~RegisterDialog() override;

signals:
    void registrationSucceeded(const QString& username);

private slots:
    void handleSubmit();
    void handleClear();

private:
    bool validateForm(QString* errorMessage) const;
    void showValidationError(const QString& message);

    Ui::RegisterDialog* ui;
};

#endif // REGISTERDIALOG_H
