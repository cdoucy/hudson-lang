#pragma once

#include "StatementNode.hpp"
#include "ExpressionNode.hpp"
#include "token.hpp"

namespace ast
{
    class DeclarationNode final : public StatementNode
    {
        public:
            using ptr = std::shared_ptr<DeclarationNode>;
            static ptr create(
                Token::Type type,
                const std::string &identifier,
                const ExpressionNode::ptr &expression = nullptr
            );

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