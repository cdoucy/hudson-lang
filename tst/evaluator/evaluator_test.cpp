#include <gtest/gtest.h>
#include "Evaluator.hpp"

struct EvaluatorTest
{
    std::string description;
    std::string expression;
    Token::Integer expectedResult;
};

static void testEvaluator(const std::vector<EvaluatorTest> &testCases)
{
    Evaluator evaluator;

    for (const auto &test : testCases) {
        std::cout << test.description << std::endl;

        evaluator.feed(test.expression + ";");

        EXPECT_EQ(evaluator.getResult(), test.expectedResult);

        evaluator.clear();
    }
}

TEST(EvaluatorTest, ValidExpressions)
{
    const std::vector<EvaluatorTest> testCases{
        EvaluatorTest{
            .description = "1. One integer",
            .expression = "1",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "2. Two operands addition",
            .expression = "1 + 2",
            .expectedResult = 3
        },
        EvaluatorTest{
            .description = "3. Three operands addition",
            .expression = "1 + 2 + 3",
            .expectedResult = 6
        },
        EvaluatorTest{
            .description = "4. Four operands addition",
            .expression = "1 + 2 + 3 + 4",
            .expectedResult = 10
        },
        EvaluatorTest{
            .description = "5. One operands addition",
            .expression = "+1",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "6. One operands subtraction",
            .expression = "-1",
            .expectedResult = -1
        },
        EvaluatorTest{
            .description = "7. Two minus one operand",
            .expression = "--1",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "8. Two plus one operand",
            .expression = "++1",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "9. Plus minus one",
            .expression = "-+1",
            .expectedResult = -1
        },
        EvaluatorTest{
            .description = "10. Minus plus one",
            .expression = "+-1",
            .expectedResult = -1
        },
        EvaluatorTest{
            .description = "11. Hardcore chained plus and minus",
            .expression = "- - - 1 + - 1 - 1 - + - - + - + + - + 1 + ++++++1 -- 1 ++ 1 - 1 + - + - + + + - + - -- +++ - 1",
            .expectedResult = -3
        },
        EvaluatorTest{
            .description = "12. Hardcore plus and minus operation",
            .expression = "- 17 + 42 + 4326 - 984 + -8392 + 2 - 1 - - 289172 + 12 - + - 728",
            .expectedResult = 284888
        },
        EvaluatorTest{
            .description = "13. Simple multiplication",
            .expression = "2 * 4",
            .expectedResult = 8
        },
        EvaluatorTest{
            .description = "14. Simple division",
            .expression = "8 / 4",
            .expectedResult = 2
        },
        EvaluatorTest{
            .description = "15. Simple modulo",
            .expression = "9 % 4",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "16. Hardcore multiplication, division and module",
            .expression = "9 % 4 * 14 / 2 * 38 % 3 * 47 / 6 % 14 * 943 / 24 % 432 / 2 * 2 * 3 * 4 % 64 / 2 * 843 % 256 % 43 * 9427 / 324",
            .expectedResult = 29
        },
        EvaluatorTest{
            .description = "17. Multiplication precedence",
            .expression = "1 + 2 * 3",
            .expectedResult = 7
        },
        EvaluatorTest{
            .description = "18. Parenthesis precedence",
            .expression = "(1 + 2) * 3",
            .expectedResult = 9
        },
        EvaluatorTest{
            .description = "19. Complex operation #1",
            .expression = "1 + 2 * 4 / (2 - 3) - 1",
            .expectedResult = -8
        },
        EvaluatorTest{
            .description = "20. Complex operation #2",
            .expression = "2 * (3 % (16 / 4) + 6) - 7",
            .expectedResult = 11
        },
        EvaluatorTest{
            .description = "21. Complex operation #3",
            .expression = "2 * 3 % (16 / 4) + 6 - 7",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "22. Complex operation #4",
            .expression = "2 * 3 % 16 / 4 + 6 - 7",
            .expectedResult = 0
        },
        EvaluatorTest{
            .description = "23. Complex operation #5",
            .expression = "1 + 2 * 4 + 7 / 2 % 2 - (5 * (58 + 4 / 2) % 2 - (42 + 2) * 3) / (5 % 2) * (128 + 321 * (12 / (2 + 1 - (43 * (50 / 2 + 1/ (43 - 53 % 3) * -2 ) ))))",
            .expectedResult = 16906
        },
        EvaluatorTest{
            .description = "24. Mult positive number",
            .expression = "2 * + 3",
            .expectedResult = 6
        },
        EvaluatorTest{
            .description = "25. Div negative number",
            .expression = "(10 + 20) / + (-(5 + 5))",
            .expectedResult = -3
        },
        EvaluatorTest{
            .description = "26. negative number in parenthesis",
            .expression = "-(5 + 5)",
            .expectedResult = -10
        },
        EvaluatorTest{
            .description = "27. Positive negative number in parenthesis",
            .expression = "-(-5 - 5)",
            .expectedResult = 10
        },
        EvaluatorTest{
            .description = "28. Negative positive number in parenthesis",
            .expression = "+(-5 - 5)",
            .expectedResult = -10
        },
        EvaluatorTest{
            .description = "29. Null number in parenthesis",
            .expression = "+(5 - 5)",
            .expectedResult = 0
        },
        EvaluatorTest{
            .description = "30. Positive number in parenthesis",
            .expression = "+(5 + 5)",
            .expectedResult = 10
        },
        EvaluatorTest{
            .description = "31. Positive number",
            .expression = "+(5)",
            .expectedResult = 5
        },
        EvaluatorTest{
            .description = "32. Negative number",
            .expression = "-(5)",
            .expectedResult = -5
        },
        EvaluatorTest{
            .description = "33. Negative number",
            .expression = "(-5)",
            .expectedResult = -5
        },
        EvaluatorTest{
            .description = "34. Positive number",
            .expression = "(+5)",
            .expectedResult = 5
        },
        EvaluatorTest{
            .description = "35. Positive negative number",
            .expression = "+(-5)",
            .expectedResult = -5
        },
        EvaluatorTest{
            .description = "36. Negative positive number",
            .expression = "-(+5)",
            .expectedResult = -5
        }
    };

    testEvaluator(testCases);
}

