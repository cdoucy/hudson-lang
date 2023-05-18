#include "Evaluator.hpp"

void Evaluator::feed(const std::string &expression)
{
    this->_parser.feed(expression);

    auto root = this->_parser.getAstRoot();

    if (root)
        root->accept(this->_evalVisitor);

    this->_parser.clear();
}

Token::Integer Evaluator::getResult() const noexcept
{
    return this->_evalVisitor.getResult();
}

void Evaluator::clear() noexcept
{
    this->_parser.clear();
    this->_evalVisitor.clearState();
}

const runtime::State &Evaluator::getState() const noexcept
{
    return this->_evalVisitor.getState();
}

const ast::EvalVisitor &Evaluator::getVisitor() const noexcept
{
    return this->_evalVisitor;
}

Evaluator::Evaluator(std::ostream &output)
:   _parser(),
    _evalVisitor(output)
{}
