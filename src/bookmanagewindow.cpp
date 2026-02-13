#include "bookmanagewindow.h"
#include "ui_bookmanagewindow.h"

#include <QAbstractItemView>
#include <QDate>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QMessageBox>
#include <QTableWidgetItem>

#include "dbmanager.h"

namespace {
QString statusToString(int status) {
    switch (status) {
    case 0:
        return QObject::tr("可借");
    case 1:
        return QObject::tr("已借");
    case 2:
        return QObject::tr("损坏");
    default:
        return QObject::tr("未知");
    }
}
}

BookManageWindow::BookManageWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::BookManageWindow) {
    ui->setupUi(this);

    ui->tableWidgetBooks->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetBooks->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetBooks->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetBooks->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->comboBoxStatus->clear();
    ui->comboBoxStatus->addItem(tr("可借"), 0);
    ui->comboBoxStatus->addItem(tr("已借"), 1);
    ui->comboBoxStatus->addItem(tr("损坏"), 2);

    connect(ui->pushButtonAdd, &QPushButton::clicked, this, &BookManageWindow::onAddClicked);
    connect(ui->pushButtonUpdate, &QPushButton::clicked, this, &BookManageWindow::onUpdateClicked);
    connect(ui->pushButtonDelete, &QPushButton::clicked, this, &BookManageWindow::onDeleteClicked);
    connect(ui->pushButtonResetForm, &QPushButton::clicked, this, &BookManageWindow::onResetForm);
    connect(ui->tableWidgetBooks->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &BookManageWindow::onRowSelected);

    reload();
}

BookManageWindow::~BookManageWindow() {
    delete ui;
}

void BookManageWindow::reload() {
    QString errorMessage;
    const auto books = DBManager::instance().fetchAllBooks(&errorMessage);
    if (!errorMessage.isEmpty()) {
        showErrorDialog(errorMessage);
    }
    populateTable(books);
}

void BookManageWindow::onAddClicked() {
    BookInfo book = collectFormData();
    if (book.bookId.isEmpty()) {
        showErrorDialog(tr("书号不能为空"));
        return;
    }
    if (book.bookName.isEmpty()) {
        showErrorDialog(tr("书名不能为空"));
        return;
    }
    if (book.author.isEmpty()) {
        showErrorDialog(tr("作者不能为空"));
        return;
    }

    QString errorMessage;
    if (!DBManager::instance().addBook(book, &errorMessage)) {
        if (errorMessage.isEmpty()) {
            errorMessage = tr("新增图书失败");
        }
        showErrorDialog(errorMessage);
        return;
    }

    QMessageBox::information(this, tr("新增成功"), tr("图书已添加"));
    emit booksChanged();
    reload();
    resetFormFields();
}

void BookManageWindow::onUpdateClicked() {
    const QModelIndex currentIndex = ui->tableWidgetBooks->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, tr("未选择记录"), tr("请先选择需要修改的图书"));
        return;
    }

    BookInfo book = collectFormData();
    if (book.bookId.isEmpty()) {
        showErrorDialog(tr("书号不能为空"));
        return;
    }

    QString errorMessage;
    if (!DBManager::instance().updateBook(book, &errorMessage)) {
        if (errorMessage.isEmpty()) {
            errorMessage = tr("更新失败，请稍后重试");
        }
        showErrorDialog(errorMessage);
        return;
    }

    QMessageBox::information(this, tr("修改成功"), tr("图书信息已更新"));
    emit booksChanged();
    reload();
}

void BookManageWindow::onDeleteClicked() {
    const QModelIndex currentIndex = ui->tableWidgetBooks->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, tr("未选择记录"), tr("请先选择需要删除的图书"));
        return;
    }

    const int row = currentIndex.row();
    if (row < 0 || row >= m_cachedBooks.size()) {
        showErrorDialog(tr("无法确定所选图书"));
        return;
    }

    const BookInfo& book = m_cachedBooks.at(row);

    if (QMessageBox::question(this,
                               tr("确认删除"),
                               tr("确定删除图书《%1》吗？此操作不可恢复。").arg(book.bookName)) != QMessageBox::Yes) {
        return;
    }

    QString errorMessage;
    if (!DBManager::instance().deleteBook(book.bookId, &errorMessage)) {
        if (errorMessage.isEmpty()) {
            errorMessage = tr("删除失败");
        }
        showErrorDialog(errorMessage);
        return;
    }

    QMessageBox::information(this, tr("删除成功"), tr("图书记录已删除"));
    emit booksChanged();
    reload();
    resetFormFields();
}

