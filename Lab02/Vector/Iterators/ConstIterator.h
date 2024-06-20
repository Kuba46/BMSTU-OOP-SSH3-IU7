#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include <memory>
#include <iostream>

#include "../Iterators/BaseIterator.h"

template<typename T>
class Vector;

template<typename T>
class ConstIterator : public BaseIterator
{
public:
    ConstIterator(const ConstIterator<T>&);
    ConstIterator(const Vector<T>&);

    const T& operator *() const;
    const T* operator ->() const;

    const T& operator [](int index) const;
    operator bool() const;

    ConstIterator<T>& operator =(const ConstIterator<T>& iterator);

    ConstIterator<T>& operator +=(int number);
    ConstIterator<T>& operator ++();
    ConstIterator<T>  operator ++(int);
    ConstIterator<T>  operator + (int number) const;

    ConstIterator<T>& operator -=(int number);
    ConstIterator<T>& operator --();
    ConstIterator<T>  operator --(int);
    ConstIterator<T>  operator - (int number) const;

    bool operator <=(const ConstIterator<T>& iterator) const;
    bool operator <(const ConstIterator<T>& iterator) const;
    bool operator >=(const ConstIterator<T>& iterator) const;
    bool operator >(const ConstIterator<T>& iterator) const;
    bool operator ==(const ConstIterator<T>& iterator) const;
    bool operator !=(const ConstIterator<T>& iterator) const;

protected:
    T* getCurrPtr() const;

    void expiredCheck(int) const;   // проверка объекта на null
    void validCheck(int) const; // проверака

private:
    std::weak_ptr<T[]> ptr;
};

#endif // CONST_ITERATOR_H