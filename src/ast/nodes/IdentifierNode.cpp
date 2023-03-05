#include "IdentifierNode.hpp"

ast::IdentifierNode::ptr ast::IdentifierNode::create(const std::string &identifier)
{
    return std::make_shared<IdentifierNode>(identifier);
}

ast::IdentifierNode::IdentifierNode(std::string identifier)
:   _identifier(std::move(identifier))
{
}

void ast::IdentifierNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

const std::string &ast::IdentifierNode::getIdentifier() const noexcept
{
    return this->_identifier;
}
