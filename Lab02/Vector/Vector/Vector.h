#ifndef VECTOR_H
#define VECTOR_H

#include <stdarg.h>

#include <iostream>
#include <cstdlib>
#include <memory>
#include <stdexcept>

#include "../Vector/BaseVector.h"
#include "../Iterators/Iterator.hpp"
#include "../Iterators/ConstIterator.hpp"
#include "../Exceptions/Exceptions.hpp"

template<typename T>
class Vector : public BaseVector
{
public:
    friend class Iterator<T>;
    friend class ConstIterator<T>;

    Vector();
    explicit Vector(int len);
    Vector(int len, T* array);
    Vector(int len, T vector, ...);
    Vector(std::initializer_list<T> args);
    explicit Vector(const Vector<T>& vector);
    Vector(Vector<T>&& vector) noexcept;

    virtual ~Vector();

    Vector<T>& operator =(const Vector<T>& vector);
    Vector<T>& operator =(std::initializer_list<T> args);
    Vector<T>& operator =(Vector<T>&& vector);

    bool setItem(int index, const T& item);
    T& getItem(int index);
    const T& getItem(int index) const;

    T& operator [](int index);
    const T& operator [](int index) const;

    T getLength() const;
    int  getSize() const noexcept override;
    bool isEmpty() const noexcept override;

    bool isZero() const;
    bool isSingle() const;

    Vector<T> getSingle() const;

    template<typename U>
    decltype(auto) operator +(const U&) const;
    Vector<T>& operator +=(const T&);
    template<typename U>
    decltype(auto) sumNum(const U&) const;
    Vector<T>& sumNumEqual(const T&);

    template<typename U>
    decltype(auto) operator +(const Vector<U>&) const;
    Vector<T>& operator +=(const Vector<T>&);
    template<typename U>
    decltype(auto) sum(const Vector<U>&) const;
    Vector<T>& sumEqual(const Vector<T>&);

    template<typename U>
    decltype(auto) operator -(const U&) const;
    Vector<T>& operator -=(const T&);
    template<typename U>
    decltype(auto) subNum(const U&) const;
    Vector<T>& subNumEqual(const T&);

    template<typename U>
    decltype(auto) operator -(const Vector<U>&) const;
    Vector<T>& operator -=(const Vector<T>&);
    template<typename U>
    decltype(auto) sub(const Vector<U>&) const;
    Vector<T>& subEqual(const Vector<T>&);
    Vector<T> operator -();
    Vector<T> reverse();

    template<typename U>
    decltype(auto) operator *(const U& number) const;
    Vector<T>& operator *=(const T& number);
    template<typename U>
    decltype(auto) mulNum(const U& number) const;
    Vector<T>& mulNumEqual(const T& number);

    template<typename U>
    decltype(auto) operator ^(const Vector<U>&) const;
    Vector<T>& operator ^=(const Vector<T>&);
    template<typename U>
    decltype(auto) mulElems(const Vector<U>&) const;
    Vector<T>& mulElemsEqual(const Vector<T>&);

    template<typename U>
    auto operator *(const Vector<U>&) const;
    T  operator *=(const Vector<T>&);
    template<typename U>
    auto scalarMul(const Vector<U>&) const;
    T  scalarMulEqual(const Vector<T>&);

    template<typename U>
    decltype(auto) operator &(const Vector<U>&) const;
    Vector<T>& operator &=(const Vector<T>&);
    template<typename U>
    decltype(auto) vectorMul(const Vector<U>&) const;
    Vector<T>& vectorMulEqual(const Vector<T>&);

    template<typename U>
    decltype(auto) operator /(const U& number) const;
    Vector<T>& operator /=(const T& number);
    template<typename U>
    decltype(auto) divNum(const U&) const;
    Vector<T>& divNumEqual(const T& number);

    template<typename U>
    decltype(auto) operator /(const Vector<U>&) const;
    Vector<T>& operator /=(const Vector<T>&);
    template<typename U>
    decltype(auto) div(const Vector<U>&) const;
    Vector<T>& divEqual(const Vector<T>&);

    bool operator ==(const Vector<T>&) const;
    bool operator !=(const Vector<T>&) const;

    Iterator<T> begin() noexcept;
    Iterator<T> end() noexcept;

    ConstIterator<T> begin() const noexcept;
    ConstIterator<T> end() const noexcept;

protected:
    T sumValue();
    void allocNewVectorMem(int amount);

private:
    std::shared_ptr<T[]> values;
};

template<typename T>
std::ostream& operator <<(std::ostream& os, const Vector<T>& v)
{
    Iterator<T> iter(v);
    os << '(';
    for (; iter; iter++)
    {
        if (iter + 1)
        {
            os << *iter << ", ";
        }
        else
        {
            os << *iter;
        }
    }
    os << ')';
    return os;
}

#endif // VECTOR_H