#include "dbmanager.h"

#include <QDateTime>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QStringList>
#include <QMetaType>
#include <QCryptographicHash>
#include <QUuid>

#include <algorithm>

namespace {
QString sqlErrorToString(const QSqlError& error) {
    return QStringLiteral("[%1] %2").arg(error.nativeErrorCode(), error.text());
}

}

DBManager& DBManager::instance() {
    static DBManager inst;
    return inst;
}

DBManager::DBManager(QObject* parent)
    : QObject(parent) {
    m_database = QSqlDatabase::addDatabase(QStringLiteral("QODBC"), QStringLiteral("LibraryConnection"));
}

void DBManager::setConnectionInfo(const ConnectionInfo& info) {
    if (m_database.isOpen()) {
        m_database.close();
    }
    m_connectionInfo = info;
}

const DBManager::ConnectionInfo& DBManager::connectionInfo() const {
    return m_connectionInfo;
}

bool DBManager::open(QString* errorMessage) {
    if (!ensureConnection(errorMessage)) {
        return false;
    }
    if (m_database.isOpen()) {
        return true;
    }
    if (!m_database.open()) {
        if (errorMessage) {
            *errorMessage = sqlErrorToString(m_database.lastError());
        }
        return false;
    }
    return true;
}

void DBManager::close() {
    if (m_database.isValid() && m_database.isOpen()) {
        m_database.close();
    }
}

bool DBManager::validateLogin(const QString& username,
                              const QString& password,
                              int role,
                              QString* userId,
                              QString* fullUsername,
                              QString* errorMessage) {
    if (!ensureConnection(errorMessage)) {
        return false;
    }

    QSqlQuery query(m_database);
    query.prepare(QStringLiteral(
        "SELECT user_id, username, password "
        "FROM user_info "
        "WHERE username = :username AND role = :role"));
    query.bindValue(QStringLiteral(":username"), username);
    query.bindValue(QStringLiteral(":role"), role);

    if (!query.exec()) {
        if (errorMessage) {
            *errorMessage = sqlErrorToString(query.lastError());
        }
        return false;
    }

    if (query.next()) {
        const QString storedPassword = query.value(QStringLiteral("password")).toString();
        if (!verifyPasswordValue(password, storedPassword)) {
            if (errorMessage) {
                *errorMessage = QStringLiteral("用户名、密码或角色不匹配");
            }
            return false;
        }
        if (userId) {
            *userId = query.value(QStringLiteral("user_id")).toString();
        }
        if (fullUsername) {
            *fullUsername = query.value(QStringLiteral("username")).toString();
        }
        return true;
    }

    if (errorMessage) {
        *errorMessage = QStringLiteral("用户名、密码或角色不匹配");
    }
    return false;
}

bool DBManager::registerUser(const QString& username,
                             const QString& password,
                             const QString& phone,
                             QString* errorMessage) {
    const QString trimmedUsername = username.trimmed();
    const QString trimmedPhone = phone.trimmed();

    if (trimmedUsername.size() < 3) {
        if (errorMessage) {
            *errorMessage = QStringLiteral("用户名长度至少为 3 个字符");
        }
        return false;
    }
    if (password.size() < 6) {
        if (errorMessage) {
            *errorMessage = QStringLiteral("密码长度至少为 6 位");
        }
        return false;
    }

    if (!ensureConnection(errorMessage)) {
        return false;
    }

    QSqlQuery checkQuery(m_database);
    checkQuery.prepare(QStringLiteral("SELECT COUNT(1) AS cnt FROM user_info WHERE username = :username"));
    checkQuery.bindValue(QStringLiteral(":username"), trimmedUsername);

    if (!checkQuery.exec()) {
        if (errorMessage) {
            *errorMessage = sqlErrorToString(checkQuery.lastError());
        }
        return false;
    }

    if (checkQuery.next() && checkQuery.value(QStringLiteral("cnt")).toInt() > 0) {
        if (errorMessage) {
            *errorMessage = QStringLiteral("用户名已存在，请选择其他用户名");
        }
        return false;
    }

    const QString userId = generateUserId();
    const QString saltedPassword = createSaltedPassword(password);

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare(QStringLiteral(
        "INSERT INTO user_info (user_id, username, password, role, phone) "
        "VALUES (:user_id, :username, :password, 0, :phone)"));
    insertQuery.bindValue(QStringLiteral(":user_id"), userId);
    insertQuery.bindValue(QStringLiteral(":username"), trimmedUsername);
    insertQuery.bindValue(QStringLiteral(":password"), saltedPassword);
    if (trimmedPhone.isEmpty()) {
        insertQuery.bindValue(QStringLiteral(":phone"), QVariant(QMetaType(QMetaType::QString)));
    } else {
        insertQuery.bindValue(QStringLiteral(":phone"), trimmedPhone);
    }

    if (!insertQuery.exec()) {
        if (errorMessage) {
            *errorMessage = sqlErrorToString(insertQuery.lastError());
        }
        return false;
    }

    return true;
}

