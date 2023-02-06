#include "IntegerNode.hpp"

ast::IntegerNode::IntegerNode(Token::Integer value)
:   _value(value)
{
}

void ast::IntegerNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

Token::Integer ast::IntegerNode::getValue() const
{
    return this->_value;
}

ast::IntegerNode::ptr ast::IntegerNode::create(Token::Integer value)
{
    return std::make_shared<ast::IntegerNode>(value);
}
