#include <iostream>
#include <gtest/gtest.h>

#include "lexer.hpp"

struct LexerTest
{
    std::string description;
    std::string expression;
    std::vector<Token> expected;
};

void testLexer(const std::vector<LexerTest> &testCases)
{
    for (const auto &testCase: testCases) {
        std::cout << testCase.description << std::endl;
        Lexer lexer;

        lexer.feed(testCase.expression);

        EXPECT_EQ(lexer.tokensCount(), testCase.expected.size());

        Token::Iterator tokenItr(lexer.getTokens());

        if (testCase.expected.empty()) {
            auto token = tokenItr.get();
            EXPECT_FALSE(token.has_value());
        }

        for (const auto &expected: testCase.expected) {
            auto token = tokenItr.get();

            EXPECT_TRUE(token.has_value());
            EXPECT_EQ(*token, expected);

            tokenItr.advance();
        }
    }
}

TEST(LexerTest, ValidExpressions)
{
    const std::vector<LexerTest> testCases{
        LexerTest{
            .description = "1. Empty expression",
            .expression  = "",
            .expected    = {},
        },
        LexerTest{
            .description = "2. Single digit expression",
            .expression  = "1",
            .expected    = {Token{Token::INTEGER, "1"}},
        },
        LexerTest{
            .description = "3. Single digit expression with break line",
            .expression  = "1\n2",
            .expected    = {Token{Token::INTEGER, "1"}, Token{Token::INTEGER, "2"}},
        },
        LexerTest{
            .description = "4. Blank expression",
            .expression  = " \t\r\f\v",
            .expected    = {},
        },
        LexerTest{
            .description = "5. Big number expression",
            .expression  = "1234567890",
            .expected    = {Token{Token::INTEGER, "1234567890"}},
        },
        LexerTest{
            .description = "6. Big number expression with break line",
            .expression  = "1234567890\n",
            .expected    = {Token{Token::INTEGER, "1234567890"}},
        },
        LexerTest{
            .description = "7. Big number expression",
            .expression  = "1234567890   \n  123\n456\n",
            .expected    = {
                Token{Token::INTEGER, "1234567890"},
                Token{Token::INTEGER, "123"},
                Token{Token::INTEGER, "456"}
            },
        },
        LexerTest{
            .description = "8. Multiple numbers expression",
            .expression  = "   11    2222   3        44444444     555 6        777777   \n",
            .expected    = {
                Token{Token::INTEGER, "11"},
                Token{Token::INTEGER, "2222"},
                Token{Token::INTEGER, "3"},
                Token{Token::INTEGER, "44444444"},
                Token{Token::INTEGER, "555"},
                Token{Token::INTEGER, "6"},
                Token{Token::INTEGER, "777777"}
            },
        },
        LexerTest{
            .description = "9. Multiple operators expression",
            .expression  = "  +    -   *    %    /    ",
            .expected    = {
                Token{Token::PLUS, "+"},
                Token{Token::MINUS, "-"},
                Token{Token::MULT, "*"},
                Token{Token::MOD, "%"},
                Token{Token::DIV, "/"}
            },
        },
        LexerTest{
            .description = "10. Parenthesis expression",
            .expression  = "  (   )  ",
            .expected    = {
                Token{Token::OPEN_PARENTHESIS, "("},
                Token{Token::CLOSE_PARENTHESIS, ")"},
            },
        },
        LexerTest{
            .description = "11. Full expression",
            .expression  = "2 * (333/(44 %  5) + 66666) - 777",
            .expected    = {
                Token{Token::INTEGER, "2"},
                Token{Token::MULT, "*"},
                Token{Token::OPEN_PARENTHESIS, "("},
                Token{Token::INTEGER, "333"},
                Token{Token::DIV, "/"},
                Token{Token::OPEN_PARENTHESIS, "("},
                Token{Token::INTEGER, "44"},
                Token{Token::MOD, "%"},
                Token{Token::INTEGER, "5"},
                Token{Token::CLOSE_PARENTHESIS, ")"},
                Token{Token::PLUS, "+"},
                Token{Token::INTEGER, "66666"},
                Token{Token::CLOSE_PARENTHESIS, ")"},
                Token{Token::MINUS, "-"},
                Token{Token::INTEGER, "777"},
            },
        },
    };

    testLexer(testCases);
}

