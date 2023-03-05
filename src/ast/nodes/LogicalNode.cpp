#include <utility>

#include "LogicalNode.hpp"

const std::initializer_list<Token::Type> logicalOperators{
    Token::AND, Token::OR,
};

ast::LogicalNode::ptr ast::LogicalNode::create(
    Token::Type oprt,
    const ast::ExpressionNode::ptr &left,
    const ast::ExpressionNode::ptr &right
) {
    return std::make_shared<ast::LogicalNode>(oprt, left, right);
}

ast::LogicalNode::LogicalNode(
    Token::Type oprt,
    ast::ExpressionNode::ptr left,
    ast::ExpressionNode::ptr right
)
:   _operator(oprt),
    _leftChild(std::move(left)),
    _rightChild(std::move(right))
{
    if (!Token::isTypeAnyOf(oprt, logicalOperators))
        throw InternalError("LogicalNode: not an logical operator");
}

void ast::LogicalNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

Token::Type ast::LogicalNode::getOperator() const
{
    return this->_operator;
}

const ast::ExpressionNode::ptr &ast::LogicalNode::getLeftChild() const
{
    return this->_leftChild;
}

const ast::ExpressionNode::ptr &ast::LogicalNode::getRightChild() const
{
    return this->_rightChild;
}
