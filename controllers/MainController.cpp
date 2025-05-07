#include "MainController.h"
#include "../models/inc/listSequence.hpp"
#include "../models/inc/arraySequence.hpp"
#include <stdexcept>
#include <sstream>

MainController::MainController(QObject *parent) : QObject(parent) {}
MainController::~MainController() = default;

void MainController::createSequence(const std::string &name, SequenceType sequenceType, ValueType valueType)
{
    if (name.empty())
    {
        emit errorOccurred("Sequence name cannot be empty");
        return;
    }

    if (sequenceExists(name))
    {
        emit errorOccurred(QString("Sequence '%1' already exists").arg(QString::fromStdString(name)));
        return;
    }

    SequenceData data;
    data.sequenceType = sequenceType;
    data.valueType = valueType;

    try
    {
        if (valueType == ValueType::Int)
        {
            if (sequenceType == SequenceType::Array)
                data.sequence = std::make_unique<ArraySequence<int>>();
            else
                data.sequence = std::make_unique<ListSequence<int>>();
        }
        else
        {
            if (sequenceType == SequenceType::Array)
                data.sequence = std::make_unique<ArraySequence<double>>();
            else
                data.sequence = std::make_unique<ListSequence<double>>();
        }
    }
    catch (const std::exception &e)
    {
        emit errorOccurred(QString("Failed to create sequence: %1").arg(e.what()));
        return;
    }

    sequences[name] = std::move(data);
    emit sequenceCreated(QString::fromStdString(name));
}

template <typename T>
Sequence<T> *MainController::getSequence(const std::string &name) const
{
    auto it = sequences.find(name);
    if (it == sequences.end())
    {
        throw std::runtime_error("Sequence not found");
    }

    try
    {
        if constexpr (std::is_same_v<T, int>)
        {
            if (std::holds_alternative<std::unique_ptr<Sequence<int>>>(it->second.sequence))
            {
                return std::get<std::unique_ptr<Sequence<int>>>(it->second.sequence).get();
            }
        }
        else
        {
            if (std::holds_alternative<std::unique_ptr<Sequence<double>>>(it->second.sequence))
            {
                return std::get<std::unique_ptr<Sequence<double>>>(it->second.sequence).get();
            }
        }
        throw std::runtime_error("Type mismatch");
    }
    catch (const std::bad_variant_access &)
    {
        throw std::runtime_error("Invalid sequence type access");
    }
}

void MainController::appendToSequence(const std::string &name, const QVariant &value)
{
    if (!sequenceExists(name))
    {
        emit errorOccurred(QString("Sequence '%1' not found").arg(QString::fromStdString(name)));
        return;
    }

    try
    {
        auto &data = sequences[name];
        if (data.valueType == ValueType::Int)
        {
            getSequence<int>(name)->append(value.toInt());
        }
        else
        {
            getSequence<double>(name)->append(value.toDouble());
        }
        emit sequenceChanged(QString::fromStdString(name));
    }
    catch (const std::exception &e)
    {
        emit errorOccurred(QString("Append failed: %1").arg(e.what()));
    }
}

void MainController::prependToSequence(const std::string &name, const QVariant &value)
{
    if (!sequenceExists(name))
    {
        emit errorOccurred(QString("Sequence '%1' not found").arg(QString::fromStdString(name)));
        return;
    }

    try
    {
        auto &data = sequences[name];
        if (data.valueType == ValueType::Int)
        {
            getSequence<int>(name)->prepend(value.toInt());
        }
        else
        {
            getSequence<double>(name)->prepend(value.toDouble());
        }
        emit sequenceChanged(QString::fromStdString(name));
    }
    catch (const std::exception &e)
    {
        emit errorOccurred(QString("Prepend failed: %1").arg(e.what()));
    }
}

void MainController::insertAtSequence(const std::string &name, int index, const QVariant &value)
{
    if (!sequenceExists(name))
    {
        emit errorOccurred(QString("Sequence '%1' not found").arg(QString::fromStdString(name)));
        return;
    }

    try
    {
        auto &data = sequences.at(name);
        if (data.valueType == ValueType::Int)
        {
            getSequence<int>(name)->insertAt(value.toInt(), index);
        }
        else
        {
            getSequence<double>(name)->insertAt(value.toDouble(), index);
        }
        emit sequenceChanged(QString::fromStdString(name));
    }
    catch (const std::out_of_range &)
    {
        emit errorOccurred("Invalid index for insertion");
    }
    catch (const std::exception &e)
    {
        emit errorOccurred(QString("Insert failed: %1").arg(e.what()));
    }
}

