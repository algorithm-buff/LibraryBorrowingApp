#ifndef MODELS_H
#define MODELS_H

#include <QString>
#include <QDate>
#include <QDateTime>

// BookInfo carries the basic metadata and availability attributes of a single book item.
struct BookInfo {
    QString bookId;
    QString bookName;
    QString author;
    QString publisher;
    QDate publishDate;
    int stock = 0;
    int status = 0; // 0=available, 1=borrowed, 2=damaged
    QString remark;
};

// BorrowRecord aggregates information needed by both reader and admin views.
struct BorrowRecord {
    int recordId = 0;
    QString userId;
    QString username;
    QString bookId;
    QString bookName;
    QString author;
    QDateTime borrowDate;
    QDateTime dueDate;
    QDateTime returnDate;
    int overdueDays = 0;

    bool isReturned() const {
        return returnDate.isValid();
    }
};

#endif // MODELS_H
