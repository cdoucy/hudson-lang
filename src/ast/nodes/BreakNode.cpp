#include "BreakNode.hpp"

ast::BreakNode::ptr ast::BreakNode::create()
{
    return std::make_shared<BreakNode>();
}

void ast::BreakNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}
