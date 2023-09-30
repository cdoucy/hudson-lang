#include "Parser.hpp"

void Parser::feed(const std::string &expression)
{
    this->_lexer.feed(expression);
    this->_tokenItr.reset(this->_lexer.getTokens());
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
        &Parser::parseAssignmentStatement,
        &Parser::parseIncrementStatement,
        &Parser::parseExpressionStatement,
        &Parser::parseDeclarationStatement,
        &Parser::parsePrint,
        &Parser::parseBlock,
        &Parser::parseWhile,
        &Parser::parseConditions,
        &Parser::parseFor
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
    const auto &token = this->_tokenItr.get();
    if (!expr)
        return nullptr;

    if (!token)
        throw syntaxError("expecting \";\"", *this->_tokenItr.prev());

    if (token->isType(Token::CLOSE_PARENTHESIS))
        throw syntaxError("unmatched parenthesis", *token);

    if (token->isType(Token::IDENTIFIER))
        throw syntaxError("unexpected identifier", *token);

    if (!token->isType(Token::SEMICOLON))
        throw syntaxError("expecting \";\"", *token);

    this->_tokenItr.advance();

    return ast::ExpressionStatementNode::create(expr);
}

ast::StatementNode::ptr Parser::parseDeclarationStatement()
{
    auto decl = this->parseDeclaration();
    if (!decl)
        return nullptr;

    auto token = this->_tokenItr.get();

    if (!token || !token->isType(Token::SEMICOLON))
        throw syntaxError("expecting \";\"", *this->_tokenItr.prev());

    this->_tokenItr.advance();

    return decl;
}

ast::StatementNode::ptr Parser::parseAssignmentStatement()
{
    auto assignment = this->parseAssignment();
    if (!assignment)
        return nullptr;

    auto token = this->_tokenItr.get();
    if (!token || !token->isType(Token::SEMICOLON))
        throw syntaxError("expecting \";\"", *this->_tokenItr.prev());

    this->_tokenItr.advance();

    return assignment;
}

ast::StatementNode::ptr Parser::parseIncrementStatement()
{
    auto increment = this->parseIncrement();
    if (!increment)
        return nullptr;

    auto token = this->_tokenItr.get();
    if (!token || !token->isType(Token::SEMICOLON))
        throw syntaxError("expecting \";\"", *this->_tokenItr.prev());

    this->_tokenItr.advance();

    return increment;
}

ast::IncrementNode::ptr Parser::parseIncrement()
{
    auto token = this->_tokenItr.get();
    if (!token || !token->isType(Token::IDENTIFIER))
        return nullptr;

    auto nextToken = this->_tokenItr.next();
    if (!nextToken || (!nextToken->isType(Token::INCR) && !nextToken->isType(Token::DECR)))
        return nullptr;

    this->_tokenItr.advance().advance();

    return ast::IncrementNode::create(token->getLexeme(), nextToken->getType());
}

ast::DeclarationNode::ptr Parser::parseDeclaration()
{
    auto token = this->_tokenItr.get();
    if (!token || (!token->isType(Token::INT_TYPE) && !token->isType(Token::STR_TYPE)))
        return nullptr;

    Token::Type declarationType = token->getType();
    this->_tokenItr.advance();

    token = this->_tokenItr.get();
    if (!token || !token->isType(Token::IDENTIFIER))
        throw syntaxError("expecting identifier", *this->_tokenItr.prev());

    std::string identifier(token->getLexeme());
    this->_tokenItr.advance();

    token = this->_tokenItr.get();
    ast::ExpressionNode::ptr expr;

    if (token && token->isType(Token::ASSIGN)) {
        this->_tokenItr.advance();

        expr = this->parseExpression();
        if (!expr)
            throw syntaxError("expecting expression", *token);
    }

    return ast::DeclarationNode::create(declarationType, identifier, expr);
}

ast::AssignmentNode::ptr Parser::parseAssignment()
{
    auto token = this->_tokenItr.get();
     if (!token || !token->isType(Token::IDENTIFIER))
        return nullptr;

     std::string identifier(token->getLexeme());

     auto nextToken = this->_tokenItr.next();
     if (!nextToken || !nextToken->isAssignableOperator())
         return nullptr;
    this->_tokenItr.advance();

    token = this->_tokenItr.get();
    this->_tokenItr.advance();

    auto expr = this->parseExpression();
    if (!expr)
        throw syntaxError("expecting expression or operator", *token);

    return ast::AssignmentNode::create(identifier, expr, token->getType());
}

