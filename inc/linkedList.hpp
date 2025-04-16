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
    LinkedList();                          // Создать пустой список
    LinkedList(int count);                 // Создать пустой список
    LinkedList(T *items, int count);       // Копировать элементы из переданного массива
    LinkedList(const LinkedList<T> &list); // Копирующий конструктор
    ~LinkedList();

    T getFirst() const;     // Получить первый элемент всписке
    T getLast() const;      // Получить последний элемент в списке
    T get(int index) const; // Получить элемент по индексу

    LinkedList<T> *getSubList(int startIndex, int endIndex); // Получить список из всех элементов, начиная с startIndex и заканчивая endIndex.

    int getLength() const; // Получить длину списка

    void append(const T &item); // Добавляет элемент в конец списка
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
