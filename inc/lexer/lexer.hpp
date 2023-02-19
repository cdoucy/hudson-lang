#pragma once

#include <string>
#include <functional>

#include "token.hpp"

class Lexer
{
    public:
        Lexer();
        ~Lexer() = default;

        void feed(const std::string &expression);

        [[nodiscard]] Token::ptr getNextToken() const noexcept;
        void popToken() noexcept;

        [[nodiscard]] std::size_t tokensCount() const noexcept;

        void clear() noexcept;

    private:
        using LexerFunction = std::function<bool (std::string::const_iterator &begin)>;

        const std::vector<LexerFunction> _lexerFunctions;

        Token::queue _queue;
        std::size_t _line;
        std::size_t _column;


        bool lex(std::string::const_iterator &begin);

        bool lexIntegerLiteral(std::string::const_iterator &begin);
        bool lexOperator(std::string::const_iterator &begin);

        template<Token::Type T>
        void pushToken(const std::string &lexeme)
        {
            this->_queue.push(Token::create<T>(lexeme, this->_line, this->_column));
            this->_column += lexeme.size();
        }

        void pushToken(Token::Type t, const std::string::const_iterator &begin, long lexemeSize);

        std::vector<LexerFunction> createLexerFunctions();
};