ast::StatementNode::ptr Parser::parsePrint()
{
    auto token = this->_tokenItr.get();
    if (!token || !token->isType(Token::PRINT))
        return nullptr;

    this->_tokenItr.advance();

    token = this->_tokenItr.get();
    if (!token || !token->isType(Token::OPEN_PARENTHESIS))
        throw syntaxError("expecting \"()\"", *this->_tokenItr.prev());

    auto leftParen = *token;

    this->_tokenItr.advance();

    token = this->_tokenItr.get();
    if (!token)
        throw syntaxError("expecting \"()\"", leftParen);

    ast::ExpressionNode::ptr expr;

    if (!token->isType(Token::CLOSE_PARENTHESIS)) {

        // Expression is optional in "print" statement, no need to check for nullptr
        expr = this->parseExpression();

        token = this->_tokenItr.get();
        if (!token || !token->isType(Token::CLOSE_PARENTHESIS))
            throw syntaxError("unmatched \")\"", leftParen);

    }

    this->_tokenItr.advance();

    token = this->_tokenItr.get();
    if (!token || !token->isType(Token::SEMICOLON))
        throw syntaxError("expecting \";\"", token ? *token : *this->_tokenItr.prev());

    this->_tokenItr.advance();

    return ast::PrintNode::create(expr);
}

ast::StatementNode::ptr Parser::parseBlock()
{
    auto token = this->_tokenItr.get();
    if (!token || !token->isType(Token::OPEN_BRACKET))
        return nullptr;

    auto openToken = *token;
    this->_tokenItr.advance();

    std::list<ast::StatementNode::ptr> statements;
    auto stmt = this->parseStatement();

    while (stmt) {
        statements.push_back(stmt);
        stmt = this->parseStatement();
    }

    token = this->_tokenItr.get();
    if (!token || !token->isType(Token::CLOSE_BRACKET))
        throw syntaxError("unmatched '{'", openToken);
    this->_tokenItr.advance();

    return ast::BlockNode::create(statements);
}

ast::StatementNode::ptr Parser::parseWhile()
{
    auto token = this->_tokenItr.get();
    if (!token || !token->isType(Token::WHILE))
        return nullptr;

    auto whileToken = *token;

    this->_tokenItr.advance();
    auto expr = this->parseParenthesizedExpression(whileToken);

    token = this->_tokenItr.get();
    if (!token)
        throw syntaxError("expecting statement or \";\"", whileToken);

    if (token->isType(Token::SEMICOLON)) {
        this->_tokenItr.advance();
        return ast::WhileNode::create(expr);
    }

    auto stmt = this->parseStatement();

    if (!stmt)
        throw syntaxError("expecting statement or \";\"", whileToken);

    return ast::WhileNode::create(expr, stmt);
}

ast::StatementNode::ptr Parser::parseFor()
{
    auto token = this->_tokenItr.get();
    if (!token || !token->isType(Token::FOR))
        return nullptr;

    const auto forToken = *token;

    token = this->_tokenItr.advance().get();

    if (!token || !token->isType(Token::OPEN_PARENTHESIS))
        throw syntaxError("expecting \"(\"", forToken);

    const auto parenToken = *token;

    this->_tokenItr.advance();

    auto initStmt = this->parseInitStatement();

    token = this->_tokenItr.get();
    if (!token || !token->isType(Token::SEMICOLON))
        throw syntaxError("expecting \";\" after init statement", *this->_tokenItr.prev());
    this->_tokenItr.advance();

    auto expr = this->parseExpression();
    if (!expr)
        throw syntaxError("expecting expression", *this->_tokenItr.prev());

    token = this->_tokenItr.get();
    if (!token || !token->isType(Token::SEMICOLON))
        throw syntaxError("expecting \";\" after expression", *this->_tokenItr.prev());
    this->_tokenItr.advance();

    auto stepStatement = this->parseStepStatement();

    token = this->_tokenItr.get();
    if (!token || !token->isType(Token::CLOSE_PARENTHESIS))
        throw syntaxError("unmatched \"(\"", parenToken);
    this->_tokenItr.advance();

    token = this->_tokenItr.get();
    if (!token)
        throw syntaxError("expecting statement or \";\"", forToken);

    if (token->isType(Token::SEMICOLON)) {
        this->_tokenItr.advance();
        return ast::ForNode::create(expr, initStmt, stepStatement);
    }

    auto stmt = this->parseStatement();

    if (!stmt)
        throw syntaxError("expecting statement or \";\"", forToken);

    return ast::ForNode::create(expr, initStmt, stepStatement, stmt);
}

ast::InitStatementNode::ptr Parser::parseInitStatement()
{
    auto decl = this->parseDeclaration();
    if (decl)
        return decl;

    return this->parseAssignment();
}

ast::StepStatementNode::ptr Parser::parseStepStatement()
{
    auto assignment = this->parseAssignment();

    if (assignment)
        return assignment;

    return this->parseIncrement();
}

