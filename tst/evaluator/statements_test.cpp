#include <gtest/gtest.h>
#include <sstream>

#include "Evaluator.hpp"

struct StatementTest
{
    std::string description;
    std::string program;
    std::string expectedOutput;
    bool shouldThrow = false;
};

void testStatements(const std::vector<StatementTest> &testCases)
{
    for (const auto &tc: testCases) {
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
    const std::vector<StatementTest> testCases{
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
                       "    for (i *= 2; i < 4; i++) {                  "
                       "        n++;                                    "
                       "    }                                           "
                       "    print(n);                                   "
                       "    print(i);                                   "
                       "}                                               ",
            .expectedOutput = "2\n4\n"
        },
        StatementTest{
            .description = "7. For loop incr by 3",
            .program = "{"
                       "    int n = 0;                                  "
                       "    int i = 3;                                  "
                       "    for (i = 0; i < 10; i += 3) {               "
                       "        n++;                                    "
                       "    }                                           "
                       "    print(n);                                   "
                       "    print(i);                                   "
                       "}                                               ",
            .expectedOutput = "4\n12\n"
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
            .program = "int n = 25; n /= 5; print(n);",
            .expectedOutput = "5\n",
        },
        StatementTest{
            .description = "7. Assign %=",
            .program = "int n = 28; n %= 5; print(n);",
            .expectedOutput = "3\n",
        },
    };

    testStatements(testCases);
}

TEST(StatementTest, Functions)
{
    const std::vector<StatementTest> testCases{
        StatementTest{
            .description = "1. print_str function",
            .program = "{                               \n"
                       "    fnc print_str(str s) {      \n"
                       "        print(s);               \n"
                       "    }                           \n"
                       "    print_str(\"hello\");       \n"
                       "}                               \n",
            .expectedOutput = "hello\n"
        },
        StatementTest{
            .description = "2. add function",
            .program = "{                               "
                       "    fnc add(int n, int m) int {     "
                       "        return n + m;           "
                       "    }"
                       "    print(add(5, 3));           "
                       "}                               ",
            .expectedOutput = "8\n"
        },
        StatementTest{
            .description = "3. Declared function scope should have access to outer variables",
            .program = "{                   "
                       "    int n = 0;      "
                       "    fnc f() {       "
                       "        print(n);   "
                       "    }               "
                       "    f();            "
                       "}                   ",
            .expectedOutput = "0\n"
        },
        StatementTest{
            .description = "4. Calling a function from a function",
            .program = "{                           "
                       "    fnc fa() {              "
                       "        print(\"hello\");   "
                       "    }                       "
                       "    fnc fb() {              "
                       "        fa();               "
                       "    }                       "
                       "    fb();                   "
                       "}                           ",
            .expectedOutput = "hello\n"
        },
        StatementTest{
            .description = "5. Function without parameter",
            .program = "{                           \n"
                       "    fnc fa() {              \n"
                       "        print(\"hello\");   \n"
                       "    }                       \n"
                       "    fa();                   \n"
                       "}                           \n",
            .expectedOutput = "hello\n"
        },
        StatementTest{
            .description = "6. Wrong argument type",
            .program = "{                                   \n"
                       "    fnc fa(int a) {                 \n"
                       "        print(a);                   \n"
                       "    }                               \n"
                       "    fa(\"hello\");                  \n"
                       "}                                   \n",
            .shouldThrow = true
        },
        StatementTest{
            .description = "7. Number of argument mismatch",
            .program = "{                                   \n"
                       "    fnc fa(int a) {                 \n"
                       "        print(a);                   \n"
                       "    }                               \n"
                       "    fa();                           \n"
                       "}                                   \n",
            .shouldThrow = true
        },
        StatementTest{
            .description = "8. Trying to call on non-callable object",
            .program = "{                                   \n"
                       "    int a;                          \n"
                       "    a();                            \n"
                       "}                                   \n",
            .shouldThrow = true
        },
        StatementTest{
            .description = "9. Assign function return to variable",
            .program = "{                                       "
                       "    fnc add(int n, int m) int {     "
                       "        return n + m;           "
                       "    }"
                       "    int n = add(5, 3);"
                       "    print(n);           "
                       "}                               ",
            .expectedOutput = "8\n"
        },
        StatementTest{
            .description = "10. Assign function return to variable wrong type",
            .program = "{                                       "
                       "    fnc add(int n, int m) int {     "
                       "        return n + m;           "
                       "    }"
                       "    str n = add(5, 3);"
                       "}                               ",
            .shouldThrow = true,
        },
        StatementTest{
            .description = "11. Return an int from a void function",
            .program = "{                                       "
                       "    fnc f() {     "
                       "        return 42;           "
                       "    }"
                       "    f();"
                       "}                               ",
            .shouldThrow = true,
        },
        StatementTest{
            .description = "12. Return wrong type",
            .program = "{                                       "
                       "    fnc f() str {     "
                       "        return 42;           "
                       "    }"
                       "    f();"
                       "}                               ",
            .shouldThrow = true,
        },
        StatementTest{
            .description = "13. Return int when the return type is void",
            .program = "{                                       "
                       "    fnc f() {     "
                       "        return 42;           "
                       "    }"
                       "    f();"
                       "}                               ",
            .shouldThrow = true,
        },
        StatementTest{
            .description = "14. Return nothing when the return type is int",
            .program = "{                                       "
                       "    fnc f() int {     "
                       "        return;           "
                       "    }"
                       "    f();"
                       "}                               ",
            .shouldThrow = true,
        },
        StatementTest{
            .description = "15. Function of return type int never return",
            .program = "{                                       "
                       "    fnc f() int {     "
                       "    }"
                       "    f();"
                       "}                               ",
            .shouldThrow = true,
        },
        StatementTest{
            .description = "16. Recursive function",
            .program = "{                                       "
                       "    fnc power(int x, int n) int {"
                       "        if (n == 0) {"
                       "            return 1;"
                       "        }"
                       "        if (n == 1) {"
                       "            return x;"
                       "        }"
                       "        return power(x, n - 1) * x;"
                       "    }"
                       "    print(power(2, 0));"
                       "    print(power(2, 1));"
                       "    print(power(2, 2));"
                       "    print(power(2, 8));"
                       "}                               ",
                       .expectedOutput = "1\n"
                                         "2\n"
                                         "4\n"
                                         "256\n"
        },
        StatementTest{
            .description = "17. Function defined in function",
            .program =
                "{                                    "
                "   fnc div(int n, int m) int {         "
                "       fnc print_int() {               "
                "           print(42);                  "
                "       }                               "
                "       print_int();                    "
                "       return n / m;                   "
                "   }                                   "
                "   div(4, 2);                          "
                "}                                      ",
            .expectedOutput =  "42\n"
        },
        StatementTest{
            .description = "18. Function in block",
            .program =
            "{                                      "
            "   {                                   "
            "       fnc foo() {                     "
            "           print(\"foo\");             "
            "       }                               "
            "       foo();                          "
            "   }                                   "
            "}                                      ",
            .expectedOutput =  "foo\n"
        },
        StatementTest{
            .description = "19. Function called outside of scope #1",
            .program =
                "{                                    "
                "   fnc div(int n, int m) int {         "
                "       fnc print_int() {               "
                "           print(42);                  "
                "       }                               "
                "       return n / m;                   "
                "   }                                   "
                "   div(4, 2);                          "
                "   print_int();                        "
                "}                                      ",
            .shouldThrow = true
        },
        StatementTest{
            .description = "20. Function called outside of scope #2",
            .program =
            "{                                      "
            "   {                                   "
            "       fnc foo() {                     "
            "           print(\"foo\");             "
            "       }                               "
            "   }                                   "
            "   foo();                              "
            "}                                      ",
            .shouldThrow = true
        }
    };

    testStatements(testCases);
}

