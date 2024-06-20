#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../Vector/Vector.h"

template<typename T>
Vector<T>::Vector()
{
    size = 0;
    allocNewVectorMem(size);
}

template<typename T>
Vector<T>::Vector(int len)
{
    if (len < 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);

    size = len;
    allocNewVectorMem(size);
    if (!values)
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__);

    Iterator<T> iterator(*this);
    for (; iterator; iterator++)
        *iterator = 0;
}

// Êîíñòðóêòîð íà îñíîâå ìàññèâà.
template<typename T>
Vector<T>::Vector(int len, T* array)
{
    if (len <= 0)
    {
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);
    }
    if (!array)
    {
        throw InvalidCopyArrayPointer(__FILE__, typeid(*this).name(), __LINE__);
    }
    size = len;
    allocNewVectorMem(size);
    if (!values)
    {
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__);
    }
    Iterator<T> iterator(*this);
    for (int i = 0; iterator; i++, iterator++)
    {
        *iterator = array[i];
    }
}

// Êîíñòðóêòîð íà îñíîâå ýëåìåíòîâ.
template<typename T>
Vector<T>::Vector(int len, T vector, ...)
{
    if (len < 1)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);

    size = len;
    allocNewVectorMem(size);
    if (!values)
    {
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__);
    }
    Iterator<T> iterator(*this);
    va_list var;
    va_start(var, vector);
    for (; iterator; iterator++)
    {
        *iterator = vector;
        vector = va_arg(var, T);
    }
    va_end(var);
}

// Êîíñòðóêòîð ñ èíèöèàëèçàöèåé.
template<typename T>
Vector<T>::Vector(std::initializer_list<T> args)
{
    if (args.size() == 0)
    {
        Vector();
        return;
    }

    size = int(args.size());
    allocNewVectorMem(size);
    if (!values)
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__);

    Iterator<T> iterator(*this);
    for (auto& currentItem : args)
    {
        *iterator = currentItem;
        iterator++;
    }
}

// Êîíñòðóêòîð îò âåêòîðà.
template<typename T>
Vector<T>::Vector(const Vector<T>& vector)
{
    size = vector.size;
    allocNewVectorMem(size);
    if (!values)
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__);

    Iterator<T> iteratorTo(*this);
    Iterator<T> iteratorFrom(vector);
    for (; iteratorTo; iteratorFrom++, iteratorTo++)
        *iteratorTo = *iteratorFrom;
}

// Êîíñòðóêòîð ïåðåíîñîì.
template<typename T>
Vector<T>::Vector(Vector<T>&& vector) noexcept
{
    size = vector.size;
    allocNewVectorMem(size);
    values = vector.values;
    vector.values = nullptr;
}

// Äåñòðóêòîð.
template<typename T>
Vector<T>::~Vector()
{
    if (values)
        values.reset();
}

// Îïåðàòîðû ïðèñâàèâàíèÿ
template<typename T>
Vector<T>& Vector<T>::operator =(const Vector<T>& vector)
{
    size = vector.size;
    allocNewVectorMem(size);
    if (!values)
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__);

    Iterator<T> iteratorTo(*this);
    Iterator<T> iteratorFrom(vector);
    for (; iteratorTo; iteratorFrom++, iteratorTo++)
        *iteratorTo = *iteratorFrom;

    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator =(std::initializer_list<T> args)
{
    size = int(args.size());
    allocNewVectorMem(size);
    if (!values)
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__);

    Iterator<T> iterator(*this);
    for (auto& currentItem : args)
    {
        *iterator = currentItem;
        iterator++;
    }

    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator =(Vector<T>&& vector)
{
    size = vector.size;
    allocNewVectorMem(size);
    if (!values)
    {
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__);
    }
    values = vector.values;
    vector.values = nullptr;

    return *this;
}

// Ïîëó÷åíèå ýëåìåíòà ïî èíäåêñó.
template<typename T>
T& Vector<T>::getItem(int index)
{
    if (index < 0 || index >= size)
        throw IndexVectorError(__FILE__, typeid(*this).name(), __LINE__);

    Iterator<T> iterator(*this);
    for (int i = 0; i < index; i++, iterator++);

    return *iterator;
}

