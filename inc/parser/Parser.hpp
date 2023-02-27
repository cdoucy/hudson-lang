#pragma once

#include "ast.hpp"
#include "lexer.hpp"

class Parser
{
    public:
        Parser() = default;
        ~Parser() = default;

        void feed(const std::string &expression);

        [[nodiscard]] const ast::INode::ptr &getAstRoot() const noexcept;

        void clear() noexcept;


    private:
        Lexer _lexer;
        ast::INode::ptr _astRoot;

        ast::ProgramNode::ptr parseProgram();
        ast::StatementNode::ptr parseStatement();
        ast::StatementNode::ptr parseExpressionStatement();
        ast::StatementNode::ptr parseDeclaration();
        ast::StatementNode::ptr parseAssignment();
        ast::ExpressionNode::ptr parseExpression();
        ast::ExpressionNode::ptr parseLogicalOr();
        ast::ExpressionNode::ptr parseLogicalAnd();
        ast::ExpressionNode::ptr parseBitwiseOr();
        ast::ExpressionNode::ptr parseBitwiseXor();
        ast::ExpressionNode::ptr parseBitwiseAnd();
        ast::ExpressionNode::ptr parseEquality();
        ast::ExpressionNode::ptr parseComparison();
        ast::ExpressionNode::ptr parseBitshift();
        ast::ExpressionNode::ptr parseTerm();
        ast::ExpressionNode::ptr parseFactor();
        ast::ExpressionNode::ptr parseUnary();
        ast::ExpressionNode::ptr parsePrimary();
        ast::ExpressionNode::ptr parseInteger();
        ast::ExpressionNode::ptr parseIdentifier();
        ast::ExpressionNode::ptr parseGrouping();

        using ParseFunction = std::function<ast::ExpressionNode::ptr ()>;

        ast::ExpressionNode::ptr parseBinaryExpression(
            const std::initializer_list<Token::Type> &matchTokens,
            const ParseFunction &parseSubExpression,
            bool logical = false
        );

        static SyntaxError syntaxError(const std::string &errorMessage, const Token::ptr &token);
};