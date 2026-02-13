#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "bookeditordialog.h"
#include "bookmanagewindow.h"
#include "bookquerywindow.h"
#include "borrowrecordwindow.h"
#include "dbmanager.h"
#include "models.h"

AdminMainWindow::AdminMainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminMainWindow) {
    ui->setupUi(this);

    ensureCentralQueryWidget();

    connect(ui->actionBookQuery, &QAction::triggered, this, &AdminMainWindow::onActionQueryTriggered);
    connect(ui->actionBorrowRecords, &QAction::triggered, this, &AdminMainWindow::onActionRecordsTriggered);
    connect(ui->actionBookMaintain, &QAction::triggered, this, &AdminMainWindow::onActionMaintainTriggered);
    connect(ui->actionLogout, &QAction::triggered, this, &AdminMainWindow::onActionLogoutTriggered);
}

AdminMainWindow::~AdminMainWindow() {
    delete ui;
}

void AdminMainWindow::setUserContext(const QString& userId, const QString& username) {
    m_userId = userId;
    m_username = username;

    ensureCentralQueryWidget();
    if (m_bookQueryWindow) {
        m_bookQueryWindow->setUserContext(m_userId, 1);
        refreshBookList();
    }

    setWindowTitle(tr("管理员主页 - %1").arg(username));
    ui->statusbar->showMessage(tr("管理员：%1").arg(username));
}

void AdminMainWindow::onActionQueryTriggered() {
    ensureCentralQueryWidget();
    if (m_bookQueryWindow) {
        m_bookQueryWindow->refreshBooks();
    }
}

void AdminMainWindow::onActionRecordsTriggered() {
    if (!m_borrowRecordWindow) {
        m_borrowRecordWindow = new BorrowRecordWindow(this);
        connect(m_borrowRecordWindow, &BorrowRecordWindow::recordReturned, this, [this]() {
            if (m_bookQueryWindow) {
                m_bookQueryWindow->refreshBooks();
            }
        });
    }

    m_borrowRecordWindow->setContext(QString(), 1, true);
    m_borrowRecordWindow->exec();
}

void AdminMainWindow::onActionMaintainTriggered() {
    if (!m_bookManageWindow) {
        m_bookManageWindow = new BookManageWindow(this);
        connect(m_bookManageWindow, &BookManageWindow::booksChanged, this, [this]() {
            if (m_bookQueryWindow) {
                m_bookQueryWindow->refreshBooks();
            }
        });
    }

    m_bookManageWindow->reload();
    m_bookManageWindow->setModal(true);
    m_bookManageWindow->exec();
}

void AdminMainWindow::onActionLogoutTriggered() {
    if (QMessageBox::question(this, tr("确认退出"), tr("确定退出当前账号吗？")) == QMessageBox::Yes) {
        emit logoutRequested();
        close();
    }
}

void AdminMainWindow::ensureCentralQueryWidget() {
    if (!m_centralContainer) {
        buildAdminCentral();
    }
}

void AdminMainWindow::buildAdminCentral() {
    m_centralContainer = new QWidget(this);
    auto* containerLayout = new QVBoxLayout(m_centralContainer);
    containerLayout->setContentsMargins(24, 24, 24, 24);
    containerLayout->setSpacing(18);

    auto* actionRow = new QWidget(m_centralContainer);
    auto* actionLayout = new QHBoxLayout(actionRow);
    actionLayout->setContentsMargins(0, 0, 0, 0);
    actionLayout->setSpacing(12);

    m_buttonAdd = new QPushButton(tr("添加书籍"), actionRow);
    m_buttonEdit = new QPushButton(tr("修改书籍"), actionRow);
    m_buttonDelete = new QPushButton(tr("删除书籍"), actionRow);

    actionLayout->addWidget(m_buttonAdd);
    actionLayout->addWidget(m_buttonEdit);
    actionLayout->addWidget(m_buttonDelete);
    actionLayout->addStretch();

    containerLayout->addWidget(actionRow);

    m_bookQueryWindow = new BookQueryWindow(m_centralContainer);
    containerLayout->addWidget(m_bookQueryWindow, 1);

    setCentralWidget(m_centralContainer);

    connect(m_buttonAdd, &QPushButton::clicked, this, &AdminMainWindow::onAddBookRequested);
    connect(m_buttonEdit, &QPushButton::clicked, this, &AdminMainWindow::onEditBookRequested);
    connect(m_buttonDelete, &QPushButton::clicked, this, &AdminMainWindow::onDeleteBookRequested);
    connect(m_bookQueryWindow, &BookQueryWindow::selectionStateChanged, this, &AdminMainWindow::onSelectionStateChanged);

    updateActionButtons(false);
}

