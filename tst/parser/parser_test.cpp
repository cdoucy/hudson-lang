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
    bool doNotAddSemi = false;
};

static void testParserError(const std::vector<SyntaxErrorTest> &expected)
{
    for (const auto &expect: expected) {
        std::cout << expect.description << std::endl;

        Parser parser;

        try {
            auto expression = expect.expression;

            if (!expect.doNotAddSemi)
                expression += ";";

            parser.feed(expression);
        } catch (const SyntaxError &err) {

            EXPECT_STREQ(err.what(), expect.errorMessage.c_str());
            EXPECT_STREQ(err.getLexeme().c_str(), expect.lexeme.c_str());
            EXPECT_EQ(err.getLine(), expect.line);
            EXPECT_EQ(err.getColumn(), expect.column);

            parser.clear();
            SUCCEED();
            continue;
        }

        FAIL();
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

TEST(ParserTest, DeclarationsAndAssignments)
{
    const std::vector<SyntaxErrorTest> expected{
        SyntaxErrorTest{
            .description = "1. Invalid identifier #1",
            .expression = "int 1n = 1;",
            .errorMessage = "Syntax error: line 0, col 0: \"int\": expecting identifier.",
            .lexeme = "int",
            .line = 0,
            .column = 0
        },
        SyntaxErrorTest{
            .description = "2. Invalid identifier #2",
            .expression = "1n = 1;",
            .errorMessage = "Syntax error: line 0, col 1: \"n\": unexpected identifier.",
            .lexeme = "n",
            .line = 0,
            .column = 1
        },
        SyntaxErrorTest{
            .description = "3. Invalid identifier #3",
            .expression = "1n1 + 1;",
            .errorMessage = "Syntax error: line 0, col 1: \"n1\": unexpected identifier.",
            .lexeme = "n1",
            .line = 0,
            .column = 1
        },
        SyntaxErrorTest{
            .description = "4. Invalid identifier #4",
            .expression = "1+1n1;",
            .errorMessage = "Syntax error: line 0, col 3: \"n1\": unexpected identifier.",
            .lexeme = "n1",
            .line = 0,
            .column = 3
        },
        SyntaxErrorTest{
            .description = "5. Expecting expression",
            .expression = "int n; int a = int n;",
            .errorMessage = "Syntax error: line 0, col 13: \"=\": expecting expression.",
            .lexeme = "=",
            .line = 0,
            .column = 13
        }
    };

    testParserError(expected);
}

TEST(ParserTest, PrintError)
{
    const std::vector<SyntaxErrorTest> expected{
        SyntaxErrorTest{
            .description = "1. Print without parenthesis",
            .expression = "print 1;",
            .errorMessage = "Syntax error: line 0, col 0: \"print\": expecting \"()\".",
            .lexeme = "print",
            .line = 0,
            .column = 0
        },
        SyntaxErrorTest{
            .description = "1. Print without parenthesis and arguments",
            .expression = "print;",
            .errorMessage = "Syntax error: line 0, col 0: \"print\": expecting \"()\".",
            .lexeme = "print",
            .line = 0,
            .column = 0
        },
        SyntaxErrorTest{
            .description = "3. Print unmatched left parenthesis",
            .expression = "print(1",
            .errorMessage = "Syntax error: line 0, col 5: \"(\": unmatched \")\".",
            .lexeme = "(",
            .line = 0,
            .column = 5
        },
        SyntaxErrorTest{
            .description = "4. Print unmatched right parenthesis",
            .expression = "print);",
            .errorMessage = "Syntax error: line 0, col 0: \"print\": expecting \"()\".",
            .lexeme = "print",
            .line = 0,
            .column = 0
        },
        SyntaxErrorTest{
            .description = "5. Print without semicolon",
            .expression = "print(1)",
            .errorMessage = "Syntax error: line 0, col 7: \")\": expecting \";\".",
            .lexeme = ")",
            .line = 0,
            .column = 7,
            .doNotAddSemi = true
        }
    };

    testParserError(expected);
}

TEST(ParserTest, WhileError)
{
    const std::vector<SyntaxErrorTest> testCases{
        SyntaxErrorTest{
            .description = "1. While without expression #1",
            .expression = "int n = 0;      "
                       "                "
                       "while { "
                       "    n = n + 1;  "
                       "}               ",
            .errorMessage = "Syntax error: line 0, col 32: \"while\": expecting \"(\".",
            .lexeme = "while",
            .line = 0,
            .column = 32
        },
        SyntaxErrorTest{
            .description = "2. While without expression #2",
            .expression = "int n = 0;          "
                       "                    "
                       "while n = n + 1;    ",
            .errorMessage = "Syntax error: line 0, col 40: \"while\": expecting \"(\".",
            .lexeme = "while",
            .line = 0,
            .column = 40
        },
        SyntaxErrorTest{
            .description = "3. While without expression #3",
            .expression = "while;",
            .errorMessage = "Syntax error: line 0, col 0: \"while\": expecting \"(\".",
            .lexeme = "while",
            .line = 0,
            .column = 0
        },
        SyntaxErrorTest{
            .description = "4. While without expression #4",
            .expression = "while () {}",
            .errorMessage = "Syntax error: line 0, col 0: \"while\": expecting expression after \"(\".",
            .lexeme = "while",
            .line = 0,
            .column = 0
        }
    };

    testParserError(testCases);
}