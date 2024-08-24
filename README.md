[![Unit tests](https://github.com/cdoucy/interpreter/actions/workflows/ci.yaml/badge.svg?branch=main)](https://github.com/cdoucy/interpreter/actions/workflows/ci.yaml)

# Hudson Programming Language

Welcome to the Hudson programming language! Hudson is a simple, yet powerful, programming language. This project is designed to be a learning tool for both language design and implementation, focusing on a clear, minimalistic syntax and core programming constructs.

This repository contains the complete specification of the Hudson programming language and the implementation of its interpreter in C++.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Testing](#examples)
- [Grammar](#grammar)
- [Contributing](#contributing)
- [License](#license)

## Overview

Hudson is a programming language that draws inspiration from several other languages while maintaining its own unique approach to syntax and semantics. It is statically typed and imperative, with a focus on simplicity and readability. This project aims to provide a foundation for further exploration into language design and interpreter construction.

## Features

- **Simple Syntax**: Hudson has a clean and minimalistic syntax that is easy to understand.
- **Basic Control Structures**: Supports `if`, `while`, `for` loops, and `break`/`continue` statements.
- **Functions**: Allows defining and invoking functions, including anonymous functions.
- **Expressions**: Includes a variety of expressions with support for logical, bitwise, and arithmetic operations.
- **Variable Declarations and Assignments**: Supports variable declarations with optional initialization and compound assignment operations.
- **Increment and Decrement Operators**: `++` and `--` are supported for quick variable updates.
- **Printing**: Built-in `print` statement for output.

## Installation

To build and run the Hudson language interpreter:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/cdoucy/hudson-lang.git
   cd hudson-lang
   ```

2. **Build the project**:
   Ensure you have CMake installed, then run:
   ```bash
   make
   ```
   This will generate the Hudson interpreter executable.

3. **Run a Hudson program**:
   ```bash
   ./hudson-interpreter examples/hello_world.hu
   ```

## Usage

You can create Hudson source files with the `.hu` extension and run them using the Hudson interpreter. Here's a basic example of a Hudson program:

```hudson
int x = 10;
int y = 20;
print(x + y);
```

## Examples

Here are some examples of what you can do in Hudson:

### Hello World

```hudson
print("Hello, World!");
```

### Loops and Conditionals

```hudson
int i = 0;
while (i < 5) {
   print(i);
   i++;
}
if (i == 5) {
   print("Done!");
} else {
   print("Something went wrong.");
}
```

### Functions and Recursion

```hudson
fnc factorial(n int) int {
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int result = factorial(5);
print(result);
```

## Testing

The Hudson programming language interpreter has been developed using Test-Driven Development (TDD) to ensure high-quality and reliable code. You can run unit tests and check code coverage with the following commands:

1. **Run the Unit Tests**:
   To run all the unit tests for the Hudson interpreter, use the following command:

   ```bash
   make run-test
   ```
This command will execute all unit tests and display the results in the terminal.

2. **Check Coverage**: To check the code coverage of the unit tests, use the command:
   To run all the unit tests for the Hudson interpreter, use the following command:

   ```bash
   make coverage
   ```
This command will generate a coverage report, showing how much of the codebase is covered by the tests. Reviewing this report can help identify untested parts of the code and ensure comprehensive test coverage.

## Grammar

The specification of the Hudson programming language in EBNF (Extended Backus-Naur Form) notation is as follows:

```ebnf
program         =   { stmt }
stmt            =   expr_stmt       |   declaration         |   assignment  |   inc_dec |   return     
                |   break           |   continue            |   print       |   block   |   while             
                |   for             |   if                  |   function
expr_stmt       =   expr ";"
declaration     =   type ident [ "=" expr ] ";"
assignment      =   ident ( "=" | "+=" | "+-" | "*=" |  "%=" | "/+" ) expr ";"
inc_dec         =   ident ( "++" | "--" ) ";"
return          =   "return" [ expr ] ";"
break           =   "break" ";"
continue        =   "continue" ";"
print           =   "print" "(" [ expr ] ")" ";"
block           =   "{" { stmt } "}"
while           =   "while" "(" expr ")" ( stmt | ";" )
for             =   "for" "(" [ declaration | assignment ] ";" expr ";" assignment | inc_dec ")" ( smt | ";" )
if              =   "if" "(" expr ")" stmt [ "else" stmt ]
function        =   "fnc" ident fnc_signature block
expr            =   or
or              =   and { "||" and }
and             =   bitwise_or { "&&" bitwise_or }
bitwise_or      =   bitwise_xor { "|"  bitwise_xor  }
bitwise_xor     =   bitwise_and { "^" bitwise_and }
bitwise_and     =   equality { "&" equality }
equality        =   comparison { "==" | "!=" comparison }
comparison      =   bitshift { "<" | "<=" | ">" | ">=" bitshift }
bitshift        =   term { ">>" | "<<" term }
term            =   factor { "-" | "+" factor }
factor          =   unary { "/" | "*" | "%" unary }
unary           =   ( "+" | "-" | "!" | "~" ) unary | call
call            =   primary { "(" [ params ] ")" }
primary         =   int_lit | ident | string_lit | anonymous_fnc | grouping
grouping        =   "(" expr ")"

params          =   expr { "," expr }
anonymous_fnc   =   'fnc' fnc_signature block
fnc_signature   =   "(" [ ident type { "," ident type } ] ")" [ type ]
type            =   "int" | "str" | "fnc" | fnc_signature
ident           =   ( letter | "_" ) { letter | digit | "_" }
int_lit         =   digit | { digit }
string_lit      =   '"' { * } '"'   
letter          =   "A" ... " Z" | "a" ... "z"
digit           =   "0" ... "9"
```

## Credits

This project was inspired by the book [Crafting Interpreters](https://craftinginterpreters.com/) by Robert Nystrom. The book provided valuable insights into the design and implementation of interpreters, which greatly influenced the development of the Hudson programming language.


## Contributing

Contributions are welcome! If you have ideas for improvements or new features, feel free to open an issue or submit a pull request. Please make sure to follow the coding standards used in the project and include tests where applicable.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