void AdminMainWindow::refreshBookList() {
    if (m_bookQueryWindow) {
        m_bookQueryWindow->refreshBooks();
    }
}

bool AdminMainWindow::ensureBookSelection(BookInfo* book, QString* errorMessage) const {
    if (!m_bookQueryWindow) {
        if (errorMessage) {
            *errorMessage = tr("请稍后再试，列表尚未加载完毕");
        }
        return false;
    }

    const auto selection = m_bookQueryWindow->currentSelectedBook();
    if (!selection.has_value()) {
        if (errorMessage) {
            *errorMessage = tr("请先选择一条书籍记录");
        }
        return false;
    }

    if (book) {
        *book = selection.value();
    }
    return true;
}

void AdminMainWindow::updateActionButtons(bool hasSelection) {
    if (m_buttonEdit) {
        m_buttonEdit->setEnabled(hasSelection);
    }
    if (m_buttonDelete) {
        m_buttonDelete->setEnabled(hasSelection);
    }
}

void AdminMainWindow::onAddBookRequested() {
    BookEditorDialog dialog(BookEditorDialog::Mode::Create, this);
    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    BookInfo book = dialog.bookData();
    QString errorMessage;
    if (!DBManager::instance().addBook(book, &errorMessage)) {
        if (errorMessage.isEmpty()) {
            errorMessage = tr("新增图书失败");
        }
        QMessageBox::critical(this, tr("操作失败"), errorMessage);
        return;
    }

    QMessageBox::information(this, tr("新增成功"), tr("书籍已成功添加"));
    refreshBookList();
}

void AdminMainWindow::onEditBookRequested() {
    BookInfo selectedBook;
    QString selectionError;
    if (!ensureBookSelection(&selectedBook, &selectionError)) {
        QMessageBox::warning(this, tr("提示"), selectionError);
        return;
    }

    QString fetchError;
    const auto fullRecord = DBManager::instance().fetchBookById(selectedBook.bookId, &fetchError);
    if (!fullRecord.has_value()) {
        if (fetchError.isEmpty()) {
            fetchError = tr("未能加载该图书的详细信息");
        }
        QMessageBox::critical(this, tr("操作失败"), fetchError);
        return;
    }

    BookEditorDialog dialog(BookEditorDialog::Mode::Edit, this);
    dialog.setBookData(fullRecord.value());

    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    BookInfo updatedBook = dialog.bookData();
    QString errorMessage;
    if (!DBManager::instance().updateBook(updatedBook, &errorMessage)) {
        if (errorMessage.isEmpty()) {
            errorMessage = tr("更新失败，请稍后重试");
        }
        QMessageBox::critical(this, tr("操作失败"), errorMessage);
        return;
    }

    QMessageBox::information(this, tr("修改成功"), tr("书籍信息已更新"));
    refreshBookList();
}

void AdminMainWindow::onDeleteBookRequested() {
    BookInfo selectedBook;
    QString selectionError;
    if (!ensureBookSelection(&selectedBook, &selectionError)) {
        QMessageBox::warning(this, tr("提示"), selectionError);
        return;
    }

    if (QMessageBox::question(this,
                               tr("确认删除"),
                               tr("确定删除图书《%1》吗？该操作不可恢复。").arg(selectedBook.bookName)) != QMessageBox::Yes) {
        return;
    }

    QString errorMessage;
    if (!DBManager::instance().deleteBook(selectedBook.bookId, &errorMessage)) {
        if (errorMessage.isEmpty()) {
            errorMessage = tr("删除失败");
        }
        QMessageBox::critical(this, tr("操作失败"), errorMessage);
        return;
    }

    QMessageBox::information(this, tr("删除成功"), tr("图书记录已删除"));
    refreshBookList();
}

void AdminMainWindow::onSelectionStateChanged(bool hasSelection) {
    updateActionButtons(hasSelection);
}
