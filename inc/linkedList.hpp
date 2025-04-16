#pragma once

template <typename T>
class LinkedList
{
private:
    struct Node
    {
        T value;

        //? Should I keep prev ptr?
        Node *next;

        //* Constructor
        Node(const T &value) : value(value), next(nullptr) {}
    };
    Node *head;
    Node *tail;
    int length;

    Node *getNodeAt(int index) const;

public:
    LinkedList();
    LinkedList(int count);
    LinkedList(T *items, int count);
    LinkedList(const LinkedList<T> &list);
    ~LinkedList();

    T getFirst() const;
    T getLast() const;
    T get(int index) const;

    LinkedList<T> *getSubList(int startIndex, int endIndex);

    int getLength() const;

    void append(const T &item);
    void prepend(const T &item);
    void set(int index, T value);
    void insertAt(T item, int index);
    LinkedList<T> *insertAtImmutable(T item, int index);
    void print() const;
    void clear();

    LinkedList<T> *concat(LinkedList<T> *list);

    T &operator[](int index);
    const T &operator[](int index) const;
    LinkedList<T> &operator=(const LinkedList<T> &other);
};

#include "../impl/linkedList.tpp"