void MainController::setInSequence(const std::string &name, int index, const QVariant &value)
{
    if (!sequenceExists(name))
    {
        emit errorOccurred(QString("Sequence '%1' not found").arg(QString::fromStdString(name)));
        return;
    }

    try
    {
        auto &data = sequences.at(name);
        if (data.valueType == ValueType::Int)
        {
            getSequence<int>(name)->set(index, value.toInt());
        }
        else
        {
            getSequence<double>(name)->set(index, value.toDouble());
        }
        emit sequenceChanged(QString::fromStdString(name));
    }
    catch (const std::out_of_range &)
    {
        emit errorOccurred("Index out of range");
    }
    catch (const std::exception &e)
    {
        emit errorOccurred(QString("Set failed: %1").arg(e.what()));
    }
}

QVariant MainController::getFromSequence(const std::string &name, int index) const
{
    if (!sequenceExists(name))
    {
        throw std::runtime_error("Sequence not found");
    }

    try
    {
        const auto &data = sequences.at(name);
        if (data.valueType == ValueType::Int)
        {
            return getSequence<int>(name)->get(index);
        }
        else
        {
            return getSequence<double>(name)->get(index);
        }
    }
    catch (const std::out_of_range &)
    {
        throw std::runtime_error("Index out of range");
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error(QString("Get failed: %1").arg(e.what()).toStdString());
    }
}

int MainController::getSequenceLength(const std::string &name) const
{
    if (!sequenceExists(name))
    {
        throw std::runtime_error("Sequence not found");
    }

    try
    {
        const auto &data = sequences.at(name);
        if (data.valueType == ValueType::Int)
        {
            return getSequence<int>(name)->getLength();
        }
        else
        {
            return getSequence<double>(name)->getLength();
        }
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error(QString("Get length failed: %1").arg(e.what()).toStdString());
    }
}

QString MainController::getSequenceAsString(const std::string &name) const
{
    if (!sequenceExists(name))
    {
        throw std::runtime_error("Sequence not found");
    }

    try
    {
        const auto &data = sequences.at(name);
        std::ostringstream oss;

        if (data.valueType == ValueType::Int)
        {
            auto *seq = getSequence<int>(name);
            for (int i = 0; i < seq->getLength(); ++i)
            {
                if (i != 0)
                    oss << ", ";
                oss << seq->get(i);
            }
        }
        else
        {
            auto *seq = getSequence<double>(name);
            for (int i = 0; i < seq->getLength(); ++i)
            {
                if (i != 0)
                    oss << ", ";
                oss << seq->get(i);
            }
        }

        return QString::fromStdString(oss.str());
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error(QString("Get as string failed: %1").arg(e.what()).toStdString());
    }
}

std::vector<std::string> MainController::getAllSequenceNames() const
{
    std::vector<std::string> names;
    for (const auto &pair : sequences)
    {
        names.push_back(pair.first);
    }
    return names;
}

void MainController::createArraySequence(const std::string &name, ValueType valueType)
{
    createSequence(name, SequenceType::Array, valueType);
}

void MainController::createListSequence(const std::string &name, ValueType valueType)
{
    createSequence(name, SequenceType::List, valueType);
}

void MainController::removeSequence(const std::string &name)
{
    if (!sequenceExists(name))
    {
        emit errorOccurred(QString("Sequence '%1' not found").arg(QString::fromStdString(name)));
        return;
    }
    sequences.erase(name);
    emit sequenceRemoved(QString::fromStdString(name));
}

bool MainController::sequenceExists(const std::string &name) const
{
    return sequences.find(name) != sequences.end();
}

MainController::ValueType MainController::getSequenceValueType(const std::string &name) const
{
    if (!sequenceExists(name))
    {
        throw std::runtime_error("Sequence not found");
    }
    return sequences.at(name).valueType;
}

void MainController::appendToImmutableSequence(const std::string &originalName, const QVariant &value, const std::string &newName)
{
    if (!sequenceExists(originalName))
    {
        emit errorOccurred(QString("Original sequence '%1' not found").arg(QString::fromStdString(originalName)));
        return;
    }

    if (sequenceExists(newName))
    {
        emit errorOccurred(QString("New sequence name '%1' already exists").arg(QString::fromStdString(newName)));
        return;
    }

    try
    {
        const auto &original = sequences.at(originalName);

        if (original.valueType == ValueType::Int)
        {
            auto *originalSeq = getSequence<int>(originalName);
            auto *newSeq = static_cast<Sequence<int> *>(originalSeq->appendImmutable(value.toInt()));
            SequenceData newSequenceData;
            newSequenceData.sequenceType = original.sequenceType;
            newSequenceData.valueType = original.valueType;
            newSequenceData.sequence = std::unique_ptr<Sequence<int>>(newSeq);
            sequences[newName] = std::move(newSequenceData);
        }
        else
        {
            auto *originalSeq = getSequence<double>(originalName);
            auto *newSeq = static_cast<Sequence<double> *>(originalSeq->appendImmutable(value.toDouble()));
            SequenceData newSequenceData;
            newSequenceData.sequenceType = original.sequenceType;
            newSequenceData.valueType = original.valueType;
            newSequenceData.sequence = std::unique_ptr<Sequence<double>>(newSeq);
            sequences[newName] = std::move(newSequenceData);
        }

        emit sequenceCreated(QString::fromStdString(newName));
    }
    catch (const std::exception &e)
    {
        emit errorOccurred(QString("Immutable append failed: %1").arg(e.what()));
    }
}

