#pragma once

#include <istream>
#include <iostream>

#include "Evaluator.hpp"


class Repl
{
    public:
        Repl(
            std::istream &input = std::cin,
            std::ostream &output = std::cout,
            std::ostream &error = std::cerr
        );
        ~Repl() = default;

        void run();

        private:
            std::istream &_input;
            std::ostream &_output;
            std::ostream &_error;
            Evaluator _evaluator;

            void interpret(const std::string &line);

            void debug(const std::string &line);
            void clear(const std::string &line);
};