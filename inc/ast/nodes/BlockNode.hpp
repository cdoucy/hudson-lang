#pragma once

#include <list>

#include "StatementNode.hpp"

namespace ast
{
    class BlockNode final : public StatementNode
    {
        public:
            using ptr = std::shared_ptr<BlockNode>;
            static ptr create(const std::list<StatementNode::ptr> &statements);

            explicit BlockNode(std::list<StatementNode::ptr> statements);
            ~BlockNode() final = default;

            void accept(IVisitor &visitor) final;

            [[nodiscard]] const std::list<StatementNode::ptr> &getStatements() const;

        private:
            std::list<StatementNode::ptr> _statements;
    };

};