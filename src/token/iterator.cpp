#include <utility>

#include "token.hpp"

Token::Iterator::Iterator(Token::queue tokens)
:   _tokens(std::move(tokens))
{
    this->advance();
}

Token::Iterator &Token::Iterator::reset(Token::queue &tokens)
{
    this->_tokens.swap(tokens);
    this->advance();
    return *this;
}

std::optional<Token> Token::Iterator::get() const noexcept
{
    if (!this->_current)
        return {};

    return std::make_optional<Token>(*this->_current);
}

std::optional<Token> Token::Iterator::next() const noexcept
{
    if (this->_tokens.empty())
        return {};

    return std::make_optional<Token>(*this->_tokens.front());
}

std::optional<Token> Token::Iterator::prev() const noexcept
{
    if (!this->_prev)
        return {};

    return std::make_optional<Token>(*this->_prev);
}

Token::Iterator &Token::Iterator::advance()
{
    if (this->_tokens.empty()) {
        this->_prev = std::move(this->_current);
        this->_current = nullptr;
        return *this;
    }

    if (this->_current)
        this->_prev = std::move(this->_current);

    this->_current = std::move(this->_tokens.front());
    this->_tokens.pop();

    return *this;
}
