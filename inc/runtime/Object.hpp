#pragma once

#include <functional>
#include <optional>

#include "token.hpp"
#include "FunctionNode.hpp"

namespace runtime
{
    class Object
    {
        public:
            using ptr = std::unique_ptr<Object>;
            using Evaluator = std::function<const Object &()>;

            Object();
            Object(Token::Type type, std::string identifier = "");
            Object(Token::Integer i, std::string identifier = "");
            Object(Token::String s, std::string identifier = "");
            explicit Object(const ast::FunctionNode &function);
            ~Object() = default;

            [[nodiscard]] const std::string &getIdentifier() const;
            [[nodiscard]] Token::Type getType() const;

            [[nodiscard]] Token::Integer getInteger() const;

            template<typename T>
            [[nodiscard]] T get() const
            {
                try {
                    return std::any_cast<T>(this->_raw);
                } catch (const std::bad_any_cast &err) {
                    throw LogicalError(fmt::format("mismatched types : {}", err.what()));
                }
            }

            template<typename T>
            void set(T value)
            {
                (void)this->get<T>();

                this->_raw = value;
            }

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

            Object &assign(const Object &other);

            [[nodiscard]] std::string string() const noexcept;
            [[nodiscard]] std::string getValueAsString() const noexcept;

        private:
            std::string _identifier;
            Token::Type _type;
            std::any _raw;

            [[nodiscard]] bool isTypeEqual(Token::Type type) const noexcept;
            [[nodiscard]] bool areTypesEqual(const Object &other, Token::Type type) const noexcept;
            void assertTypeEqual(Token::Type type) const;
            void assertTypesEqual(const Object &other, Token::Type type, const std::string &oprt = "") const;
    };
};