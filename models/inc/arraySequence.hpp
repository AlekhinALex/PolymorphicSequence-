#pragma once

#include "sequence.hpp"
#include "dynamicArray.hpp"
#include <iostream>

template <class T>
class ArraySequence : public Sequence<T>
{
private:
    DynamicArray<T> array;

public:
    ArraySequence();
    ArraySequence(T *items, int count);
    ArraySequence(int count);
    ArraySequence(const DynamicArray<T> &array);
    ~ArraySequence() override;

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

    Sequence<T> *setImmutable(int index, T data) override;
    Sequence<T> *appendImmutable(T item) override;
    Sequence<T> *prependImmutable(T item) override;
    Sequence<T> *insertAtImmutable(T item, int index) override;
    Sequence<T> *concatImmutable(Sequence<T> *list) override;

    T &operator[](int index);
    const T &operator[](int index) const;
};

#include "../impl/arraySequence.tpp"
