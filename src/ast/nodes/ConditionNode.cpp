#include "ConditionNode.hpp"

ast::ConditionNode::ptr ast::ConditionNode::create(
    const ast::ExpressionNode::ptr &expression,
    const ast::StatementNode::ptr &ifBranch,
    const ast::StatementNode::ptr &elseBranch
) {
    return std::make_shared<ConditionNode>(expression, ifBranch, elseBranch);
}

ast::ConditionNode::ConditionNode(
    ast::ExpressionNode::ptr expression,
    ast::StatementNode::ptr ifBranch,
    ast::StatementNode::ptr elseBranch
)
:   _expr(std::move(expression)),
    _ifBranch(std::move(ifBranch)),
    _elseBranch(elseBranch ? std::move(elseBranch) : nullptr)
{}

void ast::ConditionNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

const ast::ExpressionNode::ptr &ast::ConditionNode::getExpression() const
{
    return this->_expr;
}

const ast::StatementNode::ptr &ast::ConditionNode::getIfBranch() const
{
    return this->_ifBranch;
}

const ast::StatementNode::ptr &ast::ConditionNode::getElseBranch() const
{
    return this->_elseBranch;
}
