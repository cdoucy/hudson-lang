#include "UnaryNode.hpp"

#include <utility>

const std::initializer_list<Token::Type> unaryOperators{
    Token::PLUS, Token::MINUS, Token::NOT
};

ast::UnaryNode::ptr ast::UnaryNode::create(Token::Type oprt, const ast::ExpressionNode::ptr &child)
{
    return std::make_shared<UnaryNode>(oprt, child);
}

ast::UnaryNode::UnaryNode(Token::Type oprt, ast::ExpressionNode::ptr child)
: _operator(oprt), _child(std::move(child))
{
    if (!Token::isTypeAnyOf(oprt, unaryOperators))
        throw InternalError("UnaryNode: not an unary operator");
}

void ast::UnaryNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

Token::Type ast::UnaryNode::getOperator() const
{
    return this->_operator;
}

const ast::ExpressionNode::ptr &ast::UnaryNode::getChild() const
{
    return this->_child;
}
