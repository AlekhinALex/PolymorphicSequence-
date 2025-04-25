#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDateTime>
#include <QInputDialog>
#include "operationdialog.h"
#include <QRegularExpressionValidator>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controller = new MainController(this);

    connect(controller, &MainController::sequenceCreated, this, &MainWindow::onSequenceCreated);
    connect(controller, &MainController::sequenceRemoved, this, &MainWindow::onSequenceRemoved);
    connect(controller, &MainController::sequenceChanged, this, &MainWindow::onSequenceChanged);
    connect(controller, &MainController::errorOccurred, this, &MainWindow::onErrorOccurred);

    connect(ui->arraySequenceButton, &QPushButton::clicked, this, &MainWindow::onArraySequenceButtonClicked);
    connect(ui->listSequenceButton, &QPushButton::clicked, this, &MainWindow::onListSequenceButtonClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteButtonClicked);

    connect(ui->appendButton, &QPushButton::clicked, this, &MainWindow::onAppendButtonClicked);
    connect(ui->prependButton, &QPushButton::clicked, this, &MainWindow::onPrependButtonClicked);
    connect(ui->insertAtButton, &QPushButton::clicked, this, &MainWindow::onInsertAtButtonClicked);
    connect(ui->setButton, &QPushButton::clicked, this, &MainWindow::onSetButtonClicked);
    connect(ui->getButton, &QPushButton::clicked, this, &MainWindow::onGetButtonClicked);

    connect(ui->appendImmutableButton, &QPushButton::clicked, this, &MainWindow::appendImmutable);
    connect(ui->prependImmutableButton, &QPushButton::clicked, this, &MainWindow::prependImmutable);
    connect(ui->insertAtImmutableButton, &QPushButton::clicked, this, &MainWindow::insertAtImmutable);
    connect(ui->setImmutableButton, &QPushButton::clicked, this, &MainWindow::setImmutable);
    connect(ui->concatImmutableButton, &QPushButton::clicked, this, &MainWindow::concatImmutable);
    connect(ui->concatButton, &QPushButton::clicked, this, &MainWindow::concat);

    connect(ui->showSequenceButton, &QPushButton::clicked, this, &MainWindow::onShowSequenceButtonClicked);
    connect(ui->sequenceListWidget, &QListWidget::itemClicked, this, &MainWindow::onSequenceSelected);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onSequenceCreated(const QString &name) {
    ui->sequenceListWidget->addItem(name);
    logAction(QString("Sequence created: %1").arg(name));
}

void MainWindow::onSequenceRemoved(const QString &name) {
    for (int i = 0; i < ui->sequenceListWidget->count(); ++i) {
        if (ui->sequenceListWidget->item(i)->text() == name) {
            delete ui->sequenceListWidget->takeItem(i);
            logAction(QString("Sequence removed: %1").arg(name));
            return;
        }
    }
    onErrorOccurred("Sequence not found in UI list");
}

void MainWindow::onSequenceChanged(const QString &name) {
    logAction(QString("Sequence changed: %1").arg(name));
}

void MainWindow::onErrorOccurred(const QString &message) {
    QMessageBox::critical(this, "Error", message);
    logAction("Error: " + message);
}

QString MainWindow::askSequenceType() {
    QStringList types = {"int", "double"};
    bool ok;
    QString type = QInputDialog::getItem(this, "Select Value Type", "Choose value type:", types, 0, false, &ok);
    if (!ok || type.isEmpty()) throw std::runtime_error("No value type selected");
    return type;
}

void MainWindow::onArraySequenceButtonClicked() {
    bool ok;
    QString name = QInputDialog::getText(this, "Create Array Sequence", "Enter sequence name:", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
        //QString typeStr = askSequenceType();
        MainController::ValueType type = stringToValueType(askSequenceType());
        controller->createArraySequence(name.toStdString(), type);
    }
}

void MainWindow::onListSequenceButtonClicked() {
    bool ok;
    QString name = QInputDialog::getText(this, "Create List Sequence", "Enter sequence name:", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
        //QString typeStr = askSequenceType();
        MainController::ValueType type = stringToValueType(askSequenceType());
        controller->createArraySequence(name.toStdString(), type);
    }
}

void MainWindow::onDeleteButtonClicked() {
    QListWidgetItem* item = ui->sequenceListWidget->currentItem();
    if (!item) {
        onErrorOccurred("No sequence selected to delete.");
        return;
    }
    controller->removeSequence(item->text().toStdString());
}

