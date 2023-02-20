#pragma once

#include "StatementNode.hpp"
#include "ExpressionNode.hpp"
#include "token.hpp"

namespace ast
{
    class DeclarationNode final : public StatementNode
    {
        public:
            DeclarationNode(
                Token::Type type,
                std::string identifier,
                ExpressionNode::ptr expression = nullptr
            );

            ~DeclarationNode() final = default;

            void accept(IVisitor &v) final;

            [[nodiscard]] Token::Type getType() const;
            [[nodiscard]] const std::string &getIdentifier() const;
            [[nodiscard]] const ExpressionNode::ptr &getExpression() const;

        private:
            Token::Type _type;
            std::string _identifier;
            ExpressionNode::ptr _expression;
    };
};