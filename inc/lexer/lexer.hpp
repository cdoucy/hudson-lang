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
        using SingleCharTokenCreator = std::function<void (const std::string &lexeme)>;
        using DoubleCharTokenCreator = std::function<void (std::string::const_iterator &begin)>;

        const std::vector<LexerFunction> _lexerFunctions;
        const std::unordered_map<char, SingleCharTokenCreator> _singleCharTokenCreators;
        const std::unordered_map<char, DoubleCharTokenCreator> _doubleCharTokenCreators;

        Token::queue _queue;
        std::size_t _line;
        std::size_t _column;

        bool lex(std::string::const_iterator &begin);

        bool lexIntegerLiteral(std::string::const_iterator &begin);
        bool lexDoubleCharsToken(std::string::const_iterator &begin);
        bool lexSingleCharToken(const std::string::const_iterator &begin);

        template<Token::Type T>
        void pushToken(const std::string &lexeme)
        {
            this->_queue.push(Token::create<T>(lexeme, this->_line, this->_column));
            this->_column += lexeme.size();
        }

        template<Token::Type T1, Token::Type T2>
        void pushDoubleCharToken(char c, std::string::const_iterator &begin)
        {
            if (*(begin + 1) != c) {
                this->pushToken<T1>({begin, begin + 1});
                return;
            }

            this->pushToken<T2>({begin, begin + 2});
            begin++;
        }

        std::vector<LexerFunction> createLexerFunctions();
        std::unordered_map<char, SingleCharTokenCreator> createSingleCharTokenCreators();
        std::unordered_map<char, DoubleCharTokenCreator> createDoubleCharTokenCreators();
};