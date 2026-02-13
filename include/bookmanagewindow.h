#ifndef BOOKMANAGEWINDOW_H
#define BOOKMANAGEWINDOW_H

#include <QDialog>
#include <QVector>

#include "models.h"

namespace Ui {
class BookManageWindow;
}

// BookManageWindow enables administrators to add, edit, and delete book records with constraint checks.
class BookManageWindow : public QDialog {
    Q_OBJECT
public:
    explicit BookManageWindow(QWidget* parent = nullptr);
    ~BookManageWindow() override;

    void reload();

signals:
    void booksChanged();

private slots:
    void onAddClicked();
    void onUpdateClicked();
    void onDeleteClicked();
    void onRowSelected();
    void onResetForm();

private:
    void populateTable(const QVector<BookInfo>& books);
    BookInfo collectFormData() const;
    void fillFormFromRow(int rowIndex);
    void showErrorDialog(const QString& message);
    void resetFormFields();

    Ui::BookManageWindow* ui;
    QVector<BookInfo> m_cachedBooks;
};

#endif // BOOKMANAGEWINDOW_H