QVector<BookInfo> DBManager::queryBooks(const QString& keywordName,
                                        const QString& keywordAuthor,
                                        QString* errorMessage) {
    QVector<BookInfo> books;

    if (!ensureConnection(errorMessage)) {
        return books;
    }

    QStringList conditions;
    if (!keywordName.trimmed().isEmpty()) {
        conditions << QStringLiteral("book_name LIKE :book_name");
    }
    if (!keywordAuthor.trimmed().isEmpty()) {
        conditions << QStringLiteral("author LIKE :author");
    }

    QString sql = QStringLiteral(
        "SELECT book_id, book_name, author, publisher, publish_date, stock, status, remark "
        "FROM book_info");

    if (!conditions.isEmpty()) {
        sql.append(QStringLiteral(" WHERE "));
        sql.append(conditions.join(QStringLiteral(" AND ")));
    }

    sql.append(QStringLiteral(" ORDER BY book_name ASC"));

    QSqlQuery query(m_database);
    query.prepare(sql);
    if (!keywordName.trimmed().isEmpty()) {
        query.bindValue(QStringLiteral(":book_name"), QStringLiteral("%1%2%3").arg('%', keywordName.trimmed(), '%'));
    }
    if (!keywordAuthor.trimmed().isEmpty()) {
        query.bindValue(QStringLiteral(":author"), QStringLiteral("%1%2%3").arg('%', keywordAuthor.trimmed(), '%'));
    }

    if (!query.exec()) {
        if (errorMessage) {
            *errorMessage = sqlErrorToString(query.lastError());
        }
        return books;
    }

    while (query.next()) {
        BookInfo book;
        book.bookId = query.value(QStringLiteral("book_id")).toString();
        book.bookName = query.value(QStringLiteral("book_name")).toString();
        book.author = query.value(QStringLiteral("author")).toString();
        book.publisher = query.value(QStringLiteral("publisher")).toString();
        book.publishDate = query.value(QStringLiteral("publish_date")).toDate();
        book.stock = query.value(QStringLiteral("stock")).toInt();
        book.status = query.value(QStringLiteral("status")).toInt();
        book.remark = query.value(QStringLiteral("remark")).toString();
        books.push_back(book);
    }

    return books;
}

bool DBManager::hasOverdueRecords(const QString& userId,
                                  int* overdueCount,
                                  QString* errorMessage) {
    if (!ensureConnection(errorMessage)) {
        return false;
    }

    QSqlQuery query(m_database);
    query.prepare(QStringLiteral(
        "SELECT COUNT(1) AS cnt "
        "FROM borrow_record "
        "WHERE user_id = :user_id AND return_date IS NULL AND due_date < GETDATE()"));
    query.bindValue(QStringLiteral(":user_id"), userId);

    if (!query.exec()) {
        if (errorMessage) {
            *errorMessage = sqlErrorToString(query.lastError());
        }
        return false;
    }

    if (query.next()) {
        int count = query.value(QStringLiteral("cnt")).toInt();
        if (overdueCount) {
            *overdueCount = count;
        }
        return count == 0;
    }

    if (errorMessage) {
        *errorMessage = QStringLiteral("无法确定逾期情况");
    }
    return false;
}