TEST(EvaluatorTest, EqualityExpressions) {
    const std::vector<EvaluatorTest> testCases{
        EvaluatorTest{
            .description = "1. Simple equal true",
            .expression = "1 == 1",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "2. Simple equal false",
            .expression = "1 == 2",
            .expectedResult = 0
        },
        EvaluatorTest{
            .description = "3. Simple not equal true",
            .expression = "1 != 2",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "4. Simple not equal false",
            .expression = "1 != 1",
            .expectedResult = 0
        },
        EvaluatorTest{
            .description = "5. Chained equal true",
            .expression = "1 == 1 == 1 == 1",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "6. Chained equal false",
            .expression = "1 == 1 == 2 == 1",
            .expectedResult = 0
        },
        EvaluatorTest{
            .description = "7. Chained equal and not equal true",
            .expression = "2 == 2 != 1",
            .expectedResult = 0
        },
        EvaluatorTest{
            .description = "8. Chained equal and not equal true",
            .expression = "(2 == 2) == 1",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "9. Equality with parenthesis #1",
            .expression = "(2 == 2) == (2 == 2)",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "10. Equality with parenthesis #2",
            .expression = "(2 == 2) != (1 != 2)",
            .expectedResult = 0
        },
        EvaluatorTest{
            .description = "11. Equality with parenthesis #3",
            .expression = "(2 != 3) == (2 == 2)",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "12. Equality with expression #1",
            .expression = "2 * 20 + 1 == 1 + 80 / 2",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "13. Equality with expression #2",
            .expression = "2 * 20 + 1 != 1 + 80 / 2",
            .expectedResult = 0
        },
        EvaluatorTest{
            .description = "14. Equality with expression #3",
            .expression = "2 * (20 + 1) == 1 + 80 / 2",
            .expectedResult = 0
        },
        EvaluatorTest{
            .description = "15. Equality with expression #4",
            .expression = "2 * 20 + 1 != (1 + 80) / 2",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "16. Equal with unary operator",
            .expression = "1 == +1",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "17. Equal with unary operator #2",
            .expression = "+1 != -1",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "18. simple false not",
            .expression = "!1",
            .expectedResult = 0
        },
        EvaluatorTest{
            .description = "19. simple true not",
            .expression = "!0",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "20. Not with expression",
            .expression = "!(1 - 1)",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "21. Chained not",
            .expression = "!(!!(!(-1)))",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "21. Not with equality",
            .expression = "!1 == (0 == !0)",
            .expectedResult = 1
        }
    };

    testEvaluator(testCases);
}

