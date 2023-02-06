#pragma once

#include "INode.hpp"

namespace ast
{
    class ExpressionNode : public INode
    {
        public:
            using ptr = std::shared_ptr<ExpressionNode>;

            void accept(IVisitor &visitor) override = 0;
    };
};