#include <iostream>

#include "repl.hpp"

#define PROMPT ("~> ")
#define DEBUG ("__debug ")
#define DEBUG_SIZE (std::strlen(DEBUG))

void Repl::run()
{
    std::string line;
    std::cout << PROMPT;

    while (std::getline(std::cin, line)) {

        if (line.starts_with(DEBUG)) {
            std::string identifier(line.substr(DEBUG_SIZE));
            const auto &object(this->_evaluator.getState().get(identifier));

            if (!object)
                fmt::print(stderr, "Error: {} is not defined.\n", identifier);
            else {
                if (object->getType() == Token::INTEGER) {
                    fmt::print(
                        stderr,
                        "(identifier={}, type={}, value={})\n",
                        object->getIdentifier(), "int", object->getInteger()
                    );
                }
            }

            std::cout << PROMPT;
            continue;
        }

        try {
            this->_evaluator.feed(line + ";");
        } catch (const InterpreterError &err) {
            std::cerr << err.what() << std::endl << PROMPT;
            continue;
        }

        const auto &object = this->_evaluator.getVisitor().value();

        if (object.getType() == Token::INTEGER)
            std::cout << object.getInteger() << std::endl;

        std::cout << PROMPT;
    }
}
