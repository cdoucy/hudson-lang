#include "ContinueNode.hpp"

ast::ContinueNode::ptr ast::ContinueNode::create()
{
    return std::make_shared<ContinueNode>();
}

void ast::ContinueNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}
