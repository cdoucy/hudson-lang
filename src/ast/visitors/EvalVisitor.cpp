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

void ast::EvalVisitor::visit(ast::StringNode &node)
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
    this->_expressionResult = this->_state->find(node.getIdentifier());
}

Token::Integer ast::EvalVisitor::getResult() const
{
    return this->_expressionResult.getInteger();
}

void ast::EvalVisitor::visit(ast::ExpressionStatementNode &node)
{
    node.getExpression()->accept(*this);
}

void ast::EvalVisitor::visit(ast::DeclarationNode &node)
{
    runtime::Object object(node.getType(), node.getIdentifier());
    const auto &expression = node.getExpression();

    if (expression)
        object.assign(this->evaluate(expression));

    this->_state->set(node.getIdentifier(), object);
}

void ast::EvalVisitor::visit(ast::AssignmentNode &node)
{
    auto &object = this->_state->find(node.getIdentifier());
    auto value = this->evaluate(node.getExpression());

    object.assign(value);
}

void ast::EvalVisitor::visit(ast::PrintNode &node)
{
    const auto &expr = node.getExpression();
    std::string output;

    if (expr)
        output = this->evaluate(expr).getValueAsString();

    this->_output << output << std::endl;
}

void ast::EvalVisitor::visit(ast::BlockNode &node)
{
    this->_state = runtime::State::create(this->_state);

    for (const auto &stmt : node.getStatements()) {
        stmt->accept(*this);
    }

    this->_state = this->_state->restoreParent();
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
    return *this->_state;
}

const runtime::Object &ast::EvalVisitor::value() const noexcept
{
    return this->_expressionResult;
}

void ast::EvalVisitor::clearState() noexcept
{
    this->_state->clear();
}

ast::EvalVisitor::EvalVisitor(std::ostream &output)
:   _output(output),
    _expressionResult(),
    _state(runtime::State::create())
{}

void ast::EvalVisitor::visit(ast::WhileNode &node)
{
    const auto &stmt = node.getStatement();
    auto obj = this->evaluate(node.getExpression());

    while (obj) {
        if (stmt)
            stmt->accept(*this);

        obj = this->evaluate(node.getExpression());
    }
}

void ast::EvalVisitor::visit(ast::ConditionNode &node)
{
    const auto &expr = node.getExpression();
    const auto &ifBranch = node.getIfBranch();
    const auto &elseBranch = node.getElseBranch();

    if (this->evaluate(expr))
        ifBranch->accept(*this);
    else if (elseBranch)
        elseBranch->accept(*this);
}

void ast::EvalVisitor::visit(ast::ForNode &node)
{
    const auto &expr = node.getExpression();
    const auto &stmt = node.getStatement();
    const auto &init = node.getInitStatement();
    const auto &step = node.getStepStatement();

    if (init) {
        this->_state = runtime::State::create(this->_state);
        init->accept(*this);
    }

    while (this->evaluate(expr)) {
        if (stmt)
            stmt->accept(*this);

        if (step)
            step->accept(*this);
    }

    if (init)
        this->_state = this->_state->restoreParent();
}
