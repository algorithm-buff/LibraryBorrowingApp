#ifndef BOOKQUERYWINDOW_H
#define BOOKQUERYWINDOW_H

#include <QWidget>
#include <QVector>

#include <optional>

#include "models.h"

namespace Ui {
class BookQueryWindow;
}

// BookQueryWindow renders the book search UI, handles filtering, and runs borrow workflows for readers.
class BookQueryWindow : public QWidget {
    Q_OBJECT
public:
    explicit BookQueryWindow(QWidget* parent = nullptr);
    ~BookQueryWindow() override;

    void setUserContext(const QString& userId, int role);
    void refreshBooks();
    std::optional<BookInfo> currentSelectedBook() const;

signals:
    void borrowSucceeded();
    void selectionStateChanged(bool hasSelection);

private slots:
    void onSearchClicked();
    void onResetClicked();
    void onBorrowClicked();
    void onSelectionChanged();

private:
    void populateTable(const QVector<BookInfo>& books);
    void showErrorDialog(const QString& message);
    void updateBorrowAvailability();
    bool hasValidSelection() const;
    QString formatStatus(int status) const;

    Ui::BookQueryWindow* ui;
    QVector<BookInfo> m_cachedBooks;
    QString m_userId;
    int m_role = 0; // 0: reader, 1: admin
};

#endif // BOOKQUERYWINDOW_H
