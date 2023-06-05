#include "ForNode.hpp"

#include <utility>

ast::ForNode::ptr ast::ForNode::create(
    const ast::ExpressionNode::ptr &expression,
    const ast::InitStatementNode::ptr &initStmt,
    const ast::StepStatementNode::ptr &stepStmt,
    const ast::StatementNode::ptr &statement
) {
    return std::make_shared<ForNode>(expression, initStmt, stepStmt, statement);
}

ast::ForNode::ForNode(
    ast::ExpressionNode::ptr expression,
    ast::InitStatementNode::ptr initStmt,
    ast::StepStatementNode::ptr stepStmt,
    ast::StatementNode::ptr statement
)
:   _expr(std::move(expression)),
    _init(initStmt ? std::move(initStmt) : nullptr),
    _step(stepStmt ? std::move(stepStmt) : nullptr),
    _stmt(statement ? std::move(statement) : nullptr)
{}

void ast::ForNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

const ast::ExpressionNode::ptr &ast::ForNode::getExpression() const
{
    return this->_expr;
}

const ast::StatementNode::ptr &ast::ForNode::getStatement() const
{
    return this->_stmt;
}

const ast::StepStatementNode::ptr &ast::ForNode::getStepStatement() const
{
    return this->_step;
}

const ast::InitStatementNode::ptr &ast::ForNode::getInitStatement() const
{
    return this->_init;
}
