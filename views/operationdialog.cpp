#include "operationdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QRegularExpressionValidator>

OperationDialog::OperationDialog(QWidget *parent, bool needIndex)
    : QDialog(parent), hasIndex(needIndex)
{
    setWindowTitle("Enter Value");

    valueEdit = new QLineEdit(this);
    valueEdit->setPlaceholderText("Enter value...");

    // Add validator for numeric input
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("[+-]?\\d*\\.?\\d+"), this);
    valueEdit->setValidator(validator);

    if (hasIndex)
    {
        indexEdit = new QLineEdit(this);
        indexEdit->setPlaceholderText("Enter index...");
        indexLabel = new QLabel("Index:", this);

        // Add validator for positive integers
        QRegularExpressionValidator *indexValidator = new QRegularExpressionValidator(QRegularExpression("\\d+"), this);
        indexEdit->setValidator(indexValidator);
    }
    else
    {
        indexEdit = nullptr;
        indexLabel = nullptr;
    }

    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Value:", this));
    mainLayout->addWidget(valueEdit);

    if (hasIndex)
    {
        mainLayout->addWidget(indexLabel);
        mainLayout->addWidget(indexEdit);
    }

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString OperationDialog::getValue()
{
    if (valueEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Invalid Input", "Please enter a value.");
        return QString();
    }

    bool ok;
    double value = valueEdit->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid number.");
        return QString();
    }
    return valueEdit->text();
}

int OperationDialog::getIndex()
{
    if (!hasIndex || !indexEdit)
    {
        return -1;
    }

    if (indexEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Invalid Input", "Please enter an index.");
        return -1;
    }

    bool ok;
    int index = indexEdit->text().toInt(&ok);
    if (!ok || index < 0)
    {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid non-negative integer.");
        return -1;
    }
    return index;
}
