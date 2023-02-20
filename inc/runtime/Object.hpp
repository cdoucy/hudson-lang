#pragma once

#include "token.hpp"

namespace runtime
{
    class Object
    {
        public:
            using ptr = std::unique_ptr<Object>;

            Object(std::string identifier, Token::Integer i);

            ~Object() = default;

            [[nodiscard]] const std::string &getIdentifier() const;
            [[nodiscard]] Token::Type getType() const;

            [[nodiscard]] Token::Integer getInteger() const;
            void setInteger(Token::Integer i);

        private:
            std::string _identifier;
            Token::Type _type;
            std::any _raw;
    };
};