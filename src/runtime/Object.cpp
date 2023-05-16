#include <utility>
#include <fmt/format.h>

#include "Object.hpp"

runtime::Object::Object(Token::Type type, std::string identifier)
    :   _identifier(std::move(identifier)),
        _type(type)
{
    switch (type) {
        case Token::INT_TYPE: this->_raw = Token::Integer(0);   break;
        case Token::STR_TYPE: this->_raw = Token::String();     break;
        default:
            throw InternalError("invalid type");
    }
}

runtime::Object::Object(Token::Integer i, std::string identifier)
:   _identifier(std::move(identifier)),
    _type(Token::INT_TYPE),
    _raw(i)
{}

runtime::Object::Object(Token::String s, std::string identifier)
:   _identifier(std::move(identifier)),
    _type(Token::STR_TYPE),
    _raw(std::move(s))
{
}

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
    if (this->_type != Token::INT_TYPE)
        throw InternalError("token type is not integer");

    return std::any_cast<Token::Integer>(this->_raw);
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
        case Token::INT_TYPE:
            return fmt::format("{}", this->getInteger());

        case Token::STR_TYPE:
            return this->get<Token::String>();

        default:
            break;
    }

    return "null";
}