#pragma once

#include "IVisitor.hpp"
#include "IntegerNode.hpp"
#include "BinaryNode.hpp"
#include "ExpressionNode.hpp"
#include "UnaryNode.hpp"

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

            [[nodiscard]] Token::Integer getResult() const;

        private:
            Token::Integer _result;

            Token::Integer evaluateChild(const ast::ExpressionNode::ptr &child);
    };
};