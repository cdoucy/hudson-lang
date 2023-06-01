#pragma once

#include "StatementNode.hpp"
#include "ExpressionNode.hpp"

namespace ast
{
    class WhileNode final : public StatementNode
    {
        public:
            using ptr = std::shared_ptr<WhileNode>;
            static ptr create(const ExpressionNode::ptr &expression, const StatementNode::ptr &statement = nullptr);

            explicit WhileNode(ExpressionNode::ptr expression, StatementNode::ptr statement = nullptr);
            ~WhileNode() final = default;

            void accept(IVisitor &visitor) final;

            [[nodiscard]] const ExpressionNode::ptr &getExpression() const;
            [[nodiscard]] const StatementNode::ptr &getStatement() const;

        private:
            ExpressionNode::ptr _expr;
            StatementNode::ptr _stmt;
    };

};