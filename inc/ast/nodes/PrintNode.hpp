#pragma once

#include "StatementNode.hpp"
#include "ExpressionNode.hpp"

namespace ast
{
    class PrintNode final : public StatementNode
    {
        public:
            using ptr = std::shared_ptr<PrintNode>;
            static ptr create(const ExpressionNode::ptr &expr);

            explicit PrintNode(ExpressionNode::ptr expr);
            ~PrintNode() final = default;

            void accept(IVisitor &visitor) override;

            [[nodiscard]] const ExpressionNode::ptr &getExpression() const;

        private:
            ExpressionNode::ptr _expression;
    };
}