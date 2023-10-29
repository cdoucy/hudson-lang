#pragma once

#include <exception>
#include <string>

namespace runtime
{
    class Jump : public std::exception
    {
        public:
            Jump(const std::string &jumpStatement, const std::string &appropriatePlace) noexcept;

            [[nodiscard]] const char *what() const noexcept override;

        private:
            std::string _what;
    };
};