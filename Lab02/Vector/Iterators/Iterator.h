#ifndef ITERATOR_H
#define ITERATOR_H

#include <memory>
#include <iostream>

#include "../Iterators/BaseIterator.h"
#include "../Exceptions/Exceptions.hpp"

template<typename T>
class Vector;

template<typename T>
class Iterator : public BaseIterator
{
public:
    Iterator();
    Iterator(const Iterator<T>&);
    Iterator(const Vector<T>&);

    T& operator *();
    const T& operator *() const;
    T* operator ->();
    const T* operator ->() const;
    operator bool() const;

    T& operator [](int index);
    const T& operator [](int index) const;

    Iterator<T>& operator =(const Iterator<T>& iterator);

    Iterator<T>& operator +=(int number);
    Iterator<T>& operator ++();     // ���������� ���������
    Iterator<T>  operator ++(int);  // ����������� ���������
    Iterator<T>  operator + (int number) const;

    Iterator<T>& operator -=(int number);
    Iterator<T>& operator --();    // ���������� ���������
    Iterator<T>  operator --(int); // ����������� ���������
    Iterator<T>  operator - (int number) const;

    bool operator <=(const Iterator<T>& iterator) const;
    bool operator <(const Iterator<T>& iterator) const;
    bool operator >=(const Iterator<T>& iterator) const;
    bool operator >(const Iterator<T>& iterator) const;
    bool operator ==(const Iterator<T>& iterator) const;
    bool operator !=(const Iterator<T>& iterator) const;

protected:
    T* getCurrPtr() const;

    void expiredCheck(int) const;   // �������� ������� �� null
    void validCheck(int) const; // ���������

private:
    std::weak_ptr<T[]> ptr;
};

#endif // ITERATOR_H