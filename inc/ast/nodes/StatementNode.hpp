#pragma once

#include "INode.hpp"

namespace ast
{
    class StatementNode : public INode
    {
        public:
            using ptr = std::shared_ptr<StatementNode>;
    };
};