#include <gtest/gtest.h>
#include "Parser.hpp"

struct ParserErrorTest
{
    std::string description;
    std::string program;
};

void testParserError(const std::vector<ParserErrorTest> &testCases)
{
    for (const auto &tc: testCases) {
        std::cout << tc.description << std::endl;

        Parser parser;
        EXPECT_THROW(parser.feed(tc.program), SyntaxError);
    }
}

TEST(ParserTest, FunctionsDeclarationError)
{
    const std::vector<ParserErrorTest> testCases{
        ParserErrorTest{
            .description = "1. Function declaration without identifier",
            .program = "fnc () {}"
        },
        ParserErrorTest{
            .description = "1. Function declaration without identifier",
            .program = "fnc () {}"
        },
        ParserErrorTest{
            .description = "2. Function declaration without parenthesis",
            .program = "fnc f {}"
        },
        ParserErrorTest{
            .description = "3. Function declaration with already used parameter name",
            .program = "fnc f (int x, int x){}"
        },
        ParserErrorTest{
            .description = "4. Function declaration without close parenthesis",
            .program = "fnc f (int x, int y {}"
        },
        ParserErrorTest{
            .description = "5. Function declaration without body",
            .program = "fnc f (int x, int y)"
        },
        ParserErrorTest{
            .description = "6. Function declaration with return type and without body",
            .program = "fnc f (int x, int y) int"
        }
    };

    testParserError(testCases);
}

TEST(ParserTest, CallError)
{
    const std::vector<ParserErrorTest> testCases{
        ParserErrorTest{
            .description = "1. Missing param or closed parenthesis",
            .program = "f(;"
        },
        ParserErrorTest{
            .description = "2. Missing closed parenthesis",
            .program = "f(1, 2;"
        },
        ParserErrorTest{
            .description = "3. Missing expression after comma",
            .program = "f(1, );"
        }
    };

    testParserError(testCases);
}

TEST(ParserTest, BreakContinueError)
{
    const std::vector<ParserErrorTest> testCases{
        ParserErrorTest{
            .description = "1. Missing semi after break",
            .program = "break"
        },
        ParserErrorTest{
            .description = "2. Missing semi after continue",
            .program = "continue"
        },
    };

    testParserError(testCases);
}