void BookManageWindow::onRowSelected() {
    const QModelIndex currentIndex = ui->tableWidgetBooks->currentIndex();
    if (!currentIndex.isValid()) {
        resetFormFields();
        return;
    }

    const int row = currentIndex.row();
    if (row < 0 || row >= m_cachedBooks.size()) {
        resetFormFields();
        return;
    }

    fillFormFromRow(row);
}

void BookManageWindow::onResetForm() {
    ui->tableWidgetBooks->clearSelection();
    resetFormFields();
}

void BookManageWindow::populateTable(const QVector<BookInfo>& books) {
    m_cachedBooks = books;
    ui->tableWidgetBooks->clearContents();
    ui->tableWidgetBooks->setRowCount(books.size());

    for (int row = 0; row < books.size(); ++row) {
        const BookInfo& book = books.at(row);
        ui->tableWidgetBooks->setItem(row, 0, new QTableWidgetItem(book.bookId));
        ui->tableWidgetBooks->setItem(row, 1, new QTableWidgetItem(book.bookName));
        ui->tableWidgetBooks->setItem(row, 2, new QTableWidgetItem(book.author));
        ui->tableWidgetBooks->setItem(row, 3, new QTableWidgetItem(book.publisher));
        ui->tableWidgetBooks->setItem(row, 4, new QTableWidgetItem(book.publishDate.toString("yyyy-MM-dd")));
        ui->tableWidgetBooks->setItem(row, 5, new QTableWidgetItem(QString::number(book.stock)));
        ui->tableWidgetBooks->setItem(row, 6, new QTableWidgetItem(statusToString(book.status)));
        ui->tableWidgetBooks->setItem(row, 7, new QTableWidgetItem(book.remark));
    }
}

BookInfo BookManageWindow::collectFormData() const {
    BookInfo book;
    book.bookId = ui->lineEditBookId->text().trimmed();
    book.bookName = ui->lineEditBookName->text().trimmed();
    book.author = ui->lineEditAuthor->text().trimmed();
    book.publisher = ui->lineEditPublisher->text().trimmed();
    book.publishDate = ui->dateEditPublishDate->date();
    book.stock = ui->spinBoxStock->value();
    book.status = ui->comboBoxStatus->currentData().toInt();
    book.remark = ui->textEditRemark->toPlainText().trimmed();

    return book;
}

void BookManageWindow::fillFormFromRow(int rowIndex) {
    if (rowIndex < 0 || rowIndex >= m_cachedBooks.size()) {
        return;
    }

    const BookInfo& book = m_cachedBooks.at(rowIndex);
    ui->lineEditBookId->setText(book.bookId);
    ui->lineEditBookId->setReadOnly(true);
    ui->lineEditBookName->setText(book.bookName);
    ui->lineEditAuthor->setText(book.author);
    ui->lineEditPublisher->setText(book.publisher);
    ui->dateEditPublishDate->setDate(book.publishDate.isValid() ? book.publishDate : QDate::currentDate());
    ui->spinBoxStock->setValue(book.stock);

    int statusIndex = ui->comboBoxStatus->findData(book.status);
    if (statusIndex >= 0) {
        ui->comboBoxStatus->setCurrentIndex(statusIndex);
    }
    ui->textEditRemark->setPlainText(book.remark);
}

void BookManageWindow::showErrorDialog(const QString& message) {
    QMessageBox::critical(this, tr("错误"), message);
}

void BookManageWindow::resetFormFields() {
    ui->lineEditBookId->setReadOnly(false);
    ui->lineEditBookId->clear();
    ui->lineEditBookName->clear();
    ui->lineEditAuthor->clear();
    ui->lineEditPublisher->clear();
    ui->dateEditPublishDate->setDate(QDate::currentDate());
    ui->spinBoxStock->setValue(0);
    ui->comboBoxStatus->setCurrentIndex(0);
    ui->textEditRemark->clear();
}
