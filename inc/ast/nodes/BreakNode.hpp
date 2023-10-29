#pragma once

#include "StatementNode.hpp"

namespace ast
{
    class BreakNode final : public StatementNode
    {
        public:
            using ptr = std::shared_ptr<BreakNode>;
            static ptr create();
            BreakNode() = default;
            ~BreakNode() final = default;

            void accept(IVisitor &visitor) final;
    };
}