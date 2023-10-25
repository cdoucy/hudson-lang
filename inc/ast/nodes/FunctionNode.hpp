#pragma once

#include <map>

#include "token.hpp"
#include "StatementNode.hpp"
#include "ExpressionNode.hpp"
#include "BlockNode.hpp"

namespace ast
{
    class FunctionNode final : public StatementNode
    {
        public:

            struct Param {
                std::string name;
                Token::Type type;
            };

        using ptr = std::shared_ptr<FunctionNode>;
        static ptr create(
            const std::string &identifier,
            const std::vector<Param> &params,
            Token::Type returnType,
            const BlockNode::ptr &block
        );
        explicit FunctionNode(
            std::string identifier,
            const std::vector<Param> &params,
            Token::Type returnType,
            BlockNode::ptr block
        );
        ~FunctionNode() final = default;

        void accept(IVisitor &visitor) final;

        [[nodiscard]] const std::string &getIdentifier() const;
        [[nodiscard]] const BlockNode::ptr &getBlock() const;
        [[nodiscard]] const std::vector<Param> &getParams() const;
        [[nodiscard]] Token::Type getReturnType() const;

        private:
            std::string _identifier;
            std::vector<Param> _params;
            Token::Type _returnType;
            BlockNode::ptr _block;
    };
};