#ifndef BOOKEDITORDIALOG_H
#define BOOKEDITORDIALOG_H

#include <QDialog>

#include "models.h"

namespace Ui {
class BookEditorDialog;
}

// BookEditorDialog collects and validates book information for create/update flows.
class BookEditorDialog : public QDialog {
    Q_OBJECT
public:
    enum class Mode {
        Create,
        Edit
    };

    explicit BookEditorDialog(Mode mode, QWidget* parent = nullptr);
    ~BookEditorDialog() override;

    void setBookData(const BookInfo& book);
    BookInfo bookData() const;

private slots:
    void handleSubmit();

private:
    void applyMode();
    bool validateInputs(QString* errorMessage) const;

    Ui::BookEditorDialog* ui;
    Mode m_mode;
};

#endif // BOOKEDITORDIALOG_H
