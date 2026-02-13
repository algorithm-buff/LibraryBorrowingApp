#include "bookquerywindow.h"
#include "ui_bookquerywindow.h"

#include <QAbstractItemView>
#include <QFormLayout>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QMessageBox>
#include <QTableWidgetItem>

#include "dbmanager.h"

BookQueryWindow::BookQueryWindow(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::BookQueryWindow) {
    ui->setupUi(this);

    ui->tableWidgetBooks->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetBooks->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetBooks->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetBooks->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetBooks->setAlternatingRowColors(true);
    ui->tableWidgetBooks->verticalHeader()->setVisible(false);
    ui->tableWidgetBooks->setFocusPolicy(Qt::NoFocus);

    if (auto* formLayout = ui->formLayoutFilters) {
        formLayout->setHorizontalSpacing(16);
        formLayout->setVerticalSpacing(12);
    }
    if (auto* buttonLayout = ui->horizontalLayoutInfo) {
        buttonLayout->setSpacing(16);
    }

    connect(ui->pushButtonSearch, &QPushButton::clicked, this, &BookQueryWindow::onSearchClicked);
    connect(ui->pushButtonReset, &QPushButton::clicked, this, &BookQueryWindow::onResetClicked);
    connect(ui->pushButtonBorrow, &QPushButton::clicked, this, &BookQueryWindow::onBorrowClicked);
    connect(ui->tableWidgetBooks->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &BookQueryWindow::onSelectionChanged);

    updateBorrowAvailability();
}

BookQueryWindow::~BookQueryWindow() {
    delete ui;
}

void BookQueryWindow::setUserContext(const QString& userId, int role) {
    m_userId = userId;
    m_role = role;
    ui->pushButtonBorrow->setVisible(role == 0);
    if (role == 0) {
        ui->infoLabel->setText(tr("提示：选择图书后点击“借阅”即可完成登记"));
    } else {
        ui->infoLabel->setText(tr("管理员可查看库存并使用上方按钮新增、修改或删除书籍"));
    }
    refreshBooks();
}

void BookQueryWindow::refreshBooks() {
    QString errorMessage;
    const auto books = DBManager::instance().queryBooks(ui->lineEditBookName->text().trimmed(),
                                                        ui->lineEditAuthor->text().trimmed(),
                                                        &errorMessage);
    if (!errorMessage.isEmpty()) {
        showErrorDialog(errorMessage);
    }
    populateTable(books);
    emit selectionStateChanged(hasValidSelection());
}

void BookQueryWindow::onSearchClicked() {
    refreshBooks();
}

void BookQueryWindow::onResetClicked() {
    ui->lineEditBookName->clear();
    ui->lineEditAuthor->clear();
    refreshBooks();
}

void BookQueryWindow::onBorrowClicked() {
    if (m_userId.isEmpty()) {
        QMessageBox::warning(this, tr("未登录"), tr("请重新登录后再试"));
        return;
    }

    const QModelIndex currentIndex = ui->tableWidgetBooks->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::information(this, tr("未选择图书"), tr("请先选择一条可借的图书记录"));
        return;
    }

    const int row = currentIndex.row();
    if (row < 0 || row >= m_cachedBooks.size()) {
        showErrorDialog(tr("选择的图书索引无效"));
        return;
    }

    const BookInfo& book = m_cachedBooks.at(row);
    if (book.stock <= 0 || book.status != 0) {
        QMessageBox::warning(this, tr("无法借阅"), tr("该图书暂不可借，请选择其它图书"));
        return;
    }

    int overdueCount = 0;
    QString overdueError;
    if (!DBManager::instance().hasOverdueRecords(m_userId, &overdueCount, &overdueError)) {
        if (!overdueError.isEmpty()) {
            showErrorDialog(overdueError);
        } else if (overdueCount > 0) {
            QMessageBox::warning(this, tr("存在逾期"),
                                 tr("您有 %1 条逾期记录，处理后方可继续借阅").arg(overdueCount));
        } else {
            showErrorDialog(tr("借阅校验失败"));
        }
        return;
    }

    QString errorMessage;
    if (!DBManager::instance().borrowBook(m_userId, book.bookId, &errorMessage)) {
        if (errorMessage.isEmpty()) {
            errorMessage = tr("借阅失败，请稍后重试");
        }
        showErrorDialog(errorMessage);
        return;
    }

    QMessageBox::information(this, tr("借阅成功"), tr("借阅登记已完成，请按时归还"));
    emit borrowSucceeded();
    refreshBooks();
}

void BookQueryWindow::onSelectionChanged() {
    updateBorrowAvailability();
    emit selectionStateChanged(hasValidSelection());
}

void BookQueryWindow::populateTable(const QVector<BookInfo>& books) {
    m_cachedBooks = books;
    ui->tableWidgetBooks->clearContents();
    ui->tableWidgetBooks->setRowCount(books.size());

    ui->tableWidgetBooks->setColumnCount(6);

    for (int row = 0; row < books.size(); ++row) {
        const BookInfo& book = books.at(row);
        ui->tableWidgetBooks->setItem(row, 0, new QTableWidgetItem(book.bookId));
        ui->tableWidgetBooks->setItem(row, 1, new QTableWidgetItem(book.bookName));
        ui->tableWidgetBooks->setItem(row, 2, new QTableWidgetItem(book.author));
        ui->tableWidgetBooks->setItem(row, 3, new QTableWidgetItem(book.publisher));
        ui->tableWidgetBooks->setItem(row, 4, new QTableWidgetItem(QString::number(book.stock)));
        ui->tableWidgetBooks->setItem(row, 5, new QTableWidgetItem(formatStatus(book.status)));

        for (int column = 0; column < ui->tableWidgetBooks->columnCount(); ++column) {
            if (auto* item = ui->tableWidgetBooks->item(row, column)) {
                item->setTextAlignment(Qt::AlignVCenter | (column == 4 ? Qt::AlignCenter : Qt::AlignLeft));
            }
        }
    }

    updateBorrowAvailability();
}

void BookQueryWindow::showErrorDialog(const QString& message) {
    QMessageBox::critical(this, tr("错误"), message);
}

void BookQueryWindow::updateBorrowAvailability() {
    if (m_role != 0) {
        ui->pushButtonBorrow->setEnabled(false);
        return;
    }

    const auto selection = currentSelectedBook();
    if (!selection.has_value()) {
        ui->pushButtonBorrow->setEnabled(false);
        return;
    }

    const BookInfo& book = selection.value();
    const bool available = book.stock > 0 && book.status == 0;
    ui->pushButtonBorrow->setEnabled(available);
}

QString BookQueryWindow::formatStatus(int status) const {
    switch (status) {
    case 0:
        return tr("可借");
    case 1:
        return tr("已借");
    case 2:
        return tr("损坏");
    default:
        return tr("未知");
    }
}

bool BookQueryWindow::hasValidSelection() const {
    const QModelIndex currentIndex = ui->tableWidgetBooks->currentIndex();
    if (!currentIndex.isValid()) {
        return false;
    }

    const int row = currentIndex.row();
    return row >= 0 && row < m_cachedBooks.size();
}

std::optional<BookInfo> BookQueryWindow::currentSelectedBook() const {
    if (!hasValidSelection()) {
        return std::nullopt;
    }

    const QModelIndex currentIndex = ui->tableWidgetBooks->currentIndex();
    return m_cachedBooks.at(currentIndex.row());
}
