#pragma once

#include <optional>

#include "Jump.hpp"
#include "Object.hpp"

namespace runtime
{
    class Return : public Jump
    {
        public:
            explicit Return(std::optional<Object> object) noexcept;

            [[nodiscard]] bool hasValue() const noexcept;

            [[nodiscard]] const Object &getObject() const;

        private:
            std::optional<Object> _object;
    };
};