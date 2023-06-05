#pragma once

#include "StatementNode.hpp"
#include "ExpressionNode.hpp"

namespace ast
{
    class ForNode final : public StatementNode
    {
        public:
            using ptr = std::shared_ptr<ForNode>;
            static ptr create(
                const ExpressionNode::ptr &expression,
                const InitStatementNode::ptr &initStmt = nullptr,
                const StepStatementNode::ptr &stepStmt = nullptr,
                const StatementNode::ptr &statement = nullptr
            );
            explicit ForNode(
                ExpressionNode::ptr expression,
                InitStatementNode::ptr initStmt = nullptr,
                StepStatementNode::ptr stepStmt = nullptr,
                StatementNode::ptr statement = nullptr
            );
            ~ForNode() final = default;

            void accept(IVisitor &visitor) final;

            [[nodiscard]] const ExpressionNode::ptr &getExpression() const;
            [[nodiscard]] const StatementNode::ptr &getStatement() const;
            [[nodiscard]] const StepStatementNode::ptr &getStepStatement() const;
            [[nodiscard]] const InitStatementNode::ptr &getInitStatement() const;

        private:
            ExpressionNode::ptr _expr;
            InitStatementNode::ptr _init;
            StepStatementNode::ptr _step;
            StatementNode::ptr _stmt;
    };
};