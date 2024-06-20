#pragma once

#include <exception>
#include <string>

using str = std::string;

class BaseError : public std::exception
{
public:
    BaseError(str filename, str classname, int line, str info = "Error!")
    {
        message = "\nFile name: " + filename +
            "\nClass: " + classname +
            "\nLine: " + std::to_string(line) +
            "Info: " + info;
    }

    virtual const char* what() const noexcept override
    {
        return message.c_str();
    }

    virtual ~BaseError() {};

protected:
    str message;
};

class MemoryError : public BaseError
{
public:
    MemoryError(str filename, str classname, int line, str info = "Memory allocation error!\n") :
        BaseError(filename, classname, line, info) {};
};

class DeletedObject : public BaseError
{
public:
    DeletedObject(str filename, str classname, int line, str info = "Attempt to work with a remote object!\n") :
        BaseError(filename, classname, line, info) {};
};

class InvalidIterator : public BaseError
{
public:
    InvalidIterator(str filename, str classname, int line, str info = "Attempt to use an invalid iterator!\n") :
        BaseError(filename, classname, line, info) {};
};

class EmptyVectorError : public BaseError
{
public:
    EmptyVectorError(str filename, str classname, int line, str info = "The size of the vector must be greater than 0!\n") :
        BaseError(filename, classname, line, info) {};
};

class IndexVectorError : public BaseError
{
public:
    IndexVectorError(str filename, str classname, int line, str info = "Going beyond the vector limit!\n") :
        BaseError(filename, classname, line, info) {};
};

class ZeroDivError : public BaseError
{
public:
    ZeroDivError(str filename, str classname, int line, str info = "Division by zero is not allowed!\n") :
        BaseError(filename, classname, line, info) {};
};

class InvalidCopyArrayPointer : public BaseError
{
public:
    InvalidCopyArrayPointer(str filename, str classname, int line, str info = "The original array does not exist!\n") :
        BaseError(filename, classname, line, info) {};
};

class DifferentSizeVectors : public BaseError
{
public:
    DifferentSizeVectors(str filename, str classname, int line, str info = "The Vectors are different size!\n") :
        BaseError(filename, classname, line, info) {};
};