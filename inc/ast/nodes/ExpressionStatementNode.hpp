#pragma once

#include "StatementNode.hpp"
#include "ExpressionNode.hpp"

namespace ast
{
    class ExpressionStatementNode final : public StatementNode
    {
        public:
            explicit ExpressionStatementNode(ExpressionNode::ptr expression);
            ~ExpressionStatementNode() final = default;

            void accept(IVisitor &visitor) final;

            [[nodiscard]] const ExpressionNode::ptr &getExpression() const;

        private:
            ExpressionNode::ptr _expression;
    };
};