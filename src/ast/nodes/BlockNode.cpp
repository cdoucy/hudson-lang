#include "BlockNode.hpp"

ast::BlockNode::ptr ast::BlockNode::create(const std::list<StatementNode::ptr> &statements)
{
    return std::make_shared<BlockNode>(statements);
}

ast::BlockNode::BlockNode(std::list<StatementNode::ptr> statements)
: _statements(std::move(statements))
{}

void ast::BlockNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

const std::list<ast::StatementNode::ptr> &ast::BlockNode::getStatements() const
{
    return this->_statements;
}
