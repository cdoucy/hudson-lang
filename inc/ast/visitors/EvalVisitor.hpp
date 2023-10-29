#pragma once

#include <iostream>

#include "IVisitor.hpp"
#include "IntegerNode.hpp"
#include "StringNode.hpp"
#include "BinaryNode.hpp"
#include "ExpressionNode.hpp"
#include "UnaryNode.hpp"
#include "LogicalNode.hpp"
#include "IdentifierNode.hpp"

#include "ExpressionStatementNode.hpp"
#include "DeclarationNode.hpp"
#include "AssignmentNode.hpp"
#include "PrintNode.hpp"
#include "BlockNode.hpp"
#include "WhileNode.hpp"
#include "ConditionNode.hpp"
#include "ForNode.hpp"
#include "IncrementNode.hpp"

#include "FunctionNode.hpp"
#include "ReturnNode.hpp"
#include "CallNode.hpp"

#include "ProgramNode.hpp"

#include "State.hpp"
#include "Object.hpp"

namespace ast
{
    class EvalVisitor final : public IVisitor
    {
        public:
            explicit EvalVisitor(std::ostream &output = std::cout);
            ~EvalVisitor() final = default;

            void visit(IntegerNode &node) final;
            void visit(StringNode &node) final;
            void visit(BinaryNode &node) final;
            void visit(UnaryNode &node) final;
            void visit(LogicalNode &node) final;
            void visit(IdentifierNode &node) final;

            void visit(ExpressionStatementNode &node) final;
            void visit(DeclarationNode &node) final;
            void visit(AssignmentNode &node) final;
            void visit(PrintNode &node) final;
            void visit(BlockNode &node) final;
            void visit(WhileNode &node) final;
            void visit(ConditionNode &node) final;
            void visit(ForNode &node) final;
            void visit(IncrementNode &node) final;

            void visit(FunctionNode &node) final;
            void visit(CallNode &node) final;
            void visit(ReturnNode &node) final;

            void visit(ProgramNode &node) final;

            [[nodiscard]] const runtime::Object &value() const noexcept;
            [[nodiscard]] Token::Integer getResult() const;

            [[nodiscard]] const runtime::State &getState() const noexcept;

            void clearState() noexcept;

        private:
            std::ostream &_output;
            runtime::Object _expressionResult;
            runtime::State::ptr _globalState;
            runtime::State::ptr _localState;
            bool _isExecutingCall;

            const runtime::Object &evaluate(const ast::ExpressionNode::ptr &expr);

        static LogicalError invalidArgType(std::string paramName, Token::Type actualType, Token::Type expectedType);
        static LogicalError invalidReturnType(Token::Type actualType, Token::Type expectedType);
        static LogicalError missingReturn(Token::Type actualType);

    };
};