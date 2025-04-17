template <class T>
ListSequence<T>::ListSequence() : list() {}

template <class T>
ListSequence<T>::ListSequence(T *items, int count) : list(items, count) {}

template <class T>
ListSequence<T>::ListSequence(int count) : list(count) {}

template <class T>
ListSequence<T>::ListSequence(const LinkedList<T> &list) : list(list) {}

template <class T>
ListSequence<T>::~ListSequence() {}

template <class T>
T ListSequence<T>::getFirst()
{
    return list.getFirst();
}

template <class T>
T ListSequence<T>::getLast()
{
    return list.getLast();
}

template <class T>
T ListSequence<T>::get(int index)
{
    return list.get(index);
}

template <class T>
int ListSequence<T>::getLength()
{
    return list.getLength();
}

template <class T>
Sequence<T> *ListSequence<T>::getSubsequence(int startIndex, int endIndex)
{
    if (startIndex < 0 || endIndex >= getLength() || startIndex > endIndex)
    {
        throw std::out_of_range("Invalid index range");
    }

    ListSequence<T> *subList = new ListSequence<T>();
    for (int i = startIndex; i <= endIndex; i++)
    {
        subList->list.append(get(i));
    }
    return subList;
}

template <class T>
Sequence<T> *ListSequence<T>::append(T item)
{
    list.append(item);
    return this;
}

template <class T>
Sequence<T> *ListSequence<T>::prepend(T item)
{
    list.prepend(item);
    return this;
}

template <class T>
Sequence<T> *ListSequence<T>::insertAt(T item, int index)
{
    if (index < 0 || index > getLength())
    {
        throw std::out_of_range("Invalid index for insertion");
    }
    list.insertAt(item, index);
    return this;
}

template <class T>
Sequence<T> *ListSequence<T>::concat(Sequence<T> *other)
{
    if (!other)
    {
        throw std::invalid_argument("Cannot concatenate with null sequence");
    }

    for (int i = 0; i < other->getLength(); i++)
    {
        list.append(other->get(i));
    }
    return this;
}

template <class T>
Sequence<T> *ListSequence<T>::set(int index, T data)
{
    if (index < 0 || index >= getLength())
    {
        throw std::out_of_range("Index out of range");
    }
    list[index] = data;
    return this;
}

template <class T>
Sequence<T> *ListSequence<T>::setImmutable(int index, T data)
{
    ListSequence<T> *newSequence = new ListSequence<T>(*this);
    newSequence->set(index, data);
    return newSequence;
}

template <class T>
Sequence<T> *ListSequence<T>::appendImmutable(T item)
{
    ListSequence<T> *newSequence = new ListSequence<T>(*this);
    newSequence->append(item);
    return newSequence;
}

template <class T>
Sequence<T> *ListSequence<T>::prependImmutable(T item)
{
    ListSequence<T> *newSequence = new ListSequence<T>(*this);
    newSequence->prepend(item);
    return newSequence;
}

template <class T>
Sequence<T> *ListSequence<T>::insertAtImmutable(T item, int index)
{
    ListSequence<T> *newSequence = new ListSequence<T>(*this);
    newSequence->insertAt(item, index);
    return newSequence;
}

template <class T>
Sequence<T> *ListSequence<T>::concatImmutable(Sequence<T> *list)
{
    ListSequence<T> *newSequence = new ListSequence<T>(*this);
    for (int i = 0; i < list->getLength(); i++)
    {
        newSequence->append(list->get(i));
    }
    return newSequence;
}

template <class T>
void ListSequence<T>::print()
{
    list.print();
}

template <class T>
T &ListSequence<T>::operator[](int index)
{
    if (index < 0 || index >= getLength())
    {
        throw std::out_of_range("Index out of range");
    }
    return list[index];
}

template <class T>
const T &ListSequence<T>::operator[](int index) const
{
    if (index < 0 || index >= getLength())
    {
        throw std::out_of_range("Index out of range");
    }
    return list[index];
}
