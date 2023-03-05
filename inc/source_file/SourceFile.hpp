#pragma once

#include <fstream>

#include "Evaluator.hpp"

class SourceFile
{
    public:

        SourceFile(const std::string &filePath);
        ~SourceFile() = default;

        void interpret(Evaluator &evaluator);

    private:
        std::string _filePath;
        std::string _sourceContent;

        static std::string readFile(const std::string &filePath);
};