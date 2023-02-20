#include "Object.hpp"

runtime::Object::Object(std::string identifier, Token::Integer i)
:   _identifier(std::move(identifier)),
    _type(Token::INTEGER),
    _raw(i)
{}

const std::string &runtime::Object::getIdentifier() const
{
    return this->_identifier;
}

Token::Type runtime::Object::getType() const
{
    return this->_type;
}

Token::Integer runtime::Object::getInteger() const
{
    if (this->_type != Token::INTEGER)
        throw InternalError("token type is not integer");

    return std::any_cast<Token::Integer>(this->_raw);
}

void runtime::Object::setInteger(Token::Integer i)
{
    if (this->_type != Token::INTEGER)
        throw InternalError("token type is not integer");

    this->_raw = i;
}