// Ïîëó÷åíèå ýëåìåíòà ïî èíäåêñó Const.
template<typename T>
const T& Vector<T>::getItem(int index) const 
{
    if (index < 0 || index >= size)
    {
        throw IndexVectorError(__FILE__, typeid(*this).name(), __LINE__);
    }
    Iterator<T> iterator(*this);
    for (int i = 0; i < index; i++, iterator++) {}

    return *iterator;
}

template<typename T>
int Vector<T>::getSize() const noexcept
{
    return size;
}

template<typename T>
bool Vector<T>::isEmpty() const noexcept
{
    return bool(size);
}

// Óñòàíîâèòü çíà÷åíè ïî èíäåêñó
template<typename T>
bool Vector<T>::setItem(int index, const T& item)
{
    bool res = true;
    if (index < 0 || index >= size)
        res = false;
    else
    {
        Iterator<T> iterator(*this);
        for (int i = 0; i < index; i++, iterator++);
        (*iterator) = item;
    }
    return res;
}

// Îïåðàòîð èíäåêñàöèè.
template<typename T>
T& Vector<T>::operator[] (int index)
{
    return getItem(index);
}

// Îïåðàòîð èíäåêñàöèè Const.
template<typename T>
const T& Vector<T>::operator [](int index) const
{
    return getItem(index);
}

// Ïðîâåðêà íà íóëåâîé âåêòîð - äëèíà ðàâíàÿ 0
template<typename T>
bool Vector<T>::isSingle() const
{
    if (fabs(getLength() - 1) < DBL_EPSILON)
        return true;
    return false;
}

// Ïðîâåðêà íà åäèíè÷íûé âåêòîð - äëèíà ðàâíàÿ 1
template<typename T>
bool Vector<T>::isZero() const
{
    if (getLength() == 0)
        return true;
    return false;
}

// âû÷èñëåíèå äëèíû âåêòîðà
template<typename T>
T Vector<T>::getLength() const
{
    if (size < 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);

    Iterator<T> iterator(*this);
    T sum = 0.00;
    for (; iterator; iterator++)
        sum += *iterator * *iterator;
    sum = std::sqrt(sum);
    return sum;
}

template<typename T>
Vector<T> Vector<T>::getSingle() const
{
    if (size <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);

    Vector<T> singleVector(*this);

    T len = getLength();
    Iterator<T> iterator(singleVector);

    for (; iterator; iterator++)
        *iterator /= len;
    return singleVector;
}


template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::operator *(const U& num) const
{
    if (size <= 0)
        EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);

    Vector<decltype((*this)[0] * num)> newVector(*this);
    Iterator<Type> iterator(newVector);
    for (; iterator; iterator++)
        *iterator *= num;

    return newVector;
}

template<typename T>
template<typename U>
decltype(auto) Vector<T>::mulNum(const U& num) const
{
    return operator*(num);
}

template<typename T>
Vector<T>& Vector<T>::operator *=(const T& num)
{
    if (size < 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);

    Iterator<T> iterator(*this);
    for (; iterator; iterator++)
        *iterator *= num;
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::mulNumEqual(const T& num)
{
    return operator*=(num);
}

// Óìíîæåíèå ýëåìåíòîâ äâóõ âåêòîðîâ
template<typename T>
template<typename U>
decltype(auto) Vector<T>::operator ^(const Vector<U>& vector) const
{
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__);

    Vector<decltype((*this)[0] * vector[0])> newVector(size);

    Iterator<decltype((*this)[0] * vector[0])> resIter(newVector);
    Iterator<T> fIter(*this);
    Iterator<U> sIter(vector);

    for (int i = 0; resIter; i++, resIter++, fIter++, sIter++)
    {
        *resIter = *fIter * *sIter;
    }

    return newVector;
}

template<typename T>
Vector<T>& Vector<T>::operator ^=(const Vector<T>& vector)
{
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__);

    Iterator<T> fIter(*this);
    Iterator<T> sIter(vector);

    for (int i = 0; fIter; i++, fIter++, sIter++)
    {
        *fIter = *fIter * *sIter;
    }

    return (*this);
}

