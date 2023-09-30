#pragma once

#include "StatementNode.hpp"
#include "token.hpp"

namespace ast
{
    class IncrementNode final : public StepStatementNode
    {
        public:
        using ptr = std::shared_ptr<IncrementNode>;
        static ptr create(
            const std::string &identifier,
            Token::Type op
        );

        explicit IncrementNode(
            std::string identifier,
            Token::Type op
        );

        ~IncrementNode() final = default;

        void accept(IVisitor &visitor) final;

        [[nodiscard]] const std::string &getIdentifier() const;
        [[nodiscard]] Token::Type getOperator() const;

        private:
        std::string _identifier;
        Token::Type _op;
    };
};