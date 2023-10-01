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
        using ptr = std::shared_ptr<FunctionNode>;
        static ptr create(
            const std::string &identifier,
            const std::map<std::string, Token::Type> &params,
            Token::Type returnType,
            const BlockNode::ptr &block
        );
        explicit FunctionNode(
            std::string identifier,
            const std::map<std::string, Token::Type> &params,
            Token::Type returnType,
            BlockNode::ptr block
        );
        ~FunctionNode() final = default;

        void accept(IVisitor &visitor) final;

        [[nodiscard]] const std::string &getIdentifier() const;
        [[nodiscard]] const BlockNode::ptr &getBlock() const;
        [[nodiscard]] const std::map<std::string, Token::Type> &getParams() const;
        [[nodiscard]] Token::Type getReturnType() const;

        private:
            std::string _identifier;
            std::map<std::string, Token::Type> _params;
            Token::Type _returnType;
            BlockNode::ptr _block;
    };
};