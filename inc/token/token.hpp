#pragma once

#include <cstdint>
#include <queue>
#include <memory>
#include <string>
#include <any>
#include <initializer_list>

#include <fmt/format.h>

#include "InterpreterError.hpp"

class Token
{
    public:
        enum Type : uint8_t
        {
            OPEN_PARENTHESIS, CLOSE_PARENTHESIS,
            MOD, DIV, MULT,
            PLUS, MINUS,
            GT, GTE, LT, LTE,
            EQUAL, NOT_EQUAL,
            ASSIGN, NOT,
            AND, OR,
            BITWISE_AND, BITWISE_OR, BITWISE_XOR,
            BITWISE_RSHIFT, BITWISE_LSHIFT,
            INTEGER,
        };

        using Integer = long;

        using ptr = std::shared_ptr<Token>;
        using queue = std::queue<ptr>;

        template<Type T>
        static ptr create(const std::string &lexeme, std::size_t line, std::size_t column)
        {
            return std::make_shared<Token>(T, lexeme, line, column);
        }

        static ptr create(Token::Type type, const std::string &lexeme, std::size_t line, std::size_t column);

        Token(Token::Type type, const std::string &lexeme, std::size_t line = 0, std::size_t column = 0);

        [[nodiscard]] Type getType() const noexcept;

        [[nodiscard]] bool isType(Token::Type type) const noexcept;
        [[nodiscard]] bool isTypeAnyOf(const std::initializer_list<Token::Type> &types);

        [[nodiscard]] static bool isTypeAnyOf(Token::Type type, const std::initializer_list<Token::Type> &types);

        [[nodiscard]] Integer getIntegerLiteral() const;

        [[nodiscard]] const std::string &getLexeme() const noexcept;
        [[nodiscard]] std::size_t getLine() const noexcept;
        [[nodiscard]] std::size_t getColumn() const noexcept;


        bool operator==(const Token &other) const;

    private:
        Type _type;
        std::string _lexeme;
        std::any _literalValue;
        std::size_t _line;
        std::size_t _column;

        static std::any literalFromLexeme(Token::Type type, const std::string &lexeme);
        static Integer integerFromLexeme(const std::string &lexeme);
};