void MainController::prependToImmutableSequence(const std::string &originalName, const QVariant &value, const std::string &newName)
{
    if (!sequenceExists(originalName))
    {
        emit errorOccurred(QString("Original sequence '%1' not found").arg(QString::fromStdString(originalName)));
        return;
    }

    if (sequenceExists(newName))
    {
        emit errorOccurred(QString("New sequence name '%1' already exists").arg(QString::fromStdString(newName)));
        return;
    }

    try
    {
        const auto &original = sequences.at(originalName);

        if (original.valueType == ValueType::Int)
        {
            auto *originalSeq = getSequence<int>(originalName);
            auto *newSeq = static_cast<Sequence<int> *>(originalSeq->prependImmutable(value.toInt()));
            SequenceData newSequenceData;
            newSequenceData.sequenceType = original.sequenceType;
            newSequenceData.valueType = original.valueType;
            newSequenceData.sequence = std::unique_ptr<Sequence<int>>(newSeq);
            sequences[newName] = std::move(newSequenceData);
        }
        else
        {
            auto *originalSeq = getSequence<double>(originalName);
            auto *newSeq = static_cast<Sequence<double> *>(originalSeq->prependImmutable(value.toDouble()));
            SequenceData newSequenceData;
            newSequenceData.sequenceType = original.sequenceType;
            newSequenceData.valueType = original.valueType;
            newSequenceData.sequence = std::unique_ptr<Sequence<double>>(newSeq);
            sequences[newName] = std::move(newSequenceData);
        }

        emit sequenceCreated(QString::fromStdString(newName));
    }
    catch (const std::exception &e)
    {
        emit errorOccurred(QString("Immutable prepend failed: %1").arg(e.what()));
    }
}

void MainController::insertAtImmutableSequence(const std::string &originalName, int index, const QVariant &value, const std::string &newName)
{
    if (!sequenceExists(originalName))
    {
        emit errorOccurred(QString("Original sequence '%1' not found").arg(QString::fromStdString(originalName)));
        return;
    }

    if (sequenceExists(newName))
    {
        emit errorOccurred(QString("New sequence name '%1' already exists").arg(QString::fromStdString(newName)));
        return;
    }

    try
    {
        const auto &original = sequences.at(originalName);

        if (original.valueType == ValueType::Int)
        {
            auto *originalSeq = getSequence<int>(originalName);
            auto *newSeq = static_cast<Sequence<int> *>(originalSeq->insertAtImmutable(value.toInt(), index));
            SequenceData newSequenceData;
            newSequenceData.sequenceType = original.sequenceType;
            newSequenceData.valueType = original.valueType;
            newSequenceData.sequence = std::unique_ptr<Sequence<int>>(newSeq);
            sequences[newName] = std::move(newSequenceData);
        }
        else
        {
            auto *originalSeq = getSequence<double>(originalName);
            auto *newSeq = static_cast<Sequence<double> *>(originalSeq->insertAtImmutable(value.toDouble(), index));
            SequenceData newSequenceData;
            newSequenceData.sequenceType = original.sequenceType;
            newSequenceData.valueType = original.valueType;
            newSequenceData.sequence = std::unique_ptr<Sequence<double>>(newSeq);
            sequences[newName] = std::move(newSequenceData);
        }

        emit sequenceCreated(QString::fromStdString(newName));
    }
    catch (const std::out_of_range &)
    {
        emit errorOccurred("Invalid index for insertion");
    }
    catch (const std::exception &e)
    {
        emit errorOccurred(QString("Immutable insert failed: %1").arg(e.what()));
    }
}