void MainWindow::onAppendButtonClicked() {
    OperationDialog dialog(this, false);
    if (dialog.exec() == QDialog::Accepted) {
        QListWidgetItem* item = ui->sequenceListWidget->currentItem();
        if (!item) return onErrorOccurred("No sequence selected");
        controller->appendToSequence(item->text().toStdString(), dialog.getValue());
        logAction(QString("Appended value to %1").arg(item->text()));
    }
}

void MainWindow::onPrependButtonClicked() {
    OperationDialog dialog(this, false);
    if (dialog.exec() == QDialog::Accepted) {
        QListWidgetItem* item = ui->sequenceListWidget->currentItem();
        if (!item) return onErrorOccurred("No sequence selected");
        controller->prependToSequence(item->text().toStdString(), dialog.getValue());
        logAction(QString("Prepended value to %1").arg(item->text()));
    }
}

void MainWindow::onInsertAtButtonClicked() {
    OperationDialog dialog(this, true);
    if (dialog.exec() == QDialog::Accepted) {
        QListWidgetItem* item = ui->sequenceListWidget->currentItem();
        if (!item) return onErrorOccurred("No sequence selected");
        controller->insertAtSequence(item->text().toStdString(), dialog.getIndex(), dialog.getValue());
        logAction(QString("Inserted value at index %1 in %2").arg(dialog.getIndex()).arg(item->text()));
    }
}

void MainWindow::onSetButtonClicked() {
    OperationDialog dialog(this, true);
    if (dialog.exec() == QDialog::Accepted) {
        QListWidgetItem* item = ui->sequenceListWidget->currentItem();
        if (!item) return onErrorOccurred("No sequence selected");
        controller->setInSequence(item->text().toStdString(), dialog.getIndex(), dialog.getValue());
        logAction(QString("Set value at index %1 in %2").arg(dialog.getIndex()).arg(item->text()));
    }
}

void MainWindow::onGetButtonClicked() {
    OperationDialog dialog(this, true);
    if (dialog.exec() == QDialog::Accepted) {
        QListWidgetItem* item = ui->sequenceListWidget->currentItem();
        if (!item) return onErrorOccurred("No sequence selected");
        QVariant value = controller->getFromSequence(item->text().toStdString(), dialog.getIndex());
        showSequenceValueDialog(item->text(), dialog.getIndex(), value.toString());
    }
}

void MainWindow::onShowSequenceButtonClicked() {
    QListWidgetItem* item = ui->sequenceListWidget->currentItem();
    if (!item) return onErrorOccurred("No sequence selected");
    QString contents = controller->getSequenceAsString(item->text().toStdString());
    QMessageBox::information(this, "Sequence Contents", QString("Sequence %1:\n%2").arg(item->text()).arg(contents));
    logAction(QString("Displayed sequence: %1").arg(item->text()));
}

void MainWindow::showSequenceValueDialog(const QString &name, int index, const QString &value) {
    QMessageBox::information(this, "Sequence Value",
                             QString("Sequence %1\nIndex: %2\nValue: %3").arg(name).arg(index).arg(value));
    logAction(QString("Got value at index %1 from %2: %3").arg(index).arg(name).arg(value));
}

void MainWindow::logAction(const QString &action) {
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->logTextEdit->append(QString("[%1] %2").arg(timestamp).arg(action));
}

void MainWindow::onSequenceSelected(QListWidgetItem* item) {
    if (item) {
        selectedSequenceName = item->text().toStdString();
        logAction(QString("Selected sequence: %1").arg(item->text()));
    }
}

void MainWindow::showSequenceDialog(const QString& content) {
    QMessageBox::information(this, "Sequence", content);
}

QVariant MainWindow::getValidatedValue() const {
    bool ok;
    double value = QInputDialog::getDouble(nullptr, "Enter Value", "Value:", 0, -1e9, 1e9, 2, &ok);
    if (!ok) throw std::invalid_argument("Invalid value input");
    return value;
}

QString MainWindow::generateCopyName(const QString& baseName) {
    int copyNumber = 1;
    QString newName;
    do {
        newName = QString("%1 (копия %2)").arg(baseName).arg(copyNumber);
        copyNumber++;
    } while (controller->sequenceExists(newName.toStdString()));
    return newName;
}

