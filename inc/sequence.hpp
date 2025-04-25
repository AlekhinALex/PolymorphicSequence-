#pragma once

template <class T>
class Sequence
{
public:
    virtual T getFirst() = 0;
    virtual T getLast() = 0;
    virtual T get(int index) = 0;

    virtual Sequence<T> *getSubsequence(int startIndex, int endIndex) = 0;

    virtual int getLength() = 0;

    virtual Sequence<T> *set(int index, T data) = 0;
    virtual Sequence<T> *setImmutable(int index, T data) = 0;

    virtual Sequence<T> *append(T item) = 0;
    virtual Sequence<T> *appendImmutable(T item) = 0;

    virtual Sequence<T> *prepend(T item) = 0;
    virtual Sequence<T> *prependImmutable(T item) = 0;

    virtual Sequence<T> *insertAt(T item, int index) = 0;
    virtual Sequence<T> *insertAtImmutable(T item, int index) = 0;

    virtual Sequence<T> *concat(Sequence<T> *list) = 0;
    virtual Sequence<T> *concatImmutable(Sequence<T> *list) = 0;

    virtual void print() = 0;

    virtual ~Sequence() = default;
};
