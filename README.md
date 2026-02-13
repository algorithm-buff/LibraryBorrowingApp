# LibraryBorrowingApp

轻量级图书馆借阅管理系统，支持图书入库、借阅登记、归还审核、读者信息管理等核心功能，基于 C/C++ 开发，CMake 构建，仅适配 Windows 平台。

## 🌟 核心功能
- 图书信息增删改查（按书名/ISBN检索）；
- 读者信息管理（姓名/学号/联系方式）；
- 借阅/归还登记，记录借阅时间；
- 本地文件存储数据，无需数据库。

## 🛠 环境准备
Windows 需安装：
- Git for Windows：https://git-scm.com/download/win
- MinGW-w64：https://sourceforge.net/projects/mingw-w64/（配置bin目录到系统环境变量）
- CMake：3.10+（官网下载：https://cmake.org/download/）

## 🔨 编译与运行
```bash
# 克隆仓库（替换成你的仓库地址）
git clone git@github.com:zhangsan123/LibraryBorrowingApp.git
cd LibraryBorrowingApp

# 创建编译目录
mkdir build && cd build

# 生成Makefile
cmake .. -G "MinGW Makefiles"

# 编译
mingw32-make

# 运行
LibraryBorrowingApp.exe