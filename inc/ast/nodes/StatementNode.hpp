#pragma once

#include "INode.hpp"

namespace ast
{
    class StatementNode : public INode
    {
        public:
            using ptr = std::shared_ptr<StatementNode>;
    };

    class InitStatementNode : virtual public StatementNode
    {
        public:
            using ptr = std::shared_ptr<InitStatementNode>;
    };

    class StepStatementNode : virtual public StatementNode
    {
        public:
            using ptr = std::shared_ptr<StepStatementNode>;
    };
};