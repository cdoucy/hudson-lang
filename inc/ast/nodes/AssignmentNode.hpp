#pragma once

#include "StatementNode.hpp"
#include "ExpressionNode.hpp"
#include "token.hpp"

namespace ast
{
    class AssignmentNode final : public InitStatementNode, public StepStatementNode
    {
        public:
            using ptr = std::shared_ptr<AssignmentNode>;
            static ptr create(
                const std::string &identifier,
                const ExpressionNode::ptr &expression,
                Token::Type op = Token::ASSIGN
            );

            explicit AssignmentNode(
                std::string identifier,
                ExpressionNode::ptr expression,
                Token::Type op = Token::ASSIGN
            );

            ~AssignmentNode() final = default;

            void accept(IVisitor &visitor) final;

            [[nodiscard]] const std::string &getIdentifier() const;
            [[nodiscard]] const ExpressionNode::ptr &getExpression() const;
            [[nodiscard]] Token::Type getOperator() const;

        private:
            std::string _identifier;
            ExpressionNode::ptr _expression;
            Token::Type _op;
    };
};