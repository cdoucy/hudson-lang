#pragma once

#include <unordered_map>
#include <vector>

#include "ExpressionNode.hpp"

namespace ast
{
    class CallNode final : public ExpressionNode
    {
        public:
        using ptr = std::shared_ptr<CallNode>;
        static ptr create(
            const ExpressionNode::ptr &callee,
            const std::vector<ast::ExpressionNode::ptr> &params
        );
        explicit CallNode(
            ExpressionNode::ptr callee,
            const std::vector<ast::ExpressionNode::ptr> &params
        );
        ~CallNode() final = default;

        void accept(IVisitor &visitor) final;

        [[nodiscard]] const ExpressionNode::ptr &getCallee() const;
        [[nodiscard]] const std::vector<ast::ExpressionNode::ptr>  &getParams() const;

        private:
        ExpressionNode::ptr _callee;
        std::vector<ast::ExpressionNode::ptr> _params;
    };
};