void MainWindow::appendImmutable() {
    try {
        QListWidgetItem* item = ui->sequenceListWidget->currentItem();
        if (!item) throw std::runtime_error("No sequence selected");

        OperationDialog dialog(this, false);
        if (dialog.exec() == QDialog::Accepted) {
            QString originalName = item->text();
            QString newName = generateCopyName(originalName);
            controller->appendToImmutableSequence(originalName.toStdString(), dialog.getValue(), newName.toStdString());
            logAction(QString("Immutable Append: created %1 from %2").arg(newName, originalName));
        }
    } catch (const std::exception& e) {
        onErrorOccurred(QString("Immutable Append error: %1").arg(e.what()));
    }
}

void MainWindow::prependImmutable() {
    try {
        QListWidgetItem* item = ui->sequenceListWidget->currentItem();
        if (!item) throw std::runtime_error("No sequence selected");

        OperationDialog dialog(this, false);
        if (dialog.exec() == QDialog::Accepted) {
            QString originalName = item->text();
            QString newName = generateCopyName(originalName);
            controller->prependToImmutableSequence(originalName.toStdString(), dialog.getValue(), newName.toStdString());
            logAction(QString("Immutable Prepend: created %1 from %2").arg(newName, originalName));
        }
    } catch (const std::exception& e) {
        onErrorOccurred(QString("Immutable Prepend error: %1").arg(e.what()));
    }
}

void MainWindow::insertAtImmutable() {
    try {
        QListWidgetItem* item = ui->sequenceListWidget->currentItem();
        if (!item) throw std::runtime_error("No sequence selected");

        OperationDialog dialog(this, true);
        if (dialog.exec() == QDialog::Accepted) {
            QString originalName = item->text();
            QString newName = generateCopyName(originalName);
            controller->insertAtImmutableSequence(originalName.toStdString(), dialog.getIndex(), dialog.getValue(), newName.toStdString());
            logAction(QString("Immutable Insert: created %1 from %2").arg(newName, originalName));
        }
    } catch (const std::exception& e) {
        onErrorOccurred(QString("Immutable Insert error: %1").arg(e.what()));
    }
}

void MainWindow::setImmutable() {
    try {
        QListWidgetItem* item = ui->sequenceListWidget->currentItem();
        if (!item) throw std::runtime_error("No sequence selected");

        OperationDialog dialog(this, true);
        if (dialog.exec() == QDialog::Accepted) {
            QString originalName = item->text();
            QString newName = generateCopyName(originalName);
            controller->setInImmutableSequence(originalName.toStdString(), dialog.getIndex(), dialog.getValue(), newName.toStdString());
            logAction(QString("Immutable Set: created %1 from %2").arg(newName, originalName));
        }
    } catch (const std::exception& e) {
        onErrorOccurred(QString("Immutable Set error: %1").arg(e.what()));
    }
}

void MainWindow::concatImmutable() {
    try {
        QListWidgetItem* item1 = ui->sequenceListWidget->currentItem();
        if (!item1) throw std::runtime_error("Select first sequence");

        QString secondName = QInputDialog::getText(this, "Concat", "Enter name of sequence to concatenate:");
        if (secondName.isEmpty()) return;

        QString newName = generateCopyName(item1->text());
        controller->concatImmutable(item1->text().toStdString(), secondName.toStdString(), newName.toStdString());
        logAction(QString("Immutable Concat: created %1 from %2 + %3").arg(newName, item1->text(), secondName));
    } catch (const std::exception& e) {
        onErrorOccurred(QString("Immutable Concat error: %1").arg(e.what()));
    }
}

void MainWindow::concat() {
    try {
        QListWidgetItem* item1 = ui->sequenceListWidget->currentItem();
        if (!item1) throw std::runtime_error("Select first sequence");

        QString secondName = QInputDialog::getText(this, "Concat", "Enter name of sequence to concatenate:");
        if (secondName.isEmpty()) return;

        controller->concat(item1->text().toStdString(), secondName.toStdString());
        logAction(QString("Concat: %1 += %2").arg(item1->text(), secondName));
    } catch (const std::exception& e) {
        onErrorOccurred(QString("Concat error: %1").arg(e.what()));
    }
}

MainController::ValueType MainWindow::stringToValueType(const QString& typeStr){
    if (typeStr == "int") return MainController::ValueType::Int;
    if (typeStr == "double") return MainController::ValueType::Double;
    throw std::invalid_argument("Unknown type string");
}

int MainWindow::getSequenceLength(const std::string& name) const {
    return controller->getSequenceLength(name);
}

