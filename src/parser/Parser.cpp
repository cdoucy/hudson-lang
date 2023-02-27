#include "Parser.hpp"

void Parser::feed(const std::string &expression)
{
    this->_lexer.feed(expression);
    this->_astRoot = this->parseProgram();
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

ast::ProgramNode::ptr Parser::parseProgram()
{
    std::list<ast::StatementNode::ptr> statements;

    for (auto stmt = this->parseStatement(); stmt; stmt = this->parseStatement())
        statements.push_back(stmt);

    return ast::ProgramNode::create(statements);
}

ast::StatementNode::ptr Parser::parseStatement()
{
    static const std::vector<ast::StatementNode::ptr(Parser::*)()> statementsParser{
        &Parser::parseAssignment,
        &Parser::parseExpressionStatement,
        &Parser::parseDeclaration
    };

    for (const auto &parse : statementsParser) {
        const auto &stmt = (this->*parse)();
        if (stmt)
            return stmt;
    }

    return nullptr;
}

ast::StatementNode::ptr Parser::parseExpressionStatement()
{
    const auto &expr = this->parseExpression();
    const auto &token = this->_lexer.getNextToken();

    if (!expr)
        return nullptr;

    if (!token)
        throw syntaxError("expecting \";\"", this->_lexer.getPrevToken());

    if (token->isType(Token::CLOSE_PARENTHESIS))
        throw syntaxError("unmatched parenthesis", token);

    if (!token->isType(Token::SEMICOLON))
        throw syntaxError("expecting \";\"", token);

    this->_lexer.popToken();

    return ast::ExpressionStatementNode::create(expr);
}

ast::StatementNode::ptr Parser::parseDeclaration()
{
    auto token = this->_lexer.getNextToken();
    if (!token || !token->isType(Token::INT_TYPE))
        return nullptr;

    Token::Type declarationType = token->getType();
    this->_lexer.popToken();

    token = this->_lexer.getNextToken();
    if (!token || !token->isType(Token::IDENTIFIER))
        throw syntaxError("expecting identifier", this->_lexer.getPrevToken());

    std::string identifier(token->getLexeme());
    this->_lexer.popToken();

    token = this->_lexer.getNextToken();
    if (!token)
        throw syntaxError("expecting assignment or \";\"", this->_lexer.getPrevToken());

    ast::ExpressionNode::ptr expr;

    if (token->isType(Token::ASSIGN)) {
        this->_lexer.popToken();

        expr = this->parseExpression();
        if (!expr)
            throw syntaxError("expecting expression", token);

        token = this->_lexer.getNextToken();
    }

    if (!token || !token->isType(Token::SEMICOLON))
        throw syntaxError("expecting \";\"", this->_lexer.getPrevToken());

    this->_lexer.popToken();

    return ast::DeclarationNode::create(declarationType, identifier, expr);
}

ast::StatementNode::ptr Parser::parseAssignment()
{
    auto token = this->_lexer.getNextToken();
     if (!token || !token->isType(Token::IDENTIFIER))
        return nullptr;

    std::string identifier(token->getLexeme());
    this->_lexer.popToken();

    token = this->_lexer.getNextToken();
    if (!token || !token->isType(Token::ASSIGN))
        throw syntaxError("expecting assignment", this->_lexer.getPrevToken());

    this->_lexer.popToken();

    const auto &expr = this->parseExpression();
    if (!expr)
        throw syntaxError("expecting expression", token);

    token = this->_lexer.getNextToken();
    if (!token || !token->isType(Token::SEMICOLON))
        throw syntaxError("expecting \";\"", this->_lexer.getPrevToken());

    this->_lexer.popToken();

    return ast::AssignmentNode::create(identifier, expr);
}

ast::ExpressionNode::ptr Parser::parseExpression()
{
    return this->parseLogicalOr();
}

ast::ExpressionNode::ptr Parser::parseLogicalOr()
{
    return this->parseBinaryExpression(
        {Token::OR},
        [this]() {return this->parseLogicalAnd();},
        true
    );
}

ast::ExpressionNode::ptr Parser::parseLogicalAnd()
{
    return this->parseBinaryExpression(
        {Token::AND},
        [this]() {return this->parseBitwiseOr();},
        true
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

    if (!token->isTypeAnyOf({Token::PLUS, Token::MINUS, Token::NOT, Token::BITWISE_NOT}))
        return this->parsePrimary();

    this->_lexer.popToken();

    auto expression = this->parseUnary();
    if (!expression)
        throw syntaxError("expecting expression", token);

    return ast::UnaryNode::create(token->getType(), expression);
}

ast::ExpressionNode::ptr Parser::parsePrimary()
{
    static const std::vector<ast::ExpressionNode::ptr(Parser::*)()> primaryParsers{
        &Parser::parseInteger,
        &Parser::parseIdentifier,
        &Parser::parseGrouping
    };

    for (const auto &parse : primaryParsers) {
        const auto &expr = (this->*parse)();
        if (expr)
            return expr;

    }

    return nullptr;
}

ast::ExpressionNode::ptr Parser::parseInteger()
{
    auto token = this->_lexer.getNextToken();
    if (!token || !token->isType(Token::INTEGER))
        return nullptr;

    this->_lexer.popToken();
    return ast::IntegerNode::create(token->getIntegerLiteral());
}

ast::ExpressionNode::ptr Parser::parseIdentifier()
{
    auto token = this->_lexer.getNextToken();
    if (!token || !token->isType(Token::IDENTIFIER))
        return nullptr;

    this->_lexer.popToken();
    return ast::IdentifierNode::create(token->getLexeme());
}

ast::ExpressionNode::ptr Parser::parseGrouping()
{
    auto token = this->_lexer.getNextToken();
    if (!token)
        return nullptr;

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
        throw syntaxError("expecting \")\"", token);

    this->_lexer.popToken();

    return expression;
}

SyntaxError Parser::syntaxError(const std::string &errorMessage, const Token::ptr &token)
{
    return {errorMessage, token->getLexeme(), token->getLine(), token->getColumn()};
}

ast::ExpressionNode::ptr Parser::parseBinaryExpression(
    const std::initializer_list<Token::Type> &matchTokens,
    const Parser::ParseFunction &parseSubExpression,
    bool logical
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

        if (!logical)
            expression = ast::BinaryNode::create(token->getType(), expression, subExpression);
        else
            expression = ast::LogicalNode::create(token->getType(), expression, subExpression);

        token = this->_lexer.getNextToken();
    }

    return expression;
}
