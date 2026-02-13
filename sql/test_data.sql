-- 测试数据装载脚本：向 LibraryDB 注入初始数据
USE LibraryDB;
GO

PRINT N'清理现有数据';
DELETE FROM dbo.borrow_record;
DELETE FROM dbo.book_info;
DELETE FROM dbo.user_info;
GO

PRINT N'插入用户数据';
INSERT INTO dbo.user_info (user_id, username, password, role, phone)
VALUES
    ('admin', 'admin', '123456', 1, '13800000000'),
    ('user1', 'user1', '123456', 0, '13900000001');
GO

PRINT N'插入图书数据';
INSERT INTO dbo.book_info (book_id, book_name, author, publisher, publish_date, stock, status, remark)
VALUES
    ('BK001', N'嵌入式系统设计实战', N'张华', N'电子工业出版社', '2022-03-15', 3, 0, N'课程指定教材'),
    ('BK002', N'Qt 跨平台开发教程', N'李明', N'人民邮电出版社', '2021-09-01', 2, 0, N'附带源码'),
    ('BK003', N'SQL Server 高级管理', N'王磊', N'机械工业出版社', '2020-07-20', 1, 0, N'管理人员参考');
GO

PRINT N'模拟一次借阅操作';
EXEC dbo.sp_borrow_book @UserId = 'user1', @BookId = 'BK001';
GO

PRINT N'测试数据已准备就绪';
GO
