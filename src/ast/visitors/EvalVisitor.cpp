#include <functional>
#include <unordered_map>

#include "EvalVisitor.hpp"

#define OPERATOR_FUNCTION(type, op) {type, [](const auto &l, const auto &r){return l op r;}}

using OperatorFunction = std::function<
    runtime::Object(const runtime::Object &left, const runtime::Object &right)
>;

static const std::unordered_map<Token::Type, OperatorFunction> operatorFunctionsMap{
    OPERATOR_FUNCTION(Token::MOD, %),
    OPERATOR_FUNCTION(Token::DIV, /),
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

void ast::EvalVisitor::visit(ast::IntegerNode &node)
{
    this->_expressionResult = node.getValue();
}

void ast::EvalVisitor::visit(ast::BinaryNode &node)
{
    const runtime::Object left = this->evaluate(node.getLeftChild());
    const runtime::Object &right = this->evaluate(node.getRightChild());

    const auto &operatorFunc = operatorFunctionsMap.find(node.getOperator());

    if (operatorFunc == operatorFunctionsMap.end())
        throw InternalError("EvalVisitor: unknown operator");

    this->_expressionResult = operatorFunc->second(left, right);
}

void ast::EvalVisitor::visit(ast::UnaryNode &node)
{
    const runtime::Object &obj = this->evaluate(node.getChild());

    switch (node.getOperator()) {
        case Token::PLUS:
            this->_expressionResult = +obj;
            break;

        case Token::MINUS:
            this->_expressionResult = -obj;
            break;

        case Token::NOT:
            this->_expressionResult = !obj;
            break;

        case Token::BITWISE_NOT:
            this->_expressionResult = ~obj;
            break;

        default:
            throw InternalError("EvalVisitor: unknown operator");
    }
}

void ast::EvalVisitor::visit(ast::LogicalNode &node)
{
    const runtime::Object &left = this->evaluate(node.getLeftChild());

    switch (node.getOperator()) {
        case Token::AND:
            this->_expressionResult = left && this->evaluate(node.getRightChild());
            break;

        case Token::OR:
            this->_expressionResult = left || this->evaluate(node.getRightChild());
            break;

        default:
            throw InternalError("EvalVisitor: operator is not logical");
    }
}

void ast::EvalVisitor::visit(ast::IdentifierNode &node)
{
    this->_expressionResult = this->_state.get(node.getIdentifier());
}

Token::Integer ast::EvalVisitor::getResult() const
{
    return this->_expressionResult.getInteger();
}

Token::Integer ast::EvalVisitor::evaluateChild(const ast::ExpressionNode::ptr &child)
{
    if (!child)
        throw InternalError("EvalVisitor: child is null");

    child->accept(*this);

    return this->_expressionResult.getInteger();
}

void ast::EvalVisitor::visit(ast::ExpressionStatementNode &node)
{
    node.getExpression()->accept(*this);
}

void ast::EvalVisitor::visit(ast::DeclarationNode &node)
{
    Token::Integer value = 0;
    const auto &expression = node.getExpression();

    if (expression)
        value = this->evaluateChild(node.getExpression());

    runtime::Object object(value, node.getIdentifier());

    this->_state.set(node.getIdentifier(), object);
}

void ast::EvalVisitor::visit(ast::AssignmentNode &node)
{
    auto &object = this->_state.get(node.getIdentifier());
    auto value = this->evaluateChild(node.getExpression());

    object.set(value);
}

void ast::EvalVisitor::visit(ast::ProgramNode &program)
{
    for (const auto &stmt : program.getStatements())
        stmt->accept(*this);
}

const runtime::Object &ast::EvalVisitor::evaluate(const ast::ExpressionNode::ptr &expr)
{
    if (!expr)
        throw InternalError("EvalVisitor: expr is null");

    expr->accept(*this);

    return this->_expressionResult;
}

const runtime::State &ast::EvalVisitor::getState() const noexcept
{
    return this->_state;
}