bool DBManager::borrowBook(const QString& userId,
                           const QString& bookId,
                           QString* errorMessage) {
    if (!ensureConnection(errorMessage)) {
        return false;
    }

    if (!m_database.transaction()) {
        if (errorMessage) {
            *errorMessage = sqlErrorToString(m_database.lastError());
        }
        return false;
    }

    QSqlQuery selectQuery(m_database);
    selectQuery.prepare(QStringLiteral(
        "SELECT stock, status FROM book_info WHERE book_id = :book_id"));
    selectQuery.bindValue(QStringLiteral(":book_id"), bookId);

    if (!selectQuery.exec()) {
        m_database.rollback();
        if (errorMessage) {
            *errorMessage = sqlErrorToString(selectQuery.lastError());
        }
        return false;
    }

    if (!selectQuery.next()) {
        m_database.rollback();
        if (errorMessage) {
            *errorMessage = QStringLiteral("指定图书不存在");
        }
        return false;
    }

    int stock = selectQuery.value(QStringLiteral("stock")).toInt();
    int status = selectQuery.value(QStringLiteral("status")).toInt();

    if (stock <= 0 || status != 0) {
        m_database.rollback();
        if (errorMessage) {
            *errorMessage = QStringLiteral("图书暂不可借，请稍后再试");
        }
        return false;
    }

    const int newStock = stock - 1;
    const int newStatus = newStock > 0 ? 0 : 1;

    QSqlQuery updateBookQuery(m_database);
    updateBookQuery.prepare(QStringLiteral(
        "UPDATE book_info SET stock = :stock, status = :status WHERE book_id = :book_id"));
    updateBookQuery.bindValue(QStringLiteral(":stock"), newStock);
    updateBookQuery.bindValue(QStringLiteral(":status"), newStatus);
    updateBookQuery.bindValue(QStringLiteral(":book_id"), bookId);

    if (!updateBookQuery.exec()) {
        m_database.rollback();
        if (errorMessage) {
            *errorMessage = sqlErrorToString(updateBookQuery.lastError());
        }
        return false;
    }

    const QDateTime borrowDate = QDateTime::currentDateTime();
    const QDateTime dueDate = borrowDate.addDays(30);

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare(QStringLiteral(
        "INSERT INTO borrow_record (user_id, book_id, borrow_date, due_date, overdue_days) "
        "VALUES (:user_id, :book_id, :borrow_date, :due_date, 0)"));
    insertQuery.bindValue(QStringLiteral(":user_id"), userId);
    insertQuery.bindValue(QStringLiteral(":book_id"), bookId);
    insertQuery.bindValue(QStringLiteral(":borrow_date"), borrowDate);
    insertQuery.bindValue(QStringLiteral(":due_date"), dueDate);

    if (!insertQuery.exec()) {
        m_database.rollback();
        if (errorMessage) {
            *errorMessage = sqlErrorToString(insertQuery.lastError());
        }
        return false;
    }

    if (!m_database.commit()) {
        m_database.rollback();
        if (errorMessage) {
            *errorMessage = sqlErrorToString(m_database.lastError());
        }
        return false;
    }

    return true;
}

bool DBManager::returnBook(int recordId,
                           QString* errorMessage) {
    if (!ensureConnection(errorMessage)) {
        return false;
    }

    if (!m_database.transaction()) {
        if (errorMessage) {
            *errorMessage = sqlErrorToString(m_database.lastError());
        }
        return false;
    }

    QSqlQuery selectQuery(m_database);
    selectQuery.prepare(QStringLiteral(
        "SELECT book_id, due_date, return_date FROM borrow_record WHERE record_id = :record_id"));
    selectQuery.bindValue(QStringLiteral(":record_id"), recordId);

    if (!selectQuery.exec()) {
        m_database.rollback();
        if (errorMessage) {
            *errorMessage = sqlErrorToString(selectQuery.lastError());
        }
        return false;
    }

    if (!selectQuery.next()) {
        m_database.rollback();
        if (errorMessage) {
            *errorMessage = QStringLiteral("借阅记录不存在");
        }
        return false;
    }

    if (!selectQuery.value(QStringLiteral("return_date")).isNull()) {
        m_database.rollback();
        if (errorMessage) {
            *errorMessage = QStringLiteral("该记录已归还");
        }
        return false;
    }

    const QString bookId = selectQuery.value(QStringLiteral("book_id")).toString();
    const QDateTime dueDate = selectQuery.value(QStringLiteral("due_date")).toDateTime();
    const QDateTime returnDate = QDateTime::currentDateTime();
    const int overdueDays = std::max(0, static_cast<int>(dueDate.daysTo(returnDate)));

    QSqlQuery updateRecordQuery(m_database);
    updateRecordQuery.prepare(QStringLiteral(
        "UPDATE borrow_record "
        "SET return_date = :return_date, overdue_days = :overdue_days "
        "WHERE record_id = :record_id"));
    updateRecordQuery.bindValue(QStringLiteral(":return_date"), returnDate);
    updateRecordQuery.bindValue(QStringLiteral(":overdue_days"), overdueDays);
    updateRecordQuery.bindValue(QStringLiteral(":record_id"), recordId);

    if (!updateRecordQuery.exec()) {
        m_database.rollback();
        if (errorMessage) {
            *errorMessage = sqlErrorToString(updateRecordQuery.lastError());
        }
        return false;
    }

    QSqlQuery updateBookQuery(m_database);
    updateBookQuery.prepare(QStringLiteral(
        "UPDATE book_info SET stock = stock + 1, status = CASE WHEN status = 2 THEN status ELSE 0 END "
        "WHERE book_id = :book_id"));
    updateBookQuery.bindValue(QStringLiteral(":book_id"), bookId);

    if (!updateBookQuery.exec()) {
        m_database.rollback();
        if (errorMessage) {
            *errorMessage = sqlErrorToString(updateBookQuery.lastError());
        }
        return false;
    }

    if (!m_database.commit()) {
        m_database.rollback();
        if (errorMessage) {
            *errorMessage = sqlErrorToString(m_database.lastError());
        }
        return false;
    }

    return true;
}