template<typename T>
template<typename U>
decltype(auto) Vector<T>::mulElems(const Vector<U>& vector) const
{
    return operator^(vector);
}

template<typename T>
Vector<T>& Vector<T>::mulElemsEqual(const Vector<T>& vector)
{
    return operator^=(vector);
}

// Ñêàëÿðíîå ïðîèçâåäåíèå
template<typename T>
template<typename U>
auto Vector<T>::operator *(const Vector<U>& vector) const
{
    if (size <= 0 || vector.size <= 0)
        EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__);

    Vector<decltype ((*this)[0] * vector[0])> newVector(size);
    newVector = (*this) ^ vector;
    return newVector.sumValue();
}

template<typename T>
T Vector<T>::operator *=(const Vector<T>& vector)
{
    if (size <= 0 || vector.size <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__);

    (*this) ^= vector;
    return this->sumValue();
}

template<typename T>
template<typename U>
auto Vector<T>::scalarMul(const Vector<U>& vector) const
{
    return operator*(vector);
}

template<typename T>
T Vector<T>::scalarMulEqual(const Vector<T>& vector)
{
    return operator*=(vector);
}

// Âåêòîðíîå ïðîèçâåäåíèå
template<typename T>
template<typename U>
decltype(auto) Vector<T>::operator &(const Vector<U>& vector) const
{
    if (size <= 0 || vector.getSize() <= 0)
        EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__);

    if (size != 3)
        return Vector<T>();

    decltype((*this)[0] * vector[0]) x = (*this)[1] * vector[2] - (*this)[2] * vector[1];
    decltype((*this)[0] * vector[0]) y = (*this)[2] * vector[0] - (*this)[0] * vector[2];
    decltype((*this)[0] * vector[0]) z = (*this)[0] * vector[1] - (*this)[1] * vector[0];

    Vector<decltype((*this)[0] * vector[0])> new_vector(3, x, y, z);
    return new_vector;
}

template<typename T>
template<typename U>
decltype(auto) Vector<T>::vectorMul(const Vector<U>& vector) const
{
    return operator&(vector);
}

template<typename T>
Vector<T>& Vector<T>::operator &=(const Vector<T>& vector)
{
    if (size <= 0 || vector.size <= 0)
        EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__);

    if (size != 3)
        return *(new Vector<T>);

    T x = (*this)[1] * vector[2] - (*this)[2] * vector[1];
    T y = (*this)[2] * vector[0] - (*this)[0] * vector[2];
    T z = (*this)[0] * vector[1] - (*this)[1] * vector[0];

    *this = Vector<T>(3, x, y, z);
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::vectorMulEqual(const Vector<T>& vector)
{
    return operator&=(vector);
}

// Äåëåíèå äâóõ âåêòîðîâ
template<typename T>
template<typename U>
decltype(auto) Vector<T>::operator /(const Vector<U>& vector) const
{
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__);

    Vector<decltype((*this)[0] + vector[0])> newVector(size);

    Iterator<decltype((*this)[0] + vector[0])> resIter(newVector);
    Iterator<T> fIter((*this));
    Iterator<U> sIter(vector);

    for (int i = 0; resIter; i++, resIter++, fIter++, sIter++)
    {
        if (std::fabs(*sIter) < DBL_EPSILON)
        {
            throw ZeroDivError(__FILE__, typeid(*this).name(), __LINE__);
        }
        *resIter = *fIter / *sIter;
    }
    return newVector;
}

template<typename T>
Vector<T>& Vector<T>::operator /=(const Vector<T>& vector)
{
    if (size <= 0 || vector.getSize() <= 0)
        EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__);

    Iterator<T> fIter((*this));
    Iterator<T> sIter(vector);

    for (int i = 0; fIter; i++, fIter++, sIter++)
    {
        if (fabs(*sIter) < DBL_EPSILON)
        {
            throw ZeroDivError(__FILE__, typeid(*this).name(), __LINE__);
        }
        *fIter /= *sIter;
    }

    return *this;
}

