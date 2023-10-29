#include <fmt/printf.h>

#include "SourceFile.hpp"
#include "repl.hpp"

void runInteractiveMode()
{
    Repl repl;
    repl.run();
}

void runFileMode(const std::string &filePath)
{
    SourceFile source(filePath);
    Evaluator evaluator;

    source.interpret(evaluator);
}

int main(int ac, char **av)
{
    for (int i = 0; i < 10; i++) continue;

    try {
        if (ac < 2)
            runInteractiveMode();
        else
            runFileMode(std::string(av[1]));

    } catch (const std::exception &err) {
        fmt::print(stderr, "Error : {}\n", err.what());
        return 1;
    }

    return 0;
}
