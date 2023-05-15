#include "StringNode.hpp"

ast::StringNode::StringNode(Token::String s)
:   _s(std::move(s))
{}

ast::StringNode::ptr ast::StringNode::create(const Token::String &s)
{
    return std::make_shared<ast::StringNode>(s);
}

void ast::StringNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

const Token::String &ast::StringNode::getValue() const
{
    return this->_s;
}
