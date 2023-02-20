#pragma once

#include "INode.hpp"

namespace ast
{
    class ExpressionNode : public INode
    {
        public:
            using ptr = std::shared_ptr<ExpressionNode>;
    };
};