#include <fmt/format.h>

#include "State.hpp"

runtime::Object &runtime::State::get(const std::string &identifier)
{
    const auto &object = this->_state.find(identifier);

    if (object == this->_state.end())
        throw LogicalError(fmt::format("{}: undefined identifier", identifier));

    return *object->second;
}

void runtime::State::set(const std::string &identifier, const runtime::Object &object)
{
    const auto &found = this->_state.find(identifier);

    if (found != this->_state.end())
        throw LogicalError(fmt::format("{}: identifier already defined", identifier));

    this->_state.insert({identifier, std::make_unique<Object>(object)});
}

std::optional<const std::reference_wrapper<runtime::Object>> runtime::State::get(const std::string &identifier) const noexcept
{
    const auto &found = this->_state.find(identifier);

    if (found == this->_state.end())
        return {};

    return {{*found->second}};
}
