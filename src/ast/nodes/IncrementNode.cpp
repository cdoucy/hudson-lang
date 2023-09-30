#include <utility>

#include "IncrementNode.hpp"

ast::IncrementNode::IncrementNode(
    std::string identifier,
    Token::Type op
)
    :   _identifier(std::move(identifier)),
        _op(op)
{
    if (op != Token::INCR && op != Token::DECR)
        throw InternalError("IncrementNode ctor : expecting -- or ++");
}

void ast::IncrementNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

const std::string &ast::IncrementNode::getIdentifier() const
{
    return this->_identifier;
}

ast::IncrementNode::ptr ast::IncrementNode::create(
    const std::string &identifier,
    Token::Type op
) {
    return std::make_shared<IncrementNode>(identifier, op);
}

Token::Type ast::IncrementNode::getOperator() const
{
    return this->_op;
}
