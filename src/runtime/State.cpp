#include <fmt/format.h>

#include <utility>

#include "State.hpp"

std::optional<std::reference_wrapper<runtime::Object>> runtime::State::tryFind(const std::string &identifier) noexcept
{
    const auto &found = this->_state.find(identifier);

    if (found == this->_state.end()) {
        if (this->_parent)
            return this->_parent->tryFind(identifier);

        return {};
    }

    return std::make_optional(std::ref(*found->second));
}

runtime::Object &runtime::State::find(const std::string &identifier)
{
    auto found = this->tryFind(identifier);

    if (!found)
        throw LogicalError(fmt::format("{}: undefined identifier", identifier));

    return found.value().get();
}

void runtime::State::set(const std::string &identifier, const runtime::Object &object)
{
    const auto &found = this->_state.find(identifier);

    if (found != this->_state.end())
        throw LogicalError(fmt::format("{}: identifier already defined", identifier));

    this->_state.insert({identifier, std::make_unique<Object>(object)});
}

void runtime::State::clear() noexcept
{
    this->_state.clear();
}

runtime::State::~State()
{
    this->clear();
}

std::optional<runtime::Object> runtime::State::get(const std::string &identifier) const noexcept
{
    const auto &found = this->_state.find(identifier);

    if (found == this->_state.end())
        return {};

    return {*found->second};
}

runtime::State::ptr runtime::State::create(const runtime::State::ptr& parent)
{
    if (parent) {
        return std::make_shared<State>(parent);
    }

    return std::make_shared<State>();
}

runtime::State::State(runtime::State::ptr parent)
:   _parent(std::move(parent))
{
}

runtime::State::State()
:   _parent(nullptr)
{
}

runtime::State::ptr runtime::State::restoreParent()
{
    if (!this->_parent)
        throw InternalError("State::restoreParent invoked on a null parent");

    auto parent = std::move(this->_parent);

    this->_parent = nullptr;

    return parent;
}
