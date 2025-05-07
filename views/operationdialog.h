#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class OperationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OperationDialog(QWidget *parent = nullptr, bool needIndex = false);
    QString getValue();
    int getIndex();

private:
    QLineEdit *valueEdit;
    QLineEdit *indexEdit;
    QLabel *indexLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
    bool hasIndex;
};
