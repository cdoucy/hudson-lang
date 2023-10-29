#include <utility>
#include "Return.hpp"


runtime::Return::Return(std::optional<Object> object) noexcept
:   Jump("return", "function"),
    _object(std::move(object))
{}

bool runtime::Return::hasValue() const noexcept
{
    return this->_object.has_value();
}

const runtime::Object &runtime::Return::getObject() const
{
    return this->_object.value();
}
