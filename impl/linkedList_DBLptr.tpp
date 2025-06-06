#include <iostream>
#include "../inc/linkedList_DBLptr.hpp"

//* Iterator {

template <typename T>
LinkedList<T>::Iterator::Iterator(Node **nodePtr) : current(nodePtr) {}

template <typename T>
typename LinkedList<T>::Iterator &LinkedList<T>::Iterator::operator++()
{
    if (*current)
    {
        current = &((*current)->next);
    }
    return *this;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int)
{
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
T &LinkedList<T>::Iterator::operator*() const
{
    if (!current || !*current)
    {
        throw std::runtime_error("Invalid iterator");
    }
    return (*current)->value;
}

template <typename T>
bool LinkedList<T>::Iterator::operator==(const Iterator &other) const
{
    if (current == other.current)
    {
        return true;
    }

    if (!current || !other.current)
    {
        return false;
    }

    return *current == *other.current;
}

template <typename T>
bool LinkedList<T>::Iterator::operator!=(const Iterator &other) const
{
    return !(*this == other);
}

template <typename T>
void LinkedList<T>::Iterator::insert(const T &item)
{
    Node *newNode = new Node(item);
    newNode->next = *current;
    *current = newNode;
}

template <typename T>
void LinkedList<T>::Iterator::erase()
{
    if (*current)
    {
        Node *toDelete = *current;
        *current = (*current)->next;
        delete toDelete;
    }
}

template <typename T>
bool LinkedList<T>::Iterator::notEnd()
{
    return current && *current != nullptr;
}

//* } End of Iterator section

//* ConstIterator {

template <typename T>
LinkedList<T>::ConstIterator::ConstIterator(const Node *const *nodePtr) : current(nodePtr) {}

template <typename T>
typename LinkedList<T>::ConstIterator &LinkedList<T>::ConstIterator::operator++()
{
    if (current && *current)
    {
        current = (&((*current)->next));
    }
    return *this;
}

template <typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::ConstIterator::operator++(int)
{
    ConstIterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
const T &LinkedList<T>::ConstIterator::operator*() const
{
    if (!current || !*current)
    {
        throw std::runtime_error("Dereferencing invalid iterator");
    }
    return (*current)->value;
}

template <typename T>
bool LinkedList<T>::ConstIterator::operator==(const ConstIterator &other) const
{
    if (current == other.current)
    {
        return true;
    }

    if (!current || !other.current)
    {
        return false;
    }

    return *current == *other.current;
}

template <typename T>
bool LinkedList<T>::ConstIterator::operator!=(const ConstIterator &other) const
{
    return !(*this == other);
}

template <typename T>
bool LinkedList<T>::ConstIterator::notEnd() const
{
    return current && *current != nullptr;
}

//* } end of ConstIterator section

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), length(0) {}

template <class T>
LinkedList<T>::LinkedList(const int count) : head(nullptr), length(0)
{
    if (count < 0)
    {
        throw std::invalid_argument("Count cannot be negative");
    }

    T defaultValue = T();
    for (int i = 0; i < count; i++)
    {
        append(defaultValue);
    }
}

template <typename T>
LinkedList<T>::LinkedList(const T *items, const int count) : head(nullptr), length(0)
{
    if (!items)
    {
        throw std::invalid_argument("Count must be greater than 0");
    }

    for (int i = 0; i < count; i++)
    {
        append(items[i]);
    }
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) : head(nullptr), length(0)
{
    for (ConstIterator it = list.begin(); it != list.end(); ++it)
    {
        append(*it);
    }
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
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
    length = 0;
}

template <typename T>
void LinkedList<T>::append(const T &item)
{
    Iterator it(&head);

    while (it.notEnd())
    {
        ++it;
    }

    it.insert(item);
    length++;
}

template <typename T>
void LinkedList<T>::prepend(const T &item)
{
    Iterator it(&head);
    it.insert(item);
    length++;
}

template <typename T>
T &LinkedList<T>::getFirst()
{
    if (!head)
    {
        throw std::out_of_range("List is empty");
    }
    return head->value;
}

template <typename T>
const T &LinkedList<T>::getFirst() const
{
    if (!head)
    {
        throw std::out_of_range("List is empty");
    }

    ConstIterator it(&head);

    return *it;
}

template <typename T>
T &LinkedList<T>::getLast()
{
    if (!head)
    {
        throw std::out_of_range("List is empty");
    }

    Node *current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    return current->value;
}

template <typename T>
const T &LinkedList<T>::getLast() const
{
    if (!head)
    {
        throw std::out_of_range("List is empty");
    }

    const Node *current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    return current->value;
}

template <typename T>
T &LinkedList<T>::get(const int index)
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
    return current->value;
}

template <typename T>
const T &LinkedList<T>::get(const int index) const
{
    if (index < 0 || index >= length)
    {
        throw std::out_of_range("Index out of range");
    }

    const Node *current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current->value;
}

template <typename T>
void LinkedList<T>::set(const int index, const T &value)
{
    if (index < 0 || index >= length)
    {
        throw std::out_of_range("Index out of range");
    }

    Iterator it(&head);
    for (int i = 0; i < index; i++)
    {
        ++it;
    }

    *it = value;
}

template <typename T>
void LinkedList<T>::insertAt(const T &value, const int index)
{
    if (index < 0 || index > length)
    {
        throw std::out_of_range("Index out of range");
    }

    Iterator it(&head);
    for (int i = 0; i < index; i++)
    {
        ++it;
    }

    it.insert(value);

    length++;
}

template <typename T>
LinkedList<T> *LinkedList<T>::getSubList(const int startIndex, const int endIndex) const
{
    int size = getLength();
    if (startIndex < 0 || startIndex >= size ||
        endIndex < 0 || endIndex >= size ||
        startIndex > endIndex)
    {
        throw std::out_of_range("Invalid index range");
    }

    LinkedList<T> *subList = new LinkedList<T>();

    ConstIterator it(&head);
    for (int i = 0; i < startIndex; i++)
    {
        ++it;
    }

    for (int i = startIndex; i <= endIndex; i++)
    {
        subList->append(*it);
        ++it;
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
    if (length == 0)
    {
        std::cout << "Empty list";
        return;
    }

    for (auto it = this->begin(); it != this->end(); ++it)
    {
        std::cout << *it << " ";
    }
}

template <typename T>
LinkedList<T> *LinkedList<T>::concatImmutable(const LinkedList<T> &list) const
{
    if (&list == this)
    {
        throw std::invalid_argument("Cannot concatenate with itself");
    }

    LinkedList<T> *result = new LinkedList<T>(*this);
    result->concat(list);
    return result;
}

template <typename T>
void LinkedList<T>::concat(const LinkedList<T> &list)
{
    if (&list == this)
    {
        throw std::invalid_argument("Cannot concatenate with itself");
    }

    for (ConstIterator it = list.begin(); it != list.end(); ++it)
    {
        this->append(*it);
    }
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other)
{
    if (&other == this)
    {
        return *this;
    }

    clear();

    for (ConstIterator it = other.begin(); it != other.end(); ++it)
    {
        append(*it);
    }

    return *this;
}
