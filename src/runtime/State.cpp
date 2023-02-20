#include "State.hpp"
#include "map.hpp"

runtime::Object &runtime::State::get(const std::string &identifier)
{
    const auto &object = this->_state.find(identifier);

    if (object == this->_state.end())
        throw std::exception();

    return *object->second;
}

void runtime::State::set(const std::string &identifier, const runtime::Object &object)
{
    const auto &found = this->_state.find(identifier);

    if (found == this->_state.end())
        throw std::exception();

    this->_state.insert({identifier, std::make_unique<Object>(object)});
}
