#include "Parser.hpp"

void Parser::feed(const std::string &expression)
{
    this->_lexer.feed(expression);
    this->_astRoot = this->parseExpression();

    auto token = this->_lexer.getNextToken();
    if (token)
        throw syntaxError("unexpected token", token);
}

void Parser::clear() noexcept
{
    this->_lexer.clear();
    this->_astRoot.reset();
}

const ast::INode::ptr &Parser::getAstRoot() const noexcept
{
    return this->_astRoot;
}

ast::ExpressionNode::ptr Parser::parseExpression()
{
    return this->parseLogicalOr();
}

ast::ExpressionNode::ptr Parser::parseLogicalOr()
{
    return this->parseBinaryExpression(
        {Token::OR},
        [this]() {return this->parseLogicalAnd();}
    );
}

ast::ExpressionNode::ptr Parser::parseLogicalAnd()
{
    return this->parseBinaryExpression(
        {Token::AND},
        [this]() {return this->parseBitwiseOr();}
    );
}

ast::ExpressionNode::ptr Parser::parseBitwiseOr()
{
    return this->parseBinaryExpression(
        {Token::BITWISE_OR},
        [this](){return this->parseBitwiseXor();}
    );
}

ast::ExpressionNode::ptr Parser::parseBitwiseXor()
{
    return this->parseBinaryExpression(
        {Token::BITWISE_XOR},
        [this](){return this->parseBitwiseAnd();}
    );
}

ast::ExpressionNode::ptr Parser::parseBitwiseAnd()
{
    return this->parseBinaryExpression(
        {Token::BITWISE_AND},
        [this](){return this->parseEquality();}
    );
}

ast::ExpressionNode::ptr Parser::parseEquality()
{
    return this->parseBinaryExpression(
        {Token::EQUAL, Token::NOT_EQUAL},
        [this]() {return this->parseComparison();}
    );
}

ast::ExpressionNode::ptr Parser::parseComparison()
{
    return this->parseBinaryExpression(
        {Token::GT, Token::GTE, Token::LT, Token::LTE},
        [this]() {return this->parseBitshift();}
    );
}

ast::ExpressionNode::ptr Parser::parseBitshift()
{
    return this->parseBinaryExpression(
        {Token::BITWISE_LSHIFT, Token::BITWISE_RSHIFT},
        [this]() {return this->parseTerm();}
    );
}

ast::ExpressionNode::ptr Parser::parseTerm()
{
    return this->parseBinaryExpression(
        {Token::PLUS, Token::MINUS},
        [this]() {return this->parseFactor();}
    );
}

ast::ExpressionNode::ptr Parser::parseFactor()
{
    return this->parseBinaryExpression(
        {Token::MULT, Token::MOD, Token::DIV},
        [this]() {return this->parseUnary();}
    );
}

ast::ExpressionNode::ptr Parser::parseUnary()
{
    auto token = this->_lexer.getNextToken();
    if (!token)
        return nullptr;

    if (!token->isTypeAnyOf({Token::PLUS, Token::MINUS, Token::NOT}))
        return this->parsePrimary();

    this->_lexer.popToken();

    return ast::UnaryNode::create(token->getType(), this->parseUnary());
}

ast::ExpressionNode::ptr Parser::parsePrimary()
{
    auto token = this->_lexer.getNextToken();
    if (!token)
        return nullptr;

    if (token->isType(Token::INTEGER)) {
        this->_lexer.popToken();
        return ast::IntegerNode::create(token->getIntegerLiteral());
    }

    if (token->isType(Token::CLOSE_PARENTHESIS))
        throw syntaxError("expecting \"(\"", token);

    if (!token->isType(Token::OPEN_PARENTHESIS))
        return nullptr;

    this->_lexer.popToken();

    auto nextToken = this->_lexer.getNextToken();
    if (!nextToken || nextToken->isType(Token::CLOSE_PARENTHESIS))
        throw syntaxError("expecting expression", token);


    auto expression = this->parseExpression();

    if (!expression)
        throw syntaxError("expecting expression", token);

    nextToken = this->_lexer.getNextToken();

    if (!nextToken || !nextToken->isType(Token::CLOSE_PARENTHESIS))
        throw syntaxError("expecting \")\"", nextToken ? nextToken : token);

    this->_lexer.popToken();

    return expression;
}

SyntaxError Parser::syntaxError(const std::string &errorMessage, const Token::ptr &token)
{
    return {errorMessage, token->getLexeme(), token->getLine(), token->getColumn()};
}

ast::ExpressionNode::ptr Parser::parseBinaryExpression(
    const std::initializer_list<Token::Type> &matchTokens,
    const Parser::ParseFunction &parseSubExpression
)
{
    auto expression = parseSubExpression();

    auto token = this->_lexer.getNextToken();

    while (token && token->isTypeAnyOf(matchTokens)) {
        this->_lexer.popToken();

        if (!expression)
            throw syntaxError("expecting expression", token);

        auto subExpression = parseSubExpression();
        if (!subExpression)
            throw syntaxError("expecting expression", token);

        expression = ast::BinaryNode::create(token->getType(), expression, subExpression);

        token = this->_lexer.getNextToken();
    }

    return expression;
}