TEST(StatementTest, ReturnOutsideOfFunction)
{
    std::vector<StatementTest> testCases{
          StatementTest{
              .description = "1. Return outside of function",
              .program = "return;",
              .shouldThrow = true
          },
          StatementTest{
              .description = "2. two functions with return",
              .program = "{"
                         "  fnc fa() int {"
                         "      return 1;"
                         "  }"
                         "  fnc fb() int {"
                         "      return fa();"
                         "  }"
                         "  print(fb());"
                         "}",
            .expectedOutput = "1\n",
            .shouldThrow = false
          },
          StatementTest{
              .description = "3. two functions with return #2",
              .program = "{"
                         "  fnc fa() int {"
                         "      return 1;"
                         "  }"
                         "  fnc fb() int {"
                         "      int ret = fa();"
                         "      return ret;"
                         "  }"
                         "  print(fb());"
                         "}",
              .expectedOutput = "1\n",
              .shouldThrow = false
          }
    };

    testStatements(testCases);
}

TEST(StatementTest, BreakAndContinue)
{
    std::vector<StatementTest> testCases{
        StatementTest{
            .description = "1. break outside of a loop",
            .program = "break;",
            .shouldThrow = true,
        },
        StatementTest{
            .description = "2. continue outside of a loop",
            .program = "continue;",
            .shouldThrow = true,
        },
        StatementTest{
            .description = "3. break in for loop",
            .program = "{                                   \n"
                       "    for (int i = 0; i < 10; i++) {  \n"
                       "        print(i);                   \n"
                       "        break;                      \n"
                       "    }                               \n"
                       "}                                   \n",
            .expectedOutput = "0\n"
        },
        StatementTest{
            .description = "4. continue in for loop",
            .program = "{"
                       "    for (int i = 0; i < 4; i++) {"
                       "        if (i % 2 == 0)"
                       "            continue;"
                       "        print(i);"
                       "    }"
                       "}",
            .expectedOutput = "1\n3\n"
        },
        StatementTest{
            .description = "5. break in while loop",
            .program = "{"
                       "    int i = 0;"
                       "    while (1) {"
                       "        if (i == 1)"
                       "            break;"
                       "        print(i);"
                       "        i++;"
                       "    }"
                       "}",
            .expectedOutput = "0\n"
        },
        StatementTest{
            .description = "6. continue and break mixed in while loop",
            .program = "{"
                       "    int i = 0;"
                       "    while (1) {"
                       "        if (i != 10) {"
                       "            i++;"
                       "            continue;"
                       "        }"
                       "        print(i);"
                       "        break;"
                       "    }"
                       "}",
            .expectedOutput = "10\n"
        },
        StatementTest{
            .description = "7. For loop continue no block",
            .program = "{"
                       "    int i = 0;"
                       "    for (; i < 10; i++) continue;"
                       "    print(i);"
                       "}",
            .expectedOutput = "10\n"
        },
        StatementTest{
            .description = "8. For loop break no block",
            .program = "{"
                       "    int i = 0;"
                       "    for (; i < 10; i++) break;"
                       "    print(i);"
                       "}",
            .expectedOutput = "0\n"
        }
    };

    testStatements(testCases);
}
