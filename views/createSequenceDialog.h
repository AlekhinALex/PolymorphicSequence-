#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QDialogButtonBox>

class CreateSequenceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateSequenceDialog(QWidget *parent = nullptr);
    QString getSequenceName() const;
    QString getSequenceType() const;

private:
    QLineEdit *nameLineEdit;
    QComboBox *typeComboBox;
    QDialogButtonBox *buttonBox;
};
