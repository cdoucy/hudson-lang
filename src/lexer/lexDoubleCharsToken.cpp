#include "lexer.hpp"

#define TOKEN_CREATOR(c1, t1, c2, t2) {c1, [this](auto &b){this->pushDoubleCharToken<t1, t2>(c2, b);}}

std::unordered_map<char, Lexer::DoubleCharTokenCreator> Lexer::createDoubleCharTokenCreators()
{
    return std::unordered_map<char, DoubleCharTokenCreator>{
        // =, ==
        TOKEN_CREATOR('=', Token::ASSIGN, '=', Token::EQUAL),

        // !, !=
        TOKEN_CREATOR('!', Token::NOT, '=', Token::NOT_EQUAL),

        // >, >=
        TOKEN_CREATOR('>', Token::GT, '=', Token::GTE),

        // <, <=
        TOKEN_CREATOR('<', Token::LT, '=', Token::LTE),

        // &, &&
        TOKEN_CREATOR('&', Token::BITWISE_AND, '&', Token::AND),

        // |, ||
        TOKEN_CREATOR('|', Token::BITWISE_OR, '|', Token::OR),
    };
}

bool Lexer::lexDoubleCharsToken(std::string::const_iterator &begin)
{
    auto creator = this->_doubleCharTokenCreators.find(*begin);

    if (creator == this->_doubleCharTokenCreators.end())
        return false;

    creator->second(begin);

    return true;
}
