#include <unordered_map>

#include "lexer.hpp"

#define TOKEN_CREATOR(ch, type) {ch, [this](auto &l){return this->pushToken<type>(l);}}

std::unordered_map<char, Lexer::SingleCharTokenCreator> Lexer::createSingleCharTokenCreators()
{
    return {
        TOKEN_CREATOR('%', Token::MOD),
        TOKEN_CREATOR('/', Token::DIV),
        TOKEN_CREATOR('*', Token::MULT),
        TOKEN_CREATOR('+', Token::PLUS),
        TOKEN_CREATOR('-', Token::MINUS),
        TOKEN_CREATOR('(', Token::OPEN_PARENTHESIS),
        TOKEN_CREATOR(')', Token::CLOSE_PARENTHESIS)
    };
}

bool Lexer::lexSingleCharToken(const std::string::const_iterator &begin)
{
    auto creator = this->_singleCharTokenCreators.find(*begin);

    if (creator == this->_singleCharTokenCreators.end())
        return false;

    creator->second({begin, begin + 1});

    return true;
}
