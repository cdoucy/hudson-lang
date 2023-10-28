#pragma once

#include <exception>
#include <optional>

#include "Object.hpp"

namespace runtime
{
    class Return : public std::exception
    {
        public:
            explicit Return(std::optional<Object> object) noexcept;

            [[nodiscard]] bool hasValue() const noexcept;

            [[nodiscard]] const Object &getObject() const;

        private:
            std::optional<Object> _object;
    };
};