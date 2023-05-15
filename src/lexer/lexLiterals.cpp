#include "lexer.hpp"

bool Lexer::lexIntegerLiteral(std::string::const_iterator &begin)
{
    if (!std::isdigit(*begin))
        return false;

    auto it = begin;

    for (; std::isdigit(*it); ++it);

    this->pushToken(Token::INTEGER, {begin, it});

    begin = it;

    return true;
}

bool Lexer::lexStringLiteral(std::string::const_iterator &begin)
{
    if (*begin != '"')
        return false;

    auto it = begin + 1;

    for (; it != this->_expression.end() && *it != '"'; ++it) {
        auto next = it + 1;

        if (
            next != this->_expression.end() &&
            *it == '\\' && *next == '"'
        )
            ++it;
    }

    if (it == this->_expression.end()) {
        throw LexicalError("unmatched double quote", {begin, it}, this->_line, this->_column);
    }


    this->pushToken(Token::STRING, {begin, it + 1});

    begin = it + 1;

    return true;
}