#include "FunctionNode.hpp"

#include <utility>

ast::FunctionNode::ptr ast::FunctionNode::create(
    const std::string &identifier,
    const std::vector<Param> &params,
    Token::Type returnType,
    const ast::BlockNode::ptr &block
)
{
    return std::make_shared<FunctionNode>(identifier, params, returnType, block);
}

ast::FunctionNode::FunctionNode(
    std::string identifier,
    const std::vector<Param> &params,
    Token::Type returnType,
    ast::BlockNode::ptr block
):  _identifier(std::move(identifier)),
    _params(params),
    _returnType(returnType),
    _block(std::move(block))
{
}

void ast::FunctionNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

const ast::BlockNode::ptr &ast::FunctionNode::getBlock() const
{
    return this->_block;
}

const std::string &ast::FunctionNode::getIdentifier() const
{
    return this->_identifier;
}

const std::vector<ast::FunctionNode::Param> &ast::FunctionNode::getParams() const
{
    return this->_params;
}

Token::Type ast::FunctionNode::getReturnType() const
{
    return this->_returnType;
}
