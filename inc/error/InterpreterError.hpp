#pragma once

#include <exception>
#include <string>

class InterpreterError : public std::exception
{
    public:
        InterpreterError(const std::string &errorType, const std::string &errorMessage) noexcept;
        InterpreterError(const InterpreterError &other) noexcept = default;

        [[nodiscard]] const char *what() const noexcept override;
    protected:
        std::string _what;
};

class InternalError : public InterpreterError
{
    public:
        explicit InternalError(const std::string &errorMessage);
};

class ProgramError : public InterpreterError
{
    public:
        ProgramError(
            const std::string &errorType,
            const std::string &errorMessage,
            const std::string &lexeme,
            std::size_t line,
            std::size_t column
        );

        [[nodiscard]] const std::string &getLexeme() const;
        [[nodiscard]] std::size_t getLine() const;
        [[nodiscard]] std::size_t getColumn() const;

    protected:
        std::string _lexeme;
        std::size_t _line;
        std::size_t _column;
};

class LexicalError : public ProgramError
{
    public:
        LexicalError(
            const std::string &errorMessage,
            const std::string &lexeme,
            std::size_t line,
            std::size_t column
        );

};

class SyntaxError : public ProgramError
{
    public:
        SyntaxError(
            const std::string &errorMessage,
            const std::string &lexeme,
            std::size_t line,
            std::size_t column
        );
};

class LogicalError : public InterpreterError
{
    public:
        explicit LogicalError(const std::string &errorMessage);
};