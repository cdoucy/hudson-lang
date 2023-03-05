#include "Object.hpp"

#include <utility>

runtime::Object::Object(Token::Integer i, std::string identifier)
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

void runtime::Object::set(Token::Integer i,  bool overwriteType)
{
    if (overwriteType)
        this->_type = Token::INTEGER;
    else if (this->_type != Token::INTEGER)
        throw InternalError("token type is not integer");

    this->_raw = i;
}

runtime::Object::Object()
:   _identifier(),
    _type(Token::Type(-1)),
    _raw()
{
}
