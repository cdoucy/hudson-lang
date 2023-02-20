#pragma once


namespace ast
{
    class IntegerNode;
    class BinaryNode;
    class UnaryNode;

    class ExpressionStatementNode;
    class DeclarationNode;
    class AssignmentNode;

    class ProgramNode;

    class IVisitor
    {
        public:
            virtual ~IVisitor() = default;

            virtual void visit(IntegerNode &node) = 0;
            virtual void visit(BinaryNode &node) = 0;
            virtual void visit(UnaryNode &node) = 0;

            virtual void visit(ExpressionStatementNode &node) = 0;
            virtual void visit(DeclarationNode &node) = 0;
            virtual void visit(AssignmentNode &node) = 0;

            virtual void visit(ProgramNode &node) = 0;
    };
}