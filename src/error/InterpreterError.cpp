#include <fmt/format.h>

#include "InterpreterError.hpp"

#define INTERNAL_ERROR  "Internal"
#define LEXICAL_ERROR   "Lexical"
#define SYNTAX_ERROR    "Syntax"
#define LOGICAL_ERROR   "Logical"

InterpreterError::InterpreterError(const std::string &errorType, const std::string &errorMessage) noexcept
:   _what(fmt::format("{} error: {}.", errorType, errorMessage))
{}

const char *InterpreterError::what() const noexcept
{
    return this->_what.c_str();
}

InterpreterError::InterpreterError(const std::string &errorMessage) noexcept
:   _what(errorMessage)
{}

InterpreterError::InterpreterError(std::string &errorMessage, const InterpreterError &other) noexcept
:   _what(fmt::format("{}: {}", errorMessage, other._what))
{

}

InternalError::InternalError(const std::string &errorMessage) noexcept
: InterpreterError(INTERNAL_ERROR, errorMessage)
{}

ProgramError::ProgramError(
    const std::string &errorType,
    const std::string &errorMessage,
    const std::string &lexeme,
    std::size_t line,
    std::size_t column
)
:   InterpreterError(
        errorType,
        fmt::format("line {}, col {}: \"{}\": {}", line, column, lexeme, errorMessage)
    ),
    _lexeme(lexeme),
    _line(line),
    _column(column)
{}

const std::string &ProgramError::getLexeme() const
{
    return this->_lexeme;
}

std::size_t ProgramError::getLine() const
{
    return this->_line;
}

std::size_t ProgramError::getColumn() const
{
    return this->_column;
}

LexicalError::LexicalError(
    const std::string &errorMessage,
    const std::string &lexeme,
    std::size_t line,
    std::size_t column
)
: ProgramError(LEXICAL_ERROR, errorMessage, lexeme, line, column)
{}

SyntaxError::SyntaxError(
    const std::string &errorMessage,
    const std::string &lexeme,
    std::size_t line,
    std::size_t column
)
: ProgramError(SYNTAX_ERROR, errorMessage, lexeme, line, column)
{}

LogicalError::LogicalError(const std::string &errorMessage)
: InterpreterError(LOGICAL_ERROR, errorMessage)
{}
