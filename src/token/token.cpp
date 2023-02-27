#include "token.hpp"

#include <utility>

Token::Token(Token::Type type, const std::string &lexeme, std::size_t line, std::size_t column)
:   _type(type),
    _lexeme(lexeme),
    _literalValue(literalFromLexeme(type, lexeme)),
    _line(line),
    _column(column)
{}

Token::Type Token::getType() const noexcept
{
    return this->_type;
}

bool Token::isType(Token::Type type) const noexcept
{
    return this->_type == type;
}

bool Token::isTypeAnyOf(const std::initializer_list<Token::Type> &types)
{
    return Token::isTypeAnyOf(this->_type, types);
}

Token::Integer Token::getIntegerLiteral() const
{
    if (this->_type != INTEGER)
        throw InternalError("token type is not integer");

    return std::any_cast<Integer>(this->_literalValue);
}

bool Token::operator==(const Token &other) const
{
    if (this->_type != other.getType())
        return false;

    switch (this->_type) {
        case Token::INTEGER:
            return this->getIntegerLiteral() == other.getIntegerLiteral();
        default:
            return true;
    }
}

std::any Token::literalFromLexeme(Token::Type type, const std::string &lexeme)
{
    switch (type) {
        case INTEGER:
            return Token::integerFromLexeme(lexeme);
        default:
            return nullptr;
    }
}

Token::Integer Token::integerFromLexeme(const std::string &lexeme)
{
    Token::Integer value;

    try {
        value = std::stoi(lexeme);
    } catch (...) {
        throw InternalError(fmt::format("\"{}\" : not an integer", lexeme));
    }

    return value;
}

bool Token::isTypeAnyOf(Token::Type type, const std::initializer_list<Token::Type> &types)
{
    return std::any_of(types.begin(), types.end(), [type](Token::Type t) {
        return t == type;
    });
}

const std::string &Token::getLexeme() const noexcept
{
    return this->_lexeme;
}

std::size_t Token::getLine() const noexcept
{
    return this->_line;
}

std::size_t Token::getColumn() const noexcept
{
    return this->_column;
}

Token::ptr Token::create(Token::Type type, const std::string &lexeme, std::size_t line, std::size_t column)
{
    return std::make_shared<Token>(type, lexeme, line, column);
}
