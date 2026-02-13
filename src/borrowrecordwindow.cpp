#include "borrowrecordwindow.h"
#include "ui_borrowrecordwindow.h"

#include <QAbstractItemView>
#include <QColor>
#include <QDateTime>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QMessageBox>
#include <QTableWidgetItem>

#include "dbmanager.h"

BorrowRecordWindow::BorrowRecordWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::BorrowRecordWindow) {
    ui->setupUi(this);

    ui->tableWidgetRecords->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetRecords->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetRecords->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetRecords->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->pushButtonReturn, &QPushButton::clicked, this, &BorrowRecordWindow::onReturnClicked);
    connect(ui->pushButtonRefresh, &QPushButton::clicked, this, &BorrowRecordWindow::onRefreshClicked);
    connect(ui->tableWidgetRecords->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &BorrowRecordWindow::onSelectionChanged);

    ui->pushButtonReturn->setEnabled(false);
}

BorrowRecordWindow::~BorrowRecordWindow() {
    delete ui;
}

void BorrowRecordWindow::setContext(const QString& userId, int role, bool adminMode) {
    m_userId = userId;
    m_role = role;
    m_adminMode = adminMode;

    if (adminMode) {
        setWindowTitle(tr("借阅记录管理"));
        ui->pushButtonReturn->setText(tr("标记为已归还"));
    } else {
        setWindowTitle(tr("我的借阅记录"));
        ui->pushButtonReturn->setText(tr("归还所选图书"));
    }

    reload();
}

void BorrowRecordWindow::reload() {
    const QString targetUserId = m_adminMode ? QString() : m_userId;
    int overdueCount = 0;
    QString errorMessage;
    const auto records = DBManager::instance().fetchBorrowRecords(targetUserId,
                                                                  true,
                                                                  m_adminMode,
                                                                  &overdueCount,
                                                                  &errorMessage);
    if (!errorMessage.isEmpty()) {
        showErrorDialog(errorMessage);
    }

    populateTable(records, overdueCount);
}

void BorrowRecordWindow::onReturnClicked() {
    const QModelIndex currentIndex = ui->tableWidgetRecords->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::information(this, tr("未选择记录"), tr("请选择需要归还的记录"));
        return;
    }

    const int row = currentIndex.row();
    if (row < 0 || row >= m_cachedRecords.size()) {
        showErrorDialog(tr("所选记录无效"));
        return;
    }

    const auto& record = m_cachedRecords.at(row);
    if (record.isReturned()) {
        QMessageBox::information(this, tr("无需操作"), tr("该记录已经归还"));
        return;
    }

    QString errorMessage;
    if (!DBManager::instance().returnBook(record.recordId, &errorMessage)) {
        if (errorMessage.isEmpty()) {
            errorMessage = tr("归还操作失败");
        }
        showErrorDialog(errorMessage);
        return;
    }

    QMessageBox::information(this, tr("已归还"), tr("归还登记完成"));
    emit recordReturned();
    reload();
}

void BorrowRecordWindow::onRefreshClicked() {
    reload();
}

void BorrowRecordWindow::onSelectionChanged() {
    if (ui->tableWidgetRecords->currentIndex().isValid()) {
        const int row = ui->tableWidgetRecords->currentIndex().row();
        if (row >= 0 && row < m_cachedRecords.size()) {
            ui->pushButtonReturn->setEnabled(!m_cachedRecords.at(row).isReturned());
            return;
        }
    }
    ui->pushButtonReturn->setEnabled(false);
}

void BorrowRecordWindow::populateTable(const QVector<BorrowRecord>& records, int overdueCount) {
    m_cachedRecords = records;
    ui->tableWidgetRecords->clearContents();
    ui->tableWidgetRecords->setRowCount(records.size());
    ui->labelOverdue->setText(tr("逾期记录：%1 条").arg(overdueCount));

    const QColor overdueColor(255, 204, 204);

    for (int row = 0; row < records.size(); ++row) {
        const BorrowRecord& record = records.at(row);
        const bool overdueNow = !record.isReturned() && record.dueDate < QDateTime::currentDateTime();

        auto makeItem = [overdueNow, &overdueColor](const QString& text) {
            auto* item = new QTableWidgetItem(text);
            if (overdueNow) {
                item->setBackground(overdueColor);
            }
            return item;
        };

        ui->tableWidgetRecords->setItem(row, 0, makeItem(QString::number(record.recordId)));
        ui->tableWidgetRecords->setItem(row, 1, makeItem(record.bookId));
        ui->tableWidgetRecords->setItem(row, 2, makeItem(record.bookName));
        ui->tableWidgetRecords->setItem(row, 3, makeItem(record.borrowDate.toString("yyyy-MM-dd HH:mm")));
        ui->tableWidgetRecords->setItem(row, 4, makeItem(record.dueDate.toString("yyyy-MM-dd HH:mm")));
        ui->tableWidgetRecords->setItem(row, 5, makeItem(record.isReturned() ? tr("已归还") : tr("未归还")));
        ui->tableWidgetRecords->setItem(row, 6, makeItem(QString::number(record.overdueDays)));

        if (m_adminMode) {
            ui->tableWidgetRecords->setItem(row, 7, makeItem(record.username));
        } else {
            ui->tableWidgetRecords->setItem(row, 7, makeItem(QString()));
        }
    }

    // Hide or show username column depending on role.
    const int usernameColumn = 7;
    const bool showUsername = m_adminMode;
    ui->tableWidgetRecords->setColumnHidden(usernameColumn, !showUsername);

    onSelectionChanged();
}

void BorrowRecordWindow::showErrorDialog(const QString& message) {
    QMessageBox::critical(this, tr("错误"), message);
}
