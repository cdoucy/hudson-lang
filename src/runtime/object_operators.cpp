#include "Object.hpp"

#define OP(l, r, op, T) return ((l).get<T>() op (r).get<T>());

#define OP_UNARY(obj, op, T) return (op (obj).get<T>());

#define OP_CHECK_Z(l, r, op, T) {   \
    auto lv = (l).get<T>();         \
    auto rv = (r).get<T>();         \
                                    \
    if (!rv)                        \
        throw LogicalError("");     \
                                    \
    return lv op rv;                \
}

#define OP_TYPE(l, r, op, cb) {                         \
    switch ((l).getType()) {                            \
        case Token::INT:                                \
            cb(l, r, op, Token::Integer)                \
        case Token::UINT:                               \
            cb(l, r, op, Token::UInteger)               \
        default:                                        \
            throw LogicalError("wrong type");           \
    }                                                   \
}

#define DO_OP_UNARY(obj, op) {                          \
    switch ((obj).getType()) {                          \
        case Token::INT:                                \
            OP_UNARY(obj, op, Token::Integer);          \
        case Token::UINT:                               \
            OP_UNARY(obj, op, Token::UInteger);         \
        default:                                        \
            throw LogicalError("wrong type");           \
    }                                                   \
}

#define DO_OP(l, r, op) OP_TYPE(l, r, op, OP)

#define DO_OP_CHECK_Z(l, r, op) OP_TYPE(l, r, op, OP_CHECK_Z)

runtime::Object runtime::Object::operator%(const Object &right) const
{
    try {
        DO_OP_CHECK_Z(*this, right, %);
    } catch (const LogicalError &_) {
        throw LogicalError("modulo by zero");
    }
}

runtime::Object runtime::Object::operator/(const runtime::Object &right) const
{
    try {
        DO_OP_CHECK_Z(*this, right, /);
    } catch (const LogicalError &_) {
        throw LogicalError("division by zero");
    }
}

runtime::Object runtime::Object::operator*(const runtime::Object &right) const
{
    DO_OP(*this, right, *);
}

runtime::Object runtime::Object::operator+(const runtime::Object &right) const
{
    DO_OP(*this, right, +);
}

runtime::Object runtime::Object::operator-(const runtime::Object &right) const
{
    DO_OP(*this, right, -);
}

runtime::Object runtime::Object::operator==(const runtime::Object &right) const
{
    DO_OP(*this, right, ==);
}

runtime::Object runtime::Object::operator!=(const runtime::Object &right) const
{
    DO_OP(*this, right, !=);
}

runtime::Object runtime::Object::operator>(const runtime::Object &right) const
{
    DO_OP(*this, right, >);
}

runtime::Object runtime::Object::operator>=(const runtime::Object &right) const
{
    DO_OP(*this, right, >=);
}

runtime::Object runtime::Object::operator<(const runtime::Object &right) const
{
    DO_OP(*this, right, <);
}

runtime::Object runtime::Object::operator<=(const runtime::Object &right) const
{
    DO_OP(*this, right, <=);
}

runtime::Object runtime::Object::operator|(const runtime::Object &right) const
{
    DO_OP(*this, right, |);
}

runtime::Object runtime::Object::operator^(const runtime::Object &right) const
{
    DO_OP(*this, right, ^);
}

runtime::Object runtime::Object::operator&(const runtime::Object &right) const
{
    DO_OP(*this, right, &);
}

runtime::Object runtime::Object::operator<<(const runtime::Object &right) const
{
    DO_OP(*this, right, <<);
}

runtime::Object runtime::Object::operator>>(const runtime::Object &right) const
{
    DO_OP(*this, right, >>);
}

runtime::Object runtime::Object::operator+() const
{
    DO_OP_UNARY(*this, +);
}

runtime::Object runtime::Object::operator-() const
{
    DO_OP_UNARY(*this, -);
}

runtime::Object runtime::Object::operator!() const
{
    DO_OP_UNARY(*this, !);
}

runtime::Object runtime::Object::operator~() const
{
    DO_OP_UNARY(*this, ~);
}

runtime::Object::operator bool() const
{
    assertTypeEqual(Token::INT);

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

runtime::Object &runtime::Object::assign(const runtime::Object &rv)
{
    if (this->_type == rv.getType()) {
        this->_raw = rv._raw;
        return *this;
    }

    switch (this->_type) {
        case Token::INT:
            switch (rv.getType()) {
                case Token::UINT:
                    this->_raw = static_cast<Token::Integer>(rv.get<Token::UInteger>());
                    break;
                default:
                    throw LogicalError("Object::assign");
            }

            break;

        case Token::UINT:
            switch (rv.getType()) {
                case Token::INT:
                    this->_raw = static_cast<Token::UInteger>(rv.get<Token::Integer>());
                    break;
                default:
                    throw LogicalError("Object::assign");
            }

            break;

        default:
            throw LogicalError("Object::assign");
    }

    return *this;
}