template<typename T>
template<typename U>
decltype(auto) Vector<T>::div(const Vector<U>& vector) const
{
    return operator/(vector);
}

template<typename T>
Vector<T>& Vector<T>::divEqual(const Vector<T>& vector)
{
    return operator/=(vector);
}

// Äåëåíèå âåêòîðà íà ÷èñëî
template<typename T>
Vector<T>& Vector<T>::operator /=(const T& number)
{
    if (size <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);
    if (number == 0)
        throw ZeroDivError(__FILE__, typeid(*this).name(), __LINE__);

    Iterator<T> iterator(*this);
    for (; iterator; iterator++)
        *iterator /= number;
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::divNumEqual(const T& number)
{
    return operator/=(number);
}

template<typename T>
template<typename U>
decltype(auto) Vector<T>::operator /(const U& number) const
{
    if (size <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);
    if (number == 0)
        throw ZeroDivError(__FILE__, typeid(*this).name(), __LINE__);

    Vector<decltype((*this)[0] / number)> new_vector(*this);
    Iterator<decltype((*this)[0] / number)> iterator(new_vector);
    for (; iterator; iterator++)
        *iterator /= number;
    return new_vector;
}

template<typename T>
template<typename U>
decltype(auto) Vector<T>::divNum(const U& number) const
{
    return operator/(number);
}


// Ðàâíû ëè âåêòîðà.
template<typename T>
bool Vector<T>::operator ==(const Vector<T>& vector) const {
    bool res = true;
    if (size < 0 || vector.vector_size < 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);

    if (size != vector.size)
        res = true;
    else
    {
        Iterator<T> fIter(*this);
        Iterator<T> sIter(vector);
        for (; res && fIter; sIter++, fIter++)
            if (fabs(*fIter - *sIter) > DBL_EPSILON)
                res = false;
    }

    return res;
}

// Ðàçëè÷íû ëè âåêòîðà.
template<typename T>
bool Vector<T>::operator !=(const Vector<T>& vector) const
{
    bool res = false;
    if (size < 0 || vector.vector_size < 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);
    if (size != vector.size)
        res = true;
    else
    {
        Iterator<T> fIter(*this);
        Iterator<T> sIter(vector);

        for (; !res && fIter; sIter++)
            if (*fIter != *sIter)
                res = true;
    }

    return res;
}

// Ñóììèðîâàíèå âñåõ ýëåìåíòîâ.
template<typename T>
T Vector<T>::sumValue()
{
    if (size <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);

    Iterator<T> iterator(*this);
    T summary = 0;
    for (; iterator; iterator++)
        summary += *iterator;

    return summary;
}

// Ñóììà âåêòîðîâ
template<typename T>
template<typename U>
decltype(auto) Vector<T>::operator +(const Vector<U>& vector) const
{
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__);

    Vector<decltype((*this)[0] + vector[0])> newVector(size);

    Iterator<decltype((*this)[0] + vector[0])> resIter(newVector);
    Iterator<T> fIter((*this));
    Iterator<U> sIter(vector);
    for (int i = 0; resIter; i++, resIter++, fIter++, sIter++)
        *resIter = *fIter + *sIter;

    return newVector;
}

template<typename T>
template<typename U>
decltype(auto) Vector<T>::sum(const Vector<U>& vector) const
{
    return operator+(vector);
}

template<typename T>
Vector<T>& Vector<T>::operator +=(const Vector<T>& vector)
{
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__);

    Iterator<T> fIter((*this));
    Iterator<T> sIter(vector);
    for (int i = 0; fIter; i++, fIter++, sIter++)
        *fIter = *fIter + *sIter;

    return *this;
}

template<typename Type>
Vector<Type>& Vector<Type>::sumEqual(const Vector<Type>& vector)
{
    return operator+=(vector);
}

// Cóììà âåêòîðà è ÷èñëà
template<typename T>
template<typename U>
decltype(auto) Vector<T>::operator +(const U& number) const
{
    if (size <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);

    Vector<decltype((*this)[0] + number)> newVector(size);

    Iterator<decltype((*this)[0] + number)> resIter(newVector);
    Iterator<T> fIter((*this));
    for (int i = 0; resIter; i++, resIter++, fIter++)
        *resIter = *fIter + number;

    return newVector;
}