TEST(EvaluatorTest, ComparisonExpressions)
{
    const std::vector<EvaluatorTest> testCases{
        EvaluatorTest{
            .description = "1. Simple greater than",
            .expression = "2 > 1",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "2. Simple lesser than",
            .expression = "2 < 1",
            .expectedResult = 0
        },
        EvaluatorTest{
            .description = "3. Simple greater or equal than",
            .expression = "2 <= 2",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "4. Simple lesser or equal than",
            .expression = "2 >= 3",
            .expectedResult = 0
        },
        EvaluatorTest{
            .description = "5. Priority #1",
            .expression = "1 == 2 < 0 + 1",
            .expectedResult = 0
        },
        EvaluatorTest{
            .description = "6. Priority #2",
            .expression = "(1 == 2) < 0 + 1",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "7. Priority #3",
            .expression = "1 == 50 * 2 + 10 < 31 * 3 / 3 - (31 + 1) + 2",
            .expectedResult = 0
        },
        EvaluatorTest{
            .description = "8. Priority #4",
            .expression = "(1 == 50 * 2 + 10) < 31 * 3 / 3 - (31 + 1) + 2",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "9. Strings comparison #1",
            .expression = "\"tutu\" == \"tutu\"",
            .expectedResult = 1,
        },
        EvaluatorTest{
            .description = "10. Strings comparison #2",
            .expression = "\"tutu\" != \"tutu\"",
            .expectedResult = 0,
        },
        EvaluatorTest{
            .description = "11. Strings comparison #3",
            .expression = "\"tutu\" == \"toto\"",
            .expectedResult = 0,
        },
        EvaluatorTest{
            .description = "12. Strings comparison #4",
            .expression = "\"toto\" != \"tutu\"",
            .expectedResult = 1,
        }
    };

    testEvaluator(testCases);
}

TEST(EvaluatorTest, LogicalComparison)
{
    const std::vector<EvaluatorTest> testCases{
        EvaluatorTest{
            .description = "1. Simple AND",
            .expression = "1 && 1",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "2. Simple OR",
            .expression = "0 || 2",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "3. Mixed AND OR",
            .expression = "(1 - 1 || 2 * 32 - 2 * 32) || (-1 + 2 && -1) && (1 && 0 || -1)",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "4. True OR should stop evaluation",
            .expression = "1 || 1 / 0",
            .expectedResult = 1
        },
        EvaluatorTest{
            .description = "5. False AND should stop evaluation",
            .expression = "0 && 1 / 0",
            .expectedResult = 0
        }

    };

    testEvaluator(testCases);
}

