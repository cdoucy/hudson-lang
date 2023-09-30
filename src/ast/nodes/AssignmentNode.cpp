#include "AssignmentNode.hpp"

#include <utility>

ast::AssignmentNode::AssignmentNode(
    std::string identifier,
    ast::ExpressionNode::ptr expression,
    Token::Type op
)
:   _identifier(std::move(identifier)),
    _expression(std::move(expression)),
    _op(op)
{
    if (!Token::isAssignableOperator(op))
        throw InternalError("AssignmentNode ctor : expecting ASSIGN or an assignable operator");
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

ast::AssignmentNode::ptr ast::AssignmentNode::create(
    const std::string &identifier,
    const ast::ExpressionNode::ptr &expression,
    Token::Type op
) {
    return std::make_shared<AssignmentNode>(identifier, expression, op);
}

Token::Type ast::AssignmentNode::getOperator() const
{
    return this->_op;
}
