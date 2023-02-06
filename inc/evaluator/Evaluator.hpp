#pragma once

#include "Parser.hpp"

class Evaluator
{
    public:
        Evaluator() = default;
        ~Evaluator() = default;

        void feed(const std::string &expression);

        [[nodiscard]] Token::Integer getResult() const noexcept;

        void clear() noexcept;

    private:
        Parser _parser;
        ast::EvalVisitor _evalVisitor;
};