TEST(EvaluatorTest, BitwiseExpression)
{
    const std::vector<EvaluatorTest> testCases{
        EvaluatorTest{
            .description = "1. XOR",
            .expression = "1 ^ 0",
            .expectedResult = 1,
        },
        EvaluatorTest{
            .description = "2. OR",
            .expression = "1 ^ 0",
            .expectedResult = 1,
        },
        EvaluatorTest{
            .description = "3. AND",
            .expression = "1 & 0",
            .expectedResult = 0,
        },
        EvaluatorTest{
            .description = "4. Right shift",
            .expression = "1 >> 1",
            .expectedResult = 0,
        },
        EvaluatorTest{
            .description = "5. Left shift",
            .expression = "1 << 1",
            .expectedResult = 2,
        },
        EvaluatorTest{
            .description = "6. NOT #1",
            .expression = "~1",
            .expectedResult = -2,
        },
        EvaluatorTest{
            .description = "7. NOT #2",
            .expression = "~~1",
            .expectedResult = 1,
        }
    };

    testEvaluator(testCases);
}

TEST(EvaluatorTest, DeclarationAndAssignment)
{
    struct Test{
        std::string description;
        std::string expression;
        std::unordered_map<std::string, runtime::Object> expected;
        std::optional<Token::Integer> result;
    };

    std::vector<Test> testCases{
        Test{
            .description = "1. Declaration without assignment",
            .expression = "int n;",
            .expected = {
                {"n", 0}
            },
            .result = std::nullopt
        },
        Test{
            .description = "2. Declaration with assignment",
            .expression = "int n = 42;",
            .expected = {
                {"n", 42}
            },
            .result = 42
        },
        Test{
            .description = "3. Declaration without assignment and assignment",
            .expression = "int n; n = 84;",
            .expected = {
                {"n", 84}
            },
            .result = 84
        },
        Test{
            .description = "4. Declaration without assignment and assignment",
            .expression = "int n = 42; n = 84;",
            .expected = {
                {"n", 84}
            },
            .result = 84
        },
        Test{
            .description = "5. Declaration and expression #1",
            .expression = "int n = 1; 1 + n;",
            .expected = {
                {"n", 1}
            },
            .result = 2
        },
        Test{
            .description = "6. Declaration and expression #2",
            .expression = "int n = 1; n + 1;",
            .expected = {
                {"n", 1}
            },
            .result = 2
        },
        Test{
            .description = "7. Declaration without expression and expression #1",
            .expression = "int n; 1 + n;",
            .expected = {
                {"n", 0}
            },
            .result = 1
        },
        Test{
            .description = "8. Declaration without expression and expression #2",
            .expression = "int n; n + 1;",
            .expected = {
                {"n", 0}
            },
            .result = 1
        },
        Test{
            .description = "9. Multiple declarations",
            .expression = "int x = 2; int y = x + 1; int z = x + y; z + x + y;",
            .expected = {
                {"x", 2},
                {"y", 3},
                {"z", 5}
            },
            .result = 10
        },
        Test{
            .description = "10. Non alphabetic declarations",
            .expression = "int n = 42; int _x1_ = n; int __1x1__ = _x1_; int abc1_123 = 84;",
            .expected = {
                {"n", 42},
                {"_x1_", 42},
                {"abc1_123", 84}
            },
            .result = 84
        },
        Test{
            .description = "11. Declaration with complex expression",
            .expression = "int a = 42; int b = (a * 41 * ((2 + 28) * a)); b;",
            .expected = {
                {"a", 42},
                {"b", 2169720},
            },
            .result = 2169720
        },
        Test{
            .description = "12. Integer Comparisons",
            .expression = "int a = 42; int b; b = 42; a == b;",
            .expected = {
                {"a", 42},
                {"b", 42},
            },
            .result = 1
        },
        Test{
            .description = "13. String Comparisons",
            .expression = "str a = \"tutu\"; str b; b = \"tutu\"; a != b;",
            .expected = {
                {"a", runtime::Object("tutu")},
                {"b", runtime::Object("tutu")},
            },
            .result = 0,
        }
    };

    for (const auto &test : testCases) {
        std::cout << test.description << std::endl;
        Evaluator evaluator;

        evaluator.feed(test.expression);

        const auto &state = evaluator.getState();

        for (const auto &[identifier, expected] : test.expected) {
            const auto &obj = state.get(identifier);

            EXPECT_TRUE(obj);
            EXPECT_EQ(*obj, expected);

            if (test.result) {
                EXPECT_EQ(evaluator.getResult(), *test.result);
            }
        }
    }
}

