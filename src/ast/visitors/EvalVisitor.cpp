#include <functional>
#include <unordered_map>

#include "EvalVisitor.hpp"

#define OPERATOR_FUNCTION(type, op) {type, [](auto l, auto r){return l op r;}}

using OperatorFunction = std::function<Token::Integer (Token::Integer leftHand, Token::Integer rightHand)>;

static const std::unordered_map<Token::Type, OperatorFunction> operatorFunctionsMap{
    {
        Token::MOD, [](auto l, auto r) {
            if (r == 0)
                throw LogicalError("modulo by zero");

            return l % r;
        }
    },
    {
        Token::DIV, [](auto l, auto r) {
            if (r == 0)
                throw LogicalError("division by zero");

            return l / r;
        }
    },
    OPERATOR_FUNCTION(Token::MULT, *),
    OPERATOR_FUNCTION(Token::PLUS, +),
    OPERATOR_FUNCTION(Token::MINUS, -),
    OPERATOR_FUNCTION(Token::EQUAL, ==),
    OPERATOR_FUNCTION(Token::NOT_EQUAL, !=),
    OPERATOR_FUNCTION(Token::GT, >),
    OPERATOR_FUNCTION(Token::GTE, >=),
    OPERATOR_FUNCTION(Token::LT, <),
    OPERATOR_FUNCTION(Token::LTE, <=),
    OPERATOR_FUNCTION(Token::BITWISE_OR, |),
    OPERATOR_FUNCTION(Token::BITWISE_XOR, ^),
    OPERATOR_FUNCTION(Token::BITWISE_AND, &),
    OPERATOR_FUNCTION(Token::BITWISE_LSHIFT, <<),
    OPERATOR_FUNCTION(Token::BITWISE_RSHIFT, >>)
};

ast::EvalVisitor::EvalVisitor()
:   _result(0)
{}

void ast::EvalVisitor::visit(ast::IntegerNode &node)
{
    this->_result = node.getValue();
}

void ast::EvalVisitor::visit(ast::BinaryNode &node)
{
    Token::Integer leftHand = this->evaluateChild(node.getLeftChild());

    switch (node.getOperator()) {
        // AND and OR are special case since they control evaluation flow
        case Token::AND:
            this->_result = leftHand && this->evaluateChild(node.getRightChild());
            return;

        case Token::OR:
            this->_result = leftHand || this->evaluateChild(node.getRightChild());
            return;

        default:
            break;
    }

    Token::Integer rightHand = this->evaluateChild(node.getRightChild());

    auto operatorFunc = operatorFunctionsMap.find(node.getOperator());

    if (operatorFunc == operatorFunctionsMap.end())
        throw InternalError("EvalVisitor: unknown operator");

    this->_result = operatorFunc->second(leftHand, rightHand);
}

void ast::EvalVisitor::visit(ast::UnaryNode &node)
{
    Token::Integer child = this->evaluateChild(node.getChild());

    switch (node.getOperator()) {
        case Token::PLUS:
            this->_result = +child;
            break;

        case Token::MINUS:
            this->_result = -child;
            break;

        case Token::NOT:
            this->_result = !child;
            break;

        default:
            throw InternalError("EvalVisitor: unknown operator");
    }
}

Token::Integer ast::EvalVisitor::getResult() const
{
    return this->_result;
}

Token::Integer ast::EvalVisitor::evaluateChild(const ast::ExpressionNode::ptr &child)
{
    if (!child)
        throw InternalError("EvalVisitor: child is null");

    child->accept(*this);

    return this->_result;
}