ast::StatementNode::ptr Parser::parseConditions()
{
    auto token = this->_tokenItr.get();
    if (!token || !token->isType(Token::IF))
        return nullptr;

    auto ifToken = *token;
    this->_tokenItr.advance();
    auto ifExpr = this->parseParenthesizedExpression(ifToken);

    auto ifStmt = this->parseStatement();
    if (!ifStmt)
        throw syntaxError("expecting statement", ifToken);

    token = this->_tokenItr.get();
    if (!token || !token->isType(Token::ELSE))
        return ast::ConditionNode::create(ifExpr, ifStmt);
    this->_tokenItr.advance();

    auto elseToken = *token;

    auto elseStmt = this->parseStatement();
    if (!elseStmt)
        throw syntaxError("expecting statement", elseToken);

    return ast::ConditionNode::create(ifExpr, ifStmt, elseStmt);
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
    auto token = this->_tokenItr.get();
    if (!token)
        return nullptr;

    if (!token->isTypeAnyOf({Token::PLUS, Token::MINUS, Token::NOT, Token::BITWISE_NOT}))
        return this->parsePrimary();

    this->_tokenItr.advance();

    auto expression = this->parseUnary();
    if (!expression)
        throw syntaxError("expecting expression", *token);

    return ast::UnaryNode::create(token->getType(), expression);
}

ast::ExpressionNode::ptr Parser::parsePrimary()
{
    static const std::vector<ast::ExpressionNode::ptr(Parser::*)()> primaryParsers{
        &Parser::parseInteger,
        &Parser::parseString,
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
    auto token = this->_tokenItr.get();
    if (!token || !token->isType(Token::INTEGER))
        return nullptr;

    this->_tokenItr.advance();
    return ast::IntegerNode::create(token->getIntegerLiteral());
}

ast::ExpressionNode::ptr Parser::parseString()
{
    auto token = this->_tokenItr.get();
    if (!token || !token->isType(Token::STRING))
        return nullptr;

    this->_tokenItr.advance();
    return ast::StringNode::create(token->getLiteral<Token::String>());
}

ast::ExpressionNode::ptr Parser::parseIdentifier()
{
    auto token = this->_tokenItr.get();
    if (!token || !token->isType(Token::IDENTIFIER))
        return nullptr;

    this->_tokenItr.advance();
    return ast::IdentifierNode::create(token->getLexeme());
}

ast::ExpressionNode::ptr Parser::parseGrouping()
{
    auto token = this->_tokenItr.get();
    if (!token)
        return nullptr;

    if (token->isType(Token::CLOSE_PARENTHESIS))
        throw syntaxError("expecting \"(\"", *token);

    if (!token->isType(Token::OPEN_PARENTHESIS))
        return nullptr;

    this->_tokenItr.advance();

    auto nextToken = this->_tokenItr.get();
    if (!nextToken || nextToken->isType(Token::CLOSE_PARENTHESIS))
        throw syntaxError("expecting expression", *token);

    auto expression = this->parseExpression();

    if (!expression)
        throw syntaxError("expecting expression", *token);

    nextToken = this->_tokenItr.get();

    if (!nextToken || !nextToken->isType(Token::CLOSE_PARENTHESIS))
        throw syntaxError("expecting \")\"", *token);

    this->_tokenItr.advance();

    return expression;
}

SyntaxError Parser::syntaxError(const std::string &errorMessage, const Token &token)
{
    return {errorMessage, token.getLexeme(), token.getLine(), token.getColumn()};
}

ast::ExpressionNode::ptr Parser::parseBinaryExpression(
    const std::initializer_list<Token::Type> &matchTokens,
    const Parser::ParseFunction &parseSubExpression,
    bool logical
)
{
    auto expression = parseSubExpression();

    auto token = this->_tokenItr.get();

    while (token && token->isTypeAnyOf(matchTokens)) {
        this->_tokenItr.advance();

        if (!expression)
            throw syntaxError("expecting expression", *token);

        auto subExpression = parseSubExpression();
        if (!subExpression)
            throw syntaxError("expecting expression", *token);

        if (!logical)
            expression = ast::BinaryNode::create(token->getType(), expression, subExpression);
        else
            expression = ast::LogicalNode::create(token->getType(), expression, subExpression);

        token = this->_tokenItr.get();
    }

    return expression;
}

ast::ExpressionNode::ptr Parser::parseParenthesizedExpression(const Token &prevToken)
{
    auto token = this->_tokenItr.get();

    if (!token || !token->isType(Token::OPEN_PARENTHESIS))
        throw syntaxError("expecting \"(\"", prevToken);
    this->_tokenItr.advance();

    auto parenToken = *token;

    token = this->_tokenItr.get();
    if (!token)
        throw syntaxError("expecting expression after \"(\"", prevToken);
    if (token->isType(Token::CLOSE_PARENTHESIS))
        throw syntaxError("expecting expression after \"(\"", prevToken);

    auto expr = this->parseExpression();
    if (!expr)
        throw syntaxError("expecting expression after \"(\"", prevToken);

    token = this->_tokenItr.get();
    if (!token || !token->isType(Token::CLOSE_PARENTHESIS))
        throw syntaxError("unmatched \"(\"", parenToken);
    this->_tokenItr.advance();

    return expr;
}