template<typename T>
Vector<T>& Vector<T>::operator +=(const T& number)
{
    if (size <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);

    Iterator<T> fIter((*this));
    for (int i = 0; fIter; i++, fIter++)
        *fIter += number;

    return (*this);
}

template<typename T>
template<typename U>
decltype(auto) Vector<T>::sumNum(const U& number) const
{
    return operator +(number);
}

template<typename T>
Vector<T>& Vector<T>::sumNumEqual(const T& number)
{
    return operator+=(number);
}

// Ðàçíîñòü âåêòîðîâ.
template<typename T>
template<typename U>
decltype(auto) Vector<T>::operator -(const Vector<U>& vector) const
{
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__);

    Vector<decltype((*this)[0] - vector[0])> newVector(size);
    Iterator<decltype((*this)[0] - vector[0])> resIter(newVector);
    Iterator<T> fIter((*this));
    Iterator<U> sIter(vector);

    for (int i = 0; resIter; i++, resIter++, fIter++, sIter++)
        *resIter = *fIter - *sIter;

    return newVector;
}

template<typename T>
Vector<T>& Vector<T>::operator -=(const Vector<T>& vector)
{
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__);

    Iterator<T> fIter((*this));
    Iterator<T> sIter(vector);

    for (int i = 0; fIter; i++, fIter++, sIter++)
        *fIter = *fIter - *sIter;

    return *this;
}

template<typename T>
template<typename U>
decltype(auto) Vector<T>::sub(const Vector<U>& vector) const
{
    return operator-(vector);
}

template<typename T>
Vector<T>& Vector<T>::subEqual(const Vector<T>& vector)
{
    return operator-=(vector);
}

template<typename T>
template<typename U>
decltype(auto) Vector<T>::operator -(const U& number) const
{
    if (size <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);

    Vector<decltype((*this)[0] + number)> newVector(size);

    Iterator<decltype((*this)[0] + number)> resIter(newVector);
    Iterator<T> fIter((*this));
    for (int i = 0; resIter; i++, resIter++, fIter++)
        *resIter = *fIter - number;

    return newVector;
}

template<typename T>
Vector<T>& Vector<T>::operator -=(const T& number)
{
    if (size <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);

    Iterator<T> fIter((*this));
    for (int i = 0; fIter; i++, fIter++)
        *fIter -= number;

    return (*this);
}

template<typename T>
template<typename U>
decltype(auto) Vector<T>::subNum(const U& number) const
{
    return operator -(number);
}

template<typename T>
Vector<T>& Vector<T>::subNumEqual(const T& number)
{
    return operator -=(number);
}

template<typename T>
Vector<T> Vector<T>::operator -()
{
    if (size <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__);

    Vector<T> newVector(*this);
    Iterator<T> iterator(newVector);
    for (; iterator; iterator++)
        *iterator = -*iterator;

    return newVector;
}

template<typename T>
Vector<T> Vector<T>::reverse()
{
    return operator-();
}

template<typename T>
void Vector<T>::allocNewVectorMem(int amount)
{
    try
    {
        values.reset();
    }
    catch (std::bad_alloc&)
    {
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__);
    }
    std::shared_ptr<T[]> temp(new T[amount], std::default_delete<T[]>());
    values = temp;
}


template<typename T>
Iterator<T> Vector<T>::begin() noexcept
{
    Iterator<T> iterator(*this);
    return iterator;
}

template<typename T>
Iterator<T> Vector<T>::end() noexcept
{
    Iterator<T> iterator(*this);
    return iterator + size;
}

template<typename T>
ConstIterator<T> Vector<T>::begin() const noexcept
{
    ConstIterator<T> iterator(*this);
    return iterator;
}

template<typename T>
ConstIterator<T> Vector<T>::end() const noexcept
{
    ConstIterator<T> iterator(*this);
    return iterator + size;
}

#endif // VECTOR_HPP
