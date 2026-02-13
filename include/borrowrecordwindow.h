#ifndef BORROWRECORDWINDOW_H
#define BORROWRECORDWINDOW_H

#include <QDialog>
#include <QVector>

#include "models.h"

namespace Ui {
class BorrowRecordWindow;
}

// BorrowRecordWindow provides the record inspection and return workflow for both readers and admins.
class BorrowRecordWindow : public QDialog {
    Q_OBJECT
public:
    explicit BorrowRecordWindow(QWidget* parent = nullptr);
    ~BorrowRecordWindow() override;

    void setContext(const QString& userId, int role, bool adminMode);
    void reload();

signals:
    void recordReturned();

private slots:
    void onReturnClicked();
    void onRefreshClicked();
    void onSelectionChanged();

private:
    void populateTable(const QVector<BorrowRecord>& records, int overdueCount);
    void showErrorDialog(const QString& message);

    Ui::BorrowRecordWindow* ui;
    QVector<BorrowRecord> m_cachedRecords;
    QString m_userId;
    int m_role = 0;
    bool m_adminMode = false;
};

#endif // BORROWRECORDWINDOW_H
