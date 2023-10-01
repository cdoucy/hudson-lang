#pragma once

#include "StatementNode.hpp"
#include "ExpressionNode.hpp"

namespace ast
{
    class ReturnNode final : public StatementNode
    {
        public:
        using ptr = std::shared_ptr<ReturnNode>;
        static ptr create(
            const ExpressionNode::ptr &expr = nullptr
        );
        explicit ReturnNode(
            ExpressionNode::ptr expr = nullptr
        );
        ~ReturnNode() final = default;

        void accept(IVisitor &visitor) final;

        [[nodiscard]] const ExpressionNode::ptr &getExpression() const;

        private:
            ExpressionNode::ptr _expr;
    };
};