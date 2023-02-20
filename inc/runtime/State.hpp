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
            void set(const std::string &identifier, const Object &object);

        private:
            std::unordered_map<std::string, Object::ptr> _state;
    };
};