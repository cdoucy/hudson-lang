#pragma once

#include "ExpressionNode.hpp"
#include "token.hpp"

namespace ast
{
    class IntegerNode final : public ExpressionNode
    {
        public:
            using ptr = std::shared_ptr<IntegerNode>;
            static ptr create(Token::Integer value);

            explicit IntegerNode(Token::Integer value);
            virtual ~IntegerNode() final = default;

            void accept(IVisitor &visitor) override;

            [[nodiscard]] Token::Integer getValue() const;

        private:
            Token::Integer _value;
    };
};