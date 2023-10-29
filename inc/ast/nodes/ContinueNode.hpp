#pragma once

#include "StatementNode.hpp"

namespace ast
{
    class ContinueNode final : public StatementNode
    {
        public:
        using ptr = std::shared_ptr<ContinueNode>;
        static ptr create();
        ContinueNode() = default;
        ~ContinueNode() final = default;

        void accept(IVisitor &visitor) final;
    };
}