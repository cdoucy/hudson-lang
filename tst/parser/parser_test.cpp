#include <iostream>
#include <gtest/gtest.h>

#include "Parser.hpp"

struct SyntaxErrorTest
{
    std::string description;
    std::string expression;
    std::string errorMessage;
    std::string lexeme;
    std::size_t line;
    std::size_t column;
};

static void testParserError(const std::vector<SyntaxErrorTest> &expected)
{
    for (const auto &expect : expected) {
        std::cout << expect.description << std::endl;

        Parser parser;
        bool hasThrown = false;

        try {
            parser.feed(expect.expression + ";");
        } catch (const SyntaxError &err) {
            hasThrown = true;

            EXPECT_STREQ(err.what(), expect.errorMessage.c_str());
            EXPECT_STREQ(err.getLexeme().c_str(), expect.lexeme.c_str());
            EXPECT_EQ(err.getLine(), expect.line);
            EXPECT_EQ(err.getColumn(), expect.column);

            parser.clear();
        }

        EXPECT_TRUE(hasThrown);
    }
}

TEST(ParserTest, InvalidSyntaxExpressions)
{
    const std::vector<SyntaxErrorTest> expected{
        SyntaxErrorTest{
            .description = "1. Parenthesis without expression",
            .expression = "( )",
            .errorMessage = "Syntax error: line 0, col 0: \"(\": expecting expression.",
            .lexeme = "(",
            .line = 0,
            .column = 0
        },
        SyntaxErrorTest{
            .description = "2. No closing parenthesis",
            .expression = "( 1 + 1",
            .errorMessage = "Syntax error: line 0, col 0: \"(\": expecting \")\".",
            .lexeme = "(",
            .line = 0,
            .column = 0
        },
        SyntaxErrorTest{
            .description = "3. No closing parenthesis and expression",
            .expression = "(",
            .errorMessage = "Syntax error: line 0, col 0: \"(\": expecting expression.",
            .lexeme = "(",
            .line = 0,
            .column = 0
        },
        SyntaxErrorTest{
            .description = "4. No opening parenthesis",
            .expression = ")",
            .errorMessage = "Syntax error: line 0, col 0: \")\": expecting \"(\".",
            .lexeme = ")",
            .line = 0,
            .column = 0
        },
        SyntaxErrorTest{
            .description = "5. No opening parenthesis with expression",
            .expression = "1 + 1)",
            .errorMessage = "Syntax error: line 0, col 5: \")\": unmatched parenthesis.",
            .lexeme = ")",
            .line = 0,
            .column = 5
        },
        SyntaxErrorTest{
            .description = "6. No expression after plus",
            .expression = "1 +",
            .errorMessage = "Syntax error: line 0, col 2: \"+\": expecting expression.",
            .lexeme = "+",
            .line = 0,
            .column = 2
        },
        SyntaxErrorTest{
            .description = "7. No expression after mult",
            .expression = "1 *",
            .errorMessage = "Syntax error: line 0, col 2: \"*\": expecting expression.",
            .lexeme = "*",
            .line = 0,
            .column = 2
        },
        SyntaxErrorTest{
            .description = "8. No expression before div",
            .expression = "/ 1",
            .errorMessage = "Syntax error: line 0, col 0: \"/\": expecting expression.",
            .lexeme = "/",
            .line = 0,
            .column = 0
        },
        SyntaxErrorTest{
            .description = "9. Operator without expression",
            .expression = "%",
            .errorMessage = "Syntax error: line 0, col 0: \"%\": expecting expression.",
            .lexeme = "%",
            .line = 0,
            .column = 0
        },
        SyntaxErrorTest{
            .description = "10. Mult atfer plus",
            .expression = "1 + * 2",
            .errorMessage = "Syntax error: line 0, col 4: \"*\": expecting expression.",
            .lexeme = "*",
            .line = 0,
            .column = 4
        },
        SyntaxErrorTest{
            .description = "11. ! Without expression",
            .expression = "!",
            .errorMessage = "Syntax error: line 0, col 0: \"!\": expecting expression.",
            .lexeme = "!",
            .line = 0,
            .column = 0
        },
        SyntaxErrorTest{
            .description = "12. Unary + without expression",
            .expression = "1 + 1 - +",
            .errorMessage = "Syntax error: line 0, col 8: \"+\": expecting expression.",
            .lexeme = "+",
            .line = 0,
            .column = 8
        }
    };

    testParserError(expected);
}

TEST(ParserTest, InvalidEqualityExpressions)
{
    const std::vector<SyntaxErrorTest> expected{
        SyntaxErrorTest{
            .description = "1. Equal without expression",
            .expression = "==",
            .errorMessage = "Syntax error: line 0, col 0: \"==\": expecting expression.",
            .lexeme = "==",
            .line = 0,
            .column = 0
        },
        SyntaxErrorTest{
            .description = "2. Equal without before expression",
            .expression = "!= 1",
            .errorMessage = "Syntax error: line 0, col 0: \"!=\": expecting expression.",
            .lexeme = "!=",
            .line = 0,
            .column = 0
        },
        SyntaxErrorTest{
            .description = "3. Equal without after expression",
            .expression = "1 == ",
            .errorMessage = "Syntax error: line 0, col 2: \"==\": expecting expression.",
            .lexeme = "==",
            .line = 0,
            .column = 2
        },
        SyntaxErrorTest{
            .description = "4. Equal with invalid expression after",
            .expression = "1 == *",
            .errorMessage = "Syntax error: line 0, col 5: \"*\": expecting expression.",
            .lexeme = "*",
            .line = 0,
            .column = 5
        },
        SyntaxErrorTest{
            .description = "5. Equal with invalid expression before",
            .expression = "1 + != 2",
            .errorMessage = "Syntax error: line 0, col 2: \"+\": expecting expression.",
            .lexeme = "+",
            .line = 0,
            .column = 2
        }
    };

    testParserError(expected);
}