#include <iostream>
#include "../inc/dynamicArray.hpp"

template <typename T>
DynamicArray<T>::DynamicArray() : data(new T[1]), size(0), capacity(1) {}

template <typename T>
DynamicArray<T>::DynamicArray(int size) : data(new T[(size > 0 ? size : 1)]), size(size > 0 ? size : 0), capacity((size > 0 ? size : 1))
{
    for (int i = 0; i < size; ++i)
    {
        data[i] = T();
    }
}

template <typename T>
DynamicArray<T>::DynamicArray(T *items, int count) : data(new T[(count > 0 ? count : 1)]), size(count), capacity(count)
{
    for (int i = 0; i < count; ++i)
    {
        data[i] = items[i];
    }
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &dynamicArray) : data(new T[dynamicArray.capacity]), size(dynamicArray.size), capacity(dynamicArray.capacity)
{
    for (int i = 0; i < size; ++i)
    {
        data[i] = dynamicArray.data[i];
    }
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] data;
}

template <typename T>
T DynamicArray<T>::get(int index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
T DynamicArray<T>::getFirst()
{
    if (size == 0)
    {
        throw std::out_of_range("");
    }

    return data[0];
}

template <typename T>
T DynamicArray<T>::getLast()
{
    if (size == 0)
    {
        throw std::out_of_range("");
    }

    return data[size - 1];
}

template <typename T>
T *DynamicArray<T>::getData() const
{
    return data;
}

template <typename T>
int DynamicArray<T>::getSize()
{
    return size;
}

template <class T>
void DynamicArray<T>::append(const T &item)
{
    if (size >= capacity)
    {
        resize(size + 1);
    }
    else
    {
        size++;
    }
    data[size - 1] = item;
}

template <class T>
void DynamicArray<T>::prepend(const T &item)
{
    if (size >= capacity)
    {
        resize(size + 1);
    }
    else
    {
        size++;
    }

    for (int i = size - 1; i > 0; i--)
    {
        data[i] = data[i - 1];
    }

    data[0] = item;
}

template <typename T>
void DynamicArray<T>::set(int index, T value)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    data[index] = value;
}

template <class T>
void DynamicArray<T>::insertAt(const T &item, int index)
{

    if (index < 0 || index > size)
    {
        throw std::out_of_range("Index out of range");
    }

    if (index == size)
    {
        append(item);
        return;
    }

    if (index == 0)
    {
        prepend(item);
        return;
    }

    if (size >= capacity)
    {
        resize(size + 1);
    }
    else
    {
        size++;
    }

    for (int i = size - 1; i > index; i--)
    {
        data[i] = data[i - 1];
    }

    data[index] = item;
}

template <typename T>
void DynamicArray<T>::resize(int newSize)
{
    if (newSize < 0)
    {
        throw std::invalid_argument("Invalid size");
    }

    if (newSize > capacity)
    {
        int newCapacity = capacity * 2;
        while (newCapacity < newSize)
        {
            newCapacity *= 2;
        }

        T *newData = new T[newCapacity];

        for (int i = 0; i < size; ++i)
        {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    size = newSize;
}

template <typename T>
DynamicArray<T> *DynamicArray<T>::getSubArray(int startIndex, int endIndex)
{
    if (startIndex < 0 || endIndex >= size || startIndex > endIndex)
    {
        throw std::out_of_range("Invalid index range");
    }

    int subLength = endIndex - startIndex + 1;

    DynamicArray<T> *result = new DynamicArray<T>(subLength);
    result->size = subLength;
    result->capacity = subLength;

    for (int i = startIndex; i <= endIndex; i++)
    {
        result->data[i - startIndex] = data[i];
    }

    return result;
}

template <typename T>
void DynamicArray<T>::print()
{
    for (int i = 0; i < size; i++)
    {

        std::cout << "[" << data[i] << "]";
        if (i < size - 1)
        {
            std::cout << ", ";
        }
    }
}

template <class T>
void DynamicArray<T>::clear()
{
    T *newData = new T[1];
    delete[] data;
    data = newData;
    size = 0;
    capacity = 1;
}

template <typename T>
DynamicArray<T> *DynamicArray<T>::concat(DynamicArray<T> *dynamicArray)
{
    if (!dynamicArray)
    {
        throw std::invalid_argument("Cannot concatenate with null array");
    }
    int newSize = dynamicArray->size + size;

    DynamicArray<T> *result = new DynamicArray<T>(newSize);

    for (int i = 0; i < size; i++)
    {
        result->data[i] = data[i];
    }
    for (int i = size; i < newSize; i++)
    {
        result->data[i] = dynamicArray->data[i - size];
    }

    result->size = newSize;
    result->capacity = newSize;

    return result;
}

template <typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray<T> &other)
{
    if (this == &other)
    {
        return *this;
    }

    if (size != other.size)
    {
        delete[] data;
        data = new T[other.size];
        size = other.size;
    }

    for (int i = 0; i < size; i++)
    {
        data[i] = other.data[i];
    }

    return *this;
}

template <typename T>
T &DynamicArray<T>::operator[](int index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
const T &DynamicArray<T>::operator[](int index) const
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}