TEST(EvaluatorTest, String)
{
    struct Test{
        std::string description;
        std::string expression;
        std::unordered_map<std::string, runtime::Object> expected;
        std::optional<std::string> result;

    };

    std::vector<Test> testCases{
        Test{
            .description = "1. String declaration without expression",
            .expression = "str s;",
            .expected = {
                {"s", std::string()}
            },
            .result = std::nullopt
        },
        Test{
            .description = "2. String declaration with empty string",
            .expression = "str s = \"\";",
            .expected = {
                {"s", std::string()}
            },
            .result = "",
        },
        Test{
            .description = "3. String declaration non empty string",
            .expression = "str s = \"tutu\";",
            .expected = {
                {"s", std::string("tutu")}
            },
            .result = "tutu"
        },
        Test{
            .description = "4. String concat",
            .expression = "\"foo\" + \"bar\";",
            .expected = {},
            .result = "foobar"
        },
        Test{
            .description = "5. String concat #2",
            .expression = "str s = \"foo\" + \"bar\"; str s2 = s + \"tutu\"; s2 + \" \" + s;",
            .expected = {
                {"s", std::string("foobar")},
                {"s", std::string("foobartutu")},
            },
            .result = "foobartutu foobar"
        }
    };

    for (const auto &test : testCases) {
        std::cout << test.description << std::endl;
        Evaluator evaluator;

        evaluator.feed(test.expression);

        const auto &state = evaluator.getState();

        for (const auto &[identifier, expected] : test.expected) {
            const auto &obj = state.get(identifier);

            EXPECT_EQ(obj->getType(), Token::STR_TYPE);
            EXPECT_EQ(obj->get<Token::String>(), expected.get<Token::String>());
        }
    }
}

TEST(EvaluatorTest, Print)
{
    struct PrintTest{
        std::string description;
        std::string expression;
        std::string expectedStdout;
    };

    const std::vector<PrintTest> testCases{
        PrintTest{
            .description = "1. Print simple string",
            .expression = "print \"tutu\";",
            .expectedStdout = "tutu\n"
        },
        PrintTest{
            .description = "2. Print simple integer",
            .expression = "print 42;",
            .expectedStdout = "42\n"
        },
        PrintTest{
            .description = "3. Print expression",
            .expression = "int n = 3; print (5 + 2) * 3;",
            .expectedStdout = "21\n"
        },
        PrintTest{
            .description = "4. Print str variable",
            .expression = "str s = \"yo\"; print s;",
            .expectedStdout = "yo\n"
        },
        PrintTest{
            .description = "5. Print without arguments",
            .expression = "print;",
            .expectedStdout = "\n"
        },
        PrintTest{
            .description = "6. Print chained",
            .expression = "print 1; print \"yo\";",
            .expectedStdout = "1\nyo\n"
        }
    };

    Evaluator evaluator;

    for (const auto &tc : testCases) {
        std::cout << tc.description << std::endl;
        testing::internal::CaptureStdout();

        evaluator.feed(tc.expression);

        const auto &actualStdout = testing::internal::GetCapturedStdout();

        EXPECT_STREQ(actualStdout.c_str(), tc.expectedStdout.c_str());
    }
}

