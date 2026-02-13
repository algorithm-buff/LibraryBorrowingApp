#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "models.h"

class BookQueryWindow;
class BorrowRecordWindow;
class BookManageWindow;
class BookEditorDialog;
class QPushButton;
class QWidget;

namespace Ui {
class AdminMainWindow;
}

// AdminMainWindow exposes all management features required by administrators.
class AdminMainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit AdminMainWindow(QWidget* parent = nullptr);
    ~AdminMainWindow() override;

    void setUserContext(const QString& userId, const QString& username);

signals:
    void logoutRequested();

private slots:
    void onActionQueryTriggered();
    void onActionRecordsTriggered();
    void onActionMaintainTriggered();
    void onActionLogoutTriggered();
    void onAddBookRequested();
    void onEditBookRequested();
    void onDeleteBookRequested();
    void onSelectionStateChanged(bool hasSelection);

private:
    void ensureCentralQueryWidget();
    void buildAdminCentral();
    void refreshBookList();
    bool ensureBookSelection(BookInfo* book, QString* errorMessage = nullptr) const;
    void updateActionButtons(bool hasSelection);

    Ui::AdminMainWindow* ui;
    BookQueryWindow* m_bookQueryWindow = nullptr;
    BorrowRecordWindow* m_borrowRecordWindow = nullptr;
    BookManageWindow* m_bookManageWindow = nullptr;
    QWidget* m_centralContainer = nullptr;
    QPushButton* m_buttonAdd = nullptr;
    QPushButton* m_buttonEdit = nullptr;
    QPushButton* m_buttonDelete = nullptr;
    QString m_userId;
    QString m_username;
};

#endif // ADMINMAINWINDOW_H
