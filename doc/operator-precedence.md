
```
program                 -> statement* EOF
statement               -> expressionStatement | declarationStatement | assignmentStatement | incDecStatement | returnStatement | print | block | while | for | if | function
expressionStatement     -> expression ';'
declarationStatement    -> declaration ';'
assignementStatement    -> assignement ';'
incDecStatement         -> incDec ';'
returnStatement         -> return (expression)? ';'
declaration             -> Type Identifier ('=' expression)?
assignment              -> Identifier assimentOperator expression
assignmentOperator      -> '=' | '+= | '+-' | '*=' | '%=' | '/='
incDec                  -> Identifier ('++' | '--')
print                   -> 'print('expression?')' ';'
block                   -> '{' statement* '}'
while                   -> 'while' '(' expression ')' (statement | ';' )
for                     -> 'for' '(' (initStatement)? ';' expression ';' (stepStatement)? ')' (statement | ';')
initStatement           -> declaration | assignment
stepStatement           -> assignement | incDec
if                      -> 'if' '(' expression ')' statement ('else' statement)?
function                -> 'fnc' Identifier FunctionSignature block
expression              -> or
or                      -> and (( '||' ) and ) *
and                     -> bitwise_or (( '&&' ) bitwise_or ) *
bitwise_or              -> bitwise_xor (( '|' ) bitwise_xor ) *
bitwise_xor             -> bitwise_and (( '^' ) bitwise_and ) *
bitwise_and             -> equality (( '&' ) equality ) *
equality                -> comparison (( '==' | '!=' ) comparison ) *
comparison              -> bitshift (( '<' | '<=' | '>' | '>=' ) bitshift ) *
bitshift                -> term (( '>>' | '<<' ) term ) *
term                    -> factor ( ( '-' | '+' ) factor ) *
factor                  -> unary ( ( '/' | '*' | '%' ) unary ) *
unary                   -> ( '+' | '-' | '!' | '~' ) unary | call
call                    -> Identifier '(' (expression ',')* (expression)? ')' | primary
primary                 -> Integer | Identifier | String | grouping
grouping                -> '(' expression ')'

Integer                 -> ['0'-'9']+
Type                    -> 'int' | 'str' | 'fnc' FunctionSignature
FunctionSignature       -> FunctionParams (Type)? block
FunctionParams          -> '(' ( ( TypeIdent ',')* TypeIdent )?  ')'
TypeIdent               -> Identifier Type
Identifier              -> [a-zA-Z_][a-zA-Z_0-9]*
String                  -> "*"
```