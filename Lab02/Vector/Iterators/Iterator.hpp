#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "../Iterators/Iterator.h"

// конструктор копирования итератора
template<typename T>
Iterator<T>::Iterator(const Iterator<T>& iterator)
{
    this->ptr = iterator.ptr;
    this->index = iterator.index;
    this->size = iterator.size;
}

template<typename T>
Iterator<T>::Iterator(const Vector<T>& vector)
{
    this->index = 0;
    this->size = vector.getSize();
    this->ptr = vector.values;
}

// операторы разыменования
template<typename T>
T& Iterator<T>::operator *()
{
    expiredCheck(__LINE__);
    validCheck(__LINE__);

    return *getCurrPtr();
}

template<typename T>
const T& Iterator<T>::operator *() const
{
    expiredCheck(__LINE__);
    validCheck(__LINE__);

    return *getCurrPtr();
}

template<typename T>
T* Iterator<T>::operator ->()
{
    expiredCheck(__LINE__);
    validCheck(__LINE__);

    return getCurrPtr();
}

template<typename T>
const T* Iterator<T>::operator ->() const
{
    return *(operator+(index));
}

template<typename T>
T& Iterator<T>::operator [](int index)
{
    return *(operator+(index));
}

template<typename T>
const T& Iterator<T>::operator [](int index) const
{
    expiredCheck(__LINE__);
    validCheck(__LINE__);

    std::shared_ptr<T[]> copy_ptr = ptr.lock();
    return copy_ptr.get() + index;
}

// операция присваивания
template<typename T>
Iterator<T>& Iterator<T>::operator =(const Iterator<T>& iterator)
{
    iterator.expiredCheck(__LINE__);

    ptr = iterator.ptr;
    index = iterator.index;
    size = iterator.size;

    return *this;
}

// операции сложения
template<typename T>
Iterator<T>& Iterator<T>::operator +=(int number)
{
    expiredCheck(__LINE__);
    index += number;

    return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator +(int number) const
{
    expiredCheck(__LINE__);
    Iterator<T> iterator(*this);
    if (index + number <= size)
    {
        iterator += number;
    }
    return iterator;
}

template<typename T>
Iterator<T> Iterator<T>::operator ++(int)
{
    expiredCheck(__LINE__);
    if (index < size)
    {
        ++(*this);
    }
    return *this;
}

template<typename T>
Iterator<T>& Iterator<T>::operator ++()
{
    expiredCheck(__LINE__);
    if (index < size)
    {
        ++index;
    }
    return *this;
}

// операции вычитания
template<typename T>
Iterator<T>& Iterator<T>::operator -=(int number)
{
    expiredCheck(__LINE__);
    if (index >= number - 1)
    {
        index -= number;
    }
    return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator -(int number) const
{
    expiredCheck(__LINE__);

    Iterator<T> iterator(*this);
    if (index >= number - 1)
    {
        iterator -= number;
    }
    return iterator;
}

template<typename T>
Iterator<T> Iterator<T>::operator --(int)
{
    expiredCheck(__LINE__);
    if (index >= 0)
    {
        --(*this);
    }
    return *this;
}

template<typename T>
Iterator<T>& Iterator<T>::operator --()
{
    expiredCheck(__LINE__);
    if (index >= 0)
    {
        --index;
    }
    return *this;
}

// логические операции
template<typename T>
bool Iterator<T>::operator <=(const Iterator<T>& iterator) const
{
    expiredCheck(__LINE__);

    return ptr <= iterator.ptr;
}

template<typename T>
bool Iterator<T>::operator <(const Iterator<T>& iterator) const
{
    expiredCheck(__LINE__);

    return ptr < iterator.ptr;
}

template<class T>
bool Iterator<T>::operator >=(const Iterator<T>& iterator) const
{
    expiredCheck(__LINE__);

    return ptr >= iterator.ptr;
}

template<typename T>
bool Iterator<T>::operator >(const Iterator<T>& iterator) const
{
    expiredCheck(__LINE__);

    return ptr > iterator.ptr;
}

template<typename T>
bool Iterator<T>::operator ==(const Iterator<T>& iterator) const
{
    expiredCheck(__LINE__);

    return ptr == iterator.ptr;
}

template<typename T>
bool Iterator<T>::operator !=(const Iterator<T>& iterator) const
{
    expiredCheck(__LINE__);

    return ptr != iterator.ptr;
}

template<typename T>
Iterator<T>::operator bool() const
{
    expiredCheck(__LINE__);
    bool res = true;
    if (index >= size || index < 0 || size == 0)
        res = false;

    return res;
}

// проверки работы с объектом и итератором
template<typename T>
void Iterator<T>::expiredCheck(int line) const
{
    if (ptr.expired())
    {
        throw DeletedObject(__FILE__, typeid(*this).name(), line);
    }
}

template<typename T>
void Iterator<T>::validCheck(int line) const 
{
    if (this->index < 0 || this->index >= this->size)
    {
        throw InvalidIterator(__FILE__, typeid(*this).name(), line);
    }
}

// достать текущий указатель на объект
template<typename T>
T* Iterator<T>::getCurrPtr() const
{
    std::shared_ptr<T[]> copy_ptr = ptr.lock();
    return copy_ptr.get() + index;
}

#endif // ITERATOR_HPP