void MainController::setInImmutableSequence(const std::string &originalName, int index, const QVariant &value, const std::string &newName)
{
    if (!sequenceExists(originalName))
    {
        emit errorOccurred(QString("Original sequence '%1' not found").arg(QString::fromStdString(originalName)));
        return;
    }

    if (sequenceExists(newName))
    {
        emit errorOccurred(QString("New sequence name '%1' already exists").arg(QString::fromStdString(newName)));
        return;
    }

    try
    {
        const auto &original = sequences.at(originalName);

        if (original.valueType == ValueType::Int)
        {
            auto *originalSeq = getSequence<int>(originalName);
            auto *newSeq = static_cast<Sequence<int> *>(originalSeq->setImmutable(index, value.toInt()));
            SequenceData newSequenceData;
            newSequenceData.sequenceType = original.sequenceType;
            newSequenceData.valueType = original.valueType;
            newSequenceData.sequence = std::unique_ptr<Sequence<int>>(newSeq);
            sequences[newName] = std::move(newSequenceData);
        }
        else
        {
            auto *originalSeq = getSequence<double>(originalName);
            auto *newSeq = static_cast<Sequence<double> *>(originalSeq->setImmutable(index, value.toDouble()));
            SequenceData newSequenceData;
            newSequenceData.sequenceType = original.sequenceType;
            newSequenceData.valueType = original.valueType;
            newSequenceData.sequence = std::unique_ptr<Sequence<double>>(newSeq);
            sequences[newName] = std::move(newSequenceData);
        }

        emit sequenceCreated(QString::fromStdString(newName));
    }
    catch (const std::out_of_range &)
    {
        emit errorOccurred("Index out of range");
    }
    catch (const std::exception &e)
    {
        emit errorOccurred(QString("Immutable set failed: %1").arg(e.what()));
    }
}

void MainController::concatImmutable(const std::string &name1, const std::string &name2, const std::string &newName)
{
    if (!sequenceExists(name1) || !sequenceExists(name2))
    {
        emit errorOccurred("One or both sequences not found");
        return;
    }

    if (sequenceExists(newName))
    {
        emit errorOccurred(QString("New sequence name '%1' already exists").arg(QString::fromStdString(newName)));
        return;
    }

    try
    {
        const auto &s1 = sequences.at(name1);
        const auto &s2 = sequences.at(name2);

        if (s1.valueType != s2.valueType || s1.sequenceType != s2.sequenceType)
        {
            emit errorOccurred("Sequences must be of the same type to concatenate");
            return;
        }

        if (s1.valueType == ValueType::Int)
        {
            auto *seq1 = getSequence<int>(name1);
            auto *seq2 = getSequence<int>(name2);
            auto *newSeq = static_cast<Sequence<int> *>(seq1->concatImmutable(seq2));
            SequenceData newSequenceData;
            newSequenceData.sequenceType = s1.sequenceType;
            newSequenceData.valueType = s1.valueType;
            newSequenceData.sequence = std::unique_ptr<Sequence<int>>(newSeq);
            sequences[newName] = std::move(newSequenceData);
        }
        else
        {
            auto *seq1 = getSequence<double>(name1);
            auto *seq2 = getSequence<double>(name2);
            auto *newSeq = static_cast<Sequence<double> *>(seq1->concatImmutable(seq2));
            SequenceData newSequenceData;
            newSequenceData.sequenceType = s1.sequenceType;
            newSequenceData.valueType = s1.valueType;
            newSequenceData.sequence = std::unique_ptr<Sequence<double>>(newSeq);
            sequences[newName] = std::move(newSequenceData);
        }

        emit sequenceCreated(QString::fromStdString(newName));
    }
    catch (const std::exception &e)
    {
        emit errorOccurred(QString("Immutable concat failed: %1").arg(e.what()));
    }
}

void MainController::concat(const std::string &name1, const std::string &name2)
{
    if (!sequenceExists(name1) || !sequenceExists(name2))
    {
        emit errorOccurred("One or both sequences not found");
        return;
    }

    try
    {
        const auto &s1 = sequences.at(name1);
        const auto &s2 = sequences.at(name2);

        if (s1.valueType != s2.valueType || s1.sequenceType != s2.sequenceType)
        {
            emit errorOccurred("Sequences must be of the same type to concatenate");
            return;
        }

        if (s1.valueType == ValueType::Int)
        {
            auto *seq1 = getSequence<int>(name1);
            auto *seq2 = getSequence<int>(name2);
            seq1->concat(seq2);
        }
        else
        {
            auto *seq1 = getSequence<double>(name1);
            auto *seq2 = getSequence<double>(name2);
            seq1->concat(seq2);
        }

        emit sequenceChanged(QString::fromStdString(name1));
    }
    catch (const std::exception &e)
    {
        emit errorOccurred(QString("Concat failed: %1").arg(e.what()));
    }
}
