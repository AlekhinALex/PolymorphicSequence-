#include "CreateSequenceDialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>

CreateSequenceDialog::CreateSequenceDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Create Sequence");

    nameLineEdit = new QLineEdit(this);
    typeComboBox = new QComboBox(this);
    typeComboBox->addItem("int");
    typeComboBox->addItem("double");

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto *formLayout = new QFormLayout;
    formLayout->addRow("Name:", nameLineEdit);
    formLayout->addRow("Type:", typeComboBox);

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
}

QString CreateSequenceDialog::getSequenceName() const {
    return nameLineEdit->text();
}

QString CreateSequenceDialog::getSequenceType() const {
    return typeComboBox->currentText();
}
