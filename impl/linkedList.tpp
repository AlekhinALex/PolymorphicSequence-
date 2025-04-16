#include "../inc/linkedList.hpp"
#include <iostream>
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), length(0) {}

template <class T>
LinkedList<T>::LinkedList(int count) : head(nullptr), tail(nullptr), length(0)
{
    if (count < 0)
    {
        throw std::invalid_argument("Count cannot be negative");
    }

    // Initialize with zeros/default values
    T defaultValue = T();
    for (int i = 0; i < count; i++)
    {
        append(defaultValue);
    }
}

template <typename T>
LinkedList<T>::LinkedList(T *items, int count) : head(nullptr), tail(nullptr), length(0)
{
    for (int i = 0; i < count; i++)
    {
        append(items[i]);
    }
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) : head(nullptr), tail(nullptr), length(0)
{
    Node *current = list.head;
    while (current)
    {
        append(current->value);
        current = current->next;
    }
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    Node *current = head;
    while (current)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    length = 0;
}

template <typename T>
void LinkedList<T>::append(const T &item)
{
    Node *node = new Node(item);
    if (!head)
    {
        head = tail = node;
    }
    else
    {
        tail->next = node;
        tail = node;
    }
    length++;
}

template <typename T>
void LinkedList<T>::prepend(const T &item)
{
    Node *newNode = new Node(item);
    if (!head)
    {
        head = tail = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
    length++;
}

template <typename T>
T LinkedList<T>::getFirst() const
{
    if (!head)
    {
        throw std::out_of_range("List is empty");
    }
    return head->value;
}

template <typename T>
T LinkedList<T>::getLast() const
{
    if (!tail)
    {
        throw std::out_of_range("List is empty");
    }
    return tail->value;
}

template <typename T>
T LinkedList<T>::get(int index) const
{
    return getNodeAt(index)->value;
}

template <typename T>
void LinkedList<T>::set(int index, T value)
{
    getNodeAt(index)->value = value;
}

template <typename T>
void LinkedList<T>::insertAt(T value, int index)
{
    if (index < 0 || index > length)
    {
        throw std::out_of_range("Index out of range");
    }

    Node *newNode = new Node(value);
    if (index == 0)
    {
        newNode->next = head;
        head = newNode;
        if (!tail)
        {
            tail = head;
        }
    }
    else
    {
        Node *prev = getNodeAt(index - 1);
        newNode->next = prev->next;
        prev->next = newNode;
        if (index == length)
        {
            tail = newNode;
        }
    }
    length++;
}

template <typename T>
LinkedList<T> *LinkedList<T>::getSubList(int startIndex, int endIndex)
{
    int size = getLength();
    if (startIndex < 0 || startIndex >= size ||
        endIndex < 0 || endIndex >= size ||
        startIndex > endIndex)
    {
        throw std::out_of_range("Invalid index range");
    }

    LinkedList<T> *subList = new LinkedList<T>();
    Node *current = getNodeAt(startIndex);

    for (int i = startIndex; i <= endIndex; i++)
    {
        subList->append(current->value);
        current = current->next;
    }

    return subList;
}

template <typename T>
int LinkedList<T>::getLength() const
{
    return length;
}

template <typename T>
void LinkedList<T>::print() const
{
    Node *current = head;
    while (current)
    {
        std::cout << current->value;
        if (current->next)
        {
            std::cout << " -> ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}

template <typename T>
void LinkedList<T>::clear()
{
    Node *current;
    Node *old;
    current = head;
    for (int i = 0; i < length; i++)
    {
        old = current;
        current = current->next;
        delete old;
    }
    head = nullptr;
    tail = nullptr;
    length = 0;
}

template <typename T>
LinkedList<T> *LinkedList<T>::concat(LinkedList<T> *list)
{
    LinkedList<T> *newList = new LinkedList<T>();

    Node *current = head;
    while (current)
    {
        newList->append(current->value);
        current = current->next;
    }

    current = list->head;
    while (current != nullptr)
    {
        newList->append(current->value);
        current = current->next;
    }

    return newList;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::getNodeAt(int index) const
{
    if (index < 0 || index >= length)
    {
        throw std::out_of_range("Index out of range");
    }

    Node *current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current;
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other)
{
    if (&other == this)
    {
        return *this;
    }

    while (head != nullptr)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    length = 0;

    Node *current = other.head;
    while (current != nullptr)
    {
        append(current->value);
        current = current->next;
    }

    return *this;
}

template <class T>
T &LinkedList<T>::operator[](int index)
{
    if (index < 0 || index >= getLength())
    {
        throw std::out_of_range("Index out of range");
    }

    Node *current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current->value;
}

template <class T>
const T &LinkedList<T>::operator[](int index) const
{
    if (index < 0 || index >= getLength())
    {
        throw std::out_of_range("Index out of range");
    }

    Node *current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current->value;
}
