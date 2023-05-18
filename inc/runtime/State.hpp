#pragma once

#include <unordered_map>
#include <optional>

#include "Object.hpp"

namespace runtime
{
    class State
    {
        public:
            using ptr = std::shared_ptr<State>;

            static ptr create(const ptr& parent = nullptr);
            explicit State();
            explicit State(ptr parent);
            ~State();

            [[nodiscard]] std::optional<Object> get(const std::string &identifier) const noexcept;

            [[nodiscard]] Object& find(const std::string &identifier);
            [[nodiscard]] std::optional<std::reference_wrapper<Object>> tryFind(const std::string &identifier) noexcept;
            void set(const std::string &identifier, const Object &object);

            void clear() noexcept;

            ptr restoreParent();

        private:
            std::unordered_map<std::string, Object::ptr> _state;
            ptr _parent;
    };
};