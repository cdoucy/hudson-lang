#include "lexer.hpp"

bool Lexer::lexIntegerLiteral(std::string::const_iterator &begin)
{
    if (!std::isdigit(*begin))
        return false;

    auto it = begin;

    for (; std::isdigit(*it); ++it);

    std::string lexeme(begin, it);
    this->_queue.push(Token::create<Token::INTEGER>(lexeme, this->_line, this->_column));

    this->_column += lexeme.size();

    begin = it - 1;

    return true;
}