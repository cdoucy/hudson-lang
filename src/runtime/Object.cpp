#include <utility>
#include <fmt/format.h>

#include "Object.hpp"

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

std::string runtime::Object::string() const noexcept
{
    const auto &identifier = this->_identifier;
    const auto &type = Token::typeToString(this->_type);
    const auto &value = this->getValueAsString();

    return fmt::format("{{identifier={}, type={}, value={}}}", identifier, type, value);
}

std::string runtime::Object::getValueAsString() const noexcept
{
    switch (this->_type) {
        case Token::INTEGER:
            return fmt::format("{}", this->getInteger());

        default:
            break;
    }

    return "null";
}