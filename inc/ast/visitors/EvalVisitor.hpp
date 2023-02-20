#pragma once

#include "IVisitor.hpp"
#include "IntegerNode.hpp"
#include "BinaryNode.hpp"
#include "ExpressionNode.hpp"
#include "UnaryNode.hpp"

#include "ExpressionStatementNode.hpp"
#include "DeclarationNode.hpp"
#include "AssignmentNode.hpp"

#include "ProgramNode.hpp"

#include "State.hpp"

namespace ast
{
    class EvalVisitor final : public IVisitor
    {
        public:
            EvalVisitor();
            ~EvalVisitor() final = default;

            void visit(IntegerNode &node) final;
            void visit(BinaryNode &node) final;
            void visit(UnaryNode &node) final;

            void visit(ExpressionStatementNode &node) final;
            void visit(DeclarationNode &node) final;
            void visit(AssignmentNode &node) final;

            void visit(ProgramNode &node) final;

            [[nodiscard]] Token::Integer getResult() const;

        private:
            Token::Integer _result;
            runtime::State _state;

            Token::Integer evaluateChild(const ast::ExpressionNode::ptr &child);
    };
};