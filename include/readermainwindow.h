#ifndef READERMAINWINDOW_H
#define READERMAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "models.h"

class BookQueryWindow;
class BorrowRecordWindow;
class QPushButton;

namespace Ui {
class ReaderMainWindow;
}

// ReaderMainWindow is the landing page for readers, wiring menus to feature dialogs.
class ReaderMainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit ReaderMainWindow(QWidget* parent = nullptr);
    ~ReaderMainWindow() override;

    void setUserContext(const QString& userId, const QString& username);

signals:
    void logoutRequested();

private slots:
    void onActionQueryTriggered();
    void onActionRecordsTriggered();
    void onActionLogoutTriggered();
    void onBackButtonClicked();

private:
    void ensureBookQueryWidget();
    void configureBorrowedTable();
    void refreshBorrowedBooks();
    void attachReturnButton(int row, const BorrowRecord& record);

    Ui::ReaderMainWindow* ui;
    BookQueryWindow* m_bookQueryWindow = nullptr;
    BorrowRecordWindow* m_borrowRecordWindow = nullptr;
    QVector<BorrowRecord> m_activeBorrowRecords;
    QString m_userId;
    QString m_username;
};

#endif // READERMAINWINDOW_H
