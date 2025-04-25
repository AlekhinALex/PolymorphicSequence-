#include "operationdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

OperationDialog::OperationDialog(QWidget *parent, bool needIndex)
    : QDialog(parent), hasIndex(needIndex)
{
    setWindowTitle("Enter Value");

    valueEdit = new QLineEdit(this);
    valueEdit->setPlaceholderText("Enter value...");

    if (hasIndex) {
        indexEdit = new QLineEdit(this);
        indexEdit->setPlaceholderText("Enter index...");
        indexLabel = new QLabel("Index:", this);
    } else {
        indexEdit = nullptr;
        indexLabel = nullptr;
    }

    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Value:", this));
    mainLayout->addWidget(valueEdit);

    if (hasIndex) {
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

QString OperationDialog::getValue() {
    bool ok;
    double value = valueEdit->text().toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid value.");
        return QString();
    }
    return QString::number(value);
}

int OperationDialog::getIndex() {
    if (!hasIndex || !indexEdit) return -1;
    bool ok;
    int index = indexEdit->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid index.");
        return -1;
    }
    return index;
}
