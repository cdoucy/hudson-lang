#include "lexer.hpp"
#include "map.hpp"

static const std::unordered_map<std::string, Token::Type> keywordsTable{
    {"int", Token::INT_TYPE},
    {"str", Token::STR_TYPE},
    {"print", Token::PRINT}
};

bool Lexer::lexProgrammingWord(std::string::const_iterator &begin)
{
    if (!isProgrammingWord(*begin))
        return false;

    auto it = begin;

    for (; isProgrammingWord(*it); ++it);

    std::string lexeme(begin, it);
    Token::Type type = Token::IDENTIFIER;

    auto keywordType = umap::get(keywordsTable, lexeme);
    if (keywordType)
        type = *keywordType;

    this->pushToken(type, lexeme);

    begin = it;

    return true;
}

bool Lexer::isProgrammingWord(char c)
{
    return c == '_' || std::isalnum(c);
}