TEST(LexerTest, Strings)
{
    struct LexerStringTest
    {
        std::string description;
        std::string expression;
        Token expected;
        std::string expectedValue;
    };

    const std::vector<LexerStringTest> testCases{
        LexerStringTest{
            .description = "1. String literal",
            .expression = "\"toto\"",
            .expected   = {Token::STRING, "\"toto\""},
            .expectedValue = "toto",
        },
        LexerStringTest{
            .description = "2. String literal with double quotes inside",
            .expression = "\"{\\\"foo\\\": \\\"bar\\\", \\\"count\\\": 10}\"",
            .expected   = Token{Token::STRING, "\"{\\\"foo\\\": \\\"bar\\\", \\\"count\\\": 10}\""},
            .expectedValue = "{\"foo\": \"bar\", \"count\": 10}"
        },
        LexerStringTest{
            .description = "3. Empty string literal",
            .expression = "\"\"",
            .expected   = Token{Token::STRING, "\"\""},
            .expectedValue = "",
        },
        LexerStringTest{
            .description = "4. String literal with escaped characters",
            .expression = "\" \\ \\n \\a\\b \\t \\n \\v \\\" \\f \\r \\\\ \\\\n \"",
            .expected   = Token{Token::STRING, "\" \\ \\n \\a\\b \\t \\n \\v \\\" \\f \\r \\\\ \\\\n \""},
            .expectedValue = " \\ \n \a\b \t \n \v \" \f \r \\ \\n ",
        },
    };

    for (const auto &testCase: testCases) {
        std::cout << testCase.description << std::endl;
        Lexer lexer;

        lexer.feed(testCase.expression);

        Token::Iterator tokenItr(lexer.getTokens());

            auto token = tokenItr.get();

            EXPECT_TRUE(token.has_value());
            EXPECT_EQ(*token, testCase.expected);
            EXPECT_STREQ(token->getLiteral<Token::String>().c_str(), testCase.expectedValue.c_str());
    }
}

TEST(LexerTest, KeyWords)
{
    const std::vector<LexerTest> testCases{
        LexerTest{
            .description = "1. Print",
            .expression = "print",
            .expected = {
                Token{Token::PRINT, "print"}
            }
        },
        LexerTest{
            .description = "2. Simple int",
            .expression = "int",
            .expected = {
                Token{Token::INT_TYPE, "int"}
            }
        },
        LexerTest{
            .description = "3. Simple str",
            .expression = "str",
            .expected = {
                Token{Token::STR_TYPE, "str"}
            }
        }
    };

    testLexer(testCases);
}

TEST(LexerTest, Identifiers)
{
    const std::vector<LexerTest> testCases{
        LexerTest{
            .description = "1. Simple identifier",
            .expression = "n",
            .expected = {
                Token{Token::IDENTIFIER, "n"}
            }
        },
        LexerTest{
            .description = "2. Identifier with int",
            .expression = "int var_NAME2 = 1",
            .expected = {
                Token{Token::INT_TYPE, "int"},
                Token{Token::IDENTIFIER, "var_NAME2"},
                Token{Token::ASSIGN, "="},
                Token{Token::INTEGER, "1"}
            }
        },
        LexerTest{
            .description = "3. Identifier prefixed by integer",
            .expression = "123_varNAME",
            .expected = {
                Token{Token::INTEGER, "123"},
                Token{Token::IDENTIFIER, "_varNAME"},
            }
        },
        LexerTest{
            .description = "4. Identifier that starts with a keyword",
            .expression = "int letVAR123_NAMe = 1",
            .expected = {
                Token{Token::INT_TYPE, "int"},
                Token{Token::IDENTIFIER, "letVAR123_NAMe"},
                Token{Token::ASSIGN, "="},
                Token{Token::INTEGER, "1"}
            }
        }
    };

    testLexer(testCases);
}

TEST(LexerTest, InvalidExpressions)
{
    struct LexerErrorTest
    {
        std::string description;
        std::string expression;
        std::string errorMessage;
        std::string lexeme;
        std::size_t line;
        std::size_t column;
    };

    const std::vector<LexerErrorTest> expected{
        LexerErrorTest{
            .description = "1. Simple invalid token",
            .expression = "@",
            .errorMessage = "Lexical error: line 0, col 0: \"@\": unknown token.",
            .lexeme = "@",
            .line = 0,
            .column = 0
        },
        LexerErrorTest{
            .description = "2. Invalid token in expression",
            .expression = "\n2 * (333/(44 %  5) + 666@66) - 777",
            .errorMessage = "Lexical error: line 1, col 24: \"@\": unknown token.",
            .lexeme = "@",
            .line = 1,
            .column = 24
        },
        LexerErrorTest{
            .description = "3. Unmatched double quote",
            .expression = " \"tutu ",
            .errorMessage = "Lexical error: line 0, col 1: \"\"tutu \": unmatched double quote.",
            .lexeme = "\"tutu ",
            .line = 0,
            .column = 1
        }
    };

    for (const auto &expect : expected) {
        std::cout << expect.description << std::endl;

        Lexer lexer;
        bool hasThrown = false;

        try {
            lexer.feed(expect.expression);
        } catch (const LexicalError &err) {
            hasThrown = true;

            EXPECT_STREQ(err.what(), expect.errorMessage.c_str());
            EXPECT_STREQ(err.getLexeme().c_str(), expect.lexeme.c_str());
            EXPECT_EQ(err.getLine(), expect.line);
            EXPECT_EQ(err.getColumn(), expect.column);

            lexer.clear();
        }

        EXPECT_TRUE(hasThrown);
        EXPECT_EQ(lexer.tokensCount(), 0);
    }
}