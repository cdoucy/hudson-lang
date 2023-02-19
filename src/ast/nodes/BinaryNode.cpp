#include "BinaryNode.hpp"

#include <utility>

const std::initializer_list<Token::Type> binaryOperators{
    Token::MOD, Token::DIV, Token::MULT,
    Token::PLUS, Token::MINUS,
    Token::EQUAL, Token::NOT_EQUAL,
    Token::GT, Token::GTE, Token::LT, Token::LTE,
    Token::AND, Token::OR,
    Token::BITWISE_OR, Token::BITWISE_XOR, Token::BITWISE_AND,
    Token::BITWISE_LSHIFT, Token::BITWISE_RSHIFT
};

ast::BinaryNode::BinaryNode(
    Token::Type oprt,
    ast::ExpressionNode::ptr left,
    ast::ExpressionNode::ptr right
)
:   _operator(oprt),
    _leftChild(std::move(left)),
    _rightChild(std::move(right))
{
    if (!Token::isTypeAnyOf(oprt, binaryOperators))
        throw InternalError("BinaryNode: not an operator");
}

void ast::BinaryNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

Token::Type ast::BinaryNode::getOperator() const
{
    return this->_operator;
}

const ast::ExpressionNode::ptr &ast::BinaryNode::getLeftChild() const
{
    return this->_leftChild;
}

const ast::ExpressionNode::ptr &ast::BinaryNode::getRightChild() const
{
    return this->_rightChild;
}

ast::BinaryNode::ptr ast::BinaryNode::create(
    Token::Type oprt,
    const ast::ExpressionNode::ptr& left,
    const ast::ExpressionNode::ptr& right
)
{
    return std::make_shared<ast::BinaryNode>(oprt, left, right);
}