QVector<BorrowRecord> DBManager::fetchBorrowRecords(const QString& userId,
                                                    bool includeReturned,
                                                    bool adminMode,
                                                    int* overdueCount,
                                                    QString* errorMessage) {
    QVector<BorrowRecord> records;

    if (!ensureConnection(errorMessage)) {
        return records;
    }

    if (!adminMode && userId.isEmpty()) {
        if (errorMessage) {
            *errorMessage = QStringLiteral("缺少用户上下文，无法查询借阅记录");
        }
        return records;
    }

    QString sql = QStringLiteral(
        "SELECT br.record_id, br.user_id, ui.username, br.book_id, bi.book_name, bi.author, "
        "br.borrow_date, br.due_date, br.return_date, br.overdue_days "
        "FROM borrow_record br "
        "INNER JOIN user_info ui ON ui.user_id = br.user_id "
        "INNER JOIN book_info bi ON bi.book_id = br.book_id");

    QStringList conditions;
    if (!userId.isEmpty()) {
        conditions << QStringLiteral("br.user_id = :user_id");
    }
    if (!includeReturned) {
        conditions << QStringLiteral("br.return_date IS NULL");
    }

    if (!conditions.isEmpty()) {
        sql.append(QStringLiteral(" WHERE "));
        sql.append(conditions.join(QStringLiteral(" AND ")));
    }

    sql.append(QStringLiteral(" ORDER BY br.borrow_date DESC"));

    QSqlQuery query(m_database);
    query.prepare(sql);
    if (!userId.isEmpty()) {
        query.bindValue(QStringLiteral(":user_id"), userId);
    }

    if (!query.exec()) {
        if (errorMessage) {
            *errorMessage = sqlErrorToString(query.lastError());
        }
        return records;
    }

    int overdue = 0;

    while (query.next()) {
        BorrowRecord record;
        record.recordId = query.value(QStringLiteral("record_id")).toInt();
        record.userId = query.value(QStringLiteral("user_id")).toString();
        record.username = query.value(QStringLiteral("username")).toString();
        record.bookId = query.value(QStringLiteral("book_id")).toString();
        record.bookName = query.value(QStringLiteral("book_name")).toString();
        record.author = query.value(QStringLiteral("author")).toString();
        record.borrowDate = query.value(QStringLiteral("borrow_date")).toDateTime();
        record.dueDate = query.value(QStringLiteral("due_date")).toDateTime();
        record.returnDate = query.value(QStringLiteral("return_date")).toDateTime();
        record.overdueDays = query.value(QStringLiteral("overdue_days")).toInt();

        if (!record.isReturned() && record.dueDate < QDateTime::currentDateTime()) {
            ++overdue;
        }

        records.push_back(record);
    }

    if (overdueCount) {
        *overdueCount = overdue;
    }

    return records;
}

QVector<BookInfo> DBManager::fetchAllBooks(QString* errorMessage) {
    return queryBooks(QString(), QString(), errorMessage);
}

