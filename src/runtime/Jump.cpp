#include <fmt/format.h>

#include "Jump.hpp"

runtime::Jump::Jump(const std::string &jumpStatement, const std::string &appropriatePlace) noexcept
:   _what(fmt::format("use of {} outside of {}", jumpStatement, appropriatePlace))
{}

const char *runtime::Jump::what() const noexcept
{
    return this->_what.c_str();
}
