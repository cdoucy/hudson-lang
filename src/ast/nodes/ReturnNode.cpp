#include "ReturnNode.hpp"

#include <utility>

ast::ReturnNode::ptr ast::ReturnNode::create(const ast::ExpressionNode::ptr &expr)
{
    return std::make_shared<ReturnNode>(expr);
}

ast::ReturnNode::ReturnNode(ast::ExpressionNode::ptr expr)
:   _expr(std::move(expr))
{
}

void ast::ReturnNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

const ast::ExpressionNode::ptr &ast::ReturnNode::getExpression() const
{
    return this->_expr;
}