bool DBManager::addBook(const BookInfo& book,
                        QString* errorMessage) {
    if (!ensureConnection(errorMessage)) {
        return false;
    }

    QSqlQuery checkQuery(m_database);
    checkQuery.prepare(QStringLiteral(
        "SELECT COUNT(1) AS cnt FROM book_info WHERE book_id = :book_id"));
    checkQuery.bindValue(QStringLiteral(":book_id"), book.bookId);

    if (!checkQuery.exec()) {
        if (errorMessage) {
            *errorMessage = sqlErrorToString(checkQuery.lastError());
        }
        return false;
    }

    if (!checkQuery.next()) {
        if (errorMessage) {
            *errorMessage = QStringLiteral("未能读取图书校验结果");
        }
        return false;
    }

    if (checkQuery.value(QStringLiteral("cnt")).toInt() > 0) {
        if (errorMessage) {
            *errorMessage = QStringLiteral("书号已存在，无法重复添加");
        }
        return false;
    }

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare(QStringLiteral(
        "INSERT INTO book_info (book_id, book_name, author, publisher, publish_date, stock, status, remark) "
        "VALUES (:book_id, :book_name, :author, :publisher, :publish_date, :stock, :status, :remark)"));
    insertQuery.bindValue(QStringLiteral(":book_id"), book.bookId);
    insertQuery.bindValue(QStringLiteral(":book_name"), book.bookName);
    insertQuery.bindValue(QStringLiteral(":author"), book.author);
    insertQuery.bindValue(QStringLiteral(":publisher"), book.publisher);
    insertQuery.bindValue(QStringLiteral(":publish_date"), book.publishDate);
    insertQuery.bindValue(QStringLiteral(":stock"), book.stock);
    insertQuery.bindValue(QStringLiteral(":status"), book.status);
    insertQuery.bindValue(QStringLiteral(":remark"), book.remark);

    if (!insertQuery.exec()) {
        if (errorMessage) {
            *errorMessage = sqlErrorToString(insertQuery.lastError());
        }
        return false;
    }

    return true;
}

bool DBManager::updateBook(const BookInfo& book,
                           QString* errorMessage) {
    if (!ensureConnection(errorMessage)) {
        return false;
    }

    QSqlQuery updateQuery(m_database);
    updateQuery.prepare(QStringLiteral(
        "UPDATE book_info "
        "SET book_name = :book_name, author = :author, publisher = :publisher, "
        "publish_date = :publish_date, stock = :stock, status = :status, remark = :remark "
        "WHERE book_id = :book_id"));
    updateQuery.bindValue(QStringLiteral(":book_name"), book.bookName);
    updateQuery.bindValue(QStringLiteral(":author"), book.author);
    updateQuery.bindValue(QStringLiteral(":publisher"), book.publisher);
    updateQuery.bindValue(QStringLiteral(":publish_date"), book.publishDate);
    updateQuery.bindValue(QStringLiteral(":stock"), book.stock);
    updateQuery.bindValue(QStringLiteral(":status"), book.status);
    updateQuery.bindValue(QStringLiteral(":remark"), book.remark);
    updateQuery.bindValue(QStringLiteral(":book_id"), book.bookId);

    if (!updateQuery.exec()) {
        if (errorMessage) {
            *errorMessage = sqlErrorToString(updateQuery.lastError());
        }
        return false;
    }

    if (updateQuery.numRowsAffected() == 0) {
        if (errorMessage) {
            *errorMessage = QStringLiteral("未找到对应图书记录");
        }
        return false;
    }

    return true;
}

bool DBManager::deleteBook(const QString& bookId,
                           QString* errorMessage) {
    if (!ensureConnection(errorMessage)) {
        return false;
    }

    bool hasUnreturned = false;
    if (!bookHasUnreturnedRecords(bookId, &hasUnreturned, errorMessage)) {
        return false;
    }

    if (hasUnreturned) {
        if (errorMessage) {
            *errorMessage = QStringLiteral("存在未归还的借阅记录，无法删除");
        }
        return false;
    }

    QSqlQuery deleteQuery(m_database);
    deleteQuery.prepare(QStringLiteral("DELETE FROM book_info WHERE book_id = :book_id"));
    deleteQuery.bindValue(QStringLiteral(":book_id"), bookId);

    if (!deleteQuery.exec()) {
        if (errorMessage) {
            *errorMessage = sqlErrorToString(deleteQuery.lastError());
        }
        return false;
    }

    if (deleteQuery.numRowsAffected() == 0) {
        if (errorMessage) {
            *errorMessage = QStringLiteral("未找到对应图书记录");
        }
        return false;
    }

    return true;
}

