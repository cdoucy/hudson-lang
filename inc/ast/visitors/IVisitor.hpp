#pragma once


namespace ast
{
    class IntegerNode;
    class BinaryNode;
    class ExpressionNode;
    class UnaryNode;

    class IVisitor
    {
        public:
            virtual ~IVisitor() = default;

            virtual void visit(IntegerNode &node) = 0;
            virtual void visit(BinaryNode &node) = 0;
            virtual void visit(UnaryNode &node) = 0;
    };
}