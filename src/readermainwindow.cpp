#include "readermainwindow.h"
#include "ui_readermainwindow.h"

#include <QAbstractItemView>
#include <QHeaderView>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "bookquerywindow.h"
#include "borrowrecordwindow.h"
#include "dbmanager.h"

ReaderMainWindow::ReaderMainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ReaderMainWindow) {
    ui->setupUi(this);
    if (ui->mainLayout) {
        ui->mainLayout->setContentsMargins(24, 24, 24, 24);
    }
    if (ui->headerLayout) {
        ui->headerLayout->setContentsMargins(0, 0, 0, 0);
    }
    if (ui->contentLayout) {
        ui->contentLayout->setContentsMargins(0, 0, 0, 0);
    }
    if (ui->queryContainerLayout) {
        ui->queryContainerLayout->setContentsMargins(0, 0, 0, 0);
    }
    if (ui->borrowedLayout) {
        ui->borrowedLayout->setContentsMargins(16, 16, 16, 16);
    }

    configureBorrowedTable();
    ensureBookQueryWidget();

    connect(ui->actionBookQuery, &QAction::triggered, this, &ReaderMainWindow::onActionQueryTriggered);
    connect(ui->actionBorrowRecords, &QAction::triggered, this, &ReaderMainWindow::onActionRecordsTriggered);
    connect(ui->actionLogout, &QAction::triggered, this, &ReaderMainWindow::onActionLogoutTriggered);
    connect(ui->pushButtonBack, &QPushButton::clicked, this, &ReaderMainWindow::onBackButtonClicked);
}

ReaderMainWindow::~ReaderMainWindow() {
    delete ui;
}

void ReaderMainWindow::setUserContext(const QString& userId, const QString& username) {
    m_userId = userId;
    m_username = username;

    ensureBookQueryWidget();
    if (m_bookQueryWindow) {
        m_bookQueryWindow->setUserContext(m_userId, 0);
    }

    ui->labelWelcome->setText(tr("欢迎，%1！祝您阅读愉快。").arg(username));
    setWindowTitle(tr("读者主页 - %1").arg(username));
    ui->statusbar->showMessage(tr("当前用户：%1").arg(username));

    refreshBorrowedBooks();
}

void ReaderMainWindow::onActionQueryTriggered() {
    if (m_bookQueryWindow) {
        m_bookQueryWindow->refreshBooks();
    }
}

void ReaderMainWindow::onActionRecordsTriggered() {
    if (m_userId.isEmpty()) {
        QMessageBox::warning(this, tr("未登录"), tr("无法获取用户信息，请重新登录"));
        return;
    }

    if (!m_borrowRecordWindow) {
        m_borrowRecordWindow = new BorrowRecordWindow(this);
        connect(m_borrowRecordWindow, &BorrowRecordWindow::recordReturned, this, [this]() {
            if (m_bookQueryWindow) {
                m_bookQueryWindow->refreshBooks();
            }
        });
    }

    m_borrowRecordWindow->setContext(m_userId, 0, false);
    m_borrowRecordWindow->exec();
}

void ReaderMainWindow::onActionLogoutTriggered() {
    if (QMessageBox::question(this, tr("确认退出"), tr("确定退出当前账号吗？")) == QMessageBox::Yes) {
        emit logoutRequested();
        close();
    }
}

void ReaderMainWindow::onBackButtonClicked() {
    emit logoutRequested();
    close();
}

void ReaderMainWindow::ensureBookQueryWidget() {
    if (!m_bookQueryWindow) {
        m_bookQueryWindow = new BookQueryWindow(this);
        if (ui->queryContainerLayout) {
            ui->queryContainerLayout->addWidget(m_bookQueryWindow);
        }
        connect(m_bookQueryWindow, &BookQueryWindow::borrowSucceeded, this, [this]() {
            refreshBorrowedBooks();
        });
    }
}

void ReaderMainWindow::configureBorrowedTable() {
    if (!ui->tableWidgetBorrowed) {
        return;
    }

    auto* table = ui->tableWidgetBorrowed;
    if (table->columnCount() < 5) {
        table->setColumnCount(5);
    }
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setFocusPolicy(Qt::NoFocus);
    table->setShowGrid(false);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setStretchLastSection(false);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

void ReaderMainWindow::refreshBorrowedBooks() {
    if (!ui->tableWidgetBorrowed) {
        return;
    }

    auto* table = ui->tableWidgetBorrowed;
    table->clearContents();
    table->setRowCount(0);
    m_activeBorrowRecords.clear();

    if (m_userId.isEmpty()) {
        ui->labelBorrowTip->setText(tr("请先登录以查看借阅信息。"));
        return;
    }

    int overdueCount = 0;
    QString errorMessage;
    const auto records = DBManager::instance().fetchBorrowRecords(m_userId, false, false, &overdueCount, &errorMessage);
    if (!errorMessage.isEmpty()) {
        QMessageBox::critical(this, tr("加载失败"), errorMessage);
        return;
    }

    m_activeBorrowRecords = records;
    table->setRowCount(m_activeBorrowRecords.size());

    const QString tipText = m_activeBorrowRecords.isEmpty()
        ? tr("暂无未归还的书籍，继续借阅心仪的图书吧。")
        : tr("下方列出当前尚未归还的书籍，可在此直接归还。");
    ui->labelBorrowTip->setText(tipText);

    for (int row = 0; row < m_activeBorrowRecords.size(); ++row) {
        const auto& record = m_activeBorrowRecords.at(row);
        table->setItem(row, 0, new QTableWidgetItem(record.bookName));
        table->setItem(row, 1, new QTableWidgetItem(record.bookId));
        table->setItem(row, 2, new QTableWidgetItem(record.author));
        table->setItem(row, 3, new QTableWidgetItem(record.borrowDate.toString("yyyy-MM-dd HH:mm")));

        for (int column = 0; column < 4; ++column) {
            if (auto* item = table->item(row, column)) {
                item->setTextAlignment(Qt::AlignVCenter | (column == 1 ? Qt::AlignCenter : Qt::AlignLeft));
            }
        }

        attachReturnButton(row, record);
    }
}

void ReaderMainWindow::attachReturnButton(int row, const BorrowRecord& record) {
    if (!ui->tableWidgetBorrowed) {
        return;
    }

    auto* button = new QPushButton(tr("归还"), ui->tableWidgetBorrowed);
    button->setMinimumWidth(88);

    connect(button, &QPushButton::clicked, this, [this, recordId = record.recordId]() {
        if (QMessageBox::question(this, tr("确认归还"), tr("是否确定归还这本书？")) != QMessageBox::Yes) {
            return;
        }

        QString errorMessage;
        if (!DBManager::instance().returnBook(recordId, &errorMessage)) {
            if (errorMessage.isEmpty()) {
                errorMessage = tr("归还失败，请稍后重试");
            }
            QMessageBox::critical(this, tr("操作失败"), errorMessage);
            return;
        }

        QMessageBox::information(this, tr("归还成功"), tr("书籍归还成功"));
        refreshBorrowedBooks();
        if (m_bookQueryWindow) {
            m_bookQueryWindow->refreshBooks();
        }
    });

    ui->tableWidgetBorrowed->setCellWidget(row, 4, button);
}
