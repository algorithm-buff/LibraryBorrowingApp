#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QVector>

#include <optional>

#include "models.h"

// DBManager centralizes every database interaction and hides raw SQL usage from the UI layer.
class DBManager : public QObject {
    Q_OBJECT
public:
    struct ConnectionInfo {
        QString driver = QStringLiteral("ODBC Driver 17 for SQL Server");
        QString host = QStringLiteral("localhost");
        int port = 1433;
        QString databaseName = QStringLiteral("LibraryDB");
        QString username = QStringLiteral("sa");
        QString password = QStringLiteral("892698638abc.");
    };

    static DBManager& instance();

    void setConnectionInfo(const ConnectionInfo& info);
    const ConnectionInfo& connectionInfo() const;

    bool open(QString* errorMessage = nullptr);
    void close();

    bool validateLogin(const QString& username,
                       const QString& password,
                       int role,
                       QString* userId,
                       QString* fullUsername,
                       QString* errorMessage = nullptr);

    bool registerUser(const QString& username,
                      const QString& password,
                      const QString& phone,
                      QString* errorMessage = nullptr);

    QVector<BookInfo> queryBooks(const QString& keywordName,
                                 const QString& keywordAuthor,
                                 QString* errorMessage = nullptr);

    bool hasOverdueRecords(const QString& userId,
                           int* overdueCount,
                           QString* errorMessage = nullptr);

    bool borrowBook(const QString& userId,
                    const QString& bookId,
                    QString* errorMessage = nullptr);

    bool returnBook(int recordId,
                    QString* errorMessage = nullptr);

    QVector<BorrowRecord> fetchBorrowRecords(const QString& userId,
                                             bool includeReturned,
                                             bool adminMode,
                                             int* overdueCount,
                                             QString* errorMessage = nullptr);

    QVector<BookInfo> fetchAllBooks(QString* errorMessage = nullptr);

    bool addBook(const BookInfo& book,
                 QString* errorMessage = nullptr);

    bool updateBook(const BookInfo& book,
                    QString* errorMessage = nullptr);

    bool deleteBook(const QString& bookId,
                    QString* errorMessage = nullptr);

    bool bookHasUnreturnedRecords(const QString& bookId,
                                  bool* hasUnreturned,
                                  QString* errorMessage = nullptr);

    std::optional<BookInfo> fetchBookById(const QString& bookId,
                                          QString* errorMessage = nullptr);

private:
    explicit DBManager(QObject* parent = nullptr);

    bool ensureConnection(QString* errorMessage = nullptr);
    QString buildOdbcDsn() const;
    static QString generateSalt();
    static QString hashPasswordWithSalt(const QString& password, const QString& salt);
    static QString packSaltedHash(const QString& salt, const QString& hash);
    static bool isSaltedPassword(const QString& storedValue);
    static bool verifyPasswordValue(const QString& password, const QString& storedValue);
    static QString generateUserId();
    static QString createSaltedPassword(const QString& password);

    QSqlDatabase m_database;
    ConnectionInfo m_connectionInfo;
};

#endif // DBMANAGER_H
