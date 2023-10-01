#include "FunctionCallNode.hpp"

#include <utility>

ast::FunctionCallNode::ptr ast::FunctionCallNode::create(
    const std::string &identifier,
    const std::vector<ast::ExpressionNode::ptr> &params
) {
    return std::make_shared<FunctionCallNode>(identifier, params);
}

ast::FunctionCallNode::FunctionCallNode(
    std::string identifier,
    const std::vector<ast::ExpressionNode::ptr> &params
):  _identifier(std::move(identifier)),
    _params(params)
{
}

void ast::FunctionCallNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

const std::string &ast::FunctionCallNode::getIdentifier() const
{
    return this->_identifier;
}

const std::vector<ast::ExpressionNode::ptr> &ast::FunctionCallNode::getParams() const
{
    return this->_params;
}
