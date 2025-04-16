#pragma once

template <typename T>
class DynamicArray
{
private:
    T *data;
    int size;
    int capacity;

public:
    DynamicArray();
    DynamicArray(int size);
    DynamicArray(T *items, int count);
    DynamicArray(const DynamicArray<T> &dynamicArray);
    ~DynamicArray();

    T getFirst();
    T getLast();
    T get(int index);
    T *getData() const;

    int getSize();

    void append(const T &item);
    void prepend(const T &item);
    void set(int index, T value);
    void insertAt(const T &item, int index);
    void resize(int newSize);
    void print();
    void clear();

    DynamicArray<T> *getSubArray(int startIndex, int endIndex);
    DynamicArray<T> *concat(DynamicArray<T> *dynamicArray);

    T &operator[](int index);
    const T &operator[](int index) const;
    DynamicArray<T> &operator=(const DynamicArray<T> &other);
};

#include "../impl/dynamicArray.tpp"