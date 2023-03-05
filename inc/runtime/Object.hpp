#pragma once

#include <functional>

#include "token.hpp"

namespace runtime
{
    class Object
    {
        public:
            using ptr = std::unique_ptr<Object>;
            using Evaluator = std::function<const Object &()>;

            Object();
            Object(Token::Integer i, std::string identifier = "");
            ~Object() = default;

            [[nodiscard]] const std::string &getIdentifier() const;
            [[nodiscard]] Token::Type getType() const;

            [[nodiscard]] Token::Integer getInteger() const;

            void set(Token::Integer i, bool overwriteType = false);

            // Binary operations
            Object operator%(const Object &right) const;
            Object operator/(const Object &right) const;
            Object operator*(const Object &right) const;
            Object operator+(const Object &right) const;
            Object operator-(const Object &right) const;
            Object operator==(const Object &right) const;
            Object operator!=(const Object &right) const;
            Object operator>(const Object &right) const;
            Object operator>=(const Object &right) const;
            Object operator<(const Object &right) const;
            Object operator<=(const Object &right) const;
            Object operator|(const Object &right) const;
            Object operator^(const Object &right) const;
            Object operator&(const Object &right) const;
            Object operator<<(const Object &right) const;
            Object operator>>(const Object &right) const;

            // Unary operations
            Object operator+() const;
            Object operator-() const;
            Object operator!() const;
            Object operator~() const;

            explicit operator bool() const;
            Object &operator=(const Object &other) = default;

            [[nodiscard]] std::string string() const noexcept;
            [[nodiscard]] std::string getValueAsString() const noexcept;

        private:
            std::string _identifier;
            Token::Type _type;
            std::any _raw;

            [[nodiscard]] bool isTypeEqual(Token::Type type) const noexcept;
            [[nodiscard]] bool areTypesEqual(const Object &other, Token::Type type) const noexcept;
            void assertTypeEqual(Token::Type type) const;
            void assertTypesEqual(const Object &other, Token::Type type) const;
    };
};