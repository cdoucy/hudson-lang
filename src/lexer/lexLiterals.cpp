#include "lexer.hpp"

bool Lexer::lexIntegerLiteral(std::string::const_iterator &begin)
{
    if (!std::isdigit(*begin))
        return false;

    auto it = begin;

    for (; std::isdigit(*it); ++it);

    this->pushToken<Token::INTEGER>({begin, it});

    begin = it - 1;

    return true;
}