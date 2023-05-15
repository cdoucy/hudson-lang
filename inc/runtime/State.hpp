#pragma once

#include <unordered_map>
#include <optional>

#include "Object.hpp"

namespace runtime
{
    class State
    {
        public:
            State() = default;
            ~State() = default;

            [[nodiscard]] Object &get(const std::string &identifier);
            [[nodiscard]] std::optional<Object> get(const std::string &identifier) const noexcept;
            void set(const std::string &identifier, const Object &object);

            void clear() noexcept;

        private:
            std::unordered_map<std::string, Object::ptr> _state;
    };
};