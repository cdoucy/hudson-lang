#pragma once

#include "StatementNode.hpp"
#include "ExpressionNode.hpp"

namespace ast
{
    class AssignmentNode final : public StatementNode
    {
        public:
            explicit AssignmentNode(
                std::string identifier,
                ExpressionNode::ptr expression = nullptr
            );

            ~AssignmentNode() final = default;

            void accept(IVisitor &visitor) final;

            [[nodiscard]] const std::string &getIdentifier() const;
            [[nodiscard]] const ExpressionNode::ptr &getExpression() const;

        private:
            std::string _identifier;
            ExpressionNode::ptr _expression;
    };
};