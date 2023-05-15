#pragma once

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

#include "ProgramNode.hpp"

#include "State.hpp"
#include "Object.hpp"

namespace ast
{
    class EvalVisitor final : public IVisitor
    {
        public:
            EvalVisitor() = default;
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

            void visit(ProgramNode &node) final;

            const runtime::Object &value() const noexcept;
            [[nodiscard]] Token::Integer getResult() const;

            const runtime::State &getState() const noexcept;

            void clearState() noexcept;

        private:
            runtime::Object _expressionResult;
            runtime::State _state;

            Token::Integer evaluateChild(const ast::ExpressionNode::ptr &child);
            const runtime::Object &evaluate(const ast::ExpressionNode::ptr &expr);

    };
};