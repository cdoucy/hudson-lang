#pragma once

#include "ExpressionNode.hpp"
#include "token.hpp"

namespace ast
{
    class LogicalNode final : public ExpressionNode
    {
        public:
            using ptr = std::shared_ptr<LogicalNode>;

            static ptr create(
                Token::Type oprt,
                const ast::ExpressionNode::ptr &left,
                const ast::ExpressionNode::ptr &right
            );

            LogicalNode(
                Token::Type oprt,
                ast::ExpressionNode::ptr left,
                ast::ExpressionNode::ptr right
            );
            ~LogicalNode() final = default;

            void accept(IVisitor &visitor) override;
            [[nodiscard]] Token::Type getOperator() const;

            [[nodiscard]] const ExpressionNode::ptr &getLeftChild() const;
            [[nodiscard]] const ExpressionNode::ptr &getRightChild() const;

        private:
            Token::Type _operator;
            ExpressionNode::ptr _leftChild;
            ExpressionNode::ptr _rightChild;
    };
};