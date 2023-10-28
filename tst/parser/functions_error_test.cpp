#include <gtest/gtest.h>
#include "Parser.hpp"

struct FunctionsErrorTest
{
    std::string description;
    std::string program;
};

void testFunctionsError(const std::vector<FunctionsErrorTest> &testCases)
{
    for (const auto &tc: testCases) {
        std::cout << tc.description << std::endl;

        Parser parser;

        EXPECT_THROW(parser.feed(tc.program), SyntaxError);
    }
}

TEST(ParserTest, FunctionsDeclarationError)
{
    const std::vector<FunctionsErrorTest> testCases{
        FunctionsErrorTest{
            .description = "1. Function declaration without identifier",
            .program = "fnc () {}"
        },
        FunctionsErrorTest{
            .description = "1. Function declaration without identifier",
            .program = "fnc () {}"
        },
        FunctionsErrorTest{
            .description = "2. Function declaration without parenthesis",
            .program = "fnc f {}"
        },
        FunctionsErrorTest{
            .description = "3. Function declaration with already used parameter name",
            .program = "fnc f (int x, int x){}"
        },
        FunctionsErrorTest{
            .description = "4. Function declaration without close parenthesis",
            .program = "fnc f (int x, int y {}"
        },
        FunctionsErrorTest{
            .description = "5. Function declaration without body",
            .program = "fnc f (int x, int y)"
        },
        FunctionsErrorTest{
            .description = "6. Function declaration with return type and without body",
            .program = "fnc f (int x, int y) int"
        }
    };

    testFunctionsError(testCases);
}

TEST(ParserTest, CallError)
{
    const std::vector<FunctionsErrorTest> testCases{
        FunctionsErrorTest{
            .description = "1. Missing param or closed parenthesis",
            .program = "f(;"
        },
        FunctionsErrorTest{
            .description = "2. Missing closed parenthesis",
            .program = "f(1, 2;"
        },
        FunctionsErrorTest{
            .description = "3. Missing expression after comma",
            .program = "f(1, );"
        }
    };

    testFunctionsError(testCases);
}