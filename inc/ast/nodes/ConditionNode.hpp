#pragma once

#include "StatementNode.hpp"
#include "ExpressionNode.hpp"

namespace ast
{
    class ConditionNode final : public StatementNode {
        public:
            using ptr = std::shared_ptr<ConditionNode>;
            static ptr create(
                const ExpressionNode::ptr &expression,
                const StatementNode::ptr &ifBranch,
                const StatementNode::ptr &elseBranch = nullptr
            );

            ConditionNode(
                ExpressionNode::ptr expression,
                StatementNode::ptr ifBranch,
                StatementNode::ptr elseBranch = nullptr
            );
            ~ConditionNode() final = default;

            void accept(IVisitor &visitor) final;

            [[nodiscard]] const ExpressionNode::ptr &getExpression() const;
            [[nodiscard]] const StatementNode::ptr &getIfBranch() const;
            [[nodiscard]] const StatementNode::ptr &getElseBranch() const;

        private:
            ExpressionNode::ptr _expr;
            StatementNode::ptr _ifBranch;
            StatementNode::ptr _elseBranch;
    };
};