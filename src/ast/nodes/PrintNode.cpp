#include "PrintNode.hpp"

ast::PrintNode::ptr ast::PrintNode::create(const ast::ExpressionNode::ptr &expr)
{
    return std::make_shared<PrintNode>(expr);
}

ast::PrintNode::PrintNode(ast::ExpressionNode::ptr expr)
:   _expression(std::move(expr))
{
}

void ast::PrintNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

const ast::ExpressionNode::ptr &ast::PrintNode::getExpression() const
{
    return this->_expression;
}
