#pragma once
#include "sequence.hpp"
#include "linkedList.hpp"
#include <stdexcept>

template <class T>

class ListSequence : public Sequence<T>
{
private:
    LinkedList<T> list;

public:
    ListSequence();
    ListSequence(T *items, int count);
    ListSequence(int count);
    ListSequence(const LinkedList<T> &list);
    virtual ~ListSequence() override;

    T getFirst() override;
    T getLast() override;
    T get(int index) override;
    int getLength() override;

    Sequence<T> *getSubsequence(int startIndex, int endIndex) override;
    Sequence<T> *append(T item) override;
    Sequence<T> *prepend(T item) override;
    Sequence<T> *insertAt(T item, int index) override;
    Sequence<T> *set(int index, T data) override;
    Sequence<T> *concat(Sequence<T> *other) override;
    void print() override;

    //* Immutable
    Sequence<T> *appendImmutable(T item) override;
    Sequence<T> *setImmutable(int index, T data) override;
    Sequence<T> *prependImmutable(T item) override;
    Sequence<T> *insertAtImmutable(T item, int index) override;
    Sequence<T> *concatImmutable(Sequence<T> *list) override;

    T &operator[](int index);
    const T &operator[](int index) const;
};

#include "../impl/listSequence.tpp"