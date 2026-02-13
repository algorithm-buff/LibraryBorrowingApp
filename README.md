# LibraryBorrowingApp

轻量级跨平台图书馆借阅管理系统，专为中小型图书馆/校园图书室设计，支持图书入库、借阅登记、归还审核、读者信息管理等核心功能，基于 C/C++ 开发，通过 CMake 实现跨平台编译。

## 🌟 核心功能
- **图书管理**：图书信息录入、查询、修改、删除，支持按书名/作者/ISBN 检索；
- **读者管理**：读者信息（姓名/学号/联系方式）增删改查，支持读者身份验证；
- **借阅管理**：借阅登记、归还审核，自动记录借阅/归还时间，支持逾期提醒；
- **数据存储**：基于 SQL 本地存储（如 SQLite），数据持久化，无需额外数据库服务；
- **日志记录**：自动记录操作日志，方便追溯借阅/管理行为。

## 🛠 技术栈
- 开发语言：C/C++（C++11 及以上）；
- 构建工具：CMake（3.10 及以上）；
- 数据存储：SQLite（或其他轻量级 SQL 数据库）；
- 编译环境：MinGW（Windows）/ GCC（Linux）/ Clang（Mac）；
- 依赖：无第三方重型依赖，开箱即用。

## 📦 环境准备
### 1. 安装依赖
- **Windows**：安装 [Git for Windows](https://git-scm.com/download/win) + [MinGW-w64](https://sourceforge.net/projects/mingw-w64/)（配置环境变量）；
- **Linux**：
  ```bash
  sudo apt update && sudo apt install git cmake gcc g++ sqlite3 libsqlite3-dev