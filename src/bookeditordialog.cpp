#include "bookeditordialog.h"
#include "ui_bookeditordialog.h"

#include <QDate>
#include <QMessageBox>

BookEditorDialog::BookEditorDialog(Mode mode, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::BookEditorDialog)
    , m_mode(mode) {
    ui->setupUi(this);
    if (ui->verticalLayout) {
        ui->verticalLayout->setContentsMargins(24, 24, 24, 24);
    }

    ui->comboBoxStatus->clear();
    ui->comboBoxStatus->addItem(tr("可借"), 0);
    ui->comboBoxStatus->addItem(tr("已借"), 1);
    ui->comboBoxStatus->addItem(tr("损坏"), 2);

    ui->dateEditPublishDate->setDate(QDate::currentDate());
    ui->spinBoxStock->setValue(1);

    connect(ui->pushButtonSubmit, &QPushButton::clicked, this, &BookEditorDialog::handleSubmit);
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &BookEditorDialog::reject);

    applyMode();
}

BookEditorDialog::~BookEditorDialog() {
    delete ui;
}

void BookEditorDialog::setBookData(const BookInfo& book) {
    ui->lineEditBookId->setText(book.bookId);
    ui->lineEditBookName->setText(book.bookName);
    ui->lineEditAuthor->setText(book.author);
    ui->lineEditPublisher->setText(book.publisher);
    ui->dateEditPublishDate->setDate(book.publishDate.isValid() ? book.publishDate : QDate::currentDate());
    ui->spinBoxStock->setValue(book.stock);

    const int statusIndex = ui->comboBoxStatus->findData(book.status);
    if (statusIndex >= 0) {
        ui->comboBoxStatus->setCurrentIndex(statusIndex);
    }
    ui->plainTextEditRemark->setPlainText(book.remark);

    if (m_mode == Mode::Edit) {
        ui->lineEditBookId->setReadOnly(true);
    }
}

BookInfo BookEditorDialog::bookData() const {
    BookInfo book;
    book.bookId = ui->lineEditBookId->text().trimmed();
    book.bookName = ui->lineEditBookName->text().trimmed();
    book.author = ui->lineEditAuthor->text().trimmed();
    book.publisher = ui->lineEditPublisher->text().trimmed();
    book.publishDate = ui->dateEditPublishDate->date();
    book.stock = ui->spinBoxStock->value();
    book.status = ui->comboBoxStatus->currentData().toInt();
    book.remark = ui->plainTextEditRemark->toPlainText().trimmed();
    return book;
}

void BookEditorDialog::handleSubmit() {
    QString errorMessage;
    if (!validateInputs(&errorMessage)) {
        QMessageBox::warning(this, tr("信息不完整"), errorMessage);
        return;
    }

    accept();
}

void BookEditorDialog::applyMode() {
    if (m_mode == Mode::Create) {
        setWindowTitle(tr("添加新书"));
    } else {
        setWindowTitle(tr("修改书籍信息"));
    }
}

bool BookEditorDialog::validateInputs(QString* errorMessage) const {
    const QString bookId = ui->lineEditBookId->text().trimmed();
    const QString bookName = ui->lineEditBookName->text().trimmed();
    const QString author = ui->lineEditAuthor->text().trimmed();

    if (bookId.isEmpty()) {
        if (errorMessage) {
            *errorMessage = tr("书号不能为空");
        }
        return false;
    }
    if (bookName.isEmpty()) {
        if (errorMessage) {
            *errorMessage = tr("书名不能为空");
        }
        return false;
    }
    if (author.isEmpty()) {
        if (errorMessage) {
            *errorMessage = tr("作者不能为空");
        }
        return false;
    }

    return true;
}
