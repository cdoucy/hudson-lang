#include "Object.hpp"

runtime::Object runtime::Object::operator%(const Object &right) const
{
    assertTypesEqual(right, Token::INT_TYPE);

    auto l = this->getInteger();
    auto r = right.getInteger();

    if (!r)
        throw LogicalError("modulo by zero");

    auto result = l % r;

    return result;
}

runtime::Object runtime::Object::operator/(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INT_TYPE);

    auto l = this->getInteger();
    auto r = right.getInteger();

    if (!r)
        throw LogicalError("division by zero");

    auto result = l / r;

    return result;
}

runtime::Object runtime::Object::operator*(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INT_TYPE);

    return this->getInteger() * right.getInteger();
}

runtime::Object runtime::Object::operator+(const runtime::Object &right) const
{
    assertTypeEqual(right.getType());

    switch (this->getType()) {
        case Token::INT_TYPE:
            return this->getInteger() + right.getInteger();

        case Token::STR_TYPE:
            return this->get<Token::String>() + right.get<Token::String>();

        default:
            throw LogicalError(fmt::format("type {} doesn't implement operator +", Token::typeToString(this->getType())));
    }
}

runtime::Object runtime::Object::operator-(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INT_TYPE, "-");

    return this->getInteger() - right.getInteger();
}

runtime::Object runtime::Object::operator==(const runtime::Object &right) const
{
    assertTypeEqual(right.getType());

    switch (this->getType()) {
        case Token::INT_TYPE:
            return this->getInteger() == right.getInteger();

        case Token::STR_TYPE:
            return this->get<Token::String>() == right.get<Token::String>();

        default:
            throw LogicalError(fmt::format("type {} doesn't implement operator ==", Token::typeToString(this->getType())));
    }
}

runtime::Object runtime::Object::operator!=(const runtime::Object &right) const
{
    assertTypeEqual(right.getType());

    switch (this->getType()) {
        case Token::INT_TYPE:
            return this->getInteger() != right.getInteger();

        case Token::STR_TYPE:
            return this->get<Token::String>() != right.get<Token::String>();

        default:
            throw LogicalError(fmt::format("type {} doesn't implement operator !=", Token::typeToString(this->getType())));
    }
}

runtime::Object runtime::Object::operator>(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INT_TYPE);

    return this->getInteger() > right.getInteger();
}

runtime::Object runtime::Object::operator>=(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INT_TYPE);

    return this->getInteger() >= right.getInteger();
}

runtime::Object runtime::Object::operator<(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INT_TYPE);

    return this->getInteger() < right.getInteger();
}

runtime::Object runtime::Object::operator<=(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INT_TYPE);

    return this->getInteger() <= right.getInteger();
}

runtime::Object runtime::Object::operator|(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INT_TYPE);

    return this->getInteger() | right.getInteger();
}

runtime::Object runtime::Object::operator^(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INT_TYPE);

    return this->getInteger() ^ right.getInteger();
}

runtime::Object runtime::Object::operator&(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INT_TYPE);

    return this->getInteger() & right.getInteger();
}

runtime::Object runtime::Object::operator<<(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INT_TYPE);

    return this->getInteger() << right.getInteger();
}

runtime::Object runtime::Object::operator>>(const runtime::Object &right) const
{
    assertTypesEqual(right, Token::INT_TYPE);

    return this->getInteger() >> right.getInteger();
}

runtime::Object runtime::Object::operator+() const
{
    assertTypeEqual(Token::INT_TYPE);

    return +this->getInteger();
}

runtime::Object runtime::Object::operator-() const
{
    assertTypeEqual(Token::INT_TYPE);

    return -this->getInteger();
}

runtime::Object runtime::Object::operator!() const
{
    assertTypeEqual(Token::INT_TYPE);

    return !this->getInteger();
}

runtime::Object runtime::Object::operator~() const
{
    assertTypeEqual(Token::INT_TYPE);

    return ~this->getInteger();
}

runtime::Object::operator bool() const
{
    assertTypeEqual(Token::INT_TYPE);

    return this->getInteger();
}


runtime::Object &runtime::Object::assign(const runtime::Object &rv)
{
    assertTypeEqual(rv.getType());

    this->_raw = rv._raw;

    return *this;
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
        throw LogicalError(fmt::format(
            "type {} is not compatible with type {}",
            Token::typeToString(this->getType()),
            Token::typeToString(type)
        ));
}

void runtime::Object::assertTypesEqual(const Object &other, Token::Type type, const std::string &oprt) const
{
    if (!this->areTypesEqual(other, type)) {
        if (oprt.empty())
            throw LogicalError("incompatible type");
        else
            throw LogicalError(
                fmt::format(
                    "type {} doesn't implement operator {}",
                    Token::typeToString(this->getType()),
                    oprt
                )
            );
    }
}