bool DBManager::bookHasUnreturnedRecords(const QString& bookId,
                                         bool* hasUnreturned,
                                         QString* errorMessage) {
    if (!ensureConnection(errorMessage)) {
        return false;
    }

    QSqlQuery query(m_database);
    query.prepare(QStringLiteral(
        "SELECT COUNT(1) AS cnt FROM borrow_record WHERE book_id = :book_id AND return_date IS NULL"));
    query.bindValue(QStringLiteral(":book_id"), bookId);

    if (!query.exec()) {
        if (errorMessage) {
            *errorMessage = sqlErrorToString(query.lastError());
        }
        return false;
    }

    if (!query.next()) {
        if (errorMessage) {
            *errorMessage = QStringLiteral("未能读取借阅记录统计");
        }
        return false;
    }

    const bool result = query.value(QStringLiteral("cnt")).toInt() > 0;
    if (hasUnreturned) {
        *hasUnreturned = result;
    }
    return true;
}

std::optional<BookInfo> DBManager::fetchBookById(const QString& bookId,
                                                 QString* errorMessage) {
    if (!ensureConnection(errorMessage)) {
        return std::nullopt;
    }

    QSqlQuery query(m_database);
    query.prepare(QStringLiteral(
        "SELECT book_id, book_name, author, publisher, publish_date, stock, status, remark "
        "FROM book_info WHERE book_id = :book_id"));
    query.bindValue(QStringLiteral(":book_id"), bookId);

    if (!query.exec()) {
        if (errorMessage) {
            *errorMessage = sqlErrorToString(query.lastError());
        }
        return std::nullopt;
    }

    if (!query.next()) {
        return std::nullopt;
    }

    BookInfo book;
    book.bookId = query.value(QStringLiteral("book_id")).toString();
    book.bookName = query.value(QStringLiteral("book_name")).toString();
    book.author = query.value(QStringLiteral("author")).toString();
    book.publisher = query.value(QStringLiteral("publisher")).toString();
    book.publishDate = query.value(QStringLiteral("publish_date")).toDate();
    book.stock = query.value(QStringLiteral("stock")).toInt();
    book.status = query.value(QStringLiteral("status")).toInt();
    book.remark = query.value(QStringLiteral("remark")).toString();

    return book;
}

bool DBManager::ensureConnection(QString* errorMessage) {
    if (!m_database.isValid()) {
        m_database = QSqlDatabase::addDatabase(QStringLiteral("QODBC"), QStringLiteral("LibraryConnection"));
    }

    if (!m_database.isOpen()) {
        m_database.setDatabaseName(buildOdbcDsn());
    }

    if (m_database.databaseName().isEmpty()) {
        m_database.setDatabaseName(buildOdbcDsn());
    }

    if (!m_database.isOpen()) {
        if (!m_database.open()) {
            if (errorMessage) {
                *errorMessage = sqlErrorToString(m_database.lastError());
            }
            return false;
        }
    }

    return true;
}

QString DBManager::buildOdbcDsn() const {
    return QStringLiteral("Driver={%1};Server=%2,%3;Database=%4;Uid=%5;Pwd=%6;TrustServerCertificate=yes;")
        .arg(m_connectionInfo.driver,
             m_connectionInfo.host,
             QString::number(m_connectionInfo.port),
             m_connectionInfo.databaseName,
             m_connectionInfo.username,
             m_connectionInfo.password);
}

QString DBManager::generateSalt() {
    QString uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
    return uuid.remove(QLatin1Char('-')).left(16);
}

QString DBManager::hashPasswordWithSalt(const QString& password, const QString& salt) {
    const QByteArray input = QString(salt + password).toUtf8();
    return QString::fromLatin1(QCryptographicHash::hash(input, QCryptographicHash::Sha256).toHex());
}

QString DBManager::packSaltedHash(const QString& salt, const QString& hash) {
    return salt + QLatin1Char(':') + hash;
}

bool DBManager::isSaltedPassword(const QString& storedValue) {
    return storedValue.contains(QLatin1Char(':'));
}

bool DBManager::verifyPasswordValue(const QString& password, const QString& storedValue) {
    if (!isSaltedPassword(storedValue)) {
        return storedValue == password;
    }

    const QStringList parts = storedValue.split(QLatin1Char(':'));
    if (parts.size() != 2) {
        return false;
    }

    const QString& salt = parts.at(0);
    const QString& storedHash = parts.at(1);
    const QString candidateHash = hashPasswordWithSalt(password, salt);
    return QString::compare(candidateHash, storedHash, Qt::CaseInsensitive) == 0;
}

QString DBManager::generateUserId() {
    return QUuid::createUuid().toString(QUuid::WithoutBraces);
}

QString DBManager::createSaltedPassword(const QString& password) {
    const QString salt = generateSalt();
    const QString hash = hashPasswordWithSalt(password, salt);
    return packSaltedHash(salt, hash);
}
