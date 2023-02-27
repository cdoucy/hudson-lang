#pragma once

#include "ExpressionNode.hpp"
#include "token.hpp"

namespace ast
{
    class IdentifierNode final : public ExpressionNode
    {
        public:
            using ptr = std::shared_ptr<IdentifierNode>;
            static ptr create(const std::string &identifier);

            IdentifierNode(std::string identifier);
            ~IdentifierNode() final = default;

            void accept(IVisitor &visitor) override;
            [[nodiscard]] const std::string &getIdentifier() const noexcept;

        private:
            std::string _identifier;
    };
};