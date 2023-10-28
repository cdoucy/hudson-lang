#include <unordered_map>

#include "map.hpp"
#include "token.hpp"

static const std::unordered_map<Token::Type, std::string> tokenTypesString{
    {Token::INT_TYPE, "int"},
    {Token::STR_TYPE, "str"},
    {Token::FNC_TYPE, "fnc"},
    {Token::VOID_TYPE, "void"}
};

static const std::string unknownType{"unknown"};

std::string Token::typeToString(Token::Type type)
{
    const auto &found = umap::get(tokenTypesString, type);

    if (found)
        return found.value();

    return unknownType;
}

static const std::unordered_map<Token::Type, bool> assignableOperators{
    {Token::ASSIGN, true},
    {Token::DIV_GN, true},
    {Token::MINUS_GN, true},
    {Token::PLUS_GN, true},
    {Token::MULT_GN, true},
    {Token::MOD_GN, true}
};

bool Token::isAssignableOperator(Token::Type type) noexcept
{
    return umap::get(assignableOperators, type).has_value();
}

bool Token::isAssignableOperator() const noexcept
{
    return Token::isAssignableOperator(this->_type);
}
