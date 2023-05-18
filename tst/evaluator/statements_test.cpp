#include <gtest/gtest.h>
#include <sstream>

#include "Evaluator.hpp"

struct StatementTest{
    std::string description;
    std::string program;
    std::string expectedOutput;
    bool shouldThrow = false;
};

void testStatements(const std::vector<StatementTest> &testCases)
{
    for (const auto &tc : testCases) {
        std::cout << tc.description << std::endl;

        std::ostringstream out;

        Evaluator evaluator(out);

        if (tc.shouldThrow) {
            EXPECT_THROW(evaluator.feed(tc.program), LogicalError);
            continue;
        }

        EXPECT_NO_THROW(evaluator.feed(tc.program));
        EXPECT_STREQ(out.str().c_str(), tc.expectedOutput.c_str());
    }
}

TEST(EvaluatorTest, Blocks)
{
    const std::vector<StatementTest> testCases {
        StatementTest{
            .description = "1. No block",
            .program = "int n = 1; print(n);",
            .expectedOutput = "1\n"
        },
        StatementTest{
            .description = "2. Basic block",
            .program = "{ int n = 1; print(n); }",
            .expectedOutput = "1\n"
        },
        StatementTest{
            .description = "3. Double block",
            .program = "{ int n = 1 ; { print(n); } }",
            .expectedOutput = "1\n"
        },
        StatementTest{
            .description = "4. Double block error",
            .program = "{ { str s = \"yo\"; } print(s); } ",
            .expectedOutput = "",
            .shouldThrow = true
        },
        StatementTest{
            .description = "5. Shadowing",
            .program = "{                                           "
                       "    str s = \"yo\";                         "
                       "    {                                       "
                       "        str s = \"tutu\";                   "
                       "        {                                   "
                       "            print(s);                       "
                       "        }                                   "
                       "        s = \"toto\";                       "
                       "        print(s);                           "
                       "    }                                       "
                       "    print(s);                               "
                       "}                                           ",
            .expectedOutput = "tutu\ntoto\nyo\n",
        },
        StatementTest{
            .description = "6. Assigning in sub block",
            .program = "{                                           "
                       "    int n = 42;                             "
                       "    {                                       "
                       "        n = 84;                             "
                       "    }                                       "
                       "    print(n);                               "
                       "}                                           ",
            .expectedOutput = "84\n"

        }
    };

    testStatements(testCases);
}

TEST(EvaluatorTest, WhilesLoop)
{
    const std::vector<StatementTest> testCases{
        StatementTest{
            .description = "1. Basic while loop",
            .program = "{                       "
                       "    int n = 0;          "
                       "    while (n < 42) {    "
                       "        n = n + 1;      "
                       "    }                   "
                       "    print(n);           "
                       "}                       ",
            .expectedOutput = "42\n"
        },
        StatementTest{
            .description = "2. One line while loop",
            .program = "{                               "
                       "    int n = 0;                  "
                       "    while (n < 42) n = n + 1;   "
                       "    print(n);                   "
                       "}                               ",
            .expectedOutput = "42\n"
        },
        StatementTest{
            .description = "3. Nested while",
            .program = "{                           "
                       "    int i = 0;              "
                       "    int count = 0;          "
                       "                            "
                       "    while (i < 100) {       "
                       "        int j = 0;          "
                       "        while (j < 20) {    "
                       "            j = j + 1;      "
                       "        }                   "
                       "        i = i + j;          "
                       "        count = count + 1;  "
                       "    }                       "
                       "                            "
                       "    print(i);               "
                       "    print(count);           "
                       "}                           ",
            .expectedOutput = "100\n5\n"
        },
        StatementTest{
            .description = "4. While false condition",
            .program = "int n = 0;      "
                       "                "
                       "while (n < 0) { "
                       "    n = n + 1;  "
                       "}               "
                       "print(n);       ",
            .expectedOutput="0\n",
        },
        StatementTest{
            .description = "5. While without expression #1",
            .program = "int n = 0;      "
                       "                "
                       "while { "
                       "    n = n + 1;  "
                       "}               ",
                       .expectedOutput = "",
            .shouldThrow = true
        },
        StatementTest{
            .description = "6. While without expression #2",
            .program = "int n = 0;          "
                       "                    "
                       "while n = n + 1;    ",
                       .expectedOutput = "",
            .shouldThrow = true
        },
        StatementTest{
            .description = "7. While without expression #3",
            .program = "while;",
            .expectedOutput = "",
            .shouldThrow = true
        },
        StatementTest{
            .description = "8. While without expression #4",
            .program = "while () {}",
            .expectedOutput = "",
            .shouldThrow = true
        },
        StatementTest{
            .description = "9. While without expression #4",
            .program = "while () {}",
            .expectedOutput = "",
            .shouldThrow = true
        },
        StatementTest{
            .description = "10. While without statement",
            .program = "int n = 0;          "
                       "while (n == 1);     "
                       "print(n);           ",
            .expectedOutput = "0\n"
        },
    };

    testStatements(testCases);
}