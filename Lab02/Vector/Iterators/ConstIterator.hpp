#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include "../Iterators/ConstIterator.h"

// конструктор копирования итератора
template<typename T>
ConstIterator<T>::ConstIterator(const ConstIterator<T>& iterator)
{
    this->ptr = iterator.ptr;
    this->index = iterator.index;
    this->size = iterator.size;
}

template<typename T>
ConstIterator<T>::ConstIterator(const Vector<T>& vector)
{
    this->index = 0;
    this->size = vector.getSize();
    this->ptr = vector.values;
}

// операторы разыменования
template<typename T>
const T& ConstIterator<T>::operator *() const
{
    expiredCheck(__LINE__);
    validCheck(__LINE__);

    return *getCurrPtr();
}

template<typename T>
const T* ConstIterator<T>::operator ->() const
{
    expiredCheck(__LINE__);
    validCheck(__LINE__);

    return getCurrPtr();
}

// операция присваивания
template<typename T>
ConstIterator<T>& ConstIterator<T>::operator =(const ConstIterator<T>& iterator)
{
    iterator.expiredCheck(__LINE__);

    ptr = iterator.ptr;
    index = iterator.index;
    size = iterator.size;

    return *this;
}

// операции сложения
template<typename T>
ConstIterator<T>& ConstIterator<T>::operator +=(int number)
{
    expiredCheck(__LINE__);
    index += number;

    return *this;
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator +(int number) const
{
    expiredCheck(__LINE__);
    ConstIterator<T> iterator(*this);
    if (index + number <= size)
    {
        iterator += number;
    }
    return iterator;
}

template<typename Type>
ConstIterator<Type> ConstIterator<Type>::operator ++(int)
{
    expiredCheck(__LINE__);
    if (index < size)
        ++(*this);

    return *this;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator ++()
{
    expiredCheck(__LINE__);
    if (index < size)
        ++index;

    return *this;
}

// операции вычитания
template<typename T>
ConstIterator<T>& ConstIterator<T>::operator -=(int number)
{
    expiredCheck(__LINE__);
    if (index >= number - 1)
        index -= number;

    return *this;
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator -(int number) const
{
    expiredCheck(__LINE__);

    ConstIterator<T> iterator(*this);
    if (index >= number - 1)
        iterator -= number;

    return iterator;
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator --(int)
{
    expiredCheck(__LINE__);
    if (index >= 0)
    {
        --(*this);
    }
    return *this;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator --()
{
    expiredCheck(__LINE__);
    if (index >= 0)
        --index;

    return *this;
}

// логические операции
template<typename T>
bool ConstIterator<T>::operator <=(const ConstIterator<T>& iterator) const
{
    expiredCheck(__LINE__);

    return ptr <= iterator.ptr;
}

template<typename T>
bool ConstIterator<T>::operator <(const ConstIterator<T>& iterator) const
{
    expiredCheck(__LINE__);

    return ptr < iterator.ptr;
}

template<class T>
bool ConstIterator<T>::operator >=(const ConstIterator<T>& iterator) const
{
    expiredCheck(__LINE__);

    return ptr >= iterator.ptr;
}

template<typename T>
bool ConstIterator<T>::operator >(const ConstIterator<T>& iterator) const
{
    expiredCheck(__LINE__);

    return ptr > iterator.ptr;
}

template<typename T>
bool ConstIterator<T>::operator ==(const ConstIterator<T>& iterator) const
{
    expiredCheck(__LINE__);

    return ptr == iterator.ptr;
}

template<typename T>
bool ConstIterator<T>::operator !=(const ConstIterator<T>& iterator) const
{
    expiredCheck(__LINE__);

    return ptr != iterator.ptr;
}

template<typename T>
const T& ConstIterator<T>::operator [](int index) const
{
    return *(operator+(index));
}

template<typename T>
ConstIterator<T>::operator bool() const
{
    expiredCheck(__LINE__);
    bool res = true;
    if (index >= size || index < 0 || size == 0)
    {
        res = false;
    }
    return res;
}

// проверки работы с объектом и итератором
template<typename T>
void ConstIterator<T>::expiredCheck(int line) const
{
    if (ptr.expired())
    {
        throw DeletedObject(__FILE__, typeid(*this).name(), line);
    }
}

template<typename T>
void ConstIterator<T>::validCheck(int line) const
{
    if (this->index < 0 || this->index >= this->size)
    {
        throw InvalidIterator(__FILE__, typeid(*this).name(), line);
    }
}

// достать текущий указатель на объект
template<typename T>
T* ConstIterator<T>::getCurrPtr() const
{
    std::shared_ptr<T> copy = ptr.lock();
    return copy.get() + index;
}

#endif // CONST_ITERATOR_HPP