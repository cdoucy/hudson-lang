#include "lexer.hpp"
#include "map.hpp"

struct Tok
{
    Token::Type defaultType;
    std::unordered_map<char, Token::Type> transformTypes;
};

static const std::unordered_map<char, Tok> tokenTable{
    {
        '%', {Token::MOD, {}}
    },
    {
        '/', {Token::DIV, {}}
    },
    {
        '*', {Token::MULT, {}}
    },
    {
        '+', {Token::PLUS, {}}
    },
    {
        '-', {Token::MINUS, {}}
    },
    {
        '(', {Token::OPEN_PARENTHESIS, {}}
    },
    {
        ')', {Token::CLOSE_PARENTHESIS, {}}
    },
    {
        '{', {Token::OPEN_BRACKET, {}}
    },
    {
        '}', {Token::CLOSE_BRACKET, {}}
    },
    {
        '[', {Token::OPEN_SQ_BRACKET, {}}
    },
    {
        ']', {Token::CLOSE_SQ_BRACKET, {}}
    },
    {
        '^', {Token::BITWISE_XOR, {}}
    },
    {
        '~', {Token::BITWISE_NOT, {}}
    },
    {
        ';', {Token::SEMICOLON, {}}
    },
    {
        '=', {
            Token::ASSIGN, {
                {'=', Token::EQUAL}
            }
        }
    },
    {
        '!', {
            Token::NOT, {
                {'=', Token::NOT_EQUAL}
            }
        }
    },
    {
        '>', {
            Token::GT, {
                {'=', Token::GTE},
                {'>', Token::BITWISE_RSHIFT},
            }
        }
    },
    {
        '<', {
            Token::LT, {
                {'=', Token::LTE},
                {'<', Token::BITWISE_LSHIFT}
            }
        }
    },
    {
        '&', {
            Token::BITWISE_AND, {
                {'&', Token::AND}
            }
        }
    },
    {
        '|', {
            Token::BITWISE_OR, {
                {'|', Token::OR}
            }
        }
    }
};

bool Lexer::lexOperator(std::string::const_iterator &begin)
{
    auto match = umap::get(tokenTable, *begin);

    if (!match)
        return false;

    auto transformType = umap::get(match->transformTypes, *(begin + 1));

    if (!transformType)
        this->pushToken(match->defaultType, begin, 1);
    else
        this->pushToken(*transformType, begin, 2);

    return true;
}