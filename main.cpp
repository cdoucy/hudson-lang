#include <iostream>
#include <fmt/printf.h>

#include "Evaluator.hpp"

int main(int ac, char **av)
{
    std::vector<std::string> args(av, av + ac);

    if (args.size() < 2) {
        fmt::print(stderr, "USAGE: {} EXPRESSION", args.front());
        return 1;
    }

    Evaluator evaluator;
    std::string expression = args[1];

    evaluator.feed(expression);

    std::cout << evaluator.getResult() << std::endl;

    return 0;
}
