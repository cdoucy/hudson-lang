#pragma once

#include <list>
#include "StatementNode.hpp"

namespace ast
{
    class ProgramNode final : public INode
    {
        public:
            using ptr = std::shared_ptr<ProgramNode>;
            static ptr create(const std::list<StatementNode::ptr> &statements);

            ProgramNode(const std::list<StatementNode::ptr> &statements);
            ~ProgramNode() final = default;

            void accept(IVisitor &visitor) final;

            [[nodiscard]] const std::list<StatementNode::ptr> &getStatements() const;

        private:
            std::list<StatementNode::ptr> _statements;
    };
};