TEST(EvaluatorTest, EvaluatorError)
{
    struct EvaluatorErrorTest{
        std::string description;
        std::string expression;
        std::string errorMessage;
    };

    const std::vector<EvaluatorErrorTest> testCases{
        EvaluatorErrorTest{
            .description = "1. Div by zero",
            .expression = "1 / 0",
            .errorMessage = "Logical error: division by zero."
        },
        EvaluatorErrorTest{
            .description = "2. Mod by zero",
            .expression = "1 % 0",
            .errorMessage = "Logical error: modulo by zero."
        },
        EvaluatorErrorTest{
            .description = "3. Div by zero with expression",
            .expression = "10 * 2 / (25 - (5 * 5))",
            .errorMessage = "Logical error: division by zero."
        },
        EvaluatorErrorTest{
            .description = "4. Div by zero with OR",
            .expression = "0 || 1 / 0",
            .errorMessage = "Logical error: division by zero."
        },
        EvaluatorErrorTest{
            .description = "5. Div by zero with AND",
            .expression = "1 && 1 / 0",
            .errorMessage = "Logical error: division by zero."
        },
        EvaluatorErrorTest{
            .description = "6. Unknown identifier #1",
            .expression = "n",
            .errorMessage = "Logical error: n: undefined identifier."
        },
        EvaluatorErrorTest{
            .description = "7. Unknown identifier #2",
            .expression = "1 + n",
            .errorMessage = "Logical error: n: undefined identifier."
        },
        EvaluatorErrorTest{
            .description = "8. Unknown identifier #3",
            .expression = "n + 1",
            .errorMessage = "Logical error: n: undefined identifier."
        },
        EvaluatorErrorTest{
            .description = "9. Unknown identifier #4",
            .expression = "int n = n",
            .errorMessage = "Logical error: n: undefined identifier."
        },
        EvaluatorErrorTest{
            .description = "10. Unknown identifier #5",
            .expression = "n = 1",
            .errorMessage = "Logical error: n: undefined identifier."
        },
        EvaluatorErrorTest{
            .description = "11. Identifier already defined #1",
            .expression = "int n; int n;",
            .errorMessage = "Logical error: n: identifier already defined."
        },
        EvaluatorErrorTest{
            .description = "12. Identifier already defined #2",
            .expression = "int n = 1; int n;",
            .errorMessage = "Logical error: n: identifier already defined."
        },
        EvaluatorErrorTest{
            .description = "13. Identifier already defined #3",
            .expression = "int n; int n = 1;",
            .errorMessage = "Logical error: n: identifier already defined."
        },
        EvaluatorErrorTest{
            .description = "14. Identifier already defined #4",
            .expression = "int n = 1; int x = n; int n = x; x = n",
            .errorMessage = "Logical error: n: identifier already defined."
        },
        EvaluatorErrorTest{
            .description = "15. Type incompatibility #1",
            .expression = "int n = \"\";",
            .errorMessage = "Logical error: type int is not compatible with type str."
        },
        EvaluatorErrorTest{
            .description = "16. Type incompatibility #2",
            .expression = "str s = 42;",
            .errorMessage = "Logical error: type str is not compatible with type int."
        },
        EvaluatorErrorTest{
            .description = "17. Type incompatibility #3",
            .expression = "int n = 42; n = \"coucou\";",
            .errorMessage = "Logical error: type int is not compatible with type str."
        },
        EvaluatorErrorTest{
            .description = "18. Type incompatibility #4",
            .expression = "str s = \"yo\"; int n = 42; n == s;",
            .errorMessage = "Logical error: type int is not compatible with type str."
        },
        EvaluatorErrorTest{
            .description = "19. Type incompatibility #5",
            .expression = "str s = \"yo\"; int n = 42; s - n;",
            .errorMessage = "Logical error: type str doesn't implement operator -."
        },
        EvaluatorErrorTest{
            .description = "20. Type incompatibility #6",
            .expression = "str s = \"yo\"; int n = 42; n + 42 + s + 84;",
            .errorMessage = "Logical error: type int is not compatible with type str."
        }
    };

    Evaluator evaluator;

    for (const auto &test: testCases) {
        std::cout << test.description << std::endl;

        bool hasThrown = false;

        try {
            evaluator.feed(test.expression + ";");
        } catch (const LogicalError &err) {
            hasThrown = true;

            EXPECT_STREQ(err.what(), test.errorMessage.c_str());
        } catch (const SyntaxError &err) {
            hasThrown = true;

            EXPECT_STREQ(err.what(), test.errorMessage.c_str());
        }

        EXPECT_TRUE(hasThrown);

        evaluator.clear();
    }
}