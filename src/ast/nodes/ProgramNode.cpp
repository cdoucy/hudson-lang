#include "ProgramNode.hpp"

ast::ProgramNode::ProgramNode(const std::list<StatementNode::ptr> &statements)
:   _statements(statements)
{
}

void ast::ProgramNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

const std::list<ast::StatementNode::ptr> &ast::ProgramNode::getStatements() const
{
    return this->_statements;
}
