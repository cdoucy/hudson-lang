#include "lexer.hpp"
#include "string.hpp"

#define LEXER_FUNCTION(lexerFunc) ([this](std::string::const_iterator &begin) {return this->lexerFunc(begin);})

Lexer::Lexer()
:   _lexerFunctions(this->createLexerFunctions()),
    _singleCharTokenCreators(this->createSingleCharTokenCreators()),
    _doubleCharTokenCreators(this->createDoubleCharTokenCreators()),
    _queue(),
    _line(0),
    _column(0)
{
}

std::vector<Lexer::LexerFunction> Lexer::createLexerFunctions()
{
    return std::vector<Lexer::LexerFunction> {
        LEXER_FUNCTION(lexIntegerLiteral),
        LEXER_FUNCTION(lexDoubleCharsToken),
        LEXER_FUNCTION(lexSingleCharToken)
    };
}

void Lexer::feed(const std::string &expression)
{
    for (auto it = expression.begin(); it != expression.end(); ++it) {
        if (*it == '\n') {
            this->_line++;
            this->_column = 0;
            continue;
        }

        // Ignore white spaces
        if (std::isspace(*it)) {
            this->_column++;
            continue;
        }

        // Try to lex, continue if lex succeeded
        if (this->lex(it))
            continue;

        // In case of unknown token, clear tokens queue and throw
        throw LexicalError(
            "unknown token",
            std::string{it, it + 1},
            this->_line,
            this->_column
        );
    }
}

bool Lexer::lex(std::string::const_iterator &begin)
{
    for (const auto &f : this->_lexerFunctions) {
        if (f(begin))
            return true;
    }

    return false;
}

Token::ptr Lexer::getNextToken() const noexcept
{
    if (this->_queue.empty())
        return nullptr;

    return this->_queue.front();
}

void Lexer::popToken() noexcept
{
    if (this->_queue.empty())
        return;

    this->_queue.pop();
}

std::size_t Lexer::tokensCount() const noexcept
{
    return this->_queue.size();
}

void Lexer::clear() noexcept
{
    Token::queue cleared;
    this->_queue.swap(cleared);

    this->_line = 0;
    this->_column = 0;
}
