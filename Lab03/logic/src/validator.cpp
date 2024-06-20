#include "logic/include/validator.h"

Validator::Validator(const str& expression)
{
    this->expression = expression;
}

bool Validator::hasCharacterInNumber(size_t begin, char character) {
    for (size_t i = begin - 1; i >= 0 && i < expression.length() && operators.find(expression[i]) == str::npos && brackets.find(expression[i]) == str::npos; i--)
    {
        if (expression[i] == character)
        {
            return true;
        }
    }
    return false;
}

void Validator::validate()
{
    int deep = 0;
    for (size_t i = 0; i < expression.length(); i++)
    {
        char character = expression[i];
        size_t pos;
        if ((pos = digits.find(character)) != str::npos)
        {
            continue;
        }
        else if ((pos = operators.find(character)) != str::npos)
        {
            if ((i == 0 || expression[i - 1] == '(') && expression[i] == '-')
            {
                continue;
            }
            if (i == 0 || operators.find(expression[i - 1]) != str::npos || i == expression.length() - 1 || expression[i - 1] == '(')
            {
                throw InvalidExpressionException();
            }
        }
        else if ((pos = brackets.find(character)) != str::npos)
        {
            if (i > 0 && pos == 0 && digits.find(expression[i - 1]) != str::npos)
            {
                throw InvalidExpressionException();
            }
            else if (i > 0 && pos == 1 && operators.find(expression[i - 1]) != str::npos)
            {
                throw InvalidExpressionException();
            }
            deep += pos == 0 ? 1 : -1;
        }
        else if (character == point)
        {
            if (i == 0 || operators.find(expression[i - 1]) != str::npos || brackets.find(expression[i - 1]) != str::npos || hasCharacterInNumber(i, point))
            {
                throw InvalidExpressionException();
            }
        }
        else
        {
            throw InvalidExpressionException();
        }
    }
    if (deep)
    {
        throw InvalidExpressionException();
    }
}
