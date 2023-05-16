#include <iostream>

#include "repl.hpp"

#define PROMPT ("~> ")

#define DEBUG ("__debug ")
#define DEBUG_SIZE (std::strlen(DEBUG))

#define EXIT ("__exit")

#define CLEAR ("__clear")

#define ANSI_CLEAR ("\x1B[2J\x1B[H")

Repl::Repl(std::istream &input, std::ostream &output, std::ostream &error)
:   _input(input),
    _output(output),
    _error(error)
{}

void Repl::run()
{
    std::string line;
    this->_output << PROMPT;

    while (std::getline(this->_input, line)) {

        if (line == EXIT)
            break;

        if (line == CLEAR) {
            this->clear(line);
            continue;
        }

        if (line.starts_with(DEBUG)) {
            this->debug(line);
            continue;
        }

        this->interpret(line);

        this->_output << PROMPT;
    }
}

void Repl::interpret(const std::string &line)
{
    try {
        this->_evaluator.feed(line + ";");
    } catch (const InterpreterError &err) {
        this->_error << err.what() << std::endl;
        return;
    }
}

void Repl::debug(const std::string &line)
{
    std::string identifier(line.substr(DEBUG_SIZE));
    const auto &object(this->_evaluator.getState().get(identifier));

    if (!object)
        this->_error << fmt::format("Error: {} is not defined.", identifier);
    else
        this->_error << object->string();

    this->_error << std::endl;

    this->_output << PROMPT;
}

void Repl::clear(const std::string &_)
{
    (void)_;

    this->_output << ANSI_CLEAR;
    this->_error << ANSI_CLEAR;
    this->_output << PROMPT;
}

