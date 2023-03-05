#pragma once

#include <cstdint>
#include <queue>
#include <memory>
#include <string>
#include <any>
#include <initializer_list>
#include <optional>

#include <fmt/format.h>

#include "InterpreterError.hpp"

class Token
{
    public:
        enum Type : uint8_t
        {
            // Operators
            OPEN_PARENTHESIS, CLOSE_PARENTHESIS,
            MOD, DIV, MULT,
            PLUS, MINUS,
            GT, GTE, LT, LTE,
            EQUAL, NOT_EQUAL,
            ASSIGN, NOT,
            AND, OR,
            BITWISE_AND, BITWISE_OR, BITWISE_XOR, BITWISE_NOT,
            BITWISE_RSHIFT, BITWISE_LSHIFT,
            SEMICOLON,

            // Literal types
            INTEGER,

            // Keywords
            LET, INT_TYPE,

            // Identifier
            IDENTIFIER
        };

        using Integer = int;

    public:
        using ptr = std::shared_ptr<Token>;

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

    public:
        using queue = std::queue<ptr>;

        class Iterator
        {
            public:
                Iterator() = default;
                Iterator(Token::queue tokens);
                ~Iterator() = default;

                Iterator &reset(Token::queue &tokens);

                std::optional<Token> get() const noexcept;
                std::optional<Token> next() const noexcept;
                std::optional<Token> prev() const noexcept;

                Iterator &advance();


            private:
                Token::queue _tokens;
                Token::ptr _current;
                Token::ptr _prev;
        };
};