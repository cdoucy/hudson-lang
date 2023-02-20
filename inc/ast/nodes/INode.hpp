#pragma once

#include <memory>
#include "IVisitor.hpp"

namespace ast
{
    class INode
    {
        public:
            using ptr = std::shared_ptr<INode>;

            virtual ~INode() = default;

            virtual void accept(IVisitor &visitor) = 0;
    };
};