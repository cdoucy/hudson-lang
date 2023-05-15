#pragma once


namespace ast
{
    class IntegerNode;
    class StringNode;
    class BinaryNode;
    class UnaryNode;
    class LogicalNode;
    class IdentifierNode;

    class ExpressionStatementNode;
    class DeclarationNode;
    class AssignmentNode;

    class ProgramNode;

    class IVisitor
    {
        public:
            virtual ~IVisitor() = default;

            virtual void visit(IntegerNode &node) = 0;
            virtual void visit(StringNode &node) = 0;
            virtual void visit(BinaryNode &node) = 0;
            virtual void visit(UnaryNode &node) = 0;
            virtual void visit(LogicalNode &node) = 0;
            virtual void visit(IdentifierNode &node) = 0;

            virtual void visit(ExpressionStatementNode &node) = 0;
            virtual void visit(DeclarationNode &node) = 0;
            virtual void visit(AssignmentNode &node) = 0;

            virtual void visit(ProgramNode &node) = 0;
    };
}