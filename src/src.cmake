set(SOURCES

    ${PROJECT_ROOT}/src/interpreter/interpreter.cpp

    ${PROJECT_ROOT}/src/lexer/lexer.cpp
    ${PROJECT_ROOT}/src/lexer/lexLiterals.cpp
    ${PROJECT_ROOT}/src/lexer/lexOperator.cpp
    ${PROJECT_ROOT}/src/lexer/lexProgrammingWord.cpp

    ${PROJECT_ROOT}/src/parser/Parser.cpp

    ${PROJECT_ROOT}/src/token/token.cpp
    ${PROJECT_ROOT}/src/token/iterator.cpp
    ${PROJECT_ROOT}/src/token/type.cpp

    ${PROJECT_ROOT}/src/evaluator/Evaluator.cpp

    ${PROJECT_ROOT}/src/util/map.cpp

    ${PROJECT_ROOT}/src/error/InterpreterError.cpp

    ${PROJECT_ROOT}/src/ast/nodes/IntegerNode.cpp
    ${PROJECT_ROOT}/src/ast/nodes/BinaryNode.cpp
    ${PROJECT_ROOT}/src/ast/nodes/UnaryNode.cpp
    ${PROJECT_ROOT}/src/ast/nodes/LogicalNode.cpp
    ${PROJECT_ROOT}/src/ast/nodes/ExpressionNode.cpp
    ${PROJECT_ROOT}/src/ast/nodes/ProgramNode.cpp
    ${PROJECT_ROOT}/src/ast/nodes/ExpressionStatementNode.cpp
    ${PROJECT_ROOT}/src/ast/nodes/DeclarationNode.cpp
    ${PROJECT_ROOT}/src/ast/nodes/AssignmentNode.cpp
    ${PROJECT_ROOT}/src/ast/nodes/IdentifierNode.cpp
    ${PROJECT_ROOT}/src/ast/nodes/StringNode.cpp
    ${PROJECT_ROOT}/src/ast/nodes/PrintNode.cpp

    ${PROJECT_ROOT}/src/ast/visitors/EvalVisitor.cpp

    ${PROJECT_ROOT}/src/runtime/Object.cpp
    ${PROJECT_ROOT}/src/runtime/object_operators.cpp
    ${PROJECT_ROOT}/src/runtime/State.cpp

    ${PROJECT_ROOT}/src/repl/repl.cpp

    ${PROJECT_ROOT}/src/source_file/SourceFile.cpp
)