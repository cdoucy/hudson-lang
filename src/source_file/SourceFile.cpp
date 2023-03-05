#include <fmt/format.h>
#include <sstream>

#include "SourceFile.hpp"

SourceFile::SourceFile(const std::string &filePath)
:   _filePath(filePath),
    _sourceContent(readFile(filePath))
{}


void SourceFile::interpret(Evaluator &evaluator)
{
    try {
        evaluator.feed(this->_sourceContent);
    } catch (const InterpreterError &err) {
        throw InterpreterError(this->_filePath, err);
    }
}

std::string SourceFile::readFile(const std::string &filePath)
{
    std::ifstream source;
    std::ostringstream oss;

    source.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        source.open(filePath);
        oss << source.rdbuf();
    } catch (const std::system_error& e) {
        throw InterpreterError(
            "FileSystem",
            fmt::format("failed to open {} : {}", filePath, e.what())
        );
    }


    return oss.str();
}

