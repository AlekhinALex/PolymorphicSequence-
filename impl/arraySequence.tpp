#include <iostream>
#include "../inc/arraySequence.hpp"

template <class T>
ArraySequence<T>::ArraySequence() : array() {}

template <class T>
ArraySequence<T>::ArraySequence(T *items, int count) : array(items, count) {}

template <class T>
ArraySequence<T>::ArraySequence(int count) : array(count) {}

template <class T>
ArraySequence<T>::ArraySequence(const DynamicArray<T> &array) : array(array) {}

template <class T>
ArraySequence<T>::~ArraySequence() {}

template <class T>
T ArraySequence<T>::getFirst()
{
    return array.getFirst();
}

template <class T>
T ArraySequence<T>::getLast()
{
    return array.getLast();
}

template <class T>
T ArraySequence<T>::get(int index)
{
    return array.get(index);
}

template <class T>
int ArraySequence<T>::getLength()
{
    return array.getSize();
}

template <class T>
Sequence<T> *ArraySequence<T>::getSubsequence(int startIndex, int endIndex)
{
    if (startIndex < 0 || endIndex >= getLength() || startIndex > endIndex)
    {
        throw std::out_of_range("Invalid index range");
    }

    Sequence<T> *subArray = new ArraySequence<T>();

    for (int i = startIndex; i <= endIndex; i++)
    {
        subArray->append(this->get(i));
    }

    return subArray;
}

template <class T>
Sequence<T> *ArraySequence<T>::append(T item)
{
    ArraySequence<T> *newSequence = new ArraySequence<T>(*this);
    newSequence->array.append(item);
    return newSequence;
}

template <class T>
Sequence<T> *ArraySequence<T>::prepend(T item)
{
    ArraySequence<T> *newSequence = new ArraySequence<T>(*this);
    newSequence->array.prepend(item);
    return newSequence;
}

template <class T>
Sequence<T> *ArraySequence<T>::insertAt(T item, int index)
{
    if (index < 0 || index > getLength())
    {
        throw std::out_of_range("Invalid index for insertion");
    }
    ArraySequence<T> *newSequence = new ArraySequence<T>(*this);
    newSequence->array.insertAt(item, index);
    return newSequence;
}

template <class T>
Sequence<T> *ArraySequence<T>::set(int index, T data)
{
    if (index < 0 || index >= getLength())
    {
        throw std::out_of_range("Index out of range");
    }
    array[index] = data;
    return this;
}

// TODO: make sure this func is right written. Should I use concate from dynamicArray?
template <class T>
Sequence<T> *ArraySequence<T>::concat(Sequence<T> *other)
{
    if (!other)
    {
        throw std::invalid_argument("Cannot concatenate with null sequence");
    }

    ArraySequence<T> *result = new ArraySequence<T>();

    for (int i = 0; i < getLength(); i++)
    {
        result->array.append(get(i));
    }

    for (int i = 0; i < other->getLength(); i++)
    {
        result->array.append(other->get(i));
    }

    return result;
}

template <class T>
Sequence<T> *ArraySequence<T>::setImmutable(int index, T data)
{
    ArraySequence<T> *newSequence = new ArraySequence<T>(*this);
    newSequence->set(index, data);
    return newSequence;
}

template <class T>
Sequence<T> *ArraySequence<T>::appendImmutable(T item)
{
    return append(item);
}

template <class T>
Sequence<T> *ArraySequence<T>::prependImmutable(T item)
{
    return prepend(item);
}

template <class T>
Sequence<T> *ArraySequence<T>::insertAtImmutable(T item, int index)
{
    return insertAt(item, index);
}

template <class T>
Sequence<T> *ArraySequence<T>::concatImmutable(Sequence<T> *array)
{
    return concat(array);
}

template <class T>
void ArraySequence<T>::print()
{
    array.print();
}

template <class T>
T &ArraySequence<T>::operator[](int index)
{
    if (index < 0 || index >= getLength())
    {
        throw std::out_of_range("Index out of range");
    }
    return array[index];
}

template <class T>
const T &ArraySequence<T>::operator[](int index) const
{
    if (index < 0 || index >= getLength())
    {
        throw std::out_of_range("Index out of range");
    }
    return array[index];
}