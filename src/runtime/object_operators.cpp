#include "Object.hpp"

runtime::Object runtime::Object::operator%(const Object &right) const
{
    assertTypesEqual(right, Token::INTEGER);

    auto l = this->getInteger();
    auto r = right.getInteger();

    if (!r)
        throw LogicalError("modulo by zero");

    auto result = l % r;

    return result;
}

runtime::Object runtime::Object::operator/(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INTEGER);

    auto l = this->getInteger();
    auto r = right.getInteger();

    if (!r)
        throw LogicalError("division by zero");

    auto result = l / r;

    return result;
}

runtime::Object runtime::Object::operator*(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INTEGER);

    return this->getInteger() * right.getInteger();
}

runtime::Object runtime::Object::operator+(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INTEGER);

    return this->getInteger() + right.getInteger();
}

runtime::Object runtime::Object::operator-(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INTEGER);

    return this->getInteger() - right.getInteger();
}

runtime::Object runtime::Object::operator==(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INTEGER);

    return this->getInteger() == right.getInteger();
}

runtime::Object runtime::Object::operator!=(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INTEGER);

    return this->getInteger() != right.getInteger();
}

runtime::Object runtime::Object::operator>(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INTEGER);

    return this->getInteger() > right.getInteger();
}

runtime::Object runtime::Object::operator>=(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INTEGER);

    return this->getInteger() >= right.getInteger();
}

runtime::Object runtime::Object::operator<(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INTEGER);

    return this->getInteger() < right.getInteger();
}

runtime::Object runtime::Object::operator<=(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INTEGER);

    return this->getInteger() <= right.getInteger();
}

runtime::Object runtime::Object::operator|(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INTEGER);

    return this->getInteger() | right.getInteger();
}

runtime::Object runtime::Object::operator^(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INTEGER);

    return this->getInteger() ^ right.getInteger();
}

runtime::Object runtime::Object::operator&(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INTEGER);

    return this->getInteger() & right.getInteger();
}

runtime::Object runtime::Object::operator<<(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INTEGER);

    return this->getInteger() << right.getInteger();
}

runtime::Object runtime::Object::operator>>(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INTEGER);

    return this->getInteger() >> right.getInteger();
}

runtime::Object runtime::Object::operator+() const
{
    assertTypeEqual(Token::INTEGER);

    return +this->getInteger();
}

runtime::Object runtime::Object::operator-() const
{
    assertTypeEqual(Token::INTEGER);

    return -this->getInteger();
}

runtime::Object runtime::Object::operator!() const
{
    assertTypeEqual(Token::INTEGER);

    return !this->getInteger();
}

runtime::Object runtime::Object::operator~() const
{
    assertTypeEqual(Token::INTEGER);

    return ~this->getInteger();
}

runtime::Object::operator bool() const
{
    assertTypeEqual(Token::INTEGER);

    return this->getInteger();
}

bool runtime::Object::isTypeEqual(Token::Type type) const noexcept
{
    return this->_type == type;
}

bool runtime::Object::areTypesEqual(const Object &other, Token::Type type) const noexcept
{
    return this->isTypeEqual(type) && other.isTypeEqual(type);
}

void runtime::Object::assertTypeEqual(Token::Type type) const
{
    if (!this->isTypeEqual(type))
        throw LogicalError("incompatible type");
}

void runtime::Object::assertTypesEqual(const Object &other, Token::Type type) const
{
    if (!this->areTypesEqual(other, type))
        throw LogicalError("incompatible type");
}
