#include "AssignmentNode.hpp"

#include <utility>

ast::AssignmentNode::AssignmentNode(
    std::string identifier,
    ast::ExpressionNode::ptr expression
)
:   _identifier(std::move(identifier)),
    _expression(std::move(expression))
{
}

void ast::AssignmentNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

const std::string &ast::AssignmentNode::getIdentifier() const
{
    return this->_identifier;
}

const ast::ExpressionNode::ptr &ast::AssignmentNode::getExpression() const
{
    return this->_expression;
}
