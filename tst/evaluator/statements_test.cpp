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

TEST(StatementTest, Blocks)
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

TEST(StatementTest, WhilesLoop)
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
            .description = "5. While without statement",
            .program = "int n = 0;          "
                       "while (n == 1);     "
                       "print(n);           ",
            .expectedOutput = "0\n"
        },
    };

    testStatements(testCases);
}

TEST(StatementTest, Conditions)
{
    const std::vector<StatementTest> testCases{
        StatementTest{
            .description = "1. Basic true if",
            .program = "if (1) {        "
                       "    print(1);   "
                       "}               ",
            .expectedOutput = "1\n"
        },
        StatementTest{
            .description = "2. Basic false if",
            .program = "if (0) {        "
                       "    print(1);   "
                       "}               ",
            .expectedOutput = ""
        },
        StatementTest{
            .description = "3. Basic true if else",
            .program = "int n = 1;          "
                       "if (n == 1) {       "
                       "    print(1);       "
                       "} else {            "
                       "    print(0);       "
                       "}                   ",
            .expectedOutput = "1\n"
        },
        StatementTest{
            .description = "4. Basic false if else",
            .program = "int n = 0;          "
                       "if (n == 1) {       "
                       "    print(1);       "
                       "} else {            "
                       "    print(0);       "
                       "}                   ",
            .expectedOutput = "0\n"
        },
        StatementTest{
            .description = "5. Basic if else if else",
            .program = "int n = 2;          "
                       "if (n == 1) {       "
                       "    print(1);       "
                       "} else if (n == 2) {"
                       "    print(2);       "
                       "} else {            "
                       "    print(0);       "
                       "}                   ",
            .expectedOutput = "2\n"
        },
        StatementTest{
            .description = "6. If brackets",
            .program = "int n = 3;          "
                       "if (n == 1)         "
                       "    print(1);       "
                       "else if (n == 2) {  "
                       "    print(2);       "
                       "} else              "
                       "    print(0);       ",
            .expectedOutput = "0\n"
        }
    };

    testStatements(testCases);
}

TEST(StatementTest, ForLoop)
{
    const std::vector<StatementTest> testCases{
        StatementTest{
            .description = "1. Basic for loop #1",
            .program = "{"
                       "    int n = 0;                  "
                       "    for (int i = 0; i < 10; i = i + 1)"
                       "        n = i;                  "
                       "    print(n);                   "
                       "}",
            .expectedOutput = "9\n"
        },
        StatementTest{
            .description = "2. Basic for loop #2",
            .program = "{"
                       "    int i = 0;                  "
                       "    for (; i < 10; i = i + 1);        "
                       "    print(i);                   "
                       "}",
            .expectedOutput = "10\n"
        },
        StatementTest{
            .description = "3. Basic for loop #3",
            .program = "{"
                       "    int n = 0;                  "
                       "    for (int i = n; i < 10;) { "
                       "        i = i + 1;              "
                       "        if (i == 10) {          "
                       "            n = i;              "
                       "        }                       "
                       "    }                           "
                       "    print(n);                   "
                       "}",
            .expectedOutput = "10\n"
        },
        StatementTest{
            .description = "4. Basic for loop #4",
            .program = "{"
                       "    int n;                              "
                       "    for (n = 10; n < 20; n = n + 1) {   "
                       "    }                                   "
                       "    print(n);                           "
                       "}",
            .expectedOutput = "20\n"
        },
        StatementTest{
            .description = "5. For loop shadowing",
            .program = "{"
                       "    int n = 0;                                  "
                       "    int i = 42;                                 "
                       "    for (int i = 0; i < 20; i = i + 1) {        "
                       "        n = i;                                  "
                       "    }                                           "
                       "    print(n);                                   "
                       "    print(i);                                   "
                       "}                                               ",
            .expectedOutput = "19\n42\n"
        },
        StatementTest{
            .description = "6. For loop post incr",
            .program = "{"
                       "    int n = 0;                                  "
                       "    int i = 1;                                  "
                       "    for (i *= 2; i < 4; i++) {                 "
                       "        n++                                     "
                       "    }                                           "
                       "    print(n);                                   "
                       "    print(i);                                   "
                       "}                                               ",
            .expectedOutput = "2\n4\\n"
        },
        StatementTest{
            .description = "7. For loop incr by 3",
            .program = "{"
                       "    int n = 0;                                  "
                       "    for (int i = 0; i < 10; i += 3) {           "
                       "        n++                                     "
                       "    }                                           "
                       "    print(n);                                   "
                       "    print(i);                                   "
                       "}                                               ",
            .expectedOutput = "3\n12\n"
        }
    };

    testStatements(testCases);
}

TEST(StatementTest, StatementOperator)
{
    const std::vector<StatementTest> testCases{
        StatementTest{
            .description = "1. Post ++",
            .program = "int n; n++; print(n);",
            .expectedOutput = "1\n",
        },
        StatementTest{
            .description = "2. Post --",
            .program = "int n; n--; print(n);",
            .expectedOutput = "-1\n",
        },
        StatementTest{
            .description = "3. Assign +=",
            .program = "int n = 1; n += 9; print(n);",
            .expectedOutput = "10\n",
        },
        StatementTest{
            .description = "4. Assign -=",
            .program = "int n = 2; n -= 2; print(n);",
            .expectedOutput = "0\n",
        },
        StatementTest{
            .description = "5. Assign *=",
            .program = "int n = 5; n *= n; print(n);",
            .expectedOutput = "25\n",
        },
        StatementTest{
            .description = "6. Assign /=",
            .program = "int n = 25; n /= n; print(n);",
            .expectedOutput = "5\n",
        },
        StatementTest{
            .description = "7. Assign %=",
            .program = "int n = 28; n %= 5; print(n);",
            .expectedOutput = "3\n",
        },
        StatementTest{
            .description = "8. Assign >>=",
            .program = "int n = 8; n >>= 2; print(n);",
            .expectedOutput = "2\n",
        },
        StatementTest{
            .description = "9. Assign <<=",
            .program = "int n = 8; n <<= 2; print(n);",
            .expectedOutput = "32\n",
        },
        StatementTest{
            .description = "10. Assign &=",
            .program = "int n = 5; n &= 2; print(n);",
            .expectedOutput = "0\n",
        },
        StatementTest{
            .description = "11. Assign |=",
            .program = "int n = 42; n |= 17; print(n);",
            .expectedOutput = "59\n",
        },
        StatementTest{
            .description = "12. Assign ^=",
            .program = "int n = -13; n ^= 66; print(n);",
            .expectedOutput = "-79\n",
        }
    };

    testStatements(testCases);
}
