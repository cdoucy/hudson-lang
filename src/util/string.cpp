#include "string.hpp"

bool string::contains(const std::string &str, char c)
{
    return str.find(c) != std::string::npos;
}