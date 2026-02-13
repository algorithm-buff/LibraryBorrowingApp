#include <QApplication>
#include <QMessageBox>
#include <QString>

#include "dbmanager.h"
#include "loginwindow.h"

namespace {
QString buildLightStyleSheet() {
    return QStringLiteral(R"(QWidget {
        background-color: #f7f9fc;
        color: #2f3a4c;
        font-family: "Segoe UI", "Microsoft YaHei";
        font-size: 14px;
    }
    QMainWindow, QDialog {
        background-color: #f7f9fc;
    }
    QLabel {
        font-weight: 500;
    }
    QGroupBox {
        border: 1px solid #d9e2f2;
        border-radius: 10px;
        margin-top: 12px;
        background: #ffffff;
    }
    QGroupBox::title {
        subcontrol-origin: margin;
        left: 16px;
        padding: 0 4px;
        background: #f7f9fc;
        font-weight: 600;
    }
    QPushButton {
        background-color: #4c8bf5;
        color: #ffffff;
        border: none;
        border-radius: 8px;
        padding: 8px 16px;
        font-weight: 600;
    }
    QPushButton:hover {
        background-color: #5c9cff;
    }
    QPushButton:pressed {
        background-color: #3a6fd9;
    }
    QPushButton:disabled {
        background-color: #bac6dd;
        color: #f7f9fc;
    }
    QLineEdit, QComboBox, QTextEdit, QPlainTextEdit, QSpinBox, QDoubleSpinBox, QDateEdit, QTimeEdit {
        background: #ffffff;
        border: 1px solid #cfd6e6;
        border-radius: 8px;
        padding: 6px 10px;
        selection-background-color: #4c8bf5;
        selection-color: #ffffff;
    }
    QLineEdit:focus, QComboBox:focus, QTextEdit:focus, QPlainTextEdit:focus, QSpinBox:focus, QDoubleSpinBox:focus, QDateEdit:focus, QTimeEdit:focus {
        border: 1px solid #4c8bf5;
        box-shadow: 0 0 0 3px rgba(76, 139, 245, 0.15);
    }
    QTableView {
        background: #ffffff;
        border: 1px solid #d9e2f2;
        border-radius: 10px;
        gridline-color: #e2e8f5;
        alternate-background-color: #f0f4ff;
        selection-background-color: #d4e4ff;
        selection-color: #1f2733;
    }
    QHeaderView::section {
        background-color: #eef3ff;
        color: #1f2733;
        border: none;
        padding: 10px 12px;
        font-weight: 600;
    }
    QStatusBar {
        background: #edf2fb;
        border-top: 1px solid #d9e2f2;
    }
    QMessageBox {
        background: #ffffff;
    }
    QScrollBar:vertical {
        background: transparent;
        width: 12px;
        margin: 4px;
    }
    QScrollBar::handle:vertical {
        background: #c8d7f4;
        border-radius: 6px;
        min-height: 24px;
    }
    QScrollBar::handle:vertical:hover {
        background: #a9c2f0;
    }
    QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
        height: 0;
    }
    QScrollBar:horizontal {
        background: transparent;
        height: 12px;
        margin: 4px;
    }
    QScrollBar::handle:horizontal {
        background: #c8d7f4;
        border-radius: 6px;
        min-width: 24px;
    }
    QScrollBar::handle:horizontal:hover {
        background: #a9c2f0;
    }
    QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
        width: 0;
    })");
}
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setStyleSheet(buildLightStyleSheet());

    DBManager::ConnectionInfo connection;
    // TODO: Adjust credentials according to the actual SQL Server deployment.
    DBManager::instance().setConnectionInfo(connection);

    QString errorMessage;
    if (!DBManager::instance().open(&errorMessage)) {
        QMessageBox::critical(nullptr,
                              QObject::tr("数据库连接失败"),
                              QObject::tr("无法连接到数据库: %1").arg(errorMessage));
        return EXIT_FAILURE;
    }

    LoginWindow login;
    login.show();

    int result = app.exec();

    DBManager::instance().close();
    return result;
}
