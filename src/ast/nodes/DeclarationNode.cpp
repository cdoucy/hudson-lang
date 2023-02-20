#include "DeclarationNode.hpp"

#include <utility>

ast::DeclarationNode::DeclarationNode(
    Token::Type type,
    std::string identifier,
    ast::ExpressionNode::ptr expression
)
:   _type(type),
    _identifier(std::move(identifier)),
    _expression(std::move(expression))
{}

void ast::DeclarationNode::accept(ast::IVisitor &v)
{
    v.visit(*this);
}

Token::Type ast::DeclarationNode::getType() const
{
    return this->_type;
}

const std::string &ast::DeclarationNode::getIdentifier() const
{
    return this->_identifier;
}

const ast::ExpressionNode::ptr &ast::DeclarationNode::getExpression() const
{
    return this->_expression;
}
