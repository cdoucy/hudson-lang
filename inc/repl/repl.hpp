#pragma once

#include <istream>

#include "Evaluator.hpp"


class Repl
{
    public:
        Repl() = default;
        ~Repl() = default;


        void run();

    private:
        Evaluator _evaluator;
};