#include "CallNode.hpp"

#include <utility>

ast::CallNode::ptr ast::CallNode::create(
    const ast::ExpressionNode::ptr &callee,
    const std::vector<ast::ExpressionNode::ptr> &params
)
{
    return std::make_shared<CallNode>(callee, params);
}

ast::CallNode::CallNode(
    ast::ExpressionNode::ptr callee,
    const std::vector<ast::ExpressionNode::ptr> &params
):  _callee(std::move(callee)),
    _params(params)
{
}

void ast::CallNode::accept(ast::IVisitor &visitor)
{
    visitor.visit(*this);
}

const ast::ExpressionNode::ptr &ast::CallNode::getCallee() const
{
    return this->_callee;
}

const std::vector<ast::ExpressionNode::ptr> &ast::CallNode::getParams() const
{
    return this->_params;
}
