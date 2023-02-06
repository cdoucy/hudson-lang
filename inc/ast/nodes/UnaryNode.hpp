#pragma once

#include "ExpressionNode.hpp"
#include "token.hpp"

namespace ast
{
    class UnaryNode final : public ExpressionNode
    {
        public:
            using ptr = std::shared_ptr<UnaryNode>;
            static ptr create(Token::Type oprt, const ast::ExpressionNode::ptr &child);

            UnaryNode(Token::Type oprt, ast::ExpressionNode::ptr child);
            virtual ~UnaryNode() final = default;

            void accept(IVisitor &visitor) final;

            [[nodiscard]] Token::Type getOperator() const;

            [[nodiscard]] const ExpressionNode::ptr &getChild() const;

        private:
            Token::Type _operator;
            ExpressionNode::ptr _child;
    };
}