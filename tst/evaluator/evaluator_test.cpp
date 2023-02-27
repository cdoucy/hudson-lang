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
            .expression = "int n = 1; n + 1;",
            .expected = {
                {"n", 0}
            },
            .result = 1
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
            EXPECT_EQ(obj->get(), expected);

            if (test.result) {
                EXPECT_EQ(evaluator.getResult(), *test.result);
            }
        }
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
        }

        EXPECT_TRUE(hasThrown);

        evaluator.clear();
    }
}