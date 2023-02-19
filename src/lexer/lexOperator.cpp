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
        '^', {Token::BITWISE_XOR, {}}
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
    else {
        this->pushToken(*transformType, begin, 2);
        begin++;
    }

    return true;
}

void Lexer::pushToken(Token::Type t, const std::string::const_iterator &begin, long lexemeSize)
{
    const auto &end = begin + lexemeSize;
    this->_queue.push(Token::create(t, {begin, end}, this->_line, this->_column));
    this->_column += lexemeSize;
}
