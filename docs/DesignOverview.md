# 图书借阅管理小程序技术说明

本技术说明面向《嵌入式系统软件设计》课程设计验收，概述项目架构、环境要求、数据库设计与核心业务流程，便于教师与验收人员快速了解系统实现情况。

## 项目结构

- `CMakeLists.txt`：VS Code + CMake + Qt5/Qt6 构建配置，自动开启 AUTOUIC/AUTOMOC。
- `include/`：核心类头文件（`DBManager`、`LoginWindow`、`BookQueryWindow`、`BorrowRecordWindow`、`BookManageWindow`、`ReaderMainWindow`、`AdminMainWindow`、数据模型定义）。
- `src/`：对应源文件，实现 UI 逻辑及数据库交互。
- `ui/`：Qt Designer 生成的 `.ui` 界面文件，覆盖登录、主界面、查询、借阅记录、图书维护等窗口。
- `sql/`：SQL Server 2021 初始化脚本（`schema.sql`）与测试数据脚本（`test_data.sql`）。
- `docs/DesignOverview.md`：当前文档，供课程报告引用。

## 开发环境

- 操作系统：Windows 10/11。
- 编译工具链：MSVC 2019+ 或 Mingw-w64，需支持 C++17。
- Qt 框架：Qt 5.15+ 或 Qt 6.5+（已通过 CMake 自动检测）。
- 数据库：Microsoft SQL Server 2021（兼容 SSMS 21），ODBC Driver 17/18。
- IDE：VS Code（配合 CMake Tools / Qt 工具扩展）。

## 构建与运行

1. 安装 Qt 与 SQL Server ODBC 驱动，配置好 `ODBC Driver 17 for SQL Server`（或 18）。
2. 在 SQL Server 中执行 `sql/schema.sql` 初始化数据库，再执行 `sql/test_data.sql` 导入测试数据。
3. 调整 `src/main.cpp` 中 `DBManager::ConnectionInfo` 的服务器、数据库名、账号与密码。
4. 打开 VS Code，选择“CMake: Configure”，生成构建系统；随后执行“CMake: Build”。
5. 运行生成的可执行文件 `LibraryBorrowingApp`，首次启动需成功连通数据库方可进入登录界面。

## 数据库设计要点

| 表名 | 说明 | 关键字段 | 约束 |
| ---- | ---- | -------- | ---- |
| `user_info` | 用户基础信息 | `user_id`（PK）、`username`、`role` | `role` 取值 0/1；`username` 唯一索引 |
| `book_info` | 图书信息 | `book_id`（PK）、`stock`、`status` | `status` 取值 0/1/2；库存非负 |
| `borrow_record` | 借阅流水 | `record_id`（PK）、`user_id`、`book_id` | 外键指向用户/图书；`due_date` 默认 +30 天 |

- 建有模糊检索索引（书名、作者），提升查询效率。
- 通过存储过程 `sp_borrow_book`、`sp_return_book` 实现事务化借阅/归还，避免多窗口竞争导致的数据不一致。

## 核心类职责

- `DBManager`：单例封装所有 SQL 语句，负责连接初始化、参数化查询、事务提交与错误处理。
- `LoginWindow`：登录入口，根据角色调度 `ReaderMainWindow` / `AdminMainWindow`。
- `BookQueryWindow`：图书查询与借阅逻辑，使用 `QTableWidget` 呈现数据，支持模糊检索、库存状态提示。
- `BorrowRecordWindow`：借阅记录浏览、归还操作，自动计算逾期并以红色高亮提示。
- `BookManageWindow`：管理员图书维护，提供新增/修改/删除功能，并在删除前校验未归还记录。
- `ReaderMainWindow` / `AdminMainWindow`：角色主界面，菜单联动子窗口，实现多窗口导航。

## 业务流程

1. **登录验证**：输入用户名/密码/角色，`DBManager::validateLogin` 通过参数化 SQL 检查一致性，失败弹窗提示。
2. **图书查询**：`BookQueryWindow` 调用 `DBManager::queryBooks`，结果填充到 `QTableWidget`。读者模式启用“借阅”按钮，库存不足或状态异常时自动禁用。
3. **借阅登记**：借阅前调用 `DBManager::hasOverdueRecords` 核查逾期，随后进入事务：扣减库存、更新状态、写入 `borrow_record`。
4. **归还操作**：`BorrowRecordWindow` 调用 `DBManager::returnBook`，事务内写入归还时间、逾期天数并恢复库存状态。
5. **逾期提醒**：加载借阅记录时比较 `due_date` 与当前时间，对逾期未归还记录设置红色背景，并在界面顶部显示逾期数量。
6. **图书维护**：管理员可新增图书（校验书号唯一）、修改属性、删除图书（先检查 `borrow_record` 中是否存在未归还记录）。

## 扩展建议

- 如需部署于嵌入式 Windows 终端，可将配置项（数据库地址、端口等）序列化到外部 JSON 配置文件，并在 `DBManager` 中读取。
- 可进一步引入 `QSortFilterProxyModel` 提升表格排序/筛选体验。
- 结合 Qt Resource System 整合应用图标与样式，提升界面一致性。

---

如需撰写课程设计报告，可直接引用本文档中的架构描述与流程分析，并附上主要类的 UML 或时序图进一步说明逻辑。