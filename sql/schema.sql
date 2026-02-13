-- 数据库初始化脚本：创建嵌入式图书借阅管理系统的结构
-- 适用于 Microsoft SQL Server 2021 及更高版本
GO

IF DB_ID(N'LibraryDB') IS NULL
BEGIN
    PRINT N'创建数据库 LibraryDB';
    CREATE DATABASE LibraryDB;
END;
GO

USE LibraryDB;
GO

PRINT N'清理旧表定义（若存在）';
IF OBJECT_ID(N'dbo.borrow_record', N'U') IS NOT NULL DROP TABLE dbo.borrow_record;
IF OBJECT_ID(N'dbo.book_info', N'U') IS NOT NULL DROP TABLE dbo.book_info;
IF OBJECT_ID(N'dbo.user_info', N'U') IS NOT NULL DROP TABLE dbo.user_info;
GO

PRINT N'创建表 dbo.user_info';
CREATE TABLE dbo.user_info (
    user_id      VARCHAR(20)  NOT NULL PRIMARY KEY,
    username     VARCHAR(50)  NOT NULL,
    password     VARCHAR(50)  NOT NULL,
    role         INT          NOT NULL CONSTRAINT CK_user_info_role CHECK (role IN (0, 1)),
    phone        VARCHAR(20)  NULL,
    create_time  DATETIME     NOT NULL CONSTRAINT DF_user_info_create_time DEFAULT (GETDATE())
);
GO

CREATE UNIQUE INDEX IX_user_info_username ON dbo.user_info(username);
GO

PRINT N'创建表 dbo.book_info';
CREATE TABLE dbo.book_info (
    book_id      VARCHAR(20)   NOT NULL PRIMARY KEY,
    book_name    VARCHAR(100)  NOT NULL,
    author       VARCHAR(50)   NOT NULL,
    publisher    VARCHAR(100)  NULL,
    publish_date DATE          NULL,
    stock        INT           NOT NULL CONSTRAINT DF_book_info_stock DEFAULT (0) CHECK (stock >= 0),
    status       INT           NOT NULL CONSTRAINT CK_book_info_status CHECK (status IN (0, 1, 2)),
    remark       VARCHAR(200)  NULL
);
GO

CREATE INDEX IX_book_info_name ON dbo.book_info(book_name);
CREATE INDEX IX_book_info_author ON dbo.book_info(author);
GO

PRINT N'创建表 dbo.borrow_record';
CREATE TABLE dbo.borrow_record (
    record_id     INT          NOT NULL IDENTITY(1,1) PRIMARY KEY,
    user_id       VARCHAR(20)  NOT NULL,
    book_id       VARCHAR(20)  NOT NULL,
    borrow_date   DATETIME     NOT NULL CONSTRAINT DF_borrow_record_borrow_date DEFAULT (GETDATE()),
    return_date   DATETIME     NULL,
    due_date      DATETIME     NOT NULL CONSTRAINT DF_borrow_record_due_date DEFAULT (DATEADD(DAY, 30, GETDATE())),
    overdue_days  INT          NOT NULL CONSTRAINT DF_borrow_record_overdue DEFAULT (0) CHECK (overdue_days >= 0),
    CONSTRAINT FK_borrow_record_user FOREIGN KEY (user_id) REFERENCES dbo.user_info(user_id),
    CONSTRAINT FK_borrow_record_book FOREIGN KEY (book_id) REFERENCES dbo.book_info(book_id)
);
GO

CREATE INDEX IX_borrow_record_user ON dbo.borrow_record(user_id, return_date);
CREATE INDEX IX_borrow_record_book ON dbo.borrow_record(book_id, return_date);
GO

PRINT N'创建借阅事务存储过程 sp_borrow_book';
CREATE OR ALTER PROCEDURE dbo.sp_borrow_book
    @UserId VARCHAR(20),
    @BookId VARCHAR(20)
AS
BEGIN
    SET NOCOUNT ON;
    BEGIN TRY
        BEGIN TRANSACTION;

        DECLARE @Stock INT;
        DECLARE @Status INT;

        SELECT @Stock = stock, @Status = status
        FROM dbo.book_info WITH (UPDLOCK, HOLDLOCK)
        WHERE book_id = @BookId;

        IF @Stock IS NULL
        BEGIN
            RAISERROR(N'指定图书不存在', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END;

        IF @Stock <= 0 OR @Status <> 0
        BEGIN
            RAISERROR(N'图书库存不足或状态不可借', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END;

        UPDATE dbo.book_info
        SET stock = @Stock - 1,
            status = CASE WHEN @Stock - 1 > 0 THEN 0 ELSE 1 END
        WHERE book_id = @BookId;

        INSERT INTO dbo.borrow_record(user_id, book_id, borrow_date, due_date, overdue_days)
        VALUES (@UserId, @BookId, GETDATE(), DATEADD(DAY, 30, GETDATE()), 0);

        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        IF XACT_STATE() <> 0 ROLLBACK TRANSACTION;
        DECLARE @ErrMsg NVARCHAR(4000) = ERROR_MESSAGE();
        DECLARE @ErrSeverity INT = ERROR_SEVERITY();
        DECLARE @ErrState INT = ERROR_STATE();
        RAISERROR(@ErrMsg, @ErrSeverity, @ErrState);
    END CATCH;
END;
GO

PRINT N'创建归还事务存储过程 sp_return_book';
CREATE OR ALTER PROCEDURE dbo.sp_return_book
    @RecordId INT
AS
BEGIN
    SET NOCOUNT ON;
    BEGIN TRY
        BEGIN TRANSACTION;

        DECLARE @BookId VARCHAR(20);
        DECLARE @ReturnDate DATETIME;
        DECLARE @DueDate DATETIME;

        SELECT @BookId = book_id,
               @ReturnDate = return_date,
               @DueDate = due_date
        FROM dbo.borrow_record WITH (UPDLOCK, HOLDLOCK)
        WHERE record_id = @RecordId;

        IF @BookId IS NULL
        BEGIN
            RAISERROR(N'借阅记录不存在', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END;

        IF @ReturnDate IS NOT NULL
        BEGIN
            RAISERROR(N'该记录已归还', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END;

        DECLARE @Now DATETIME = GETDATE();
        DECLARE @OverdueDays INT = CASE WHEN @Now > @DueDate THEN DATEDIFF(DAY, @DueDate, @Now) ELSE 0 END;

        UPDATE dbo.borrow_record
        SET return_date = @Now,
            overdue_days = @OverdueDays
        WHERE record_id = @RecordId;

        UPDATE dbo.book_info
        SET stock = stock + 1,
            status = CASE WHEN status = 2 THEN status ELSE 0 END
        WHERE book_id = @BookId;

        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        IF XACT_STATE() <> 0 ROLLBACK TRANSACTION;
        DECLARE @ErrMsg NVARCHAR(4000) = ERROR_MESSAGE();
        DECLARE @ErrSeverity INT = ERROR_SEVERITY();
        DECLARE @ErrState INT = ERROR_STATE();
        RAISERROR(@ErrMsg, @ErrSeverity, @ErrState);
    END CATCH;
END;
GO

PRINT N'初始化脚本完成';
GO
