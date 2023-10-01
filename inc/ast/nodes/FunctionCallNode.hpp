#pragma once

#include <unordered_map>
#include <vector>

#include "ExpressionNode.hpp"

namespace ast
{
    class FunctionCallNode final : public ExpressionNode
    {
        public:
        using ptr = std::shared_ptr<FunctionCallNode>;
        static ptr create(
            const std::string &identifier,
            const std::vector<ast::ExpressionNode::ptr> &params
        );
        explicit FunctionCallNode(
            std::string identifier,
            const std::vector<ast::ExpressionNode::ptr> &params
        );
        ~FunctionCallNode() final = default;

        void accept(IVisitor &visitor) final;

        [[nodiscard]] const std::string &getIdentifier() const;
        [[nodiscard]] const std::vector<ast::ExpressionNode::ptr>  &getParams() const;

        private:
        std::string _identifier;
        std::vector<ast::ExpressionNode::ptr> _params;
    };
};