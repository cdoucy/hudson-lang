#pragma once

#include "ExpressionNode.hpp"
#include "token.hpp"

namespace ast
{
    class StringNode final : public ExpressionNode
    {
        public:
            using ptr = std::shared_ptr<StringNode>;
            static ptr create(const Token::String &s);

            explicit StringNode(Token::String s);

            void accept(IVisitor &visitor) override;

            [[nodiscard]] const Token::String &getValue() const;

        private:
            std::string _s;
    };
}