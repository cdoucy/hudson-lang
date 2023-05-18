#include "WhileNode.hpp"

#include <utility>

ast::WhileNode::ptr ast::WhileNode::create(
    const ast::ExpressionNode::ptr &expression,
    const ast::StatementNode::ptr &statement
) {
    return std::make_shared<WhileNode>(expression, statement);
}

ast::WhileNode::WhileNode(ast::ExpressionNode::ptr expression, ast::StatementNode::ptr statement)
:   _expr(std::move(expression)),
    _stmt(statement ? std::move(statement) : nullptr)
{}

void ast::WhileNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

const ast::ExpressionNode::ptr &ast::WhileNode::getExpression() const
{
    return this->_expr;
}

const ast::StatementNode::ptr &ast::WhileNode::getStatement() const
{
    return this->_stmt;
}
