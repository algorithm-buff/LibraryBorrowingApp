cmake_minimum_required(VERSION 3.21)

project(LibraryBorrowingApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if (MSVC)
    add_compile_options(/W4 /permissive- /Zc:__cplusplus /utf-8)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(Qt6 COMPONENTS Core Gui Widgets Sql QUIET)
if (Qt6_FOUND)
    set(QT_LIBS Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Sql)
else()
    find_package(Qt5 COMPONENTS Core Gui Widgets Sql REQUIRED)
    set(QT_LIBS Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Sql)
endif()

set(SOURCE_FILES
    src/main.cpp
    src/dbmanager.cpp
    src/loginwindow.cpp
    src/bookquerywindow.cpp
    src/borrowrecordwindow.cpp
    src/bookmanagewindow.cpp
    src/readermainwindow.cpp
    src/adminmainwindow.cpp
    src/registerdialog.cpp
    src/bookeditordialog.cpp
)

set(UI_FILES
    ui/loginwindow.ui
    ui/bookquerywindow.ui
    ui/borrowrecordwindow.ui
    ui/bookmanagewindow.ui
    ui/readermainwindow.ui
    ui/adminmainwindow.ui
    ui/registerdialog.ui
    ui/bookeditordialog.ui
)

set(HEADER_FILES
    include/dbmanager.h
    include/loginwindow.h
    include/bookquerywindow.h
    include/borrowrecordwindow.h
    include/bookmanagewindow.h
    include/readermainwindow.h
    include/adminmainwindow.h
    include/registerdialog.h
    include/bookeditordialog.h
    include/models.h
)

add_executable(LibraryBorrowingApp
    ${SOURCE_FILES}
    ${UI_FILES}
    ${HEADER_FILES}
)

set_target_properties(LibraryBorrowingApp PROPERTIES
    AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/ui"
)

target_include_directories(LibraryBorrowingApp PRIVATE include)

target_link_libraries(LibraryBorrowingApp PRIVATE ${QT_LIBS})

if (WIN32)
    target_compile_definitions(LibraryBorrowingApp PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

message(STATUS "Configured LibraryBorrowingApp with Qt libraries: ${QT_LIBS}")
