#pragma once

#include <QObject>
#include <QString>
#include <QVariant>
#include <memory>
#include <unordered_map>
#include <variant>
#include <vector>
#include <string>
#include "../models/inc/sequence.hpp"

class MainController : public QObject
{
    Q_OBJECT

public:
    enum class SequenceType
    {
        Array,
        List
    };
    enum class ValueType
    {
        Int,
        Double
    };

    template <typename T>
    Sequence<T> *getSequence(const std::string &name) const;

    explicit MainController(QObject *parent = nullptr);
    ~MainController();

    void createSequence(const std::string &name, SequenceType sequenceType, ValueType valueType);
    void createArraySequence(const std::string &name, ValueType valueType = ValueType::Int);
    void createListSequence(const std::string &name, ValueType valueType = ValueType::Int);
    void removeSequence(const std::string &name);

    bool sequenceExists(const std::string &name) const;
    ValueType getSequenceValueType(const std::string &name) const;

    void appendToSequence(const std::string &name, const QVariant &value);
    void prependToSequence(const std::string &name, const QVariant &value);
    void insertAtSequence(const std::string &name, int index, const QVariant &value);
    void setInSequence(const std::string &name, int index, const QVariant &value);
    void concat(const std::string &name1, const std::string &name2);

    void appendToImmutableSequence(const std::string &originalName, const QVariant &value, const std::string &newName);
    void prependToImmutableSequence(const std::string &originalName, const QVariant &value, const std::string &newName);
    void insertAtImmutableSequence(const std::string &originalName, int index, const QVariant &value, const std::string &newName);
    void setInImmutableSequence(const std::string &originalName, int index, const QVariant &value, const std::string &newName);
    void concatImmutable(const std::string &name1, const std::string &name2, const std::string &newName);

    QVariant getFromSequence(const std::string &name, int index) const;
    int getSequenceLength(const std::string &name) const;
    QString getSequenceAsString(const std::string &name) const;
    std::vector<std::string> getAllSequenceNames() const;

signals:
    void sequenceCreated(const QString &name);
    void sequenceRemoved(const QString &name);
    void sequenceChanged(const QString &name);
    void errorOccurred(const QString &message);

private:
    struct SequenceData
    {
        SequenceType sequenceType;
        ValueType valueType;
        std::variant<std::unique_ptr<Sequence<int>>, std::unique_ptr<Sequence<double>>> sequence;
    };

    std::unordered_map<std::string, SequenceData> sequences;
};
