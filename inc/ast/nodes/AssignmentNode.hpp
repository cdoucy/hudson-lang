#pragma once

#include "StatementNode.hpp"
#include "ExpressionNode.hpp"

namespace ast
{
    class AssignmentNode final : public StatementNode
    {
        public:
            using ptr = std::shared_ptr<AssignmentNode>;
            static ptr create(const std::string &identifier, const ExpressionNode::ptr &expression);

            explicit AssignmentNode(
                std::string identifier,
                ExpressionNode::ptr expression
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