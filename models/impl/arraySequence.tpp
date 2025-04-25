
template <class T>
ArraySequence<T>::ArraySequence() : array() {}

template <class T>
ArraySequence<T>::ArraySequence(T *items, int count)
{
    if (items == nullptr && count > 0)
    {
        throw std::invalid_argument("Null array with non-zero count");
    }
    if (count < 0)
    {
        throw std::invalid_argument("Negative count");
    }
    array = DynamicArray<T>(items, count);
}

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
T ArraySequence<T>::get(int index) {
    if (index < 0 || index >= array.getSize()) {
        throw std::out_of_range("Index " + std::to_string(index) +
                              " out of range [0, " +
                              std::to_string(array.getSize()-1) + "]");
    }
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
    if (startIndex < 0 || endIndex >= this->getLength() || startIndex > endIndex)
    {
        throw std::out_of_range("Invalid subsequence range");
    }

    ArraySequence<T> *newSequence = new ArraySequence<T>();
    for (int i = startIndex; i <= endIndex; i++)
    {
        newSequence->append(this->get(i));
    }
    return newSequence;
}

template <class T>
Sequence<T> *ArraySequence<T>::append(T item)
{
    array.append(item);
    return this;
}

template <class T>
Sequence<T> *ArraySequence<T>::prepend(T item)
{
    array.prepend(item);
    return this;
}

template <class T>
Sequence<T> *ArraySequence<T>::insertAt(T item, int index)
{
    if (index < 0 || index > getLength())
    {
        throw std::out_of_range("Invalid index for insertion");
    }
    array.insertAt(item, index);
    return this;
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

template <class T>
Sequence<T> *ArraySequence<T>::concat(Sequence<T> *other)
{
    if (!other)
    {
        throw std::invalid_argument("Cannot concatenate with null sequence");
    }

    for (int i = 0; i < other->getLength(); i++)
    {
        array.append(other->get(i));
    }
    return this;
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
    ArraySequence<T> *newSequence = new ArraySequence<T>(*this);
    newSequence->append(item);
    return newSequence;
}

template <class T>
Sequence<T> *ArraySequence<T>::prependImmutable(T item)
{
    ArraySequence<T> *newSequence = new ArraySequence<T>(*this);
    newSequence->prepend(item);
    return newSequence;
}

template <class T>
Sequence<T> *ArraySequence<T>::insertAtImmutable(T item, int index)
{
    ArraySequence<T> *newSequence = new ArraySequence<T>(*this);
    newSequence->insertAt(item, index);
    return newSequence;
}

template <class T>
Sequence<T> *ArraySequence<T>::concatImmutable(Sequence<T> *other)
{
    ArraySequence<T> *newSequence = new ArraySequence<T>(*this);
    for (int i = 0; i < other->getLength(); i++)
    {
        newSequence->append(other->get(i));
    }
    return newSequence;
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
